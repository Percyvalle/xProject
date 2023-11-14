#pragma once

#include "xProjectHeaders_common.hpp"

namespace Net 
{
	enum MessageType {
		Registration,
		Ping,
	};

	struct MessageHeader {
		MessageType m_type = MessageType::Ping;
		uint32_t m_size = 0;
	};

	struct MessageBody {
		std::vector<uint8_t> m_data;
	};

	struct Message {
		MessageHeader m_header;
		MessageBody m_body;

		uint32_t Size() { return m_body.m_data.size(); }
	};

	class Connection;
	struct 	OwnerMessage {
		std::shared_ptr<Connection>	m_remoteConnection = nullptr;
		Message m_remoteMsg;
	};
}