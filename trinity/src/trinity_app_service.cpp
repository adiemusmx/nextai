﻿#include "trinity_app_service.h"
#include "GL/glut.h"
#include "trinity_message_center.h"
#include "trinity_widget_picture.h"
#include "trinity_object_manager.h"
#include "trinity_util_log.h"
#include <algorithm>

namespace Trinity
{

AppService* AppService::getInstance()
{
	static AppService service;
	return &service;
}

void AppService::init(AppServiceParam& param)
{
	glutInitWindowPosition(param.windowsArea.left, param.windowsArea.top);
	glutInitWindowSize(RECT_getWidth(param.windowsArea), RECT_getHeight(param.windowsArea));
	glutInit(&param.argc, param.argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(param.windowsTitle);

	// Render
	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(keyBoardFunc);
	glutMouseFunc(mouseFunc);
}

void AppService::addEventListener(AppEventListener* listener)
{
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
	std::vector<AppEventListener*> startTmp = m_listeners;
	std::for_each(startTmp.begin(), startTmp.end(), [&](auto p)
	{
		p->initStarted();
	});

	// Init completed
	std::vector<AppEventListener*> completeTmp = m_listeners;
	std::for_each(completeTmp.begin(), completeTmp.end(), [&](auto p)
	{
		p->initCompleted();
	});

	// main loop
	glutMainLoop();
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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0, 480, 480, 0.0, -1.0, 1.0);

	// Draw
	ObjectManager::getInstance()->draw();

	// Swap buffers
	glutSwapBuffers();
}

void AppService::idleFunc()
{
	glutPostRedisplay();
}

void AppService::keyBoardFunc(int key, int x, int y)
{
	TRI_INFO_LOG("[ORIGIN] key[%d] x[%d] y[%d]", key, x, y);
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
	TRI_INFO_LOG("[ORIGIN] button[%d] state[%d] x[%d] y[%d]", button, state, x, y);
}

}