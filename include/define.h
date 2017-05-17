#include <windows.h>
#include <GL/glut.h>

// λ�õĽṹ��
struct stPosition
{
	GLint x;
	GLint y;
};

// ��¼ʳ���λ��
stPosition foodPosition;

// �жϵ�ǰ����Ϸ״̬
bool isRunning = false;

// ��Ϸ�߽綨��
#define BORDER_UP		(50)
#define BORDER_DOWN		(-50)
#define BORDER_LEFT		(-50)
#define BORDER_RIGHT	(50)

#define SQUARE_LENGTH	(1)

// С�ߵ������ʼ�����Ⱥ���󳤶�
#define SNAKE_INIT_LEN	(3)
#define SNAKE_MAX_LEN	(200)

int snakeLen = SNAKE_INIT_LEN;
stPosition snakeBody[SNAKE_MAX_LEN]; 

// �����ö��
enum eDirection
{
	eDirectionUp,
	eDirectionDown,
	eDirectionLeft,
	eDirectionRight
};

// ������¼��һ��С�����ĸ������չ
eDirection nextDirection = eDirectionUp;

// ���ڱ���С����һ���ƶ��н��ܵ��������
bool isValidSetDirection = true;

bool isFood(GLint x, GLint y);
stPosition randomFood(void);
bool isFood(GLint x, GLint y);
void eatFood(GLint x, GLint y);
void initSnake();