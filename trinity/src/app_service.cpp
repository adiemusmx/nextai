#include "app_service.h"
#include "GL/glut.h"
#include "message_center.h"
#include "widget_picture.h"
#include "object_manager.h"

namespace Trinity {

AppService* AppService::getInstance()
{
	static AppService service;
	return &service;
}
//GL_Picture* pic;
void AppService::init(AppServiceParam& param)
{
	glutInitWindowPosition(param.windowsArea.left, param.windowsArea.top);
	glutInitWindowSize(RECT_getWidth(param.windowsArea), RECT_getHeight(param.windowsArea));
	glutInit(&param.argc, param.argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow(param.windowsTitle);

	// 描画
	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(keyBoardFunc);

	//pic = new GL_Picture(NULL);
	//pic->setPicturePath("../res/background.bmp");
}

void AppService::mainLoop()
{
	glutMainLoop();
}

AppService::AppService()
{
}


// 显示主函数
void AppService::displayFunc()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0, 480, 480, 0.0, -1.0, 1.0);

	// Draw
	ObjectManager::getInstance()->draw();

	// 交换两个缓存
	glutSwapBuffers();
}

// 空闲控制函数
void AppService::idleFunc()
{
	glutPostRedisplay();
}

// 键盘处理函数
void AppService::keyBoardFunc(int key, int x, int y)
{
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
}
