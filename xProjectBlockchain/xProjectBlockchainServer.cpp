#include "xProjectBlockchainServer.hpp"

BlockchainServer::BlockchainServer(const std::string& _address, const uint16_t _port)
	: ServerInterface(_address, _port)
{
}

BlockchainServer::~BlockchainServer()
{
}
