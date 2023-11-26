#pragma once

#include "xProjectServerInterface.hpp"

#include <sha256/SHA256.h>

class RouteManager : public Net::ServerInterface {
private:
	std::unordered_map<std::shared_ptr<Net::Connection>, std::string> m_available�lientsMap;
	
	// Temporary
	std::vector<std::shared_ptr<Net::Connection>> m_available�lientsVec;

public:
	explicit RouteManager(const std::string& _address, const uint16_t _port);
	virtual ~RouteManager();

	void HandleMessage(std::shared_ptr<Net::Connection> _handleClient, Net::Message _handleMessage) override;

	void HandleConnect(std::shared_ptr<Net::Connection> _handleClient) override;

	void HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient) override;
};