#include "trinity_util_time.h"

#ifdef SYSTEM_LINUX
#include "time.h"
#include "sys/time.h"
#endif

namespace Trinity {

DateTime::DateTime()
{
	m_year = 1900;
	m_month = 1;
	m_day = 1;
	m_hour = 0;
	m_minute = 0;
	m_second = 0;
	m_millisecond = 0;
}

DateTime::DateTime(size_t totalMillisecond)
{
	// TODO
}

DateTime::DateTime(int32 year, int32 month, int32 day, int32 hour, int32 minute, int32 second, int32 millisecond)
{
	m_year = year;
	m_month = month;
	m_day = day;
	m_hour = hour;
	m_minute = minute;
	m_second = second;
	m_millisecond = millisecond;
}

DateTime::~DateTime()
{

}

DateTime& DateTime::DateTime(const DateTime& date)
{
	m_year = date.m_year;
	m_month = date.m_month;
	m_day = date.m_day;
	m_hour = date.m_hour;
	m_minute = date.m_minute;
	m_second = date.m_second;
	m_millisecond = date.m_millisecond;
}

DateTime DateTime::operator=(const DateTime& date)
{
	m_year = date.m_year;
	m_month = date.m_month;
	m_day = date.m_day;
	m_hour = date.m_hour;
	m_minute = date.m_minute;
	m_second = date.m_second;
	m_millisecond = date.m_millisecond;
}

DateTime DateTime::operator-(const DateTime& after, const DateTime& before)
{
	DateTime ret;
	// TODO
}

int32 DateTime::getMilliseconds()
{
	// TODO
}

static DateTime DateTime::now()
{
#ifdef SYSTEM_WINDOWS
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	DateTime date(sys.wYear, sys.wMonth, sys.wDay, sys.wHour, sys.wMinute, sys.wSecond, sys.wMilliseconds);
#endif

#ifdef SYSTEM_LINUX
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);

	// Millisecond
	timeval tv;
	gettimeofday(&tv, NULL);

	DateTime date(t->tm_year + 1900, t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, tv.tv_usec / 1000);
#endif

	return date;
}

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