#pragma once

#include "xProjectClientInterface.hpp"
#include "xProjectHeaders_common.hpp"
#include "xProjectMessage.hpp"

class BlockchainClient : public Net::ClientInterface 
{
private:
	UUIDv4::UUID m_uuid;	

public:

	void pingServer();
};