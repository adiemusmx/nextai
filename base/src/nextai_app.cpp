#include "stdafx.h"
#include "base/nextai_app.h"
#include "base/nextai_message.h"
#include "base/nextai_file_system.h"

#include <GL/glut.h>
#include <GL/glu.h>

#define VECTOR_NOTIFY(listeners, func,...)	\
	for (size_t loopIdx = 0; loopIdx < listeners.size(); ++loopIdx) \
	if (listeners[loopIdx]->func(__VA_ARGS__) == ListenerResult::BLOCK_OTHERS) break; \

namespace NextAI {

	ListenerResult AppEventListener::initStarted()
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::initCompleted()
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::cleanupStarted()
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::cleanupCompleted()
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::renderStarted()
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::renderCompleted()
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::render()
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::hardkey(HardkeyID key)
	{
		return ListenerResult::OK;
	}

	ListenerResult AppEventListener::touch(TouchType touch, int32 touchCount, const int32 touchId[], const Point touchPos[])
	{
		return ListenerResult::OK;
	}

	AppService* AppService::instance()
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

		std::wstring path = FileSystem::getCurrentDirectory();
		NEXTAI_TRACE_LOG("BASE", "App workspace[{}]", path);

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
		NEXTAI_TRACE_LOG("BASE", "listener[{}]", (void*)listener);
		std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
		if (iter == m_listeners.end())
		{
			m_listeners.push_back(listener);
		}
		else
		{
			NEXTAI_WARN_LOG("BASE", "Listener[{}] duplicate.", (void*)listener);
		}
	}

	void AppService::removeEventListener(AppEventListener* listener)
	{
		NEXTAI_TRACE_LOG("BASE", "listener[{}]", (void*)listener);
		std::vector<AppEventListener*>::iterator iter = std::find(m_listeners.begin(), m_listeners.end(), listener);
		if (iter != m_listeners.end())
		{
			m_listeners.erase(iter);
		}
		else
		{
			NEXTAI_WARN_LOG("BASE", "Listener[{}] not found.", (void*)listener);
		}
	}

	void AppService::run()
	{
		// Init started
		VECTOR_NOTIFY(m_listeners, initStarted);

		//ObjectManager::instance()->init();

		VECTOR_NOTIFY(m_listeners, initCompleted);

		// main loop
		glutMainLoop();

		VECTOR_NOTIFY(m_listeners, cleanupStarted);

		//ObjectManager::instance()->cleanup();

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

	void SpdLogInitial();
	AppService::AppService()
	{
		// Log
		SpdLogInitial();

		NEXTAI_TRACE_FUNC("BASE");
	}

	AppService::~AppService()
	{
		NEXTAI_TRACE_FUNC("BASE");
		m_listeners.clear();
	}

	void AppService::displayFunc()
	{
		AppService* instance = AppService::instance();
	
		// Gl environment
		GLint width = instance->m_area.width();
		GLint height = instance->m_area.height();
		glViewport(0, 0, width, height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
	#if 1
		glOrtho(0.0, AppService::instance()->m_area.width(), AppService::instance()->m_area.height(), 0.0, -1.0, 1.0);
	#else
		glOrtho(instance->m_ortho.m_left, instance->m_ortho.m_right, 
			instance->m_ortho.m_bottom, instance->m_ortho.m_top, 
			instance->m_ortho.m_near, instance->m_ortho.m_far);
	#endif

		// Render
		VECTOR_NOTIFY(AppService::instance()->m_listeners, renderStarted);
		VECTOR_NOTIFY(AppService::instance()->m_listeners, render);
		VECTOR_NOTIFY(AppService::instance()->m_listeners, renderCompleted);

		// Swap buffers
		glutSwapBuffers();
	}

	void AppService::idleFunc()
	{
		glutPostRedisplay();
	}

	void AppService::keyBoardFunc(int key, int x, int y)
	{
		NEXTAI_TRACE_LOG("BASE", "GLUT key[{}] pos[{},{}]", key, x, y);
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
			NEXTAI_TRACE_LOG("BASE", "[Gesture][TouchType_BEGAN] pos[{},{}]", x, y);
			VECTOR_NOTIFY(instance()->m_listeners, touch, TouchType_BEGAN, 1, touchId, touchPos);
		}
		else if (state == GLUT_UP)
		{
			NEXTAI_TRACE_LOG("BASE", "[Gesture][TouchType_ENDED] pos[{},{}]", x, y);
			VECTOR_NOTIFY(instance()->m_listeners, touch, TouchType_ENDED, 1, touchId, touchPos);
		}
	}

	void AppService::motionFunc(int x, int y)
	{
		int32 touchId[TOUCH_POINT_MAX_COUNT] = {0};
		Point touchPos[TOUCH_POINT_MAX_COUNT] = {0};

		touchPos[0].x = x;
		touchPos[0].y = y;
		NEXTAI_TRACE_LOG("BASE", "[Gesture][TouchType_MOVED] pos[{},{}]", x, y);
		VECTOR_NOTIFY(instance()->m_listeners, touch, TouchType_MOVED, 1, touchId, touchPos);
	}

	void AppService::passiveMotionFunc(int x, int y)
	{
		// NEXTAI_INFO_LOG("[GLUT] x[%d] y[%d]", x, y);
	}

}
