#pragma once

#include "common_define.h"
#include "common_types.h"

namespace Trinity {

class AppServiceParam
{
public:
	// Environment param
	int argc;
	char** argv;

	// Windows start position, width and height.
	RECT windowsArea;

	// Windows title
	char* windowsTitle;
};

class AppService
{

public:
	// Get the instance of the app service.
	static AppService* getInstance();

	// Initialize
	void init(AppServiceParam& param);

	// Main Loop
	void mainLoop();

	// Internal function of draw
	static void displayFunc();

	// Internal function of idle
	static void idleFunc();

	// Internal function of key
	static void keyBoardFunc(int key, int x, int y);

private:
	// Constructor
	AppService();

	// Disable copy constructor
	DISABLE_CLASS_COPY(AppService);
};
}