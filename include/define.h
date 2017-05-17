#include <windows.h>
#include <GL/glut.h>

// 位置的结构体
struct stPosition
{
	GLint x;
	GLint y;
};

// 记录食物的位置
stPosition foodPosition;

// 判断当前的游戏状态
bool isRunning = false;

// 游戏边界定义
#define BORDER_UP		(50)
#define BORDER_DOWN		(-50)
#define BORDER_LEFT		(-50)
#define BORDER_RIGHT	(50)

#define SQUARE_LENGTH	(1)

// 小蛇的身体初始化长度和最大长度
#define SNAKE_INIT_LEN	(3)
#define SNAKE_MAX_LEN	(200)

int snakeLen = SNAKE_INIT_LEN;
stPosition snakeBody[SNAKE_MAX_LEN]; 

// 方向的枚举
enum eDirection
{
	eDirectionUp,
	eDirectionDown,
	eDirectionLeft,
	eDirectionRight
};

// 用来记录下一次小蛇向哪个方向进展
eDirection nextDirection = eDirectionUp;

// 用于避免小蛇在一次移动中接受到多个命令
bool isValidSetDirection = true;

bool isFood(GLint x, GLint y);
stPosition randomFood(void);
bool isFood(GLint x, GLint y);
void eatFood(GLint x, GLint y);
void initSnake();