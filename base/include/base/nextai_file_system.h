#ifndef _NEXTAI_FILE_SYSTEM_H_
#define _NEXTAI_FILE_SYSTEM_H_

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
		static bool isExist(const std::wstring& path);
		
		/* ����ļ���Ȩ�� */
		static ACCESS_MODE getAccessMode(const std::wstring& path);
		
		/* �ж��ļ��Ƿ��Ǿ���·�� */
		static bool isAbsolute(const std::wstring& path);
		
		/* ��õ�ǰ·�� */
		static const std::wstring getCurrentDirectory();
		
	private:
		FileSystem();
		virtual ~FileSystem();
		
		/* ���ÿ��� */
		DISABLE_CLASS_COPY(FileSystem);
		
		static std::wstring m_currentDirectory;
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
		bool open(const std::wstring& wpath, FileAccessMode mode);
		
		/* �ļ��Ƿ��Ѿ����� */
		bool isOpen();
		
		/* �ر��ļ� */
		FileStatus close();
		
		/* �������� */
		FileStatus write(const std::wstring& string);
		FileStatus writeLine(const std::wstring& string);
		FileStatus write(const BIT_DATA* buffer, uint32 bufferSize);
		
#if 0	/* TODO */
		/* �������� */
		FileStatus read(std::wstring& string);
		FileStatus readLine(std::wstring& string);
#endif
		FileStatus read(BIT_DATA* buffer, uint32 bufferSize);
		
		/* �Ƿ񵽴��ļ�β�� */
		bool EndOfFile();
		
		/* ˢ���ļ� */
		FileStatus flush();
		
	private:
		/* ���ÿ��� */
		DISABLE_CLASS_COPY(File);
		
		std::wfstream m_file;
	};
}

OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::FileAccessMode);
OUT_STREAM_ENUM_CLASS_DECLARE(NextAI::FileStatus);

#endif // !_NEXTAI_FILE_SYSTEM_H_