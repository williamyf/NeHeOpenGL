#pragma once
#include <windows.h>
#include <gl/glew.h>
#include <gl/glut.h>

namespace 
{
	HGLRC           hRC = NULL;							// ������ɫ��������
	HDC             hDC = NULL;							// OpenGL��Ⱦ��������
	HWND            hWnd = NULL;						// �������ǵĴ��ھ��
	HINSTANCE       hInstance;							// ��������ʵ��

	bool	keys[256];									// ������̰���������
	bool	active = TRUE;								// ���ڵĻ��־��ȱʡΪTRUE
	bool	fullscreen = TRUE;							// ȫ����־ȱʡ��ȱʡ�趨��ȫ��ģʽ
}
LRESULT	CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);				// WndProc�Ķ���

int InitGL(GLvoid);
int DrawGLScene(GLvoid);								// �����￪ʼ�������еĻ���
GLvoid ReSizeGLScene(GLsizei width, GLsizei height);				// ����OpenGL���ڴ�С
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag);
GLvoid KillGLWindow(GLvoid);							// �������ٴ���

void ErrorExit(LPTSTR lpszFunction);

int WINAPI WinMain(HINSTANCE	hInstance,				// ��ǰ����ʵ��
	HINSTANCE	hPrevInstance,				// ǰһ������ʵ��
	LPSTR		lpCmdLine,				// �����в���
	int		nCmdShow);				// ������ʾ״̬