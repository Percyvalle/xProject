#pragma once

#include "xProjectServerInterface.hpp"
#include "xProjectHeaders_common.hpp"
#include "xProjectMessage.hpp"

class BlockchainServer : public Net::ServerInterface
{
private:
public:
	explicit BlockchainServer(const std::string& _address, const uint16_t _port);
	virtual ~BlockchainServer();
};

