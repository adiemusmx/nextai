#include "define.h"
#include <time.h>
#include <stdlib.h>

// ��ʼ��OPENGL����
void initWindows(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-52, 53, -53, 52, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	// ��ʼ��С�ߵ�����
	initSnake();

    return;
}

// �������Σ�������ʾ���顣ָ���������Ͻǵ��������ɫ
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

// ��ʾ�߿�ĺ���
void displayBorder(void)
{
	// Ĭ���Ǻ�ɫ�Ŀ�
	GLint red = 1;
	GLint green = 0;
	GLint blue = 0;

	// ��
	for (GLint x = BORDER_LEFT; x <= BORDER_RIGHT; x = x + SQUARE_LENGTH)
	{
		displaySquare(x, BORDER_UP, red, green, blue);
	}

	// ��
	for (GLint x = BORDER_LEFT; x <= BORDER_RIGHT; x = x + SQUARE_LENGTH)
	{
		displaySquare(x, BORDER_DOWN, red, green, blue);
	}

	// ��
	for (GLint y = BORDER_DOWN; y <= BORDER_UP; y = y + SQUARE_LENGTH)
	{
		displaySquare(BORDER_LEFT, y, red, green, blue);
	}

	// ��
	for (GLint y = BORDER_DOWN; y <= BORDER_UP; y = y + SQUARE_LENGTH)
	{
		displaySquare(BORDER_RIGHT, y, red, green, blue);
	}
}

// �ж��Ƿ��Ǳ߽�
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

// ��ʼ��С��
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

// �Ƿ���С�ߵķ�Χ
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

// ��ʾһ��С�ߡ�ָ��С�ߵ���һ��λ��
void moveSnake(eDirection dir)
{
	GLint nextPositionX = snakeBody[0].x;
	GLint nextPositionY = snakeBody[0].y;

	isValidSetDirection = true;

	// �жϵ�ǰ�ķ���
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

	// �����ʳ���Ե�
	if (isFood(nextPositionX, nextPositionY))
	{
		eatFood(nextPositionX, nextPositionY);
	}
	// �����ǽ�ڻ����߱��壬���Ƴ�
	else if (isBorder(nextPositionX, nextPositionY) ||
		isSnake(nextPositionX, nextPositionY))
	{
		isRunning = false;
		return;
	}

	// �ƶ���ǰ������
	for (int i = snakeLen - 1; i > 0; --i)
	{
		snakeBody[i].x = snakeBody[i - 1].x;
		snakeBody[i].y = snakeBody[i - 1].y;
	}

	// ����ͷ����λ��
	snakeBody[0].x = nextPositionX;
	snakeBody[0].y = nextPositionY;
}

// ��ʾС�ߵ�����
void displaySnake(void)
{
	// Ĭ������ɫ�Ŀ�
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
	// Ĭ������ɫ�Ŀ�
	GLint red = 0;
	GLint green = 1;
	GLint blue = 0;
	displaySquare(foodPosition.x, foodPosition.y, red, green, blue);
}

// ��ʾ������
void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0, 0);
    
	// չʾ��Ϸ�ı߿�
	displayBorder();

	// ��ʾһ��С��
	displaySnake();
	
	// ��ʾʳ��
	displayFood();

	// ������������
	glutSwapBuffers();

    glFlush();

    return;
}

// ���п��ƺ���
void idleFunc(void)
{
	static int count = 0;
	count++;

	if (count > 5)
	{
		// �ƶ�С��
		moveSnake(nextDirection);
		count = 0;
	}
	
	displayFunc();
}

// ͨ�������趨����
void keySetNextPosition(eDirection dir)
{
	// ���֮ǰ�趨�ķ���û�б��軭�����ܸ�������
	if (!isValidSetDirection)
	{
		return;
	}

	// С�߲�����Ϊ���̶������˶����п���֮����ڷ�����ߣ�
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

// ���̴�����
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

// �жϵ�ǰλ���ǲ���ʳ��
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

// ���һ��ʳ���λ��
stPosition randomFood(void)
{
	stPosition randomPos;
	while (true)
	{
		// ��������ӱ߽絽�߽�
		randomPos.x = ((rand() % ((BORDER_RIGHT - BORDER_LEFT - 1) * 10) + 1) / 10.0f) + BORDER_LEFT;
		randomPos.y = ((rand() % ((BORDER_UP - BORDER_DOWN - 1) * 10) + 1) / 10.0f) + BORDER_DOWN;

		// �жϵ�ǰ��λ���Ƿ����ʳ������Ƿ����ߵ�����
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

// �Ե�һ��ʳ��
void eatFood(GLint x, GLint y)
{
	// �жϵ�ǰ��С���Ƿ��Ѿ����������ĳ���
	if (snakeLen == SNAKE_MAX_LEN)
	{
		isRunning = false;
	}
	
	++snakeLen;

	// �ƶ���ǰ������
	for (int i = snakeLen - 1; i > 0; --i)
	{
		snakeBody[i].x = snakeBody[i - 1].x;
		snakeBody[i].y = snakeBody[i - 1].y;
	}

	// ����ͷ����λ��
	snakeBody[0].x = x;
	snakeBody[0].y = y;

	foodPosition = randomFood();
}

// �볡����
int main(int argc, char *argv[])
{
	// ��ʼ��glut
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(480, 480);
    glutCreateWindow("OpenGL Game - Snake");
    
	// ��ʼ��
	initWindows();

	// �軭
    glutDisplayFunc(displayFunc);
	glutIdleFunc(idleFunc);
	glutSpecialFunc(keyBoardFunc);

	// ��ѭ��
    glutMainLoop();

    return 0;
}
