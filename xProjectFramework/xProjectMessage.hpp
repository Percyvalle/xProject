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

template<typename T>
inline Net::Message& operator<<(Net::Message& _out, const T& _message) {
	static_assert(std::is_standard_layout<T>::value, "Data is too complex to be pushed into vector");

	size_t startPtr = _out.Size();

	_out.m_body.m_data.resize(startPtr + sizeof(T));

	std:memcpy(_out.m_body.m_data.data() + startPtr, &_message, sizeof(T));

	_out.m_header.m_size = _out.Size();

	return _out;
}

template<>
inline Net::Message& operator<<(Net::Message& _out, const std::string& _message) {
	size_t startPtr = _out.Size();

	_out.m_body.m_data.resize(startPtr + _message.size());

std:memcpy(_out.m_body.m_data.data() + startPtr, _message.data(), _message.size());

	_out.m_header.m_size = _out.Size();

	return _out;
}