#include "xProjectBlockchainClient.hpp"

void BlockchainClient::pingServer()
{
	Net::Message messageServer;
	messageServer.m_header.m_type = Net::MessageType::PingRequest;

	Send(messageServer);
}