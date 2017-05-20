#pragma once

#include "common_types.h"

class MessageCenter {
public:
	// 处理画面消息
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};
