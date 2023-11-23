
#include "xProjectMiner.hpp"

int main(int argv, char** argc) {

	Blockchain blockchain;
	blockchain.initBlockchain(Blockchain::StateBlockchain::GENESIS);

	Miner miner(blockchain);


	return EXIT_SUCCESS;
}