#include "stdafx.h"
#include "base/nextai_string.h"

namespace NextAI
{
	std::string StringUtil::ws2s(const std::wstring& ws)
	{
		//const char* curLocale = setlocale(LC_ALL, NULL);
		//setlocale(LC_ALL, "en_US.UTF-8");
		size_t _Dsize = 4 * ws.size() + 1;
		char *_Dest = new char[_Dsize];
		memset(_Dest, 0, _Dsize);
		wcstombs(_Dest, ws.c_str(), _Dsize);
		std::string result = _Dest;
		delete[]_Dest;
		//setlocale(LC_ALL, curLocale);
		return result;
	}
	
	std::wstring StringUtil::s2ws(const std::string& s)
	{
		//const char* curLocale = setlocale(LC_ALL, NULL);
		//setlocale(LC_ALL, "en_US.UTF-8");
		size_t _Dsize = s.size() + 1;
		wchar_t *_Dest = new wchar_t[_Dsize];
		wmemset(_Dest, 0, _Dsize);
		mbstowcs(_Dest, s.c_str(), _Dsize);
		std::wstring result = _Dest;
		delete[]_Dest;
		//setlocale(LC_ALL, curLocale);
		return result;
	}
}

std::wostream& operator<<(std::wostream& os, const std::string& obj)
{
	std::wstring output;
	output = NextAI::StringUtil::s2ws(obj);
	return os << output;
}