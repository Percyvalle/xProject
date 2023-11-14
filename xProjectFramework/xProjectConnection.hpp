#pragma once

#include "xProjectHeaders_common.hpp"

#include "xProjectMessage.hpp"
#include "xProjectQueue.hpp"

namespace Net 
{
	class Connection : std::enable_shared_from_this<Connection> {
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
	public:
		Connection(OwnerConnection _owner, boost::asio::io_context& _context,
				   boost::asio::ip::tcp::socket _socket, Xp::Queue<Net::OwnerMessage>& _messageIn)
			: m_conContext(_context), m_conSocket(std::move(_socket)), m_owner(_owner), m_messageIn(_messageIn)
		{}

		virtual ~Connection(){}

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
						
						spdlog::info("Read Header Done | Type: {0}", std::to_string(m_temporaryMessageIn.m_header.m_type));

						if (m_temporaryMessageIn.m_header.m_size > 0) {
							m_temporaryMessageIn.m_body.m_data.resize(m_temporaryMessageIn.m_header.m_size);
							//ReadBody();
						}
						else {
							AddMessageToQueue();
						}
					}
					else {
						spdlog::warn("Read Header Error: {0}", _error_code.message());
						spdlog::info("Socket Error: {0}:{1}", m_conSocket.remote_endpoint().address().to_string(), m_conSocket.remote_endpoint().port());
						Disconnect();
					}
				}
			);
		}
		void ReadBody(){}

		void WriteHeader(){
			boost::asio::async_write(m_conSocket, boost::asio::buffer(&m_messageOut.back().m_header, sizeof(Net::MessageHeader)), 
				[this](boost::system::error_code _error_code, std::size_t _length)
				{
					if (!_error_code) {
						if (m_messageOut.back().Size() > 0) {
							//WriteBody();
						}
						else {
							m_messageOut.pop_back();

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
		void WriteBody(){}

		void AddMessageToQueue() {
			if (OwnerConnection::Server) {
				m_messageIn.push_back({this->shared_from_this(), m_temporaryMessageIn});
			}
			else {
				m_messageIn.push_back({ nullptr, m_temporaryMessageIn });
			}

			ReadHeader();
		}
	};
}