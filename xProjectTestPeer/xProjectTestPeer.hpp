#pragma once

#include "xProjectClientInterface.hpp"
#include "xProjectServerInterface.hpp"

using json = nlohmann::json;

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
	void RegistrationPeerMessage() {	
		json regMessageJson;
		regMessageJson["addr"] = m_uniqueConnection->getLocalAddress();
		regMessageJson["port"] = m_uniqueConnection->getLocalAddress();
		
		Net::Message regMessage;
		regMessage.m_header.m_type = Net::MessageType::RegistrationRequest;
		regMessage << regMessageJson.dump();

		Send(regMessage);
	}

	void GetPeerMessage() {
		Net::Message getPeerMessage;
		getPeerMessage.m_header.m_type = Net::MessageType::GetPeerRequest;

		Send(getPeerMessage);
	}

	void PingServer() {
		Net::Message pingMessage;
		pingMessage.m_header.m_type = Net::MessageType::PingRequest;

		Send(pingMessage);
	}

	void Update() {
		while (true)
		{
			if (IsConnected()) {
				if (!Incoming().empty()) {

					Net::Message message = Incoming().pop_back().m_remoteMsg;

					spdlog::info("{0}", message.getStr());
					switch (message.Type())
					{
					case Net::MessageType::PingResponse:
						break;
					case Net::MessageType::RegistrationResponse:
						break;
					case Net::MessageType::GetPeerResponse:
						break;
					}

				}
			}
		}
	}
};

class TestPeer {
private:
	std::shared_ptr<TestServerPeer> m_srvPeer = nullptr;
	std::shared_ptr<TestClientPeer> m_clnPeer = nullptr;

public:
	TestPeer(std::shared_ptr<TestServerPeer> _srvPeer, std::shared_ptr<TestClientPeer> _clnPeer) : m_srvPeer(_srvPeer), m_clnPeer(_clnPeer) {}
};