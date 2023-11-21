
#include "xProjectBlockchain.hpp"

int main(int argv, char** argc) {

	Blockchain blockchain;
	blockchain.initBlockchain(Blockchain::StateBlockchain::GENESIS);

	return EXIT_SUCCESS;
}