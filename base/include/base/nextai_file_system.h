#ifndef _NEXTAI_FILE_SYSTEM_H_
#define _NEXTAI_FILE_SYSTEM_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"

namespace NextAI
{
	/* �ļ�ϵͳ */
	class FileSystem
	{
	public:
		/* ����ģʽ */
		enum ACCESS_MODE
		{
			ACCESS_MODE_NO_EXIST,		/* �ļ������� */
			/* ---------------- */
			ACCESS_MODE_DENIED,			/* ���ʾܾ� */
			ACCESS_MODE_READ_ONLY,		/* ֻ��Ȩ�� */
			ACCESS_MODE_WRITE_ONLY,		/* ֻдȨ�� */
			ACCESS_MODE_READ_WRITE		/* ��дȨ�� */
		};

	public:
		/* �ж��ļ��Ƿ���� */
		static BOOL isExist(const WCHAR* path);

		/* ����ļ���Ȩ�� */
		static ACCESS_MODE getAccessMode(const WCHAR* path);

		/* �ж��ļ��Ƿ��Ǿ���·�� */
		static BOOL isAbsolute(const WCHAR* path);

		/* ��õ�ǰ·�� */
		static const WCHAR* getCurrentDirectory();

	private:
		FileSystem();
		virtual ~FileSystem();

		FileSystem(const FileSystem&);
		FileSystem& operator=(const FileSystem&);

		static WCHAR m_currentDirectory[FILE_PATH_MAX_LENGTH];
	};
}

#endif // !_NEXTAI_FILE_SYSTEM_H_