
#include "xProjectClientInterface.hpp"

class TestClient : public Net::ClientInterface {
private:
public:
	void TestPingServerMessage() {
		Net::Message messageServer;
		messageServer.m_header.m_type = Net::MessageType::Ping;

		Send(messageServer);
	}

	void TestRegistrationServerMessage() {
		Net::Message messageServer;
		messageServer.m_header.m_type = Net::MessageType::Registration;

		Send(messageServer);
	}
};

int main(int argv, char** argc) {

#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif // _DEBUG

	TestClient client;
	client.Connect("127.0.0.1", 20055);
	client.TestRegistrationServerMessage();
	client.TestPingServerMessage();
	client.TestPingServerMessage();

	while (true) {

	}

	return EXIT_SUCCESS;
}