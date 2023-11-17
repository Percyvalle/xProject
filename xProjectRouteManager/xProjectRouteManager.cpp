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
	switch (_handleMessage.m_header.m_type)
	{
	case Net::MessageType::Ping:
		spdlog::info("[Server] Handle Ping Message");

		_handleClient->Send(_handleMessage);
		break;
	case Net::MessageType::Registration:
		spdlog::info("[Server] Handle Registration Message");
		
		Net::Message responseMessage;

		responseMessage.m_header.m_type = Net::MessageType::Registration;

		SHA256 shaMessage;
		shaMessage.update(_handleClient->getUuid().str());
		responseMessage << SHA256::toString(shaMessage.digest()).c_str();

#ifdef _DEBUG
		spdlog::debug("UUID: {0}", _handleClient->getUuid().str());
		spdlog::debug("SHA256: {0}", SHA256::toString(shaMessage.digest()));
#endif // DEBUG

		_handleClient->Send(responseMessage);

		break;
	}
}

void RouteManager::HandleConnect(std::shared_ptr<Net::Connection> _handleClient)
{
}

void RouteManager::HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient)
{
}
