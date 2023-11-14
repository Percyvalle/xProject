#pragma once

#include "xProjectServerInterface.hpp"

class RouteManager : public Net::ServerInterface {
private:
public:
	RouteManager(const std::string& _address, const uint16_t _port);
	virtual ~RouteManager();
};