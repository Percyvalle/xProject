
#include "xProjectClientInterface.hpp"

class TestClient : public Net::ClientInterface {
private:
public:
	void PingServerMessage() {
		Net::Message messageServer;
		messageServer.m_header.m_type = Net::MessageType::Ping;

		Send(messageServer);
	}
};

int main(int argv, char** argc) {

	TestClient client;
	client.Connect("127.0.0.1", 20055);
	client.PingServerMessage();

	while (client.Incoming().empty()) {

	}

	return EXIT_SUCCESS;
}