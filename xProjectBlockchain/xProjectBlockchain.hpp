#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectTransactionBlock.hpp"
#include "xProjectTransactionsPool.hpp"

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

	static std::string miningHash();

	bool addBlock(const int& _difficulty,const std::string& _prevblockHash,const std::string& m_timeMarkBlock);

	void addInTransactionsPool(const Transaction& _transaction);

	bool initBlockchain(StateBlockchain _state);

	bool isValid() const;
};