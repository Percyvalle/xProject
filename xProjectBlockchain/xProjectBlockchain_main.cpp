#include "xProjectMiner.hpp"

#include "xProjectBlockchainClient.hpp"
#include "xProjectBlockchainServer.hpp"

void ClientUpdate(std::shared_ptr<BlockchainClient> _client) {
	while (true)
	{
		if (_client->IsConnected()) {
			if (!_client->Incoming().empty()) {

				Net::Message message = _client->Incoming().pop_back().m_remoteMsg;

				spdlog::info("{0}", message.getStr());
				switch (message.Type())
				{
				case Net::MessageType::PingResponse:
					break;
				case Net::MessageType::RegistrationResponse:
					break;
				case Net::MessageType::GetPeerResponse:
					_client->Reconnect(message.getStr(), 20056);
					
					_client->PingServer();
					break;
				}

			}
		}
	}
}

int main(int argv, char** argc) {

#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif // _DEBUG

	try
	{
		Blockchain blockchain;
		blockchain.initBlockchain(Blockchain::StateBlockchain::GENESIS);

		Miner miner(blockchain);

		std::shared_ptr<BlockchainServer> server = std::make_shared<BlockchainServer>("127.0.0.1", 20057);
		server->Start();

		std::shared_ptr<BlockchainClient> client = std::make_shared<BlockchainClient>();
		client->Connect("127.0.0.1", 20055);
		client->PingServer();
		client->RegistrationServer();
		client->GetPeerAddress();

		std::thread updateClientThread(ClientUpdate, client);

		while (true)
		{
			server->Update();
		}
	}
	catch (const std::exception& _error)
	{
		spdlog::error("{0}", _error.what());
	}

	return EXIT_SUCCESS;
}