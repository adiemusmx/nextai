#ifndef _APP_EVENT_HANDLER_H_
#define _APP_EVENT_HANDLER_H_

#include "base/nextai_app.h"

class AppEventHandler : public NextAI::AppEventListener
{
public:
	static AppEventHandler* instance();

	virtual NextAI::ListenerResult initStarted();

	virtual NextAI::ListenerResult initCompleted();

	virtual NextAI::ListenerResult cleanupCompleted();

	virtual NextAI::ListenerResult render();

	virtual NextAI::ListenerResult touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[]);

private:
	AppEventHandler() {}
	virtual ~AppEventHandler() {}
};

#endif // !_APP_EVENT_HANDLER_H_