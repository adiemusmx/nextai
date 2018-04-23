#include "base/mapbar_string.h"
#include "base/mapbar_basic_define.h"

namespace MapBarDL
{
	MbString::MbString()
	{
		m_buffer = L"";
	}

	MbString::MbString(const WCHAR* str)
	{
		m_buffer = str;
	}

	MbString::MbString(const MbString& str)
	{
		m_buffer = str.m_buffer;
	}

	MbString::~MbString()
	{

	}

	MbString MbString::operator=(const MbString& str)
	{
		m_buffer = str.m_buffer;
		return *this;
	}

	BOOL MbString::operator==(const MbString& str)const
	{
		return m_buffer == str.m_buffer;
	}

	BOOL MbString::operator==(const WCHAR* str)const
	{
		return m_buffer == std::wstring(str);
	}

	BOOL MbString::operator>(const MbString& str)const
	{
		return m_buffer > str.m_buffer;
	}

	BOOL MbString::operator>(const WCHAR* str)const
	{
		return m_buffer > std::wstring(str);
	}

	WCHAR MbString::operator[](int32 index)const
	{
		return m_buffer[index];
	}

	MbString MbString::sub(int32 startPos, int32 endPos)
	{
		MbAssert(0);
		return L"";
	}

	MbString MbString::operator()(int32 startPos, int32 endPos)
	{
		MbAssert(0);
		return L"";
	}

	MbString MbString::replace(const MbString& oldStr, const MbString& newStr)
	{
		MbAssert(0);
		return L"";
	}

	int32 MbString::find(const MbString& str)const
	{
		MbAssert(0);
		return 0;
	}

	int32 MbString::find(const WCHAR* str)const
	{
		MbAssert(0);
		return 0;
	}

	BOOL MbString::startsWith(const MbString& str)const
	{
		MbAssert(0);
		return FALSE;
	}

	BOOL MbString::startsWith(const WCHAR* str)const
	{
		MbAssert(0);
		return FALSE;
	}

	BOOL MbString::endsWith(const MbString& str)const
	{
		MbAssert(0);
		return FALSE;
	}

	BOOL MbString::endsWith(const WCHAR* str)const
	{
		MbAssert(0);
		return FALSE;
	}

	void MbString::trim(const MbString& characters)
	{
		MbAssert(0);
	}

	void MbString::trim(const WCHAR* characters)
	{
		MbAssert(0);
	}

	void MbString::trimStart(const MbString&)
	{
		MbAssert(0);
	}

	void MbString::trimStart(const WCHAR* characters)
	{
		MbAssert(0);
	}

	void MbString::trimEnd(const MbString&)
	{
		MbAssert(0);
	}

	void MbString::trimEnd(const WCHAR* characters)
	{
		MbAssert(0);
	}

	void MbString::split(const MbString& characters)
	{
		MbAssert(0);
	}

	void MbString::split(const WCHAR* characters)
	{
		MbAssert(0);
	}

	size_t MbString::length()const
	{
		return m_buffer.length();
	}

	MbString MbString::cat(const MbString& str)const
	{
		MbAssert(0);
		return L"";
	}

	MbString MbString::operator+(const MbString& str)const
	{
		MbAssert(0);
		return L"";
	}

	MbString MbString::operator+=(const MbString& str)
	{
		MbAssert(0);
		return L"";
	}

	MbString MbString::operator*(size_t times)const
	{
		MbAssert(0);
		return L"";
	}

	const WCHAR* MbString::cStr()const
	{
		return m_buffer.c_str();
	}
}