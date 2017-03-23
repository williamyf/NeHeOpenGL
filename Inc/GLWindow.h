#pragma once
#include <windows.h>
#include <gl/glew.h>
#include <gl/glut.h>

LRESULT	CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);		// WndProc的定义
int WINAPI _tWinMain2(	HINSTANCE	hInstance,				// 当前窗口实例
						HINSTANCE	hPrevInstance,			// 前一个窗口实例 always NULL
						LPTSTR		lpCmdLine,				// 命令行参数
						int			nCmdShow);				// 窗口显示状态

int InitGL(GLvoid);
int DrawGLScene(GLvoid);									// 从这里开始进行所有的绘制
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);		// 重置OpenGL窗口大小
BOOL CreateGLWindow(TCHAR* title, int width, int height, int bits, bool fullscreenflag);
GLvoid KillGLWindow(GLvoid);								// 正常销毁窗口

void ErrorExit(LPTSTR lpszFunction);