#include <GL/glut.h>

void initSnake();

// 初始化OPENGL界面
void initWindows(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5.2, 5.3, -5.3, 5.2, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	// 初始化小蛇的数据
	initSnake();

    return;
}

// 画正方形，用于显示方块。指定方块左上角的坐标和颜色
void displaySquare(GLfloat x, GLfloat y, GLfloat red, GLfloat green, GLfloat blue)
{
	glBegin(GL_QUADS);

	glColor3f(red, green, blue);
	glVertex2f(x,y);
	glVertex2f(x + 0.1, y);
	glVertex2f(x + 0.1, y - 0.1);
	glVertex2f(x, y - 0.1);

	glEnd();
}

// 表示边框的函数
void displayBorder(void)
{
	// 上
	for (GLfloat x = -5; x <= 5; x = x + 0.1)
	{
		displaySquare(x, 5, 1.0f, 0.0f, 0.0f);
	}

	// 下
	for (GLfloat x = -5; x <= 5; x = x + 0.1)
	{
		displaySquare(x, -5, 1.0f, 0.0f, 0.0f);
	}

	// 左
	for (GLfloat y = -5; y <= 5; y = y + 0.1)
	{
		displaySquare(5, y, 1.0f, 0.0f, 0.0f);
	}

	// 右
	for (GLfloat y = -5; y <= 5; y = y + 0.1)
	{
		displaySquare(-5, y, 1.0f, 0.0f, 0.0f);
	}
}

// 方向的枚举
enum eDirection
{
	eDirectionUp,
	eDirectionDown,
	eDirectionLeft,
	eDirectionRight
};

// 位置的结构体
struct stPosition
{
	GLfloat x;
	GLfloat y;
};

// 小蛇的身体
#define SNAKE_INIT_LEN 3
#define SNAKE_MAX_LEN 200
int snakeMaxCount = SNAKE_INIT_LEN;
stPosition snakeBody[SNAKE_MAX_LEN]; 

// 初始化小蛇
void initSnake(void)
{
	snakeMaxCount = SNAKE_INIT_LEN;
	snakeBody[0].x = 0;
	snakeBody[0].y = 0;
	snakeBody[1].x = 0;
	snakeBody[1].y = -0.1f;
	snakeBody[2].x = 0;
	snakeBody[2].y = -0.2f;
}

eDirection nextDirection = eDirectionUp;
bool isValidSetDirection = true;

// 显示一条小蛇。指定小蛇的下一个位置
void moveSnake(eDirection dir)
{
	GLfloat nextPositionX = 0.0f;
	GLfloat nextPositionY = 0.0f;

	isValidSetDirection = true;

	// 判断当前的方向
	switch (dir)
	{
	case eDirectionUp:
		nextPositionY = 0.1f;
		break;
	case eDirectionDown:
		nextPositionY = -0.1f;
		break;
	case eDirectionLeft:
		nextPositionX = -0.1f;
		break;
	case eDirectionRight:
		nextPositionX = 0.1f;
		break;
	}

	// 移动当前的数据
	for (int i = snakeMaxCount - 1; i > 0; --i)
	{
		snakeBody[i].x = snakeBody[i - 1].x;
		snakeBody[i].y = snakeBody[i - 1].y;
	}

	// 设置头部的位置
	snakeBody[0].x += nextPositionX;
	snakeBody[0].y += nextPositionY;
}

void displaySnake(void)
{
	for (int i = 0; i < snakeMaxCount; ++i)
	{
		displaySquare(snakeBody[i].x, snakeBody[i].y, 0.0f, 1.0f, 0.0f);
	}
}

void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0, 0);
    
	// 展示游戏的边框
	displayBorder();

	// 显示一条小蛇
	displaySnake();

	// 交换两个缓存
	glutSwapBuffers();

    glFlush();

    return;
}

void idleFunc(void)
{
	static int count = 0;
	count++;

	if (count > 20)
	{
		// 移动小蛇
		moveSnake(nextDirection);
		count = 0;
	}
	
	displayFunc();
}

// 通过键盘设定方向
void keySetNextPosition(eDirection dir)
{
	// 如果之前设定的方向没有被描画，则不能更换方向
	if (!isValidSetDirection)
	{
		return;
	}

	// 小蛇不能因为键盘而反向运动
	if ((dir == eDirectionUp && nextDirection == eDirectionDown) ||
		(dir == eDirectionDown && nextDirection == eDirectionUp) ||
		(dir == eDirectionLeft && nextDirection == eDirectionRight) ||
		(dir == eDirectionRight && nextDirection == eDirectionLeft))
	{
		return;
	}
	nextDirection = dir;
	isValidSetDirection = false;
}

// 键盘处理函数
void keyBoardFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		keySetNextPosition(eDirectionUp);
		break;
	case GLUT_KEY_DOWN:
		keySetNextPosition(eDirectionDown);
		break;
	case GLUT_KEY_LEFT:
		keySetNextPosition(eDirectionLeft);
		break;
	case GLUT_KEY_RIGHT:
		keySetNextPosition(eDirectionRight);
		break;
	}
}

// 入场函数
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
	//glutKeyboardFunc(keyBoardFunc);
	glutSpecialFunc(keyBoardFunc);

	// 主循环
    glutMainLoop();

    return 0;
}
