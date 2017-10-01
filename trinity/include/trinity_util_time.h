#ifndef _TRINITY_UTIL_TIME_H_
#define _TRINITY_UTIL_TIME_H_

#include "trinity_common_types.h"

namespace Trinity
{

// Get the current system time.
// # TODO # Now only works on Windows.
struct DateTime
{
	int32 year;
	int32 month;
	int32 day;
	int32 hour;
	int32 minute;
	int32 second;
	int32 millisecond;
};

void Util_getCurrentSystemTime(DateTime& dateTime);

}

#endif // !_TRINITY_UTIL_TIME_H_