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

						HandleConnect(clientConnection);

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

		void Update(bool _wait = false){
			
			if (_wait) {
				m_messageIn.wait();
			}

			while (!m_messageIn.empty()) {

				OwnerMessage onwerMessage = m_messageIn.pop_back();

				HandleMessage(onwerMessage.m_remoteConnection, onwerMessage.m_remoteMsg);
			}
		}

		void CheckConnectClients() {
			if (m_connections.empty()) {
				return;
			}

			bool invalidClientSocket = false;
			for (std::shared_ptr<Net::Connection> client : m_connections) {
				if (client != nullptr && client->IsConnected()) {
					Net::Message pingMessage;
					pingMessage.m_header.m_type = Net::MessageType::Ping;

					client->Send(pingMessage);
				}
				else {
					client.reset();
					invalidClientSocket = true;
				}

				if (invalidClientSocket) {
					m_connections.erase(std::remove(m_connections.begin(), m_connections.end(), nullptr), m_connections.end());
				}
			}
		}

		virtual void HandleMessage(std::shared_ptr<Net::Connection> _handleClient, Net::Message _handleMessage) {}

		virtual void HandleConnect(std::shared_ptr<Net::Connection> _handleClient) {}

		virtual void HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient) {}
	};

}