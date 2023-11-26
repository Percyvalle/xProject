#include "xProjectRouteManager.hpp"

RouteManager::RouteManager(const std::string& _address, const uint16_t _port)
	: Net::ServerInterface(_address, _port)
{
}

RouteManager::~RouteManager()
{
}

void RouteManager::HandleMessage(std::shared_ptr<Net::Connection> _handleClient, Net::Message _handleMessage)
{
	Net::Message responseMessage;
	switch (_handleMessage.m_header.m_type)
	{
	case Net::MessageType::PingRequest:
		spdlog::info("[Server] Handle Ping Message");

		responseMessage.m_header.m_type = Net::MessageType::PingResponse;
		responseMessage << "Ping OK!";

		break;
	case Net::MessageType::RegistrationRequest:
		spdlog::info("[Server] Handle Registration Message");
		
		responseMessage.m_header.m_type = Net::MessageType::RegistrationResponse;

		SHA256 shaMessage;
		shaMessage.update(_handleClient->getUuid().str());

		m_availableÑlients[_handleClient] = SHA256::toString(shaMessage.digest());
		responseMessage << _handleClient->getUuid().str();

#ifdef _DEBUG
		spdlog::debug("UUID: {0}", _handleClient->getUuid().str());
		spdlog::debug("SHA256: {0}", m_availableÑlients[_handleClient]);
#endif // DEBUG

		break;
	}

	_handleClient->Send(responseMessage);
}

void RouteManager::HandleConnect(std::shared_ptr<Net::Connection> _handleClient)
{
}

void RouteManager::HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient)
{
}
