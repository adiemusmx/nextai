// Trinity.cpp : 定义控制台应用程序的入口点。
#include "log.h"
#include "render_system.h"

// 初始化OPENGL界面
void initWindows(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-52, 53, -53, 52, 5, 15);
	glMatrixMode(GL_MODELVIEW);
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	return;
}

int main(int argc, char *argv[])
{
	// 初始化glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(480, 480);
	glutCreateWindow("OpenGL Game - Snake");

	// 初始化
	initWindows();

	// 描画
	glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(keyBoardFunc);

	// 主循环
	glutMainLoop();

	return 0;
}