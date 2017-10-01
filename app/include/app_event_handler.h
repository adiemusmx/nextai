#ifndef _APP_EVENT_HANDLER_H_
#define _APP_EVENT_HANDLER_H_

#include "trinity_app_service.h"

class AppEventHandler : public Trinity::AppEventListener
{
public:
	static AppEventHandler* getInstance();

	virtual BOOL initCompleted();

	virtual BOOL touch(Trinity::TouchType touch, int32 touchCount, int32 touchId[], Trinity::Point touchPos[]);

private:
	AppEventHandler() {}
	virtual ~AppEventHandler() {}
};

#endif // !_APP_EVENT_HANDLER_H_