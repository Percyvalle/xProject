#include "xProjectBlockchainClient.hpp"

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

void BlockchainClient::SetUUID(std::string _uuid)
{
	m_uuid.fromStr(_uuid.c_str());
}
