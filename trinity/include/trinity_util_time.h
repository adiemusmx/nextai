#ifndef _TRINITY_UTIL_TIME_H_
#define _TRINITY_UTIL_TIME_H_

#include "trinity_common_types.h"

namespace Trinity {

// Date
class DateTime
{
public:
	DateTime();
	DateTime(size_t totalMillisecond);
	DateTime(int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second, int32 millisecond);
	virtual ~DateTime();

	DateTime& DateTime(const DateTime& date);
	DateTime operator=(const DateTime& date);

	DateTime operator-(const DateTime& after, const DateTime& before);

	int32 getMilliseconds();

	static DateTime now();

private:
	int32 m_year;
	int32 m_month;
	int32 m_day;
	int32 m_hour;
	int32 m_minute;
	int32 m_second;
	int32 m_millisecond;
};

void Util_getCurrentSystemTime(DateTime& dateTime);


}

#endif // !_TRINITY_UTIL_TIME_H_