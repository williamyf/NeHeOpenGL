#include "../Inc/GLWindow.h"
#include <Strsafe.h>
#include <tchar.h>

namespace
{
	HGLRC		g_hRC = NULL;				// 窗口着色描述表句柄
	HDC			g_hDC = NULL;				// OpenGL渲染描述表句柄
	HWND		g_hWnd = NULL;				// 保存我们的窗口句柄
	HINSTANCE	g_hInstance = NULL;			// 保存程序的实例

	bool		g_keys[256];				// 保存键盘按键的数组
	bool		g_active = TRUE;			// 窗口的活动标志，缺省为TRUE
	bool		g_fullscreen = TRUE;		// 全屏标志缺省，缺省设定成全屏模式
}

LRESULT	CALLBACK WndProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)							// 检查Windows消息
	{
	case WM_ACTIVATE:						// 监视窗口激活消息
	{
		if (!HIWORD(wParam))					// 检查最小化状态
		{
			g_active = TRUE;					// 程序处于激活状态
		}
		else
		{
			g_active = FALSE;					// 程序不再激活
		}

		return 0;						// 返回消息循环
	}
	case WM_SYSCOMMAND:						// 系统中断命令
	{
		switch (wParam)						// 检查系统调用
		{
		case SC_SCREENSAVE:				// 屏保要运行?
		case SC_MONITORPOWER:				// 显示器要进入节电模式?
			return 0;					// 阻止发生
		}
		break;							// 退出
	}
	case WM_CLOSE:							// 收到Close消息?
	{
		PostQuitMessage(0);					// 发出退出消息
		return 0;						// 返回
	}
	case WM_KEYDOWN:						// 有键按下么?
	{
		g_keys[wParam] = TRUE;					// 如果是，设为TRUE
		return 0;						// 返回
	}
	case WM_KEYUP:							// 有键放开么?
	{
		g_keys[wParam] = FALSE;					// 如果是，设为FALSE
		return 0;						// 返回
	}
	case WM_SIZE:							// 调整OpenGL窗口大小
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));		// LoWord=Width,HiWord=Height
		return 0;							// 返回
	}
	}
	// 向 DefWindowProc传递所有未处理的消息。
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);							// 启用阴影平滑
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// 黑色背景
	glClearDepth(1.0f);									// 设置深度缓存
	glEnable(GL_DEPTH_TEST);							// 启用深度测试
	glDepthFunc(GL_LEQUAL);								// 所作深度测试的类型
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// 告诉系统对透视进行修正
	return TRUE;										// 初始化 OK
}

#define LESSON		5
#define _DrawLesson(l)	DrawLesson##l();
#define DrawLesson(l)	_DrawLesson(l)

