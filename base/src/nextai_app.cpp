#include "base/nextai_app.h"
#include "base/nextai_message.h"
#include "base/nextai_log.h"

#include <GL/glut.h>
#include <GL/glu.h>
#include <algorithm>

#define VECTOR_NOTIFY(listeners, func,...)	\
	for (size_t loopIdx = 0; loopIdx < listeners.size(); ++loopIdx) \
		if (listeners[loopIdx]->func(__VA_ARGS__)) break;\

namespace NextAI {

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

	/* Ortho */
	m_ortho.m_left = -1.5f;
	m_ortho.m_right = -1.5f;
	m_ortho.m_near = -10.0f;
	m_ortho.m_far = 10.0f;
	if (m_area.width() <= m_area.height())
	{
		m_ortho.m_bottom = -1.5f * (float)m_area.height() / (float)m_area.width();
		m_ortho.m_top = 1.5 * (float)m_area.height() / (float)m_area.width();
	}
	else
	{
		m_ortho.m_bottom = -1.5f * (float)m_area.width() / (float)m_area.height();
		m_ortho.m_top = 1.5f * (float)m_area.width() / (float)m_area.height();
	}

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
	nextai_INFO_LOG("listener[%p]", listener);
	std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (iter == m_listeners.end())
	{
		m_listeners.push_back(listener);
	}
	else
	{
		nextai_WARNING_LOG("Listener[%p] duplicate.", listener);
	}
}

void AppService::removeEventListener(AppEventListener* listener)
{
	nextai_INFO_LOG("listener[%p]", listener);
	std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (iter != m_listeners.end())
	{
		m_listeners.erase(iter);
	}
	else
	{
		nextai_WARNING_LOG("Listener[%p] not found.", listener);
	}
}

void AppService::run()
{
	// Init started
	VECTOR_NOTIFY(m_listeners, initStarted);

	//ObjectManager::getInstance()->init();

	VECTOR_NOTIFY(m_listeners, initCompleted);

	// main loop
	glutMainLoop();

	VECTOR_NOTIFY(m_listeners, cleanupStarted);

	//ObjectManager::getInstance()->cleanup();

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

Vector<float> AppService::pos2ortho(const ScreenPoint& p)
{
	Vector<float> ret;
	ret.x = (m_ortho.m_right - m_ortho.m_left) * p.x / m_area.width() + m_ortho.m_left;
	ret.y = (m_ortho.m_top - m_ortho.m_bottom) * (m_area.height() - p.y) / m_area.height() + m_ortho.m_bottom;
	return ret;
}

ScreenPoint AppService::ortho2pos(const Vector<float>& r)
{
	ScreenPoint ret;
	ret.x = (r.x - m_ortho.m_left) * m_area.width() / (m_ortho.m_right - m_ortho.m_left);
	ret.y = m_area.height() - (r.y - m_ortho.m_bottom) * m_area.height() / (m_ortho.m_top - m_ortho.m_bottom);
	return ret;
}

AppService::AppService()
{
	nextai_TRACE_LOG_START();
}

AppService::~AppService()
{
	nextai_TRACE_LOG_START();
	m_listeners.clear();
}

void AppService::displayFunc()
{
	AppService* instance = getInstance();
	
	// Gl environment
	GLint width = instance->m_area.width();
	GLint height = instance->m_area.height();
	glViewport(0, 0, width, height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glOrtho(instance->m_ortho.m_left, instance->m_ortho.m_right, 
		instance->m_ortho.m_bottom, instance->m_ortho.m_top, 
		instance->m_ortho.m_near, instance->m_ortho.m_far);

	// Render
	VECTOR_NOTIFY(getInstance()->m_listeners, renderStarted);

	VECTOR_NOTIFY(getInstance()->m_listeners, render);

	// Object manager draw
	// ObjectManager::getInstance()->draw();

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
	nextai_VERBOSE_LOG("[GLUT] key[%d] x[%d] y[%d]", key, x, y);
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
		nextai_VERBOSE_LOG("[Gesture][TouchType_BEGAN] pos[%d,%d]", x, y);
		VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_BEGAN, 1, touchId, touchPos);
	}
	else if (state == GLUT_UP)
	{
		nextai_VERBOSE_LOG("[Gesture][TouchType_ENDED] pos[%d,%d]", x, y);
		VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_ENDED, 1, touchId, touchPos);
	}
}

void AppService::motionFunc(int x, int y)
{
	int32 touchId[TOUCH_POINT_MAX_COUNT] = {0};
	Point touchPos[TOUCH_POINT_MAX_COUNT] = {0};

	touchPos[0].x = x;
	touchPos[0].y = y;
	nextai_VERBOSE_LOG("[Gesture][TouchType_MOVED] pos[%d,%d]", x, y);
	VECTOR_NOTIFY(getInstance()->m_listeners, touch, TouchType_MOVED, 1, touchId, touchPos);
}

void AppService::passiveMotionFunc(int x, int y)
{
	// nextai_INFO_LOG("[GLUT] x[%d] y[%d]", x, y);
}

}
