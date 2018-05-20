#include "base/mapbar_time.h"

#ifdef SYSTEM_LINUX
#include "time.h"
#include "sys/time.h"
#endif

namespace MapBarDL {

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

DateTime::DateTime(uint32 year, uint32 month, uint32 day, uint32 hour, uint32 minute, uint32 second, uint32 millisecond)
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

DateTime::DateTime(const DateTime& date)
{
	m_year = date.m_year;
	m_month = date.m_month;
	m_day = date.m_day;
	m_hour = date.m_hour;
	m_minute = date.m_minute;
	m_second = date.m_second;
	m_millisecond = date.m_millisecond;
}

DateTime& DateTime::operator=(const DateTime& date)
{
	m_year = date.m_year;
	m_month = date.m_month;
	m_day = date.m_day;
	m_hour = date.m_hour;
	m_minute = date.m_minute;
	m_second = date.m_second;
	m_millisecond = date.m_millisecond;
	return *this;
}

BOOL DateTime::operator<(const DateTime& date)const
{
	BOOL ret = FALSE;
	if (getTotalSeconds() < date.getTotalSeconds())
		ret = TRUE;
	else if (getTotalSeconds() > date.getTotalSeconds())
		ret = FALSE;
	else
		ret = m_millisecond < date.m_millisecond;
	return ret;
}

BOOL DateTime::operator>(const DateTime& date)const
{
	BOOL ret = FALSE;
	if (getTotalSeconds() > date.getTotalSeconds())
		ret = TRUE;
	else if (getTotalSeconds() < date.getTotalSeconds())
		ret = FALSE;
	else
		ret = m_millisecond > date.m_millisecond;
	return ret;
}

BOOL DateTime::operator<=(const DateTime& date)const
{
	return !(*this > date);
}

BOOL DateTime::operator>=(const DateTime& date)const
{
	return !(*this < date);
}

BOOL DateTime::operator==(const DateTime& date)const
{
	return ((getTotalSeconds() == date.getTotalSeconds()) && (m_millisecond == date.m_millisecond));
}

time_t DateTime::operator-(const DateTime& date)const
{
	return ((getTotalSeconds() - date.getTotalSeconds()) * 1000 + m_millisecond - date.m_millisecond);
}

time_t DateTime::getTotalSeconds()const
{
	time_t ret = 0;
	for (size_t i = 1900; i < m_year; ++i)
	{
		ret += 365 * 24 * 60 * 60;
		if (isLeapYear(i))
		{
			ret += 24 * 60 * 60;
		}
	}
	for (size_t i = 1; i < m_month; ++i)
	{
		const int32 daysTable[2][12] =
		{
			{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },
			{ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }
		};
		ret += daysTable[isLeapYear(m_year)][i] * 24 * 60 * 60;
	}
	ret += (m_day - 1) * 24 * 60 * 60;
	ret += m_hour * 60 * 60;
	ret += m_minute * 60;
	ret += m_second;
	return ret;
}

DateTime DateTime::now()
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

#if 0
void Util_getCurrentSystemTime(DateTime& dateTime)
{
#ifdef SYSTEM_WINDOWS
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	dateTime.m_year = sys.wYear;
	dateTime.m_month = sys.wMonth;
	dateTime.m_day = sys.wDay;
	dateTime.m_hour = sys.wHour;
	dateTime.m_minute = sys.wMinute;
	dateTime.m_second = sys.wSecond;
	dateTime.m_millisecond = sys.wMilliseconds;
#endif

#ifdef SYSTEM_LINUX
	time_t timer;
	struct tm* t;
	timer = time(NULL);
	t = localtime(&timer);
	dateTime.m_year = t->tm_year + 1900;
	dateTime.m_month = t->tm_mon;
	dateTime.m_day = t->tm_mday;
	dateTime.m_hour = t->tm_hour;
	dateTime.m_minute = t->tm_min;
	dateTime.m_second = t->tm_sec;

	timeval tv;
	gettimeofday(&tv, NULL);
	dateTime.m_millisecond = tv.tv_usec / 1000;
#endif
}
#endif
}