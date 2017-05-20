#include "util.h"

namespace Trinity {

	void Util_getCurrentSystemTime(Time& time)
	{
		memset(&time, 0x00, sizeof(time));

#ifdef SYSTEM_WINDOWS
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		time.year = sys.wYear;
		time.month = sys.wMonth;
		time.day = sys.wDay;
		time.hour = sys.wHour;
		time.minute = sys.wMinute;
		time.millisecond = sys.wMilliseconds;
#endif // SYSTEM_WINDOWS
	}

}