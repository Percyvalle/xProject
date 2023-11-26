
#include "xProjectMiner.hpp"

#include "xProjectBlockchainClient.hpp"

int main(int argv, char** argc) {

#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif // _DEBUG

	Blockchain blockchain;
	blockchain.initBlockchain(Blockchain::StateBlockchain::GENESIS);

	Miner miner(blockchain);
	
	BlockchainClient client;
	client.Connect("127.0.0.1", 20055);
	client.PingServer();
	client.RegistrationServer();

	while (true)
	{
		if (client.IsConnected()) {
			if (!client.Incoming().empty()) {

				Net::Message message = client.Incoming().pop_back().m_remoteMsg;

				switch (message.Type())
				{
				case Net::MessageType::PingResponse:
					spdlog::info("{0}", message.getStr());
					break;
				case Net::MessageType::RegistrationResponse:
					spdlog::info("{0}", message.getStr());
					client.SetUUID(message.getStr());
					break;
				}

			}
		}
	}

	return EXIT_SUCCESS;
}