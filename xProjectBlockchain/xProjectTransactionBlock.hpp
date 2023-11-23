#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectTransaction.hpp"

#include <merklecpp/merklecpp.h>

class TransactionBlock {
private:

	struct HeaderBlock {
		int m_nonceBlock = 0;
		int m_difficultyBlock = 0;
		uint32_t m_versionBlock = 0;
		std::string m_blockHash;
		std::string m_prevBlockHash;
		std::string m_timeMarkBlock;

		merkle::Tree m_transactionHashes;
	} m_headerTransactionBlock;

	SHA256 m_shaGenerate;
	std::vector<Transaction> m_transactisonList;
public:

	TransactionBlock(int _version, int _difficulty, std::string _hashBlock, std::string _prevblockHash, std::string m_timeMarkBlock, std::vector<Transaction> _data = {});

	const std::string getHash() const;
	const std::string getPrevHash() const;
	const uint32_t getVersion() const;
};