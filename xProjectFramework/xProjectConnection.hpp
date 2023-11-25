#pragma once

#include "xProjectHeaders_common.hpp"

#include "xProjectMessage.hpp"
#include "xProjectQueue.hpp"

namespace Net 
{
	static UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

	class Connection : public std::enable_shared_from_this<Connection> {
	public:
		enum OwnerConnection {
			Server,
			Client
		};

	private:
		boost::asio::io_context& m_conContext;
		boost::asio::ip::tcp::socket m_conSocket;

		Xp::Queue<Net::Message> m_messageOut;
		Xp::Queue<Net::OwnerMessage>& m_messageIn;

		Net::Message m_temporaryMessageIn;

		OwnerConnection m_owner;

		UUIDv4::UUID uuid = uuidGenerator.getUUID();
	public:
		Connection(OwnerConnection _owner, boost::asio::io_context& _context,
				   boost::asio::ip::tcp::socket _socket, Xp::Queue<Net::OwnerMessage>& _messageIn)
			: m_conContext(_context), m_conSocket(std::move(_socket)), m_owner(_owner), m_messageIn(_messageIn)
		{}

		virtual ~Connection(){}

		const UUIDv4::UUID& getUuid() const {
			return uuid;
		}

		void ConnectToClient()
		{
			if (m_owner == OwnerConnection::Server) {
				if (IsConnected()) {
					ReadHeader();
				}
			}
		}

		void ConnectToServer(const boost::asio::ip::tcp::resolver::results_type& _endpoint)
		{
			if (m_owner == OwnerConnection::Client) {
				boost::asio::async_connect(m_conSocket, _endpoint,
					[this](boost::system::error_code _error_code, boost::asio::ip::tcp::endpoint _endpoint) {
						if (!_error_code) {
							ReadHeader();
						}
					}
				);
			}
		}

		void Disconnect() {
			if (IsConnected()) {
				boost::asio::post(m_conContext,
					[this]() { m_conSocket.close(); }
				);
			}
		}

		bool IsConnected() {
			return m_conSocket.is_open();
		}

		void Send(const Net::Message& _message) {
			boost::asio::post(m_conContext,
				[this, _message]() 
				{
					bool messageIsEmpty = m_messageOut.empty();
					m_messageOut.push_back(_message);
					if (messageIsEmpty) {
						WriteHeader();
					}
				}
			);
		}

	private:

		void ReadHeader(){
			boost::asio::async_read(m_conSocket, boost::asio::buffer(&m_temporaryMessageIn.m_header, sizeof(Net::MessageHeader)),
				[this](boost::system::error_code _error_code, std::size_t _length)
				{
					if (!_error_code) {
						
						spdlog::debug("Read Header Done | Type: {0}", std::to_string(m_temporaryMessageIn.m_header.m_type));

						if (m_temporaryMessageIn.m_header.m_size > 0) {
							m_temporaryMessageIn.m_body.m_data.resize(m_temporaryMessageIn.m_header.m_size);
							ReadBody();
						}
						else {
							AddMessageToQueue();
						}
					}
					else {
						spdlog::warn("Read Header Error: {0}", _error_code.message());
						spdlog::warn("Socket Error: {0}:{1}", m_conSocket.remote_endpoint().address().to_string(), m_conSocket.remote_endpoint().port());
						Disconnect();
					}
				}
			);
		}
		void ReadBody(){
			
			boost::asio::async_read(m_conSocket, boost::asio::buffer(m_temporaryMessageIn.m_body.m_data.data(), m_temporaryMessageIn.Size()),
				[this](boost::system::error_code _error_code, std::size_t length)
				{
					if (!_error_code) {
#ifdef _DEBUG
						spdlog::debug("Read Body Done | Message: {0}", m_temporaryMessageIn.getStr());
#endif // _DEBUG

						AddMessageToQueue();
					}
					else {
						spdlog::warn("Read Header Error: {0}", _error_code.message());
						spdlog::warn("Socket Error: {0}:{1}", m_conSocket.remote_endpoint().address().to_string(), m_conSocket.remote_endpoint().port());
						Disconnect();
					}					
				}
			);
		}

		void WriteHeader(){
			boost::asio::async_write(m_conSocket, boost::asio::buffer(&m_messageOut.front().m_header, sizeof(Net::MessageHeader)),
				[this](boost::system::error_code _error_code, std::size_t _length)
				{
					if (!_error_code) {
						if (m_messageOut.front().Size() > 0) {
							WriteBody();
						}
						else {
							m_messageOut.pop_front();

							if (!m_messageOut.empty()) {
								WriteHeader();
							}
						}
					}
					else {
						spdlog::warn("Write Header Error: {0}", _error_code.message());
						spdlog::info("Socket Error: {0}:{1}", m_conSocket.remote_endpoint().address().to_string(), m_conSocket.remote_endpoint().port());
						Disconnect();
					}
				}
			);
		}
		void WriteBody(){
			boost::asio::async_write(m_conSocket, boost::asio::buffer(m_messageOut.front().m_body.m_data.data(), m_messageOut.front().Size()),
				[this](boost::system::error_code _error_code, std::size_t length)
				{
					if (!_error_code) {
						m_messageOut.pop_front();

						if (!m_messageOut.empty()) {
							WriteHeader();
						}
					}
					else {
						spdlog::warn("Write Body Error: {0}", _error_code.message());
						spdlog::info("Socket Error: {0}:{1}", m_conSocket.remote_endpoint().address().to_string(), m_conSocket.remote_endpoint().port());
						Disconnect();
					}
				}
			);
		}

		void AddMessageToQueue() {
			if (m_owner == OwnerConnection::Server) {
				m_messageIn.push_back({this->shared_from_this(), m_temporaryMessageIn});
			}
			else {
				m_messageIn.push_back({ nullptr, m_temporaryMessageIn });
			}

			ReadHeader();
		}
	};
}