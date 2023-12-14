
#include "xProjectClientInterface.hpp"
#include "xProjectServerInterface.hpp"

class TestClient : public Net::ClientInterface {
private:
public:
	void TestPingServerMessage() {
		Net::Message messageServer;
		messageServer.m_header.m_type = Net::MessageType::PingRequest;

		Send(messageServer);
	}

	void TestRegistrationServerMessage() {
		Net::Message messageServer;
		messageServer.m_header.m_type = Net::MessageType::RegistrationRequest;

		Send(messageServer);
	}
};

class TestServer : public Net::ServerInterface {
private:
public:
	TestServer(std::string _address, uint16_t _port) : Net::ServerInterface(_address, _port) {}
	virtual ~TestServer() {}

	void HandleMessage(std::shared_ptr<Net::Connection> _handleClient, Net::Message _handleMessage) {

	}

	void HandleConnect(std::shared_ptr<Net::Connection> _handleClient) {
		spdlog::info("Connect: {0}:{1}", _handleClient->getAddress(), _handleClient->getPort());
	}

	void HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient) {

	}
};

int main(int argv, char** argc) {

#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif // _DEBUG

	TestClient client;
	client.Connect("127.0.0.1", 20055);
	client.TestPingServerMessage();
	client.TestRegistrationServerMessage();

	TestServer server("127.0.0.1", 20056);
	server.Start();

	while (true) {
		server.Update(true);
	}

	return EXIT_SUCCESS;
}