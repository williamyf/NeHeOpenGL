#pragma once
#include <windows.h>
#include <gl/glew.h>
#include <gl/glut.h>

LRESULT	CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);		// WndProc�Ķ���
int WINAPI _tWinMain2(	HINSTANCE	hInstance,				// ��ǰ����ʵ��
						HINSTANCE	hPrevInstance,			// ǰһ������ʵ�� always NULL
						LPTSTR		lpCmdLine,				// �����в���
						int			nCmdShow);				// ������ʾ״̬

int InitGL(GLvoid);
int DrawGLScene(GLvoid);									// �����￪ʼ�������еĻ���
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);		// ����OpenGL���ڴ�С
BOOL CreateGLWindow(TCHAR* title, int width, int height, int bits, bool fullscreenflag);
GLvoid KillGLWindow(GLvoid);								// �������ٴ���

void ErrorExit(LPTSTR lpszFunction);