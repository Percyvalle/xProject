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
		{
			spdlog::info("[Server] Handle Ping Request");

			responseMessage.m_header.m_type = Net::MessageType::PingResponse;
			responseMessage << "Ping OK!";

			break;
		}
	case Net::MessageType::RegistrationRequest:
		{
			spdlog::info("[Server] Handle Registration Request");

			responseMessage.m_header.m_type = Net::MessageType::RegistrationResponse;

			Net::PeerInfo registrationPeer;
			registrationPeer.m_addressPeer = _handleClient->getRemoteAddress();
			registrationPeer.m_portPeer = _handleClient->getRemotePort();

			m_available�lientsVec.push_back(_handleClient);
			m_available�lientsMap.insert({ _handleClient, registrationPeer });

			break;
		}
	case Net::MessageType::GetPeerRequest:
		{
			spdlog::info("[Server] Handle GetPeer Request");

			responseMessage.m_header.m_type = Net::MessageType::GetPeerResponse;

			if (m_available�lientsVec.size() > 1) {
				// Temporary (Convert to JSON)
				for (std::shared_ptr<Net::Connection> i : m_available�lientsVec) {
					if (i->getRemotePort() != _handleClient->getRemotePort()) {
						responseMessage << i->getRemoteAddress();
						//responseMessage << std::to_string(i->getPort());
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
	}

	_handleClient->Send(responseMessage);
}

void RouteManager::HandleConnect(std::shared_ptr<Net::Connection> _handleClient)
{
	spdlog::info("[Server] New Connection: {0}:{1}", _handleClient->getRemoteAddress(), _handleClient->getRemotePort());
}

void RouteManager::HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient)
{
	spdlog::debug("[Server] Disconnect");

	m_available�lientsVec.erase(std::remove(m_available�lientsVec.begin(), m_available�lientsVec.end(), _handleClient), m_available�lientsVec.end());
	m_available�lientsMap.erase(_handleClient);
}
