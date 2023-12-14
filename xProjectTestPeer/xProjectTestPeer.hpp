#pragma once

#include "xProjectClientInterface.hpp"
#include "xProjectServerInterface.hpp"

class TestServerPeer : public Net::ServerInterface {
private:
public:
	TestServerPeer(const std::string& _address, const uint16_t& _port) : Net::ServerInterface(_address, _port) {}
	virtual ~TestServerPeer() {}

	void HandleMessage(std::shared_ptr<Net::Connection> _handleClient, Net::Message _handleMessage) {}

	void HandleConnect(std::shared_ptr<Net::Connection> _handleClient) {}

	void HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient) {}
};

class TestClientPeer : public Net::ClientInterface {
private:
public:
	void RegistrationPeerMessage() {}

	void GetPeerMessage() {}
};

class TestPeer {
private:
	std::shared_ptr<TestServerPeer> m_srvPeer = nullptr;
	std::shared_ptr<TestClientPeer> m_clnPeer = nullptr;

public:
	TestPeer(std::shared_ptr<TestServerPeer> _srvPeer, std::shared_ptr<TestClientPeer> _clnPeer) : m_srvPeer(_srvPeer), m_clnPeer(_clnPeer) {}
};