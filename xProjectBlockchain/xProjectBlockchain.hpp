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
	std::list<TransactionBlock> m_data;

public:

	void initBlockchain(StateBlockchain _state);

	void createBlock();

	void isValid();
};