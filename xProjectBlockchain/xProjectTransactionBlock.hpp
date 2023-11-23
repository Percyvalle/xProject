#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectTransaction.hpp"

#include <merklecpp/merklecpp.h>
#include <fort/fort.hpp>

class TransactionBlock {
private:

	struct HeaderBlock {
		uint32_t m_nonceBlock = 0;
		uint32_t m_difficultyBlock = 0;
		uint32_t m_versionBlock = 0;
		std::string m_blockHash;
		std::string m_prevBlockHash;
		std::string m_timeMarkBlock;

		merkle::Tree m_transactionHashes;
	} m_headerTransactionBlock;

	std::vector<Transaction> m_transactisonList;
public:

	TransactionBlock(uint32_t _version, uint32_t _difficulty, std::string _prevblockHash, std::string m_timeMarkBlock, std::vector<Transaction> _data);

	void setHash(const std::string& _hash);
	void setNonce(const uint32_t& _nonce);

	std::string getMerkleRoot();
	std::string getHash();
	std::string getPrevHash();
	std::string getTimeMark();
	uint32_t getVersion();
	uint32_t getDifficulty();
	std::vector<Transaction> getTransactionList();

	void printBlock();
};