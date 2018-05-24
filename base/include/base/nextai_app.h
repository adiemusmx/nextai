#ifndef _nextai_app_H_
#define _nextai_app_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"

namespace NextAI {

class AppServiceParam
{
public:
	// Environment param
	int argc;
	char** argv;

	// Windows start position, width and height.
	Rect windowsArea;

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
	virtual BOOL initStarted();

	// After App Service init.
	virtual BOOL initCompleted();

	// Before App Service cleanup.
	virtual BOOL cleanupStarted();

	// After App Service cleanup.
	virtual BOOL cleanupCompleted();

	// Before Render.
	virtual BOOL renderStarted();

	// Render.
	virtual BOOL render();

	// After Render.
	virtual BOOL renderCompleted();

	// Hardkey
	virtual BOOL hardkey(HardkeyID key);

	// touchCount indicates valid data count of touch.
	// touchId and touchPos has TOUCH_POINT_MAX_COUNT elements.
	virtual BOOL touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[]);
};

#define NEXT_AI_APP_SERVICE() NextAI::AppService::getInstance()

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

	// Windows property
	size_t getWindowsWidth();
	size_t getWindowsHeight();


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
	virtual ~AppService();

	// Disable copy constructor
	DISABLE_CLASS_COPY(AppService);

	// Event listeners
	std::vector<AppEventListener*> m_listeners;

	Rect m_area;
};
}

#endif // !_nextai_app_H_