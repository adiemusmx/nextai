// Trinity.cpp : 定义控制台应用程序的入口点。
//

#include "Log.h"
#include "GlutRender.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	LOG_LEVEL_INIT();
	LOG_LEVEL_SET_PERMISSION(E_LOG_LEVEL_OBJECT, true);

	GlutRender::getInstance()->Init(hInstance);

	return 0;
}
