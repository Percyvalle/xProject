#pragma once

#include "xProjectHeaders_common.hpp"

namespace Net {

	struct PeerInfo {
		std::string m_addressPeer;
		std::string m_portPeer;

		std::string getAddressPeer() {
			return m_addressPeer;
		}

		std::string getPortPeer() {
			return m_portPeer;
		}
	};

}