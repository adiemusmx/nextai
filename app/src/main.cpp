#include "trinity/trinity_app_service.h"
#include "app_event_handler.h"

int main(int argc, char* argv[])
{
	Trinity::AppService* rs = Trinity::AppService::getInstance();

	// Initialize environment
	Trinity::AppServiceParam param;
	param.argc = argc;
	param.argv = argv;
	param.windowsArea = {0, 0, 1024, 768};
	param.windowsTitle = "Trinity sample app";
	rs->init(param);

	rs->addEventListener(AppEventHandler::getInstance());

	// main loop
	rs->run();

	return 0;
}