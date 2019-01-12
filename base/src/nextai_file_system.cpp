#include "stdafx.h"
#include "base/nextai_file_system.h"

#define  FILE_EXIST_FLAG	0     /* Check for file existence */
#define  FILE_EXE_FLAG		1     /* Check for execute permission. */
#define  FILE_WRITE_FLAG	2     /* Check for write permission */
#define  FILE_READ_FLAG		4     /* Check for read permission */

namespace NextAI
{
	bool waccess(const WCHAR* wpath, int32 openmode)
	{
		char path[PATH_LENGTH_MAX] = {0};
		wcstombs(path, wpath, element_of(path));

#ifdef SYSTEM_LINUX
		return access(path, openmode) == 0 ? true : false;
#else
		return _access(path, openmode) == 0 ? true : false;
#endif
	}

	void wgetcwd(WCHAR* wpath, size_t wpathLengh)
	{
		char path[PATH_LENGTH_MAX] = {0};
#ifdef SYSTEM_LINUX
		getcwd(path, element_of(path));
#else
		GetCurrentDirectory(element_of(path), path);
#endif
		mbstowcs(wpath, path, wpathLengh);
		return;
	}

	WCHAR FileSystem::m_currentDirectory[FILE_PATH_MAX_LENGTH] = { 0 };

	BOOL FileSystem::isExist(const WCHAR* path)
	{
		return waccess(path, FILE_READ_FLAG);
	}

	FileSystem::ACCESS_MODE FileSystem::getAccessMode(const WCHAR* path)
	{
		if (!waccess(path, FILE_EXIST_FLAG))
			return FileSystem::ACCESS_MODE_NO_EXIST;

		BOOL readable = waccess(path, FILE_READ_FLAG);
		BOOL writeable = waccess(path, FILE_WRITE_FLAG);

		if (readable == TRUE && writeable == FALSE)
			return FileSystem::ACCESS_MODE_READ_ONLY;
		else if (readable == FALSE && writeable == TRUE)
			return FileSystem::ACCESS_MODE_WRITE_ONLY;
		else if (readable == TRUE && writeable == TRUE)
			return FileSystem::ACCESS_MODE_READ_WRITE;

		return FileSystem::ACCESS_MODE_DENIED;
	}

	BOOL FileSystem::isAbsolute(const WCHAR* path)
	{
#if defined(SYSTEM_WINDOWS)
		return (path[1] == ':');
#else
		return (path[0] == '/');
#endif
	}

	const std::wstring FileSystem::getCurrentDirectory()
	{
		memset(m_currentDirectory, 0x00, sizeof(m_currentDirectory));

		wgetcwd(m_currentDirectory, element_of(m_currentDirectory));

		uint32 pathLength = wcslen(m_currentDirectory);

		if (pathLength > 1 && (pathLength < element_of(m_currentDirectory) - 2) && (m_currentDirectory[pathLength - 1] != '/' || m_currentDirectory[pathLength - 1] != '\\'))
		{
#if defined(SYSTEM_WINDOWS)
			m_currentDirectory[pathLength] = '/';
#else
			m_currentDirectory[pathLength] = '/';
#endif
		}

		return m_currentDirectory;
	}

	File::File()
	{

	}

	File::~File()
	{

	}

	static std::ios::openmode _FileAccessMode2iosMode(FileAccessMode mode)
	{
		const std::ios::openmode modeTable[] = {
			std::ios::in,
			std::ios::out,
			std::ios::in | std::ios::out,
			std::ios::app,
			std::ios::in | std::ios::binary,
			std::ios::out | std::ios::binary,
			std::ios::app | std::ios::binary
		};

		return modeTable[(int32)mode];
	}

	BOOL File::open(const WCHAR* wpath, FileAccessMode mode)
	{
		BASE_INFO_LOG(L"wpath[{}] mode[{}]", wpath, mode);
#ifdef SYSTEM_LINUX
		char path[PATH_LENGTH_MAX] = { 0 };
		wcstombs(path, wpath, element_of(path));
		m_file.open(path, _FileAccessMode2iosMode(mode));
#else
		m_file.open(wpath, _FileAccessMode2iosMode(mode));
#endif
		return isOpen();
	}

	BOOL File::isOpen()
	{
		return m_file.is_open() ? TRUE : FALSE;
	}

	FileStatus File::close()
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;
		
		m_file.close();
		return FileStatus::OK;
	}

	FileStatus File::write(const WCHAR* string)
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;
		
		return FileStatus::OK;
	}

	FileStatus File::writeLine(const WCHAR* string)
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;
			
		m_file << string << std::endl;
		return FileStatus::OK;
	}

	FileStatus File::write(const BIT_DATA* buffer, uint32 bufferSize)
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;

		m_file.write((const WCHAR *)buffer, bufferSize);
		return FileStatus::OK;
	}

	FileStatus File::read(WCHAR* string, uint32 size)
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;

		m_file.read(string, size);
		return FileStatus::OK;
	}

	FileStatus File::readLine(WCHAR* string, uint32 size)
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;

		m_file.read(string, size);
		return FileStatus::OK;
	}

	FileStatus File::read(BIT_DATA* buffer, uint32 bufferSize)
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;

		m_file.read((WCHAR *)buffer, bufferSize);
		return FileStatus::OK;
	}

	BOOL File::EndOfFile()
	{
		return m_file.eof() ? TRUE : FALSE;
	}

	FileStatus File::flush()
	{
		if (!m_file.is_open()) return FileStatus::NotOpen;

		m_file.flush();
		return FileStatus::OK;
	}
}