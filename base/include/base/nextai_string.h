#ifndef _NEXTAI_STRING_H_
#define _NEXTAI_STRING_H_

#include <string>

namespace NextAI
{
	class StringUtil
	{
	public:
		static std::string ws2s(const std::wstring& ws);
		static std::wstring s2ws(const std::string& s);
	};
}

std::wostream& operator<<(std::wostream& os, const std::string& obj);

#endif // !_NEXTAI_STRING_H_