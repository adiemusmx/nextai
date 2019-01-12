#ifndef _STDAFX_H_
#define _STDAFX_H_

#include "base/nextai_log.h"

#define CLIENT_TRACE_LOG(format, ...)		NEXTAI_TRACE_LOG("CLIENT", format, ##__VA_ARGS__)
#define CLIENT_INFO_LOG(format, ...)		NEXTAI_INFO_LOG("CLIENT", format, ##__VA_ARGS__)
#define CLIENT_WARN_LOG(format, ...)		NEXTAI_WARN_LOG("CLIENT", format, ##__VA_ARGS__)
#define CLIENT_ERROR_LOG(format, ...)		NEXTAI_ERROR_LOG("CLIENT", format, ##__VA_ARGS__)
#define CLIENT_TRACE_FUNC()					NEXTAI_TRACE_FUNC("CLIENT")

#endif // !_STDAFX_H_