#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectTransactionBlock.hpp"

class Blockchain {
public:
	enum StateBlockchain {
		GENESIS,
		JOIN
	};

private:
	std::vector<TransactionBlock> m_data;

public:

	void initBlockchain(StateBlockchain _state);

	void createBlock();

	bool isValid();
};