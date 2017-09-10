#include "app_service.h"

int main(int argc, char *argv[])
{
	Trinity::AppService* rs = Trinity::AppService::getInstance();

	// Initialize environment
	Trinity::AppServiceParam param;
	param.argc = argc;
	param.argv = argv;
	param.windowsArea = {100, 100, 800, 480};
	param.windowsTitle = "Trinity sample app";
	rs->init(param);

	// main loop
	rs->mainLoop();

	return 0;
}