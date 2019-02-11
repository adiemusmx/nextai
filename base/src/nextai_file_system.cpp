#include "stdafx.h"
#include "base/nextai_file_system.h"
#include "base/nextai_string.h"

#define  FILE_EXIST_FLAG	0     /* Check for file existence */
#define  FILE_EXE_FLAG		1     /* Check for execute permission. */
#define  FILE_WRITE_FLAG	2     /* Check for write permission */
#define  FILE_READ_FLAG		4     /* Check for read permission */

namespace NextAI
{
	bool waccess(const std::wstring& wpath, int32 openmode)
	{
		std::string path = StringUtil::ws2s(wpath);
#ifdef SYSTEM_LINUX
		return access(path.c_str(), openmode) == 0 ? true : false;
#else
		return _access(path.c_str(), openmode) == 0 ? true : false;
#endif
	}
	
	void wgetcwd(std::wstring& wpath, size_t wpathLengh)
	{
		char path[MAX_PATH] = {0};
#ifdef SYSTEM_LINUX
		getcwd(path, element_of(path));
#else
		GetCurrentDirectory(element_of(path), path);
#endif
		wpath = StringUtil::s2ws(path);
		return;
	}
	
	std::wstring FileSystem::m_currentDirectory = L"";
	
	bool FileSystem::isExist(const std::wstring& path)
	{
		return waccess(path.c_str(), FILE_READ_FLAG);
	}
	
	FileSystem::ACCESS_MODE FileSystem::getAccessMode(const std::wstring& path)
	{
		if (!waccess(path, FILE_EXIST_FLAG))
		{ return FileSystem::ACCESS_MODE_NO_EXIST; }
		
		bool readable = waccess(path, FILE_READ_FLAG);
		bool writeable = waccess(path, FILE_WRITE_FLAG);
		
		if (readable == true && writeable == false)
		{ return FileSystem::ACCESS_MODE_READ_ONLY; }
		else if (readable == false && writeable == true)
		{ return FileSystem::ACCESS_MODE_WRITE_ONLY; }
		else if (readable == true && writeable == true)
		{ return FileSystem::ACCESS_MODE_READ_WRITE; }
		
		return FileSystem::ACCESS_MODE_DENIED;
	}
	
	bool FileSystem::isAbsolute(const std::wstring& path)
	{
#if defined(SYSTEM_WINDOWS)
		return (path[1] == ':');
#else
		return (path[0] == '/');
#endif
	}
	
	const std::wstring FileSystem::getCurrentDirectory()
	{
		m_currentDirectory = L"";
		wgetcwd(m_currentDirectory, element_of(m_currentDirectory));
		uint32 pathLength = m_currentDirectory.size();
		
		if (pathLength > 1 && (pathLength < element_of(m_currentDirectory) - 2) && (m_currentDirectory[pathLength - 1] != '/' || m_currentDirectory[pathLength - 1] != '\\'))
		{
			m_currentDirectory += L"/";
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
		const std::ios::openmode modeTable[] =
		{
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
	
	bool File::open(const std::wstring& wpath, FileAccessMode mode)
	{
		NEXTAI_TRACE_LOG(L"wpath[{}] mode[{}]", wpath, mode);
#ifdef SYSTEM_LINUX
		char path[PATH_LENGTH_MAX] = { 0 };
		wcstombs(path, wpath, element_of(path));
		m_file.open(path, _FileAccessMode2iosMode(mode));
#else
		m_file.open(wpath, _FileAccessMode2iosMode(mode));
#endif
		return isOpen();
	}
	
	bool File::isOpen()
	{
		return m_file.is_open() ? true : false;
	}
	
	FileStatus File::close()
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		m_file.close();
		return FileStatus::OK;
	}
	
	FileStatus File::write(const std::wstring& string)
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		return FileStatus::OK;
	}
	
	FileStatus File::writeLine(const std::wstring& string)
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		m_file << string << std::endl;
		return FileStatus::OK;
	}
	
	FileStatus File::write(const BIT_DATA* buffer, uint32 bufferSize)
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		m_file.write((const WCHAR *)buffer, bufferSize);
		return FileStatus::OK;
	}
	
#if 0 /* TODO */
	FileStatus File::read(std::wstring& string)
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		m_file.read(string, size);
		return FileStatus::OK;
	}
	
	FileStatus File::readLine(std::wstring& string)
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		m_file.read(string, size);
		return FileStatus::OK;
	}
#endif
	
	FileStatus File::read(BIT_DATA* buffer, uint32 bufferSize)
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		m_file.read((WCHAR *)buffer, bufferSize);
		return FileStatus::OK;
	}
	
	bool File::EndOfFile()
	{
		return m_file.eof() ? true : false;
	}
	
	FileStatus File::flush()
	{
		if (!m_file.is_open())
		{
			return FileStatus::NotOpen;
		}
		
		m_file.flush();
		return FileStatus::OK;
	}
}

std::wostream& operator<<(std::wostream& os, NextAI::FileAccessMode mode)
{
	switch (mode)
	{
		OUT_STREAM_ENUM_CLASS_CASE(FileAccessMode::Read);
		OUT_STREAM_ENUM_CLASS_CASE(FileAccessMode::Write);
		OUT_STREAM_ENUM_CLASS_CASE(FileAccessMode::ReadWrite);
		OUT_STREAM_ENUM_CLASS_CASE(FileAccessMode::Append);
		OUT_STREAM_ENUM_CLASS_CASE(FileAccessMode::ReadBinary);
		OUT_STREAM_ENUM_CLASS_CASE(FileAccessMode::WriteBinary);
		OUT_STREAM_ENUM_CLASS_CASE(FileAccessMode::AppendBinary);
	}
	
	return os << L"FileAccessMode::Unknown";
}


std::wostream& operator<<(std::wostream& os, NextAI::FileStatus mode)
{
	switch (mode)
	{
		OUT_STREAM_ENUM_CLASS_CASE(FileStatus::OK);
		OUT_STREAM_ENUM_CLASS_CASE(FileStatus::NotOpen);
	}
	
	return os << L"FileStatus::Unknown";
}