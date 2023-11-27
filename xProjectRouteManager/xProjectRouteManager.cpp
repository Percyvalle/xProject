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
		spdlog::info("[Server] Handle Ping Request");

		responseMessage.m_header.m_type = Net::MessageType::PingResponse;
		responseMessage << "Ping OK!";

		break;
	case Net::MessageType::RegistrationRequest:
		spdlog::info("[Server] Handle Registration Request");
		
		responseMessage.m_header.m_type = Net::MessageType::RegistrationResponse;

		// Temporary
		m_availableÑlientsVec.push_back(_handleClient);

		break;
	case Net::MessageType::GetPeerRequest:
		spdlog::info("[Server] Handle GetPeer Request");

		responseMessage.m_header.m_type = Net::MessageType::GetPeerResponse;

		if (m_availableÑlientsVec.size() > 1) {
			// Temporary (Convert to JSON)
			for (std::shared_ptr<Net::Connection> i : m_availableÑlientsVec) {
				if (i->getPort() != _handleClient->getPort()) {
					responseMessage << i->getAddress() << ":" << std::to_string(i->getPort());
				}
			}
		}
		else {
			responseMessage << "None";
		}

#ifdef _DEBUG
		spdlog::debug("BODY: {0}", responseMessage.getStr());
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
	m_availableÑlientsMap.erase(_handleClient);
}
