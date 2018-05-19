#ifndef _APP_EVENT_HANDLER_H_
#define _APP_EVENT_HANDLER_H_

#include "trinity/trinity_app_service.h"

class AppEventHandler : public MapBarDL::AppEventListener
{
public:
	static AppEventHandler* getInstance();

	virtual BOOL initCompleted();

	virtual BOOL render();

	virtual BOOL touch(MapBarDL::TouchType touch, int32 touchCount, const int32 touchId[], const MapBarDL::ScreenPoint touchPos[]);

private:
	AppEventHandler() {}
	virtual ~AppEventHandler() {}
};

#endif // !_APP_EVENT_HANDLER_H_