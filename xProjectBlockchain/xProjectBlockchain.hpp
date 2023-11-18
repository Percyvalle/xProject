#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectTransactionBlock.hpp"

class Blockchain {
public:
	enum StateBlockchain {
		UNDEFINE,
		GENESIS,
		JOIN
	};

private:
	std::list<TransactionBlock> m_data;

public:

	void initBlockchain(StateBlockchain _state = StateBlockchain::UNDEFINE);

};