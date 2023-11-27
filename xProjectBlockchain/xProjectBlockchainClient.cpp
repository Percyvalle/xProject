#include "xProjectBlockchainClient.hpp"

BlockchainClient::BlockchainClient()
{
	GeneratePublicKey();
	GeneratePrivateKey();
}

void BlockchainClient::PingServer()
{
	Net::Message messageServer;
	messageServer.m_header.m_type = Net::MessageType::PingRequest;

	Send(messageServer);
}

void BlockchainClient::RegistrationServer()
{
	Net::Message messageServer;
	messageServer.m_header.m_type = Net::MessageType::RegistrationRequest;

	Send(messageServer);
}

void BlockchainClient::GetPeerAddress()
{
	Net::Message messageServer;
	messageServer.m_header.m_type = Net::MessageType::GetPeerRequest;
	messageServer << m_uuid.str();

	Send(messageServer);
}

void BlockchainClient::GeneratePublicKey()
{
	shaGenerator.update(m_uuid.str());
	shaPublicKey = SHA256::toString(shaGenerator.digest());

	spdlog::info("Public Key: {0}", shaPublicKey);
}

void BlockchainClient::GeneratePrivateKey()
{
	shaGenerator.update(shaPublicKey);
	spdlog::info("Private Key: {0}", SHA256::toString(shaGenerator.digest()));
}
