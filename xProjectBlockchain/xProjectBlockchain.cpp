#include "xProjectBlockchain.hpp"

void Blockchain::initBlockchain(StateBlockchain _state)
{
}

void Blockchain::createBlock()
{
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