//lesson5.3D空间
//我们使用多边形和四边形创建3D物体，在这一课里，我们把三角形变为立体的金子塔形状，把四边形变为立方体。
//Q:为什么旋转的速度与窗口的大小有关系??? 遇到现象是随着窗口的变大旋转速度越来越慢
void DrawLesson5()
{
	static GLfloat	rtri(0.f);							// 用于三角形的角度
	static GLfloat	rquad(0.f);							// 用于四边形的角度

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除屏幕及深度缓存
	glLoadIdentity();									// 重置模型观察矩阵
	glTranslatef(-1.5f, 0.0f, -6.0f);					// 左移 1.5 单位，并移入屏幕 6.0
	glRotatef(rtri, 1.0f, 0.0f, 0.0f);					// 绕Y轴旋转金字塔

	glBegin(GL_TRIANGLES);					// 开始绘制金字塔的各个面
	
	glColor3f(1.0f, 0.0f, 0.0f);			// 红色
	glVertex3f(0.0f, 1.0f, 0.0f);			// 三角形的上顶点 (前侧面)
	glColor3f(0.0f, 1.0f, 0.0f);			// 绿色
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 三角形的左下顶点 (前侧面)
	glColor3f(0.0f, 0.0f, 1.0f);			// 蓝色
	glVertex3f(1.0f, -1.0f, 1.0f);			// 三角形的右下顶点 (前侧面)
	
	glColor3f(1.0f, 0.0f, 0.0f);			// 红色
	glVertex3f(0.0f, 1.0f, 0.0f);			// 三角形的上顶点 (右侧面)
	glColor3f(0.0f, 0.0f, 1.0f);			// 蓝色
	glVertex3f(1.0f, -1.0f, 1.0f);			// 三角形的左下顶点 (右侧面)
	glColor3f(0.0f, 1.0f, 0.0f);			// 绿色
	glVertex3f(1.0f, -1.0f, -1.0f);			// 三角形的右下顶点 (右侧面)

	glColor3f(1.0f, 0.0f, 0.0f);			// 红色
	glVertex3f(0.0f, 1.0f, 0.0f);			// 三角形的上顶点 (后侧面)
	glColor3f(0.0f, 1.0f, 0.0f);			// 绿色
	glVertex3f(1.0f, -1.0f, -1.0f);			// 三角形的左下顶点 (后侧面)
	glColor3f(0.0f, 0.0f, 1.0f);			// 蓝色
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 三角形的右下顶点 (后侧面)

	glColor3f(1.0f, 0.0f, 0.0f);			// 红色
	glVertex3f(0.0f, 1.0f, 0.0f);			// 三角形的上顶点 (左侧面)
	glColor3f(0.0f, 0.0f, 1.0f);			// 蓝色
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 三角形的左下顶点 (左侧面)
	glColor3f(0.0f, 1.0f, 0.0f);			// 绿色
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 三角形的右下顶点 (左侧面)
	
	glEnd();								// 金字塔绘制结束

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -7.0f);		// 先右移再移入屏幕
	glRotatef(rquad, 1.0f, 1.0f, 1.0f);		// 在XYZ轴上旋转立方体

	glBegin(GL_QUADS);						// 开始绘制立方体
	
	glColor3f(0.0f, 1.0f, 0.0f);			// 颜色改为绿色
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右上顶点 (顶面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左上顶点 (顶面)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的左下顶点 (顶面)
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的右下顶点 (顶面)
	glColor3f(1.0f, 0.5f, 0.0f);			// 颜色改成橙色
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的右上顶点(底面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的左上顶点(底面)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 四边形的左下顶点(底面)
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右下顶点(底面)
	glColor3f(1.0f, 0.0f, 0.0f);			// 颜色改成红色
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的右上顶点(前面)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的左上顶点(前面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的左下顶点(前面)
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的右下顶点(前面)
	glColor3f(1.0f, 1.0f, 0.0f);			// 颜色改成黄色
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右上顶点(后面)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 四边形的左上顶点(后面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左下顶点(后面)
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右下顶点(后面)
	glColor3f(0.0f, 0.0f, 1.0f);			// 颜色改成蓝色
	glVertex3f(-1.0f, 1.0f, 1.0f);			// 四边形的右上顶点(左面)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// 四边形的左上顶点(左面)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// 四边形的左下顶点(左面)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// 四边形的右下顶点(左面)
	glColor3f(1.0f, 0.0f, 1.0f);			// 颜色改成紫罗兰色
	glVertex3f(1.0f, 1.0f, -1.0f);			// 四边形的右上顶点(右面)
	glVertex3f(1.0f, 1.0f, 1.0f);			// 四边形的左上顶点(右面)
	glVertex3f(1.0f, -1.0f, 1.0f);			// 四边形的左下顶点(右面)
	glVertex3f(1.0f, -1.0f, -1.0f);			// 四边形的右下顶点(右面)
	glEnd();								// 立方体绘制结束

	rtri += 0.05f;							// 增加三角形的旋转变量
	rquad -= 0.05f;							// 减少四边形的旋转变量
}

//lesson4.旋转
//在这一课里，我将教会你如何旋转三角形和四边形。左图中的三角形沿Y轴旋转，四边形沿着X轴旋转。
void DrawLesson4()
{
	static GLfloat	rtri(0.f);							// 用于三角形的角度
	static GLfloat	rquad(0.f);							// 用于四边形的角度
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// 清除屏幕及深度缓存
	glLoadIdentity();									// 重置模型观察矩阵
	glTranslatef(-1.5f, 0.0f, -6.0f);					// 左移 1.5 单位，并移入屏幕 6.0
	glRotatef(rtri, 0.0f, 1.0f, 0.0f);					// 绕Y轴旋转三角形
	
	glBegin(GL_TRIANGLES);					// 绘制三角形
	glColor3f(1.0f, 0.0f, 0.0f);			// 设置当前色为红色
	glVertex3f(0.0f, 1.0f, 0.0f);			// 上顶点
	glColor3f(0.0f, 1.0f, 0.0f);			// 设置当前色为绿色
	glVertex3f(-1.0f, -1.0f, 0.0f);			// 左下
	glColor3f(0.0f, 0.0f, 1.0f);			// 设置当前色为蓝色
	glVertex3f(1.0f, -1.0f, 0.0f);			// 右下
	glEnd();								// 三角形绘制结束
	
	glLoadIdentity();						// 重置模型观察矩阵
	glTranslatef(1.5f, 0.0f, -6.0f);		// 右移1.5单位,并移入屏幕 6.0
	glRotatef(rquad, 1.0f, 0.0f, 0.0f);		//  绕X轴旋转四边形
	glColor3f(0.5f, 0.5f, 1.0f);			// 一次性将当前色设置为蓝色
	glBegin(GL_QUADS);						// 绘制正方形
	glVertex3f(-1.0f, 1.0f, 0.0f);			// 左上
	glVertex3f(1.0f, 1.0f, 0.0f);			// 右上
	glVertex3f(1.0f, -1.0f, 0.0f);			// 左下
	glVertex3f(-1.0f, -1.0f, 0.0f);			// 右下
	glEnd();								// 正方形绘制结束
	rtri += 0.1f;							// 增加三角形的旋转变量
	rquad -= 0.05f;							// 减少四边形的旋转变量

}

//lesson3.添加颜色
//作为第二课的扩展，我将叫你如何使用颜色。你将理解两种着色模式，在左图中，三角形用的是光滑着色，四边形用的是平面着色。
void DrawLesson3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// 清除屏幕及深度缓存
	glLoadIdentity();										// 重置模型观察矩阵
	glTranslatef(-1.5f, 0.0f, -6.0f);						// 左移 1.5 单位，并移入屏幕 6.0

	glBegin(GL_TRIANGLES);						// 绘制三角形
	glColor3f(1.0f, 0.0f, 0.0f);				// 设置当前色为红色
	glVertex3f(0.0f, 1.0f, 0.0f);				// 上顶点
	glColor3f(0.0f, 1.0f, 0.0f);				// 设置当前色为绿色
	glVertex3f(-1.0f, -1.0f, 0.0f);				// 左下
	glColor3f(0.0f, 0.0f, 1.0f);				// 设置当前色为蓝色
	glVertex3f(1.0f, -1.0f, 0.0f);				// 右下
	glEnd();									// 三角形绘制结束

	glTranslatef(3.0f, 0.0f, 0.0f);				// 右移3单位
	glColor3f(0.5f, 0.5f, 1.0f);				// 一次性将当前色设置为蓝色
	glBegin(GL_QUADS);							// 绘制正方形
	glVertex3f(-1.0f, 1.0f, 0.0f);				// 左上
	glVertex3f(1.0f, 1.0f, 0.0f);				// 右上
	glVertex3f(1.0f, -1.0f, 0.0f);				// 左下
	glVertex3f(-1.0f, -1.0f, 0.0f);				// 右下
	glEnd();									// 正方形绘制结束
}

//lesson2.你的第一个多边形
//在第一个教程的基础上，我们添加了一个三角形和一个四边形。也许你认为这很简单，但你已经迈出了一大步，要知道任何在OpenGL中绘制的模型都会被分解为这两种简单的图形。
//读完了这一课，你会学到如何在空间放置模型，并且会知道深度缓存的概念。
void DrawLesson2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// 清除屏幕及深度缓存
	glLoadIdentity();										// 重置当前的模型观察矩阵
	
	glTranslatef(-1.5f, 0.0f, -6.0f);						// 左移 1.5 单位，并移入屏幕 6.0
	glBegin(GL_TRIANGLES);									// 绘制三角形
	glVertex3f(0.0f, 1.0f, 0.0f);							// 上顶点
	glVertex3f(-1.0f, -1.0f, 0.0f);							// 左下
	glVertex3f(1.0f, -1.0f, 0.0f);							// 右下
	glEnd();												// 三角形绘制结束

	glTranslatef(3.0f, 0.0f, 0.0f);							// 右移3单位
	glBegin(GL_QUADS);										// 绘制正方形
	glVertex3f(-1.0f, 1.0f, 0.0f);							// 左上
	glVertex3f(1.0f, 1.0f, 0.0f);							// 右上
	glVertex3f(1.0f, -1.0f, 0.0f);							// 左下
	glVertex3f(-1.0f, -1.0f, 0.0f);							// 右下
	glEnd();												// 正方形绘制结束

}

//lesson1.创建一个OpenGL窗口
//在这个教程里, 我将教你在Windows环境中创建OpenGL程序.它将显示一个空的OpenGL窗口, 可以在窗口和全屏模式下切换, 按ESC退出.它是我们以后应用程序的框架.
//理解OpenGL如何工作非常重要，你可以在教程的末尾下载源程序，但我强烈建议你至少读一遍教程，然后再开始编程.
void DrawLesson1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// 清除屏幕和深度缓存
	glLoadIdentity();							// 重置当前的模型观察矩阵
}

