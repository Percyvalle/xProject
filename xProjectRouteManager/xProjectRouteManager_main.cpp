#include "xProjectRouteManager.hpp"

int main(int argv, char** argc) {
	RouteManager routeManager("127.0.0.1", 20055);
	routeManager.Start();

	for (;;) {

	}

	return EXIT_SUCCESS;
}