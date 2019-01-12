#ifndef _NEXTAI_STRING_H_
#define _NEXTAI_STRING_H_

#include <string>
#include <cstdlib>

namespace NextAI
{
	inline std::wstring ansi2wstr(const char* str)
	{
		size_t length = strlen(str);
		if (length == 0)	return L"";

		wchar_t* buffer = new wchar_t[length];
		
		memset(buffer, 0x00, sizeof(wchar_t) * length);
		mbstowcs(buffer, str, length);
		std::wstring ret = buffer;
		
		delete[] buffer;
		return ret;
	}

	inline std::string mbs2str(const wchar_t* str)
	{

	}

	inline std::wstring str2wstr(const std::string& str)
	{

	}

	inline std::string wstr2str(const std::wstring& str)
	{

	}
}

#endif // !_NEXTAI_STRING_H_