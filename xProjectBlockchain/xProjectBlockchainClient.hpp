#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectClientInterface.hpp"
#include "xProjectHeaders_common.hpp"
#include "xProjectMessage.hpp"

static UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;

static SHA256 shaGenerator;

class BlockchainClient : public Net::ClientInterface 
{
private:
	UUIDv4::UUID m_uuid = uuidGenerator.getUUID();
	
	std::string shaPublicKey;

public:
	
	explicit BlockchainClient();

	void PingServer();

	void RegistrationServer();

	void GetPeerAddress();

private:
	void GeneratePublicKey();

	void GeneratePrivateKey();

};