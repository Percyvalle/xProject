#include "xProjectBlockchain.hpp"

std::string Blockchain::currentDataTime()
{
	return boost::posix_time::to_simple_string(boost::posix_time::microsec_clock::universal_time());
}

void Blockchain::addInTransactionsPool(const Transaction& _transaction)
{
	m_tempTransactionsPool.m_transactionsPoolData.push_back(_transaction);
}

void Blockchain::setTransactionsPool(const std::vector<Transaction>& _transactionsPool)
{
	m_tempTransactionsPool.m_transactionsPoolData.resize(_transactionsPool.size());
	memcpy(m_tempTransactionsPool.m_transactionsPoolData.data(), _transactionsPool.data(), sizeof(Transaction) * _transactionsPool.size());
}

bool Blockchain::initBlockchain(StateBlockchain _state)
{
	switch (_state)
	{
	case Blockchain::StateBlockchain::GENESIS:
		// Temporary
		m_tempTransactionsPool.m_transactionsPoolData.emplace_back();
		
		addBlock(1, 1, std::string(63, '0') + '1', currentDataTime());
		break;
	case Blockchain::StateBlockchain::JOIN:
		break;
	default:
		return false;
	}

	return true;
}

bool Blockchain::addBlock(const uint32_t& _version, const uint32_t& _difficulty, const std::string& _prevblockHash, const std::string& _timeMarkBlock)
{
	if (m_tempTransactionsPool.m_transactionsPoolData.size() == 0)
	{
		return false;
	}
	
	TransactionBlock block(_version, _difficulty, _prevblockHash, _timeMarkBlock, m_tempTransactionsPool.m_transactionsPoolData);
	Utils::miningHash(block);
	block.printBlock();


	m_data.push_back(block);

	return true;
}

bool Blockchain::isValid()
{
	for (int i = 1; i < m_data.size(); i++) {
		if (m_data[i].getPrevHash() != m_data[i - 1].getHash()) {
			return false;
		}
	}
	return true;
}
