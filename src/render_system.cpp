#include "render_system.h"

#include "GL/glut.h"
#include "message_center.h"
#include "gl_picture.h"

namespace Trinity {

	RenderSystem* RenderSystem::getInstance()
	{
		static RenderSystem render;
		return &render;
	}
	GL_Picture* pic;
	void RenderSystem::init(int* argc, char *argv[])
	{
		glutInitWindowPosition(SCREEN_AREA_LEFT, SCREEN_AREA_TOP);
		glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
		glutInit(argc, argv);
		glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
		glutCreateWindow("Trinity - sample");

		// 描画
		glutDisplayFunc(displayFunc);
		glutIdleFunc(idleFunc);
		glutSpecialFunc(keyBoardFunc);

		pic = new GL_Picture(NULL);
		pic->setPicturePath("../res/background.bmp");
	}

	void RenderSystem::mainLoop()
	{
		glutMainLoop();
	}

	RenderSystem::RenderSystem()
	{
	}

	
	// 显示主函数
	void RenderSystem::displayFunc(void)
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glOrtho(0.0, 480, 480, 0.0, -1.0, 1.0);

		RenderSystem::getInstance()->draw();

		// 交换两个缓存
		glutSwapBuffers();
	}

	// 空闲控制函数
	void RenderSystem::idleFunc(void)
	{
		glutPostRedisplay();
	}

	// 键盘处理函数
	void RenderSystem::keyBoardFunc(int key, int x, int y)
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

	void RenderSystem::draw()
	{
		pic->Draw();
	}
}
