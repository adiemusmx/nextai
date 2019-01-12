#ifndef _STDAFX_H_
#define _STDAFX_H_

#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <string>

#include <GL/glut.h>
#include <GL/glu.h>
#include <algorithm>

#include "base/nextai_basic_define.h"
#include "render_system/render_system.h"
#include "render_system/render_font.h"
#include "base/nextai_log.h"

#define TRINITY_TRACE_LOG(format, ...)		NEXTAI_TRACE_LOG("TRINITY", format, ##__VA_ARGS__)
#define TRINITY_INFO_LOG(format, ...)		NEXTAI_INFO_LOG("TRINITY", format, ##__VA_ARGS__)
#define TRINITY_WARN_LOG(format, ...)		NEXTAI_WARN_LOG("TRINITY", format, ##__VA_ARGS__)
#define TRINITY_ERROR_LOG(format, ...)		NEXTAI_ERROR_LOG("TRINITY", format, ##__VA_ARGS__)
#define TRINITY_TRACE_FUNC()				NEXTAI_TRACE_FUNC("TRINITY")

#endif // !_STDAFX_H_