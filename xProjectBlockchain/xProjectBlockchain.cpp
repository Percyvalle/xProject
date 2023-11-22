#include "xProjectBlockchain.hpp"

std::string Blockchain::miningHash()
{
	return std::string();
}

void Blockchain::addInTransactionsPool(const Transaction& _transaction)
{
	m_tempTransactionsPool.m_transactionsPoolData.push_back(_transaction);
}

bool Blockchain::initBlockchain(StateBlockchain _state)
{
	switch (_state)
	{
	case Blockchain::GENESIS:
		break;
	case Blockchain::JOIN:
		break;
	default:
		return false;
	}

	return true;
}

bool Blockchain::addBlock(const int& _difficulty, const std::string& _prevblockHash, const std::string& m_timeMarkBlock)
{
	if (m_tempTransactionsPool.m_transactionsPoolData.size() == 0)
	{
		return false;
	}

	m_data.emplace_back(_difficulty, _prevblockHash, m_timeMarkBlock, m_tempTransactionsPool.m_transactionsPoolData);
	return true;
}

bool Blockchain::isValid() const
{
	for (int i = 1; i < m_data.size(); i++) {
		if (m_data[i].getPrevHash() != m_data[i - 1].getHash()) {
			return false;
		}
	}
	return true;
}
