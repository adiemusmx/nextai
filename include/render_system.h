﻿#pragma once

#include "widget_picture.h"

namespace Trinity {

class GLRenderer
{

public:
	/* 获得Render的实例 */
	static GLRenderer* getInstance();

	void init(int* argc, char* argv[]);

	void mainLoop();

	// 显示主函数
	static void displayFunc(void);

	// 空闲控制函数
	static void idleFunc(void);

	// 键盘处理函数
	static void keyBoardFunc(int key, int x, int y);

private:
	// 构造函数
	GLRenderer();

	// 禁止拷贝构造
	DISABLE_CLASS_COPY(GLRenderer);

	// 描画函数
	void draw();
};
}