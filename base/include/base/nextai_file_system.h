#ifndef _NEXTAI_FILE_SYSTEM_H_
#define _NEXTAI_FILE_SYSTEM_H_

#include "base/nextai_basic_define.h"
#include "base/nextai_basic_types.h"

namespace NextAI
{
	/* 文件系统 */
	class FileSystem
	{
	public:
		/* 访问模式 */
		enum ACCESS_MODE
		{
			ACCESS_MODE_NO_EXIST,		/* 文件不存在 */
			/* ---------------- */
			ACCESS_MODE_DENIED,			/* 访问拒绝 */
			ACCESS_MODE_READ_ONLY,		/* 只读权限 */
			ACCESS_MODE_WRITE_ONLY,		/* 只写权限 */
			ACCESS_MODE_READ_WRITE		/* 读写权限 */
		};

	public:
		/* 判断文件是否存在 */
		static BOOL isExist(const WCHAR* path);

		/* 获得文件的权限 */
		static ACCESS_MODE getAccessMode(const WCHAR* path);

		/* 判断文件是否是绝对路径 */
		static BOOL isAbsolute(const WCHAR* path);

		/* 获得当前路径 */
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