#pragma once

#include "xProjectHeaders_common.hpp"
#include "xProjectMessage.hpp"
#include "xProjectQueue.hpp"
#include "xProjectConnection.hpp"

namespace Net {

	class ClientInterface {
	protected:
		boost::asio::io_context m_mainContext;

		std::thread m_threadContext;

		std::unique_ptr<Net::Connection> m_uniqueConnection;

	private:
		Xp::Queue<Net::OwnerMessage> m_messageIn;

	public:
		bool Connect(const std::string& _address, const uint16_t& _port) {
			try
			{
				boost::asio::ip::tcp::resolver resolver(m_mainContext);
				boost::asio::ip::tcp::resolver::results_type endpoint = resolver.resolve(_address, std::to_string(_port));

				m_uniqueConnection = std::make_unique<Net::Connection>(Net::Connection::Client, m_mainContext, boost::asio::ip::tcp::socket(m_mainContext), m_messageIn);

				m_uniqueConnection->ConnectToServer(endpoint);

				m_threadContext = std::thread([this]() { m_mainContext.run(); });
			}
			catch (const std::exception& _error)
			{
				spdlog::error("[Client] Connect Error: {0}", _error.what());
				return false;
			}

			return true;
		}

		bool Reconnect(const std::string& _address, const uint16_t& _port) {
			try
			{
				Disconnect();

				m_messageIn.clear();

				Connect(_address, _port);
			}
			catch (const std::exception& _error)
			{
				spdlog::error("[Client] Reconnect Error: {0}", _error.what());
				return false;
			}

			return true;
		}

		void Disconnect() {
			if (IsConnected()) {
				m_uniqueConnection->Disconnect();
			}

			m_mainContext.stop();

			if (m_threadContext.joinable()) {
				m_threadContext.join();
			}

			m_uniqueConnection.release();
		}

		bool IsConnected() {
			return m_uniqueConnection ? m_uniqueConnection->IsConnected() : false;
		}

		void Send(const Net::Message& _message) {
			if (IsConnected()) {
				m_uniqueConnection->Send(_message);
			}
		}

		Xp::Queue<Net::OwnerMessage>& Incoming() {
			return m_messageIn;
		}

	};

}