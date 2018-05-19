#include <GL/glut.h>

struct stPosition
{
	GLint x;
	GLint y;
};

stPosition foodPosition;

bool isRunning = false;

#define BORDER_UP		(50)
#define BORDER_DOWN		(-50)
#define BORDER_LEFT		(-50)
#define BORDER_RIGHT	(50)

#define SQUARE_LENGTH	(1)

#define SNAKE_INIT_LEN	(3)
#define SNAKE_MAX_LEN	(200)

int snakeLen = SNAKE_INIT_LEN;
stPosition snakeBody[SNAKE_MAX_LEN]; 

enum eDirection
{
	eDirectionUp,
	eDirectionDown,
	eDirectionLeft,
	eDirectionRight
};

eDirection nextDirection = eDirectionUp;

bool isValidSetDirection = true;

bool isFood(GLint x, GLint y);
stPosition randomFood(void);
bool isFood(GLint x, GLint y);
void eatFood(GLint x, GLint y);
void initSnake();
