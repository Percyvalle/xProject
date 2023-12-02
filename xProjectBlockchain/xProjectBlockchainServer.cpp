#include "xProjectBlockchainServer.hpp"

BlockchainServer::BlockchainServer(const std::string& _address, const uint16_t _port)
	: ServerInterface(_address, _port)
{
}

BlockchainServer::~BlockchainServer()
{
}

void BlockchainServer::HandleMessage(std::shared_ptr<Net::Connection> _handleClient, Net::Message _handleMessage)
{
}

void BlockchainServer::HandleConnect(std::shared_ptr<Net::Connection> _handleClient)
{
}

void BlockchainServer::HandleDisconnect(std::shared_ptr<Net::Connection> _handleClient)
{
}
