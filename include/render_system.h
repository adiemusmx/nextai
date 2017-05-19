#pragma once

#include "render_system/t_picture.h"
#include "render_system/t_window.h"

namespace Trinity {

class RenderSystem {

  public:
    /* 获得Render的实例 */
    static RenderSystem *getInstance();

    void Init(HINSTANCE hInstance);
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam,
                                       LPARAM lParam);

  private:
    // 构造函数
    RenderSystem();

    // 禁止拷贝构造
    D_DISABLE_COPY(RenderSystem);

    // 终止程序
    void TerminateApplication();

    // 描画函数
    void Draw();

    // 初始化OpenGL
    bool InitOpenGL();

  private:
    // 环境句柄
    HINSTANCE m_hInstance;

    // 类名
    WCHAR m_className[10];

    // 当前是否处理消息
    BOOL m_enableMessageLoop;

    // Window类
    TWindow m_window;
};
}