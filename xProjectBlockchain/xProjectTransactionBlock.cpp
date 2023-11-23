#include "xProjectTransactionBlock.hpp"

TransactionBlock::TransactionBlock(int _version, int _difficulty, std::string _hashBlock, std::string _prevblockHash, std::string m_timeMarkBlock, std::vector<Transaction> _data)
{
	m_headerTransactionBlock.m_versionBlock = _version;
	m_headerTransactionBlock.m_difficultyBlock = _difficulty;
	m_headerTransactionBlock.m_prevBlockHash = _prevblockHash;
	m_headerTransactionBlock.m_timeMarkBlock = m_timeMarkBlock;
	
	m_transactisonList = _data;
	
	// Move to miningHash
	//SHA256 tempSha;
	//for (Transaction& i : m_transactisonList) {
	//	tempSha.update(i.m_transactionHash);
	//	m_headerTransactionBlock.m_transactionHashes.insert(SHA256::toString(tempSha.digest()));
	//}

	//m_shaGenerate.update(std::to_string(_version) + std::to_string(_difficulty) + _prevblockHash + m_timeMarkBlock + m_headerTransactionBlock.m_transactionHashes.root().to_string());
	//m_headerTransactionBlock.m_blockHash = SHA256::toString(m_shaGenerate.digest());
}

const std::string TransactionBlock::getHash() const
{
	return m_headerTransactionBlock.m_blockHash;
}

const std::string TransactionBlock::getPrevHash() const
{
	return m_headerTransactionBlock.m_prevBlockHash;
}

const uint32_t TransactionBlock::getVersion() const
{
	return m_headerTransactionBlock.m_versionBlock;
}
