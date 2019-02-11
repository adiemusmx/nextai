#include "stdafx.h"
#include "base/nextai_time.h"

namespace NextAI
{

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
		BOOL ret = false;
		
		if (getTotalSeconds() < date.getTotalSeconds())
		{ ret = true; }
		else if (getTotalSeconds() > date.getTotalSeconds())
		{ ret = false; }
		else
		{ ret = m_millisecond < date.m_millisecond; }
		
		return ret;
	}
	
	BOOL DateTime::operator>(const DateTime& date)const
	{
		BOOL ret = false;
		
		if (getTotalSeconds() > date.getTotalSeconds())
		{ ret = true; }
		else if (getTotalSeconds() < date.getTotalSeconds())
		{ ret = false; }
		else
		{ ret = m_millisecond > date.m_millisecond; }
		
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
}