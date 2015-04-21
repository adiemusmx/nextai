#include <GL/glut.h>

void initSnake();

// ��ʼ��OPENGL����
void initWindows(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-5.2, 5.3, -5.3, 5.2, 5, 15);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	// ��ʼ��С�ߵ�����
	initSnake();

    return;
}

// �������Σ�������ʾ���顣ָ���������Ͻǵ��������ɫ
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

// ��ʾ�߿�ĺ���
void displayBorder(void)
{
	// ��
	for (GLfloat x = -5; x <= 5; x = x + 0.1)
	{
		displaySquare(x, 5, 1.0f, 0.0f, 0.0f);
	}

	// ��
	for (GLfloat x = -5; x <= 5; x = x + 0.1)
	{
		displaySquare(x, -5, 1.0f, 0.0f, 0.0f);
	}

	// ��
	for (GLfloat y = -5; y <= 5; y = y + 0.1)
	{
		displaySquare(5, y, 1.0f, 0.0f, 0.0f);
	}

	// ��
	for (GLfloat y = -5; y <= 5; y = y + 0.1)
	{
		displaySquare(-5, y, 1.0f, 0.0f, 0.0f);
	}
}

// �����ö��
enum eDirection
{
	eDirectionUp,
	eDirectionDown,
	eDirectionLeft,
	eDirectionRight
};

// λ�õĽṹ��
struct stPosition
{
	GLfloat x;
	GLfloat y;
};

// С�ߵ�����
#define SNAKE_INIT_LEN 3
#define SNAKE_MAX_LEN 200
int snakeMaxCount = SNAKE_INIT_LEN;
stPosition snakeBody[SNAKE_MAX_LEN]; 

// ��ʼ��С��
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

// ��ʾһ��С�ߡ�ָ��С�ߵ���һ��λ��
void moveSnake(eDirection dir)
{
	GLfloat nextPositionX = 0.0f;
	GLfloat nextPositionY = 0.0f;

	isValidSetDirection = true;

	// �жϵ�ǰ�ķ���
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

	// �ƶ���ǰ������
	for (int i = snakeMaxCount - 1; i > 0; --i)
	{
		snakeBody[i].x = snakeBody[i - 1].x;
		snakeBody[i].y = snakeBody[i - 1].y;
	}

	// ����ͷ����λ��
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
    
	// չʾ��Ϸ�ı߿�
	displayBorder();

	// ��ʾһ��С��
	displaySnake();

	// ������������
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

	// С�߲�����Ϊ���̶������˶�
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
	//glutKeyboardFunc(keyBoardFunc);
	glutSpecialFunc(keyBoardFunc);

	// ��ѭ��
    glutMainLoop();

    return 0;
}
