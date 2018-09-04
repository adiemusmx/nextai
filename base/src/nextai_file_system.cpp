#include "base/nextai_file_system.h"
#include "base/nextai_log.h"
#include <io.h>
#include <fstream>

#define  FILE_EXIST_FLAG	0     /* Check for file existence */
#define  FILE_EXE_FLAG		1     /* Check for execute permission. */
#define  FILE_WRITE_FLAG	2     /* Check for write permission */
#define  FILE_READ_FLAG		4     /* Check for read permission */

namespace NextAI
{
	WCHAR FileSystem::m_currentDirectory[FILE_PATH_MAX_LENGTH] = { 0 };

	BOOL FileSystem::isExist(const WCHAR* path)
	{
#if 0
		WCHAR fullpath[FILE_PATH_MAX_LENGTH] = { 0 };
		wcscat_s(fullpath, path);
		return _waccess(fullpath, FILE_EXIST_FLAG);
#else
		std::wifstream file(path, std::ios::in);
		return file ? TRUE : FALSE;
#endif
	}

	FileSystem::ACCESS_MODE FileSystem::getAccessMode(const WCHAR* path)
	{
		if (!_waccess(path, FILE_EXIST_FLAG))
			return FileSystem::ACCESS_MODE_NO_EXIST;

		BOOL readable = _waccess(path, FILE_READ_FLAG);
		BOOL writeable = _waccess(path, FILE_WRITE_FLAG);

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

	const WCHAR* FileSystem::getCurrentDirectory()
	{
		memset(m_currentDirectory, 0x00, sizeof(m_currentDirectory));

		_wgetcwd(m_currentDirectory, element_of(m_currentDirectory));

		int32 pathLength = wcslen(m_currentDirectory);

		if (pathLength > 1 && pathLength < element_of(m_currentDirectory) - 2 && (m_currentDirectory[pathLength - 1] != '/' || m_currentDirectory[pathLength - 1] != '\\'))
		{
#if defined(SYSTEM_WINDOWS)
			//m_currentDirectory[pathLength] = '\\';
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
			std::ios::app,
			std::ios::in | std::ios::binary,
			std::ios::out | std::ios::binary,
			std::ios::app | std::ios::binary
		};

		return modeTable[(int32)mode];
	}

	BOOL File::open(const WCHAR* path, FileAccessMode mode)
	{
		NEXTAI_INFO_W_LOG(L"path[%s] mode[%d]", path, mode);
		
		m_file.open(path, _FileAccessMode2iosMode(mode));
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