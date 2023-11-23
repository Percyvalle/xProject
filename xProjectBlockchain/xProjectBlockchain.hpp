#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectTransactionBlock.hpp"
#include "xProjectTransactionsPool.hpp"
#include "xProjectUtils.hpp"

class Blockchain {
public:
	enum StateBlockchain {
		GENESIS,
		JOIN
	};

private:
	std::vector<TransactionBlock> m_data;

	TransactionsPool m_tempTransactionsPool;

public:

	static inline std::string currentDataTime();

	void addInTransactionsPool(const Transaction& _transaction);

	void setTransactionsPool(const std::vector<Transaction>& _transactionsPool);

	bool addBlock(const uint32_t& _version, const uint32_t& _difficulty, const std::string& _prevblockHash, const std::string& _timeMarkBlock);

	bool initBlockchain(StateBlockchain _state);

	bool isValid();
};