#include "GlutRender.h"

#include "glut.h"
#include "MessageCenter.h"

#include "Picture.h"

GlutRender* GlutRender::getInstance()
{
	static GlutRender render;
	return &render;
}

GlutRender::GlutRender()
{
	m_hInstance = NULL;
	memcpy(m_ClassName, L"Trinity", sizeof(m_ClassName));
	m_enableMessageLoop = TRUE;
}

void GlutRender::TerminateApplication()
{
	// 发送终止消息
	PostMessage(m_Window, WM_QUIT, 0, 0);
}

void GlutRender::Draw()
{
	// 重新设置窗口的大小
	m_Window.ReshapeGL();

	// 用户自定义的绘制过程
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Dummy
	Picture pic; 
	pic.Draw();

	// 强制执行所有的OpenGL命令
	glFlush();

	// 交换前后帧缓存 
	m_Window.SwapBuffers();
}

void GlutRender::Init(HINSTANCE hInstance)
{
	m_hInstance = hInstance;

	/// 注册一个窗口
	WNDCLASSEX windowClass;												/**< 窗口类 */
	ZeroMemory(&windowClass, sizeof(WNDCLASSEX));						/**< 清空结构为0 */
	windowClass.cbSize = sizeof(WNDCLASSEX);							/**< 窗口结构的大小 */
	windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;				/**< 设置窗口类型为，移动时重画，并为窗口取得DC */
	windowClass.lpfnWndProc = (WNDPROC)(WindowProc);					/**< WndProc处理消息 */
	windowClass.hInstance = m_hInstance;								/**< 设置实例 */
	windowClass.hbrBackground = (HBRUSH)(COLOR_APPWORKSPACE);			/**< 设置背景 */
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);					/**< 载入光标 */
	windowClass.lpszClassName = m_ClassName;							/**< 设置类名 */
	if (RegisterClassEx(&windowClass) == 0)								/**< 尝试注册窗口类 */
	{																	/**< NOTE: Failure, Should Never Happen */
		MessageBox(HWND_DESKTOP, L"Register Failed!", L"Error", MB_OK | MB_ICONEXCLAMATION);
	}

	while (m_enableMessageLoop)											/**< 循环直道WM_QUIT退出程序 */
	{
		/// 创建一个窗口
		if (m_Window.Create(m_ClassName, m_ClassName, m_hInstance, this) == true)
		{
			/// 如果初始化失败，则退出
			if (InitOpenGL() == false)									/**< 调用自定义的初始化函数 */
				TerminateApplication();									/**< 关闭窗口退出程序 */
			else														/**< 成功开始消息循环 */
			{
				MSG msg;												/**< Window消息结构 */
				bool isMessagePumpActive = true;						/**< 当消息不为空时，处理消息循环 */
				while (isMessagePumpActive == true)						/**< 当消息不为空时，处理消息循环 */
				{														/**< 成功创建窗口，检测窗口消息 */
					if (PeekMessage(&msg, m_Window, 0, 0, PM_REMOVE) != 0)
					{
						/// 检测是否为WM_QUIT消息
						if (msg.message != WM_QUIT)
							DispatchMessage(&msg);						/**< 如果不是发送消息到消息回调函数中处理 */
						else
						{
							m_enableMessageLoop = false;				/**< 停止程序循环 */
							break;
						}
					}
				}														/**< 如果isMessagePumpActive == true，则循环 */
			}
			m_Window.Destroy();											/**< 删除窗口 */
		}
		else															/**< 如果创建窗口失败 */
		{
			MessageBox(HWND_DESKTOP, L"Create Failed", L"Error", MB_OK | MB_ICONEXCLAMATION);
			m_enableMessageLoop = false;								/**< 停止程序循环 */
		}
	}

	UnregisterClass(m_ClassName, hInstance);							/**< 取消注册的窗口 */
}

bool GlutRender::InitOpenGL()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	return true;
}

LRESULT CALLBACK GlutRender::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	GlutRender* render = GlutRender::getInstance();
	switch (uMsg)					/**< 处理不同的Windows消息 */
	{
	case WM_SYSCOMMAND:				/**< 截获系统命令 */
		switch (wParam)
		{
		case SC_SCREENSAVE:			/**< 截获屏幕保护启动命令 */
		case SC_MONITORPOWER:		/**< 截获显示其省电模式启动命令 */
			return 0;				/**< 不启用这两个命令 */
		}
		break;						/**< 退出 */
	case WM_CLOSE:					/**< 关闭窗口 */
		render->TerminateApplication();	/**< 调用TerminateApplication函数 */
		return 0;
	case WM_EXITMENULOOP:
	case WM_EXITSIZEMOVE:
		return 0;
	case WM_MOVE:
		break;
	case WM_PAINT:
		render->Draw();	/**< 描画函数 */
		break;
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONUP:
		MessageCenter::WindowProc(hWnd, uMsg, wParam, lParam);	/**< 消息处理 */
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);	/**< 调用默认的窗口消息处理函数 */
}