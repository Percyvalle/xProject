#pragma once

#include "xProjectBlockchainHeaders_common.hpp"
#include "xProjectTransactionBlock.hpp"

namespace Utils {
	
	inline void setCursorPosition(int x, int y)
	{
		static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		std::cout.flush();
		COORD coord = { (SHORT)x, (SHORT)y };
		SetConsoleCursorPosition(hOut, coord);
	}

	inline void miningHash(TransactionBlock& _block)
	{
		SHA256 shaGenerate;
		std::string hash = std::to_string(_block.getDifficulty()) + std::to_string(_block.getVersion()) + _block.getPrevHash() + _block.getMerkleRoot();

		for (int i = 0; i < INT_MAX; i++) {

			setCursorPosition(0, 0);

			shaGenerate.update(hash + std::to_string(i));
			hash = SHA256::toString(shaGenerate.digest());
			spdlog::info("Mining... {0}", hash);

			if (hash.substr(0, _block.getDifficulty()) == std::string(_block.getDifficulty(), '0')) {
				_block.setHash(hash);
				_block.setNonce(i);
				break;
			}
		}
	}
}