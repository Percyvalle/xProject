#pragma once

#include "xProjectBlockchain.hpp"

class Miner {
private:

	Blockchain m_blockchain;
public:
	Miner(Blockchain& _blockchain);
};