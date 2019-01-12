#include "stdafx.h"
#include "base/nextai_app.h"
#include "app_event_handler.h"

int main(int argc, char *argv[])
{
	NextAI::AppService* rs = NextAI::AppService::instance();
	// Initialize environment
	NextAI::AppServiceParam param;
	param.argc = argc;
	param.argv = argv;
	param.windowsArea = {0, 0, 1024, 768};
	param.windowsTitle = "Next AI Demo Program";
	rs->init(param);

	rs->addEventListener(AppEventHandler::instance());

	// main loop
	rs->run();

	return 0;
}