#include "base/nextai_string.h"
#include "base/nextai_basic_define.h"

namespace NextAI
{
	MbString::MbString()
	{
#ifdef D_USE_STD_STRING
		m_buffer = L"";
#else
		m_bufferSize = D_nextai_STRING_BUFFER_DEFAULT_SIZE;
		m_buffer = MbNewArray(WCHAR, m_bufferSize);
		memset(m_buffer, 0x00, sizeof(WCHAR)* m_bufferSize);
#endif
	}

	MbString::MbString(const WCHAR* str)
	{
#ifdef D_USE_STD_STRING
		m_buffer = str;
#else
		wcscpy_s(m_buffer, m_bufferSize, str);
#endif
	}

	MbString::MbString(const MbString& str)
	{
#ifdef D_USE_STD_STRING
		m_buffer = str.m_buffer;
#else
		if (m_buffer != str.m_buffer)
		{
			memcpy(m_buffer, str.m_buffer, sizeof(WCHAR)* m_bufferSize);
		}
#endif
	}

	MbString::~MbString()
	{

	}

	MbString MbString::operator=(const MbString& str)
	{
#ifdef D_USE_STD_STRING
		m_buffer = str.m_buffer;
#else
		if (m_buffer != str.m_buffer)
		{
			memcpy(m_buffer, str.m_buffer, sizeof(WCHAR)* m_bufferSize);
		}
#endif
		return *this;
	}

	BOOL MbString::operator==(const MbString& str)const
	{
#ifdef D_USE_STD_STRING
		return m_buffer == str.m_buffer;
#else
		return wcscmp(m_buffer, str.m_buffer) == 0 ? TRUE : FALSE;
#endif
	}

	BOOL MbString::operator==(const WCHAR* str)const
	{
#ifdef D_USE_STD_STRING
		return m_buffer == std::wstring(str);
#else
		return wcscmp(m_buffer, str) == 0 ? TRUE : FALSE;
#endif
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
#ifdef D_USE_STD_STRING
		return m_buffer.length();
#else
		return wcslen(m_buffer);
#endif
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
#ifdef D_USE_STD_STRING
		return m_buffer.c_str();
#else
		return m_buffer;
#endif
	}
}