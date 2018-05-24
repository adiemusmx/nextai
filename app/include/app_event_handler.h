#ifndef _APP_EVENT_HANDLER_H_
#define _APP_EVENT_HANDLER_H_

#include "base/nextai_app.h"

class AppEventHandler : public NextAI::AppEventListener
{
public:
	static AppEventHandler* getInstance();

	virtual BOOL initCompleted();

	virtual BOOL render();

	virtual BOOL touch(NextAI::TouchType touch, int32 touchCount, const int32 touchId[], const NextAI::ScreenPoint touchPos[]);

private:
	AppEventHandler() {}
	virtual ~AppEventHandler() {}
};

#endif // !_APP_EVENT_HANDLER_H_