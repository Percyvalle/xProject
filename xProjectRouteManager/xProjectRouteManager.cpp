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
	}
}
