#ifndef _NEXTAI_FILE_SYSTEM_H_
#define _NEXTAI_FILE_SYSTEM_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"
#include <fstream>

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
		static const std::wstring getCurrentDirectory();

	private:
		FileSystem();
		virtual ~FileSystem();

		/* ���ÿ��� */
		DISABLE_CLASS_COPY(FileSystem);

		static WCHAR m_currentDirectory[FILE_PATH_MAX_LENGTH];
	};

	/* �ļ�����ģʽ */
	enum class FileAccessMode
	{
		Read,			/* ���ļ� */
		Write,			/* д�ļ� */
		ReadWrite,		/* ��д�ļ� */
		Append,			/* ׷���ļ� */
		ReadBinary,		/* �����ƶ��ļ� */
		WriteBinary,	/* д�ļ� */
		AppendBinary,	/* ׷���ļ� */
	};

	enum class FileStatus
	{
		OK,				/* ���� */
		NotOpen			/* δ�� */
	};

	/* ��׼�ļ� */
	class File
	{
	public:
		File();
		virtual ~File();

		/* ���ļ� */
		BOOL open(const WCHAR* wpath, FileAccessMode mode);

		/* �ļ��Ƿ��Ѿ����� */
		BOOL isOpen();

		/* �ر��ļ� */
		FileStatus close();

		/* �������� */
		FileStatus write(const WCHAR* string);
		FileStatus writeLine(const WCHAR* string);
		FileStatus write(const BIT_DATA* buffer, uint32 bufferSize);

		/* �������� */
		FileStatus read(WCHAR* string, uint32 size);
		FileStatus readLine(WCHAR* string, uint32 size);
		FileStatus read(BIT_DATA* buffer, uint32 bufferSize);

		/* �Ƿ񵽴��ļ�β�� */
		BOOL EndOfFile();

		/* ˢ���ļ� */
		FileStatus flush();

	private:
		/* ���ÿ��� */
		DISABLE_CLASS_COPY(File);

		std::wfstream m_file;
	};
}

#endif // !_NEXTAI_FILE_SYSTEM_H_