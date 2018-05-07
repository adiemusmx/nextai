#include "stdafx.h"
#include "trinity/trinity_app_service.h"
#include "trinity/trinity_message_center.h"
#include "trinity/trinity_widget_picture.h"
#include "trinity/trinity_object_manager.h"
#include "base/mapbar_log.h"
#include <algorithm>

#define VECTOR_NOTIFY(listeners, func,...)	\
	for (size_t loopIdx = 0; loopIdx < listeners.size(); ++loopIdx) \
		if (listeners[loopIdx]->func(__VA_ARGS__)) break;\

namespace MapBarDL {

BOOL AppEventListener::initStarted()
{
	return FALSE;
}

BOOL AppEventListener::initCompleted()
{
	return FALSE;
}

BOOL AppEventListener::cleanupStarted()
{
	return FALSE;
}

BOOL AppEventListener::cleanupCompleted()
{
	return FALSE;
}

BOOL AppEventListener::renderStarted()
{
	return FALSE;
}

BOOL AppEventListener::renderCompleted()
{
	return FALSE;
}

BOOL AppEventListener::render()
{
	return FALSE;
}

BOOL AppEventListener::hardkey(HardkeyID key)
{
	return FALSE;
}

BOOL AppEventListener::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
{
	return FALSE;
}

AppService* AppService::getInstance()
{
	static AppService service;
	return &service;
}

void AppService::init(AppServiceParam& param)
{
	// Glut init
	glutInit(&param.argc, param.argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

	m_area = param.windowsArea;
	glutInitWindowPosition(m_area.left, m_area.top);
	glutInitWindowSize(m_area.width(), m_area.height());

	glutCreateWindow(param.windowsTitle);

	// Render
	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(keyBoardFunc);
	glutMouseFunc(mouseFunc);
	glutMotionFunc(motionFunc);
	glutPassiveMotionFunc(passiveMotionFunc);
}

void AppService::addEventListener(AppEventListener* listener)
{
	MAPBAR_INFO_LOG("listener[%p]", listener);
	std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (iter == m_listeners.end())
	{
		m_listeners.push_back(listener);
	}
	else
	{
		MAPBAR_WARNING_LOG("Listener[%p] duplicate.", listener);
	}
}

void AppService::removeEventListener(AppEventListener* listener)
{
	MAPBAR_INFO_LOG("listener[%p]", listener);
	std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (iter != m_listeners.end())
	{
		m_listeners.erase(iter);
	}
	else
	{
		MAPBAR_WARNING_LOG("Listener[%p] not found.", listener);
	}
}

void AppService::run()
{
	// Init started
	VECTOR_NOTIFY(m_listeners, initStarted);

	ObjectManager::getInstance()->init();

	VECTOR_NOTIFY(m_listeners, initCompleted);

	// main loop
	glutMainLoop();

	VECTOR_NOTIFY(m_listeners, cleanupStarted);

	ObjectManager::getInstance()->cleanup();

	VECTOR_NOTIFY(m_listeners, cleanupCompleted);
}

size_t AppService::getWindowsWidth()
{
	return m_area.width();
}

size_t AppService::getWindowsHeight()
{
	return  m_area.height();
}

AppService::AppService()
{
	MAPBAR_TRACE_LOG_START();
}

AppService::~AppService()
{
	MAPBAR_TRACE_LOG_START();
	m_listeners.clear();
}

void drawCNString(const char* str) {
	int len, i;
	wchar_t* wstring;
	HDC hDC = wglGetCurrentDC();
	GLuint list = glGenLists(1);

	// 计算字符的个数
	// 如果是双字节字符的（比如中文字符），两个字节才算一个字符
	// 否则一个字节算一个字符
	len = 0;
	for (i = 0; str[i] != '\0'; ++i)
	{
		if (IsDBCSLeadByte(str[i]))
			++i;
		++len;
	}

	// 将混合字符转化为宽字符
	wstring = (wchar_t*)malloc((len + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len);
	wstring[len] = L'\0';

	// 逐个输出字符
	for (i = 0; i < len; i++) {
		wglUseFontBitmapsW(hDC, wstring[i], 1, list);
		glCallList(list);
	}

	// 回收所有临时资源
	free(wstring);
	glDeleteLists(list, 1);
}

#if 1
#define MAX_CHAR        128

void drawString(const char* str) {
	static int isFirstCall = 1;
	static GLuint lists;

	if( isFirstCall ) { // 如果是第一次调用，执行初始化
		// 为每一个ASCII字符产生一个显示列表
		isFirstCall = 0;

		// 申请MAX_CHAR个连续的显示列表编号
		lists = glGenLists(MAX_CHAR);

		// 把每个字符的绘制命令都装到对应的显示列表中
		wglUseFontBitmaps(wglGetCurrentDC(), 0, MAX_CHAR, lists);
	}
	// 调用每个字符对应的显示列表，绘制每个字符
	for (; *str != '\0'; ++str)
		glCallList(lists + *str);
}
#endif

void AppService::displayFunc()
{
	// Gl environment
	glViewport(0, 0, getInstance()->m_area.width(), getInstance()->m_area.height());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	float width = (float)getInstance()->m_area.width();
	float height = (float)getInstance()->m_area.height();
	
	if (width <= height)
	{
		glOrtho(0, 1.5, 0, 1.5 * height / width, -10.0, 10.0);
	}
	else
	{
		glOrtho(0, 1.5 * width / height, 0, 1.5, -10.0, 10.0);
	}

	// Render
	VECTOR_NOTIFY(getInstance()->m_listeners, renderStarted);

	VECTOR_NOTIFY(getInstance()->m_listeners, render);

	// Object manager draw
	ObjectManager::getInstance()->draw();

	// Render
	VECTOR_NOTIFY(getInstance()->m_listeners, renderCompleted);
	//glClear(GL_COLOR_BUFFER_BIT);

	// Swap buffers
	glutSwapBuffers();
}

void AppService::idleFunc()
{
	glutPostRedisplay();
}

void AppService::keyBoardFunc(int key, int x, int y)
{
	MAPBAR_VERBOSE_LOG("[GLUT] key[%d] x[%d] y[%d]", key, x, y);
	switch (key)
	{
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_RIGHT:
		break;
	}
}

void AppService::mouseFunc(int button, int state, int x, int y)
{
	int32 touchId[TOUCH_POINT_MAX_COUNT] = {0};
	Point touchPos[TOUCH_POINT_MAX_COUNT] = {0};

	touchPos[0].x = x;
	touchPos[0].y = y;
	if (state == GLUT_DOWN)
	{
		MAPBAR_VERBOSE_LOG("[Gesture][TouchType_BEGAN] pos[%d,%d]", x, y);
		VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_BEGAN, 1, touchId, touchPos);
	}
	else if (state == GLUT_UP)
	{
		MAPBAR_VERBOSE_LOG("[Gesture][TouchType_ENDED] pos[%d,%d]", x, y);
		VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_ENDED, 1, touchId, touchPos);
	}
}

void AppService::motionFunc(int x, int y)
{
	int32 touchId[TOUCH_POINT_MAX_COUNT] = {0};
	Point touchPos[TOUCH_POINT_MAX_COUNT] = {0};

	touchPos[0].x = x;
	touchPos[0].y = y;
	MAPBAR_VERBOSE_LOG("[Gesture][TouchType_MOVED] pos[%d,%d]", x, y);
	VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_MOVED, 1, touchId, touchPos);
}

void AppService::passiveMotionFunc(int x, int y)
{
	// MAPBAR_INFO_LOG("[GLUT] x[%d] y[%d]", x, y);
}

}
