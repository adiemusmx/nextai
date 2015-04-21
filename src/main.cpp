#include <GL/glut.h>

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5, 5, -5, 5, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    return;
}

void displayBorder(void)
{
	glBegin(GL_LINE_LOOP);

	glVertex2f(4.8f,4.8f);
	glVertex2f(4.8f,-4.8f);
	glVertex2f(-4.8f,-4.8f);
	glVertex2f(-4.8f,4.8f);

	glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0, 0);
    
	// 展示游戏的边框
	displayBorder();

    glFlush();

    return;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(480, 480);
    glutCreateWindow("OpenGL Game - Snake");
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
