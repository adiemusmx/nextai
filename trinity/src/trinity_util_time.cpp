#include "trinity_util_time.h"

#ifdef SYSTEM_LINUX
#include "time.h"
#include "sys/time.h"
#endif

namespace Trinity {

void Util_getCurrentSystemTime(DateTime& dateTime)
{
#ifdef SYSTEM_WINDOWS
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	dateTime.year = sys.wYear;
	dateTime.month = sys.wMonth;
	dateTime.day = sys.wDay;
	dateTime.hour = sys.wHour;
	dateTime.minute = sys.wMinute;
	dateTime.second = sys.wSecond;
	dateTime.millisecond = sys.wMilliseconds;
#endif

#ifdef SYSTEM_LINUX
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	dateTime.year = t->tm_year + 1900;
	dateTime.month = t->tm_mon;
	dateTime.day = t->tm_mday;
	dateTime.hour = t->tm_hour;
	dateTime.minute = t->tm_min;
	dateTime.second = t->tm_sec;

	timeval tv;
	gettimeofday(&tv, NULL);
	dateTime.millisecond = tv.tv_usec / 1000;
#endif
}

}