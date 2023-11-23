#include "xProjectTransactionBlock.hpp"

TransactionBlock::TransactionBlock(uint32_t _version, uint32_t _difficulty, std::string _prevblockHash, std::string m_timeMarkBlock, std::vector<Transaction> _data)
{
	m_headerTransactionBlock.m_versionBlock = _version;
	m_headerTransactionBlock.m_difficultyBlock = _difficulty;
	m_headerTransactionBlock.m_prevBlockHash = _prevblockHash;
	m_headerTransactionBlock.m_timeMarkBlock = m_timeMarkBlock;
	
	m_transactisonList = _data;

	SHA256 tempSha;
	for (Transaction& i : m_transactisonList) {
		tempSha.update(i.m_transactionHash);
		m_headerTransactionBlock.m_transactionHashes.insert(SHA256::toString(tempSha.digest()));
	}
}

void TransactionBlock::setHash(const std::string& _hash)
{
	m_headerTransactionBlock.m_blockHash = _hash;
}

void TransactionBlock::setNonce(const uint32_t& _nonce)
{
	m_headerTransactionBlock.m_nonceBlock = _nonce;
}

std::string TransactionBlock::getMerkleRoot()
{
	return m_headerTransactionBlock.m_transactionHashes.root().to_string();
}

std::string TransactionBlock::getHash()
{
	return m_headerTransactionBlock.m_blockHash;
}

std::string TransactionBlock::getPrevHash()
{
	return m_headerTransactionBlock.m_prevBlockHash;
}

std::string TransactionBlock::getTimeMark()
{
	return m_headerTransactionBlock.m_timeMarkBlock;
}

uint32_t TransactionBlock::getVersion()
{
	return m_headerTransactionBlock.m_versionBlock;
}

uint32_t TransactionBlock::getDifficulty()
{
	return m_headerTransactionBlock.m_difficultyBlock;
}

std::vector<Transaction> TransactionBlock::getTransactionList()
{
	return m_transactisonList;
}

void TransactionBlock::printBlock()
{
	fort::table blocktable;
	blocktable << fort::header << "Version Block: " << m_headerTransactionBlock.m_versionBlock << fort::endr
		<< "Time" << m_headerTransactionBlock.m_timeMarkBlock << fort::endr
		<< "Hash: " << m_headerTransactionBlock.m_blockHash << fort::endr
		<< "Previous Hash: " << m_headerTransactionBlock.m_prevBlockHash << fort::endr
		<< "Difficulty: " << m_headerTransactionBlock.m_difficultyBlock << fort::endr
		<< "Nonce: " << m_headerTransactionBlock.m_nonceBlock << fort::endr
		<< "Transactions Hash: " << getMerkleRoot() << fort::endr;
	std::cout << blocktable.to_string() << std::endl;
}
