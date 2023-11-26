#pragma once

namespace Net {
	
	
	enum MessageType {
		RegistrationRequest,
		RegistrationResponse,
		PingRequest,
		PingResponse,
		GetPeerRequest,
		GetPeerResponse
	};
}