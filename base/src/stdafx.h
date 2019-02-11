#ifndef _NEXTAI_STDAFX_H_
#define _NEXTAI_STDAFX_H_

#include <vld.h>

#ifdef SYSTEM_LINUX

#include <algorithm>
#include <sys/io.h>
#include <unistd.h>
#include "time.h"
#include "sys/time.h"

#else

#include <io.h>

#endif

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>

#include <GL/glut.h>
#include <GL/glu.h>

#define MODULE_NAME "BASE"
#include "base/nextai_log.h"

#endif // !_NEXTAI_STDAFX_H_