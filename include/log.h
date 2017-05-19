#pragma once

#include "common_define.h"
#include "common_types.h"

namespace Trinity {

	// LOG输出的位置
	enum E_LOG_OUTPUT {
		E_LOG_OUTPUT_FILE,    // 输出到文件
		E_LOG_OUTPUT_CONSOLE, // 输出到控制台
		E_LOG_OUTPUT_MAX
	}

	// LOG输出的级别
	enum E_LOG_LEVEL {
		E_LOG_LEVEL_OFF,     // 关闭
		E_LOG_LEVEL_VERBOSE, // 最详细
		E_LOG_LEVEL_TRACE,   // 跟踪函数调用
		E_LOG_LEVEL_INFO,    // 输出信息
		E_LOG_LEVEL_WARNING, // 发生警告，可能不会影响功能
		E_LOG_LEVEL_ERROR,   // 发生错误，会影响功能
		E_LOG_LEVEL_MAX
	};

	// 输出log的对象
	class Logger {
	public:
		// 初始化LogManager
		static Logger *getInstance() {
			static Logger instance;
			return &intance;
		}

		// 输出LOG
		void print(const CHAR *funcName, INT32 lineNum, E_LOG_LEVEL level, const CHAR *format, ...);

		// #未实现# 设定文件输出路径，最大D_TEXT_MAX_LENGTH
		void openFile(WCHAR *filePath);
		void closeFile();

		// #未实现# 设定Level是否可以输出LOG
		void setLevel(E_LOG_OUTPUT output, E_LOG_LEVEL level);

	private:
		// 保存Level的许可
		BOOL m_logLevel[E_LOG_OUTPUT_MAX];
	};
}

// 用于详细输出信息
#define TRI_VERBOSE_LOG(format, ...)                                                      \
    {                                                                                     \
        WCHAR __log[D_TEXT_MAX_LENGTH];                                                   \
        sprintf_s(__log, D_TEXT_MAX_LENGTH, format, ##__VA_ARGS__);                       \
        Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_VERBOSE, __log); \
    }

// 用于函数开始
#define TRI_TRACE_LOG_START()                                                               \
    {                                                                                       \
        Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, "[START]"); \
    }

// 用于函数结尾
#define TRI_TRACE_LOG_END()                                                               \
    {                                                                                     \
        Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, "[END]"); \
    }

// 用于函数中间，需要提供一个char*类型的flag值用于区分
#define TRI_TRACE_LOG(format, ...)                                                      \
    {                                                                                   \
        WCHAR __log[D_TEXT_MAX_LENGTH];                                                 \
        sprintf_s(__log, D_TEXT_MAX_LENGTH, format, ##__VA_ARGS__);                     \
        Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_TRACE, __log); \
    }

#define TRI_INFO_LOG(format, ...)                                                      \
    {                                                                                  \
        WCHAR __log[D_TEXT_MAX_LENGTH];                                                \
        sprintf_s(__log, D_TEXT_MAX_LENGTH, format, ##__VA_ARGS__);                    \
        Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_INFO, __log); \
    }

// 用于输出警告，请尽量使用自然语言，即使没有源码的人，也能了解警告的内容或者可能造成的后果
#define TRI_WARNING_LOG(format, ...)                                                      \
    {                                                                                     \
        WCHAR __log[D_TEXT_MAX_LENGTH];                                                   \
        sprintf_s(__log, D_TEXT_MAX_LENGTH, format, ##__VA_ARGS__);                       \
        Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_WARNING, __log); \
    }

// 用于输出错误，请尽量使用自然语言，即使没有源码的人，也能了解错误的内容或者可能造成的后果
#define TRI_ERROR_LOG(format, ...)                                                      \
    {                                                                                   \
        WCHAR __log[D_TEXT_MAX_LENGTH];                                                 \
        sprintf_s(__log, D_TEXT_MAX_LENGTH, format, ##__VA_ARGS__);                     \
        Logger::getInstance()->print(__FUNCTION__, __LINE__, E_LOG_LEVEL_ERROR, __log); \
    }