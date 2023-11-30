
#include "xProjectMiner.hpp"

#include "xProjectBlockchainClient.hpp"

int main(int argv, char** argc) {

#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif // _DEBUG

	try
	{
		Blockchain blockchain;
		blockchain.initBlockchain(Blockchain::StateBlockchain::GENESIS);

		Miner miner(blockchain);

		BlockchainClient client;
		client.Connect("127.0.0.1", 20055);
		client.PingServer();
		client.RegistrationServer();
		client.GetPeerAddress();

		while (true)
		{
			if (client.IsConnected()) {
				if (!client.Incoming().empty()) {

					Net::Message message = client.Incoming().pop_back().m_remoteMsg;

					spdlog::info("{0}", message.getStr());
					switch (message.Type())
					{
					case Net::MessageType::PingResponse:
						break;
					case Net::MessageType::RegistrationResponse:
						break;
					case Net::MessageType::GetPeerResponse:
						client.Disconnect();
						client.Connect("127.0.0.1", std::strtol(message.getStr().c_str(), nullptr, NULL));
						break;
					}

				}
			}
		}
	}
	catch (const std::exception& _error)
	{
		spdlog::error("{0}", _error.what());
	}

	return EXIT_SUCCESS;
}