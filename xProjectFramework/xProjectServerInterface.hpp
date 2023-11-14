#pragma once

#include "xProjectHeaders_common.hpp"
#include "xProjectQueue.hpp"
#include "xProjectMessage.hpp"
#include "xProjectConnection.hpp"

namespace Net {

	class ServerInterface {
	protected:
		Xp::Queue<Net::OwnerMessage> m_messageIn;
		
		boost::asio::io_context m_mainContext;
		boost::asio::ip::tcp::acceptor m_acceptor;

		std::deque<std::shared_ptr<Net::Connection>> m_connections;

		std::thread m_threadContext;

	public:
		
		ServerInterface(const std::string& _address, const uint16_t& _port)
			: m_acceptor(m_mainContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::address_v4::from_string(_address), _port))
		{}

		~ServerInterface() { Stop(); }

		bool Start() {
			try
			{

				WaitForClientConnection();

				m_threadContext = std::thread([this]() {m_mainContext.run(); });
			}
			catch (const std::exception& _error)
			{
				spdlog::error("[Server] Start Error: {0}", _error.what());
				return false;
			}

			spdlog::info("[Server] Start {0}:{1}", m_acceptor.local_endpoint().address().to_string(), m_acceptor.local_endpoint().port());
			return true;
		}

		void Stop() {
			m_mainContext.stop();

			if (m_threadContext.joinable()) { m_threadContext.join(); }
		}

		void WaitForClientConnection() {
			m_acceptor.async_accept(
				[this](boost::system::error_code _error_code, boost::asio::ip::tcp::socket _socket)
				{
					if (!_error_code)
					{
						spdlog::info("[Server] New Connection: {0}:{1}", _socket.remote_endpoint().address().to_string(), _socket.remote_endpoint().port());
						
						std::shared_ptr<Net::Connection> clientConnection = std::make_shared<Net::Connection>(
							Net::Connection::OwnerConnection::Server, m_mainContext, std::move(_socket), m_messageIn);

						m_connections.push_back(clientConnection);

						clientConnection->ConnectToClient();
					}
					else {
						spdlog::warn("[Server] New Connection Error: {0}", _error_code.message());
					}

					WaitForClientConnection();
				}
			);
		}
	};

}