#include "trinity_app_service.h"
#include "GL/glut.h"
#include "trinity_message_center.h"
#include "trinity_widget_picture.h"
#include "trinity_object_manager.h"
#include "trinity_util_log.h"
#include <algorithm>

#define VECTOR_NOTIFY(listeners, func,...)	\
	for (size_t loopIdx = 0; loopIdx < listeners.size(); ++loopIdx) \
		if (listeners[loopIdx]->func(__VA_ARGS__)) break;\

namespace Trinity {

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
	glutInitWindowSize(RECT_getWidth(m_area), RECT_getHeight(m_area));

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
	TRI_INFO_LOG("listener[%p]", listener);
	std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (iter == m_listeners.end())
	{
		m_listeners.push_back(listener);
	}
	else
	{
		TRI_WARNING_LOG("Listener[%p] duplicate.", listener);
	}
}

void AppService::removeEventListener(AppEventListener* listener)
{
	TRI_INFO_LOG("listener[%p]", listener);
	std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (iter != m_listeners.end())
	{
		m_listeners.erase(iter);
	}
	else
	{
		TRI_WARNING_LOG("Listener[%p] not found.", listener);
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

AppService::AppService()
{
	TRI_TRACE_LOG();
}

AppService::~AppService()
{
	TRI_TRACE_LOG();
	m_listeners.clear();
}

void AppService::displayFunc()
{
	// Gl environment
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0, RECT_getWidth(getInstance()->m_area), RECT_getHeight(getInstance()->m_area), 0.0, -1.0, 1.0);

	// Render
	VECTOR_NOTIFY(getInstance()->m_listeners, renderStarted);

	// Object manager draw
	ObjectManager::getInstance()->draw();

	// Render
	VECTOR_NOTIFY(getInstance()->m_listeners, renderCompleted);

	// Swap buffers
	glutSwapBuffers();
}

void AppService::idleFunc()
{
	glutPostRedisplay();
}

void AppService::keyBoardFunc(int key, int x, int y)
{
	TRI_INFO_LOG("[GLUT] key[%d] x[%d] y[%d]", key, x, y);
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
		TRI_INFO_LOG("[Gesture][TouchType_BEGAN] pos[%d,%d]", x, y);
		VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_BEGAN, 1, touchId, touchPos);
	}
	else if (state == GLUT_UP)
	{
		TRI_INFO_LOG("[Gesture][TouchType_ENDED] pos[%d,%d]", x, y);
		VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_ENDED, 1, touchId, touchPos);
	}
}

void AppService::motionFunc(int x, int y)
{
	int32 touchId[TOUCH_POINT_MAX_COUNT] = {0};
	Point touchPos[TOUCH_POINT_MAX_COUNT] = {0};

	touchPos[0].x = x;
	touchPos[0].y = y;
	TRI_INFO_LOG("[Gesture][TouchType_MOVED] pos[%d,%d]", x, y);
	VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_MOVED, 1, touchId, touchPos);
}

void AppService::passiveMotionFunc(int x, int y)
{
	// TRI_INFO_LOG("[GLUT] x[%d] y[%d]", x, y);
}

}
