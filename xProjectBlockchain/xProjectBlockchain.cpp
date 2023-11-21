#include "xProjectBlockchain.hpp"

std::string Blockchain::miningHash()
{
	return std::string();
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

bool Blockchain::createBlock()
{
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