int DrawGLScene(GLvoid)	// 此过程中包括所有的绘制代码
{
	DrawLesson(LESSON);
	return TRUE;		// 一切 OK
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)						// 防止被零除
	{
		height = 1;							// 将Height设为1
	}

	glViewport(0, 0, width, height);		// 重置当前的视口
	
	glMatrixMode(GL_PROJECTION);			// 选择投影矩阵
	glLoadIdentity();						// 重置投影矩阵
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);	// 设置视口的大小
	
	glMatrixMode(GL_MODELVIEW);				// 选择模型观察矩阵
	glLoadIdentity();						// 重置模型观察矩阵

}

BOOL CreateGLWindow(TCHAR* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;	// 保存查找匹配的结果
	WNDCLASS	wc;				// 窗口类结构
	DWORD		dwStyle;		// 窗口风格
	DWORD		dwExStyle;		// 扩展窗口风格
	RECT		WindowRect;		// 取得矩形的左上角和右下角的坐标值
	WindowRect.left = (long)0;			// 将Left   设为 0
	WindowRect.right = (long)width;		// 将Right  设为要求的宽度
	WindowRect.top = (long)0;			// 将Top    设为 0
	WindowRect.bottom = (long)height;	// 将Bottom 设为要求的高度

	g_fullscreen = fullscreenflag;		// 设置全局全屏标志

	g_hInstance = GetModuleHandle(NULL);	// 取得我们窗口的实例

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// 移动时重画，并为窗口取得DC
	wc.lpfnWndProc = (WNDPROC)WndProc2;					// WndProc处理消息
	wc.cbClsExtra = 0;									// 无额外窗口数据
	wc.cbWndExtra = 0;									// 无额外窗口数据
	wc.hInstance = g_hInstance;							// 设置实例
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);				// 装入缺省图标
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// 装入鼠标指针
	wc.hbrBackground = NULL;							// GL不需要背景
	wc.lpszMenuName = NULL;								// 不需要菜单
	wc.lpszClassName = TEXT("OpenG");							// 设定类名字
	if (!RegisterClass(&wc))							// 尝试注册窗口类
	{
		MessageBox(NULL, _T("注册窗口失败"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		ErrorExit(TEXT("RegisterClass"));
		return FALSE;
	}

	if (g_fullscreen)	// 要尝试全屏模式吗?
	{
		DEVMODE dmScreenSettings;									// 设备模式
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));		// 确保内存清空为零
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);			// Devmode 结构的大小
		dmScreenSettings.dmPelsWidth = width;						// 所选屏幕宽度
		dmScreenSettings.dmPelsHeight = height;						// 所选屏幕高度
		dmScreenSettings.dmBitsPerPel = bits;						// 每象素所选的色彩深度
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		
		// 尝试设置显示模式并返回结果。注: CDS_FULLSCREEN 移去了状态条。
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// 若模式失败，提供两个选项：退出或在窗口内运行。
			if (MessageBox(NULL, _T("全屏模式在当前显卡上设置失败！\n使用窗口模式？"), _T("NeHe G"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				g_fullscreen = FALSE;	// 选择窗口模式(Fullscreen=FALSE)
			}
			else
			{
				// 弹出一个对话框，告诉用户程序结束
				MessageBox(NULL, _T("程序将被关闭"), _T("错误"), MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (g_fullscreen)								// 仍处于全屏模式吗?
	{
		dwExStyle = WS_EX_APPWINDOW;			// 扩展窗体风格
		dwStyle = WS_POPUP;						// 窗体风格
		ShowCursor(FALSE);						// 隐藏鼠标指针
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// 扩展窗体风格
		dwStyle = WS_OVERLAPPEDWINDOW;					//  窗体风格
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	// 调整窗口达到真正要求的大小

	if (!(g_hWnd = CreateWindowEx(dwExStyle,				// 扩展窗体风格
								_T("OpenG"),				// 类名字
								title,					// 窗口标题
								WS_CLIPSIBLINGS |		// 必须的窗体风格属性
								WS_CLIPCHILDREN |		// 必须的窗体风格属性
								dwStyle,				// 选择的窗体属性
								0, 0,					// 窗口位置
								WindowRect.right - WindowRect.left,	// 计算调整好的窗口宽度
								WindowRect.bottom - WindowRect.top,	// 计算调整好的窗口高度
								NULL,					// 无父窗口
								NULL,					// 无菜单
								g_hInstance,				// 实例
								NULL))					// 不向WM_CREATE传递任何东东
		)
	{
		KillGLWindow();	// 重置显示区
		MessageBox(NULL, _T("不能创建一个窗口设备描述表"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		ErrorExit(TEXT("CreateWindowEx"));
		return FALSE;
	}

	// pfd 告诉窗口我们所希望的东东，即窗口使用的像素格式
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// 上述格式描述符的大小
		1,								// 版本号
		PFD_DRAW_TO_WINDOW |			// 格式支持窗口
		PFD_SUPPORT_OPENGL |			// 格式必须支持OpenGL
		PFD_DOUBLEBUFFER,				// 必须支持双缓冲
		PFD_TYPE_RGBA,					// 申请 RGBA 格式
		bits,							// 选定色彩深度
		0, 0, 0, 0, 0, 0,				// 忽略的色彩位
		0,								// 无Alpha缓存
		0,								// 忽略Shift Bit
		0,								// 无累加缓存
		0, 0, 0, 0,						// 忽略聚集位
		16,								// 16位 Z-缓存 (深度缓存)
		0,								// 无蒙板缓存
		0,								// 无辅助缓存
		PFD_MAIN_PLANE,					// 主绘图层
		0,								// Reserved
		0, 0, 0							// 忽略层遮罩
	};

	if (!(g_hDC = GetDC(g_hWnd)))		// 取得设备描述表了么?
	{
		KillGLWindow();					// 重置显示区
		MessageBox(NULL, _T("不能创建一种相匹配的像素格式"),_T( "错误"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;					// 返回 FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(g_hDC, &pfd)))	// Windows 找到相应的象素格式了吗?
	{
		KillGLWindow();	// 重置显示区
		MessageBox(NULL, _T("不能设置像素格式"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(g_hDC, PixelFormat, &pfd))	// 能够设置象素格式么?
	{
		KillGLWindow();	// 重置显示区
		MessageBox(NULL, _T("不能设置像素格式"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(g_hRC = wglCreateContext(g_hDC)))		// 能否取得着色描述表?
	{
		KillGLWindow();	// 重置显示区
		MessageBox(NULL, _T("不能创建OpenGL渲染描述表"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!wglMakeCurrent(g_hDC, g_hRC))		// 尝试激活着色描述表
	{
		KillGLWindow();	// 重置显示区
		MessageBox(NULL, _T("不能激活当前的OpenGL渲然描述表"), _T("错误"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(g_hWnd, SW_SHOW);				// 显示窗口
	SetForegroundWindow(g_hWnd);				// 略略提高优先级
	SetFocus(g_hWnd);							// 设置键盘的焦点至此窗口

	ReSizeGLScene(width, height);				// 设置透视 GL 屏幕
	
	if (!InitGL())								// 初始化新建的GL窗口
	{
		KillGLWindow();							// 重置显示区
		MessageBox(NULL, _T("Initialization Failed."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;								// 成功
}

GLvoid KillGLWindow(GLvoid)
{
	if (g_fullscreen)							// 我们处于全屏模式吗?
	{
		ChangeDisplaySettings(NULL, 0);			// 是的话，切换回桌面
		ShowCursor(TRUE);						// 显示鼠标指针
	}
	if (g_hRC)								// 我们拥有OpenGL渲染描述表吗?
	{
		if (!wglMakeCurrent(NULL, NULL))					// 我们能否释放DC和RC描述表?
		{
			MessageBox(NULL, _T("释放DC或RC失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(g_hRC))					// 我们能否删除RC?
		{
			MessageBox(NULL, _T("释放RC失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		}
		g_hRC = NULL;							// 将RC设为 NULL
	}
	if (g_hDC && !ReleaseDC(g_hWnd, g_hDC))					// 我们能否释放 DC?
	{
		MessageBox(NULL, _T("释放DC失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		g_hDC = NULL;							// 将 DC 设为 NULL
	}
	if (g_hWnd && !DestroyWindow(g_hWnd))					// 能否销毁窗口?
	{
		MessageBox(NULL, _T("释放窗口句柄失败。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		g_hWnd = NULL;							// 将 g_hWnd 设为 NULL
	}
	if (!UnregisterClass(_T("OpenG"), g_hInstance))				// 能否注销类?
	{
		MessageBox(NULL, _T("不能注销窗口类。"), _T("关闭错误"), MB_OK | MB_ICONINFORMATION);
		g_hInstance = NULL;							// 将 g_hInstance 设为 NULL
	}

}

void ErrorExit(LPTSTR lpszFunction)
{
	// Retrieve the system error message for the last-error code
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);
	
	// Display the error message and exit the process
	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));
	StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);
	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);
	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

int WINAPI _tWinMain2(	HINSTANCE	hInstance,				// 当前窗口实例
						HINSTANCE	hPrevInstance,			// 前一个窗口实例 always NULL
						LPTSTR		lpCmdLine,				// 命令行参数
						int			nCmdShow)				// 窗口显示状态
{
	MSG		msg;			// Windowsx消息结构
	BOOL	done = FALSE;	// 用来退出循环的Bool 变量

	// 提示用户选择运行模式
	//if (MessageBox(NULL, _T("你想在全屏模式下运行么？"), _T("设置全屏模式"), MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		g_fullscreen = FALSE;	// FALSE为窗口模式
	}

	// 创建OpenGL窗口
	// CreateGLWindow函数的参数依次为标题、宽度、高度、色彩深度，以及全屏标志。
	if (!CreateGLWindow(_T("NeHe's OpenGL程序框架"), 640, 480, 16, g_fullscreen))
	{
		return 0;	// 失败退出
	}

	while (!done)	// 保持循环直到 done=TRUE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// 有消息在等待吗?
		{
			if (msg.message == WM_QUIT)					// 收到退出消息?
			{
				done = TRUE;							// 是，则done=TRUE
			}
			else										// 不是，处理窗口消息
			{
				TranslateMessage(&msg);					// 翻译消息
				DispatchMessage(&msg);					// 发送消息
			}
		}
		else											// 如果没有消息
		{
			// 绘制场景。监视ESC键和来自DrawGLScene()的退出消息
			if (g_active)								// 程序激活的么?
			{
				if (g_keys[VK_ESCAPE])					// ESC 按下了么?
				{
					done = TRUE;						// ESC 发出退出信号
				}
				else									// 不是退出的时候，刷新屏幕
				{
					DrawGLScene();						// 绘制场景
					SwapBuffers(g_hDC);					// 交换缓存 (双缓存)
				}
			}

			if (g_keys[VK_F1])							// F1键按下了么?
			{
				g_keys[VK_F1] = FALSE;					// 若是，使对应的Key数组中的值为 FALSE
				KillGLWindow();							// 销毁当前的窗口
				g_fullscreen = !g_fullscreen;			// 切换 全屏 / 窗口 模式
				
				// 重建 OpenGL 窗口
				if (!CreateGLWindow(_T("NeHe's OpenGL 程序框架"), 640, 480, 16, g_fullscreen))
				{
					return 0; // 如果窗口未能创建，程序退出
				}
			}
		}
	}

	// 关闭程序
	KillGLWindow();			// 销毁窗口
	return (msg.wParam);	// 退出程序
}
