#include "define.h"
#include <time.h>
#include <stdlib.h>

// 初始化OPENGL界面
void initWindows(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-52, 53, -53, 52, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	// 初始化小蛇的数据
	initSnake();

    return;
}

// 画正方形，用于显示方块。指定方块左上角的坐标和颜色
void displaySquare(GLint x, GLint y, GLint red, GLint green, GLint blue)
{
	glBegin(GL_QUADS);

	glColor3f(red, green, blue);
	glVertex2f(x,y);
	glVertex2f(x + SQUARE_LENGTH, y);
	glVertex2f(x + SQUARE_LENGTH, y - SQUARE_LENGTH);
	glVertex2f(x, y - SQUARE_LENGTH);

	glEnd();
}

// 表示边框的函数
void displayBorder(void)
{
	// 默认是红色的块
	GLint red = 1;
	GLint green = 0;
	GLint blue = 0;

	// 上
	for (GLint x = BORDER_LEFT; x <= BORDER_RIGHT; x = x + SQUARE_LENGTH)
	{
		displaySquare(x, BORDER_UP, red, green, blue);
	}

	// 下
	for (GLint x = BORDER_LEFT; x <= BORDER_RIGHT; x = x + SQUARE_LENGTH)
	{
		displaySquare(x, BORDER_DOWN, red, green, blue);
	}

	// 左
	for (GLint y = BORDER_DOWN; y <= BORDER_UP; y = y + SQUARE_LENGTH)
	{
		displaySquare(BORDER_LEFT, y, red, green, blue);
	}

	// 右
	for (GLint y = BORDER_DOWN; y <= BORDER_UP; y = y + SQUARE_LENGTH)
	{
		displaySquare(BORDER_RIGHT, y, red, green, blue);
	}
}

// 判断是否是边界
bool isBorder(GLint x, GLint y)
{
	if (x <= BORDER_LEFT || x >= BORDER_RIGHT || y <= BORDER_DOWN || y >= BORDER_UP)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 初始化小蛇
void initSnake(void)
{
	isRunning = true;
	foodPosition = randomFood();

	snakeLen = SNAKE_INIT_LEN;
	snakeBody[0].x = 0;
	snakeBody[0].y = 0;
	snakeBody[1].x = 0;
	snakeBody[1].y = -1 * SQUARE_LENGTH;
	snakeBody[2].x = 0;
	snakeBody[2].y = -2 * SQUARE_LENGTH;
}

// 是否是小蛇的范围
bool isSnake(GLint x, GLint y)
{
	for (int i = 0; i < snakeLen; ++i)
	{
		if (snakeBody[i].x == x && snakeBody[i].y == y)
		{
			return true;
		}
	}
	return false;
}

// 显示一条小蛇。指定小蛇的下一个位置
void moveSnake(eDirection dir)
{
	GLint nextPositionX = snakeBody[0].x;
	GLint nextPositionY = snakeBody[0].y;

	isValidSetDirection = true;

	// 判断当前的方向
	switch (dir)
	{
	case eDirectionUp:
		nextPositionY += SQUARE_LENGTH;
		break;
	case eDirectionDown:
		nextPositionY += -SQUARE_LENGTH;
		break;
	case eDirectionLeft:
		nextPositionX += -SQUARE_LENGTH;
		break;
	case eDirectionRight:
		nextPositionX += SQUARE_LENGTH;
		break;
	}

	// 如果是食物，则吃掉
	if (isFood(nextPositionX, nextPositionY))
	{
		eatFood(nextPositionX, nextPositionY);
	}
	// 如果是墙壁或者蛇本体，则推出
	else if (isBorder(nextPositionX, nextPositionY) ||
		isSnake(nextPositionX, nextPositionY))
	{
		isRunning = false;
		return;
	}

	// 移动当前的数据
	for (int i = snakeLen - 1; i > 0; --i)
	{
		snakeBody[i].x = snakeBody[i - 1].x;
		snakeBody[i].y = snakeBody[i - 1].y;
	}

	// 设置头部的位置
	snakeBody[0].x = nextPositionX;
	snakeBody[0].y = nextPositionY;
}

// 表示小蛇的身体
void displaySnake(void)
{
	// 默认是绿色的块
	GLint red = 0;
	GLint green = 1;
	GLint blue = 0;
	for (int i = 0; i < snakeLen; ++i)
	{
		displaySquare(snakeBody[i].x, snakeBody[i].y, red, green, blue);
	}
}

void displayFood(void)
{
	// 默认是绿色的块
	GLint red = 0;
	GLint green = 1;
	GLint blue = 0;
	displaySquare(foodPosition.x, foodPosition.y, red, green, blue);
}

// 显示主函数
void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0, 0);
    
	// 展示游戏的边框
	displayBorder();

	// 显示一条小蛇
	displaySnake();
	
	// 显示食物
	displayFood();

	// 交换两个缓存
	glutSwapBuffers();

    glFlush();

    return;
}

// 空闲控制函数
void idleFunc(void)
{
	static int count = 0;
	count++;

	if (count > 5)
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

	// 小蛇不能因为键盘而反向运动（有可能之后存在反向道具）
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

// 判断当前位置是不是食物
bool isFood(GLint x, GLint y)
{
	if (x == foodPosition.x && y == foodPosition.y)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// 随机一个食物的位置
stPosition randomFood(void)
{
	stPosition randomPos;
	while (true)
	{
		// 随机数，从边界到边界
		randomPos.x = ((rand() % ((BORDER_RIGHT - BORDER_LEFT - 1) * 10) + 1) / 10.0f) + BORDER_LEFT;
		randomPos.y = ((rand() % ((BORDER_UP - BORDER_DOWN - 1) * 10) + 1) / 10.0f) + BORDER_DOWN;

		// 判断当前的位置是否存在食物，或者是否是蛇的身体
		if (isFood(randomPos.x, randomPos.y) || isSnake(randomPos.x, randomPos.y))
		{
			continue;
		}
		else
		{
			break;
		}
	}
	return randomPos;
}

// 吃掉一个食物
void eatFood(GLint x, GLint y)
{
	// 判断当前的小蛇是否已经超过了最大的长度
	if (snakeLen == SNAKE_MAX_LEN)
	{
		isRunning = false;
	}
	
	++snakeLen;

	// 移动当前的数据
	for (int i = snakeLen - 1; i > 0; --i)
	{
		snakeBody[i].x = snakeBody[i - 1].x;
		snakeBody[i].y = snakeBody[i - 1].y;
	}

	// 设置头部的位置
	snakeBody[0].x = x;
	snakeBody[0].y = y;

	foodPosition = randomFood();
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
	glutSpecialFunc(keyBoardFunc);

	// 主循环
    glutMainLoop();

    return 0;
}
