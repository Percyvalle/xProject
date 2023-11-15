#include "xProjectRouteManager.hpp"

#include <boost/program_options.hpp>

#define DEFAULT_PATH_CONFIG "./config/config.ini"
#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 20055

static std::string routeManagerPathConfig = DEFAULT_PATH_CONFIG;
static std::string routeManagerAddress = DEFAULT_ADDRESS;
static uint16_t routeManagerPort = DEFAULT_PORT;

void initConfig() {
	ini::IniFile routeManagerConfig(routeManagerPathConfig);
	
	if (routeManagerConfig.empty()) {
		throw std::exception(("Read Config File Error: " + routeManagerPathConfig).c_str());
	}

	std::string temporaryValueAddress = routeManagerConfig["ROUTE_MANAGER_CONFIG"]["ROUTE_MANAGER_ADDRESS"].as<std::string>();
	if (!temporaryValueAddress.empty()) {
		routeManagerAddress = temporaryValueAddress;
	}

	uint16_t temporaryValuePort = routeManagerConfig["ROUTE_MANAGER_CONFIG"]["ROUTE_MANAGER_PORT"].as<uint16_t>();
	if (temporaryValuePort) {
		routeManagerPort = temporaryValuePort;
	}
}

int main(int argv, char** argc) {

#ifdef _DEBUG
	spdlog::set_level(spdlog::level::debug);
#endif // _DEBUG

	boost::program_options::options_description routeManagerOptionsDescription;
	routeManagerOptionsDescription.add_options()
		("config_path", boost::program_options::value<std::string>()->required(), "* Config Path");

	boost::program_options::variables_map variablesMap;

	try
	{
		boost::program_options::store(boost::program_options::command_line_parser(argv, argc).options(routeManagerOptionsDescription).run(), variablesMap);

		if (variablesMap.find("config_path") != variablesMap.end()) {
			routeManagerPathConfig = variablesMap["config_path"].as<std::string>();
		}

		initConfig();

		RouteManager routeManager(routeManagerAddress, routeManagerPort);
		routeManager.Start();
	
		while (true)
		{
			routeManager.Update(true);
		}
	}
	catch (const std::exception& _error)
	{
		spdlog::error("{0}", _error.what());
	}

	return EXIT_SUCCESS;
}