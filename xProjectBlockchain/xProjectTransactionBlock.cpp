#include "xProjectTransactionBlock.hpp"

TransactionBlock::TransactionBlock(int _version, int _difficulty, std::string _prevblockHash, std::string m_timeMarkBlock, std::vector<Transaction> _data)
{
	m_headerTransactionBlock.m_versionBlock = _version;
	m_headerTransactionBlock.m_difficultyBlock = _difficulty;
	m_headerTransactionBlock.m_prevBlockHash = _prevblockHash;
	m_headerTransactionBlock.m_timeMarkBlock = m_timeMarkBlock;
	
	m_transactisonList = _data;
	for (Transaction& i : m_transactisonList) {
		m_headerTransactionBlock.m_transactionHashes.insert(i.m_transactionHash);
	}
	
	m_shaGenerate.update(std::to_string(_version) + std::to_string(_difficulty) + _prevblockHash + m_timeMarkBlock + m_headerTransactionBlock.m_transactionHashes.root().to_string());
	m_headerTransactionBlock.m_blockHash = SHA256::toString(m_shaGenerate.digest());
}

const std::string TransactionBlock::getHash() const
{
	return m_headerTransactionBlock.m_blockHash;
}

const std::string TransactionBlock::getPrevHash() const
{
	return m_headerTransactionBlock.m_prevBlockHash;
}
