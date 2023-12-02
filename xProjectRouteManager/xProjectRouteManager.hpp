#pragma once

#include "xProjectServerInterface.hpp"
#include "xProjectPeerInfo.hpp"

class RouteManager : public Net::ServerInterface {
private:
	std::unordered_map<std::shared_ptr<Net::Connection>, Net::PeerInfo> m_availableÑlientsMap;
	std::vector<std::shared_ptr<Net::Connection>> m_availableÑlientsVec;

public:
	explicit RouteManager(const std::string& _address, const uint16_t _port);
	virtual ~RouteManager();

	void HandleMessage(std::shared_ptr<Net::Connection> _handleClient, Net::Message _handleMessage) override;

	void HandleConnect(std::shared_ptr<Net::Connection> _handleClient) override;

	void HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient) override;
};