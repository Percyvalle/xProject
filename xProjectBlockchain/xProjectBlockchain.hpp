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

	static std::string miningHash();

	bool initBlockchain(StateBlockchain _state);

	bool createBlock();

	bool isValid() const;
};