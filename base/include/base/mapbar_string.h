#ifndef _MAPBAR_STRING_H_
#define _MAPBAR_STRING_H_

#include "base/mapbar_basic_types.h"

namespace MapBarDL
{
	class MbString
	{
	public:
		/* ���캯�� */
		MbString();
		MbString(const WCHAR* str);

		/* �������캯�� */
		MbString(const MbString& str);

		/* �������� */
		virtual ~MbString();

		/* ��ֵ */
		virtual MbString operator=(const MbString& str);
		
		/* �Ƚ��ַ��� */
		virtual BOOL operator==(const MbString& str)const;
		virtual BOOL operator==(const WCHAR* str)const;
		virtual BOOL operator!=(const MbString& str)const { return !((*this) == str); }
		virtual BOOL operator!=(const WCHAR* str)const { return !((*this) == str); }
		virtual BOOL operator>(const MbString& str)const;
		virtual BOOL operator>(const WCHAR* str)const;
		virtual BOOL operator<(const MbString& str)const { return !((*this) > str); }
		virtual BOOL operator<(const WCHAR* str)const { return !((*this) > str); }

		/* ȡ�������ַ� */
		virtual WCHAR operator[](int32 index)const;
		
		/* ��ȡ�ַ��� */
		virtual MbString sub(int32 startPos, int32 endPos);
		virtual MbString operator()(int32 startPos, int32 endPos);

		/* �滻�ַ��� */
		virtual MbString replace(const MbString& oldStr, const MbString& newStr);

		/* �����ַ��� */
		virtual int32 find(const MbString& str)const;
		virtual int32 find(const WCHAR* str)const;
		virtual BOOL startsWith(const MbString& str)const;
		virtual BOOL startsWith(const WCHAR* str)const;
		virtual BOOL endsWith(const MbString& str)const;
		virtual BOOL endsWith(const WCHAR* str)const;

		/* ����ַ�����Ĭ������ո��Ʊ�� */
		virtual void trim(const MbString& characters);
		virtual void trim(const WCHAR* characters = NULL);
		virtual void trimStart(const MbString& characters);
		virtual void trimStart(const WCHAR* characters = NULL);
		virtual void trimEnd(const MbString& characters);
		virtual void trimEnd(const WCHAR* characters = NULL);

		/* �з��ַ��� */
		virtual void split(const MbString& characters);
		virtual void split(const WCHAR* characters);

		/* �ַ������� */
		virtual size_t length()const;

		/* �ַ���ƴ�� */
		virtual MbString cat(const MbString& str)const;
		virtual MbString operator+(const MbString& str)const;
		virtual MbString operator+=(const MbString& str);
		virtual MbString operator*(size_t times)const;		/* �ַ����ظ�times�� */

		virtual const WCHAR* cStr()const;

	private:
		std::wstring m_buffer;
	};
}

#endif // !_MAPBAR_STRING_H_