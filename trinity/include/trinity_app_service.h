#ifndef _TRINITY_APP_SERVICE_H_
#define _TRINITY_APP_SERVICE_H_

#include "trinity_common_define.h"
#include "trinity_common_types.h"

namespace Trinity
{

class AppServiceParam
{
public:
	// Environment param
	int argc;
	char** argv;

	// Windows start position, width and height.
	RECT windowsArea;

	// Windows title
	const char* windowsTitle;
};

// Hardkey ID
enum HardkeyID
{
	HardkeyID_F1,
	HardkeyID_F2,
	HardkeyID_F3,
	HardkeyID_F4,
	HardkeyID_F5,
	HardkeyID_F6,
	HardkeyID_F7,
	HardkeyID_F8,
	HardkeyID_F9,
	HardkeyID_F10,
	HardkeyID_F11,
	HardkeyID_F12,
	HardkeyID_LEFT,
	HardkeyID_UP,
	HardkeyID_RIGHT,
	HardkeyID_DOWN,
	HardkeyID_PAGE_UP,
	HardkeyID_PAGE_DOWN,
	HardkeyID_HOME,
	HardkeyID_END,
	HardkeyID_INSERT
};

// Touch Type
enum TouchType
{
	TouchType_BEGAN,		// began
	TouchType_MOVED,		// move
	TouchType_ENDED,		// ended
	TouchType_CANCELLED		// cancelled
};

// App event listener
class AppEventListener
{
public:
	// Before App Service init.
	virtual void initStarted();

	// After App Service init.
	virtual void initCompleted();

	// Before App Service cleanup.
	virtual void cleanupStarted();

	// After App Service cleanup.
	virtual void cleanupCompleted();

	// Before Render.
	virtual void renderStarted();

	// After Render.
	virtual void renderCompleted();

	// Hardkey
	virtual void hardkey(HardkeyID key);

	// touchCount indicates valid data count of touch.
	// touchId and touchPos has 10 elements.
	virtual void touch(TouchType touch, int32 touchCount, int32 touchId[], POINT touchPos[]);
};

// App core service
class AppService
{

public:
	// Get the instance of the app service.
	static AppService* getInstance();

	// Initialize
	void init(AppServiceParam& param);

	// Event listeners
	void addEventListener(AppEventListener* listener);
	void removeEventListener(AppEventListener* listener);

	// Run
	void run();

private:
	// function of draw
	static void displayFunc();

	// function of idle
	static void idleFunc();

	// function of key
	static void keyBoardFunc(int key, int x, int y);

	// Function of mouse
	static void mouseFunc(int button, int state, int x, int y);

	// Motion of mouse
	static void motionFunc(int x, int y);
	static void passiveMotionFunc(int x, int y);

private:
	// Constructor
	AppService();
	~AppService();

	// Disable copy constructor
	DISABLE_CLASS_COPY(AppService);

	// Event listeners
	std::vector<AppEventListener*> m_listeners;
};
}

#endif // !_TRINITY_APP_SERVICE_H_