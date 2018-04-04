#ifndef _TRINITY_UTIL_TIME_H_
#define _TRINITY_UTIL_TIME_H_

#include "trinity_common_types.h"
#include <string>

namespace Trinity {

// Date
class DateTime
{
public:
	DateTime();
	DateTime(uint32 year, uint32 month, uint32 day, uint32 hour, uint32 minute, uint32 second, uint32 millisecond);
	virtual ~DateTime();

	DateTime(const DateTime& date);
	DateTime& operator=(const DateTime& date);

	BOOL operator<(const DateTime& date)const;
	BOOL operator>(const DateTime& date)const;
	BOOL operator<=(const DateTime& date)const;
	BOOL operator>=(const DateTime& date)const;
	BOOL operator==(const DateTime& date)const;
	time_t operator-(const DateTime& date)const;

	// Get the total seconds of the date time.
	time_t getTotalSeconds()const;

	// Get the time of system
	static DateTime now();

	inline static BOOL isLeapYear(uint32 year) {
		return (year % 100 != 0 && year % 4 == 0) || (year % 400 == 0);
	}

	void setYear(uint32 year) { m_year = year; }
	uint32 getYear() { return m_year; }

	void setMonth(uint32 month) { m_month = month; }
	uint32 getMonth() { return m_month; }

	void setDay(uint32 day) { m_day = day; }
	uint32 getDay() { return m_day; }

	void setHour(uint32 hour) { m_hour = hour; }
	uint32 getHour() { return m_hour; }

	void setMinute(uint32 minute) { m_minute = minute; }
	uint32 getMinute() { return m_minute; }

	void setSecond(uint32 second) { m_second = second; }
	uint32 getSecond() { return m_second; }

	void setMillisecond(uint32 millisecond) { m_millisecond = millisecond; }
	uint32 getMillisecond() { return m_millisecond; }

private:
	uint32 m_year;
	uint32 m_month;
	uint32 m_day;
	uint32 m_hour;
	uint32 m_minute;
	uint32 m_second;
	uint32 m_millisecond;
};

//void Util_getCurrentSystemTime(DateTime& dateTime);


}

#endif // !_TRINITY_UTIL_TIME_H_