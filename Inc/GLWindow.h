#pragma once
#include <windows.h>
#include <gl/glew.h>
#include <gl/glut.h>

namespace 
{
	HGLRC           hRC = NULL;							// 窗口着色描述表句柄
	HDC             hDC = NULL;							// OpenGL渲染描述表句柄
	HWND            hWnd = NULL;						// 保存我们的窗口句柄
	HINSTANCE       hInstance;							// 保存程序的实例

	bool	keys[256];									// 保存键盘按键的数组
	bool	active = TRUE;								// 窗口的活动标志，缺省为TRUE
	bool	fullscreen = TRUE;							// 全屏标志缺省，缺省设定成全屏模式
}
LRESULT	CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);				// WndProc的定义

int InitGL(GLvoid);
int DrawGLScene(GLvoid);								// 从这里开始进行所有的绘制
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);				// 重置OpenGL窗口大小
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);
GLvoid KillGLWindow(GLvoid);							// 正常销毁窗口

void ErrorExit(LPTSTR lpszFunction);

int WINAPI WinMain(HINSTANCE	hInstance,				// 当前窗口实例
	HINSTANCE	hPrevInstance,				// 前一个窗口实例
	LPSTR		lpCmdLine,				// 命令行参数
	int		nCmdShow);				// 窗口显示状态