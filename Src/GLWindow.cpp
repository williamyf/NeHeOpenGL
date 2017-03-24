#include "../Inc/GLWindow.h"
#include <Strsafe.h>
#include <tchar.h>

namespace
{
	HGLRC		g_hRC = NULL;				// ������ɫ��������
	HDC			g_hDC = NULL;				// OpenGL��Ⱦ��������
	HWND		g_hWnd = NULL;				// �������ǵĴ��ھ��
	HINSTANCE	g_hInstance = NULL;			// ��������ʵ��

	bool		g_keys[256];				// ������̰���������
	bool		g_active = TRUE;			// ���ڵĻ��־��ȱʡΪTRUE
	bool		g_fullscreen = TRUE;		// ȫ����־ȱʡ��ȱʡ�趨��ȫ��ģʽ
}

LRESULT	CALLBACK WndProc2(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)							// ���Windows��Ϣ
	{
	case WM_ACTIVATE:						// ���Ӵ��ڼ�����Ϣ
	{
		if (!HIWORD(wParam))					// �����С��״̬
		{
			g_active = TRUE;					// �����ڼ���״̬
		}
		else
		{
			g_active = FALSE;					// �����ټ���
		}

		return 0;						// ������Ϣѭ��
	}
	case WM_SYSCOMMAND:						// ϵͳ�ж�����
	{
		switch (wParam)						// ���ϵͳ����
		{
		case SC_SCREENSAVE:				// ����Ҫ����?
		case SC_MONITORPOWER:				// ��ʾ��Ҫ����ڵ�ģʽ?
			return 0;					// ��ֹ����
		}
		break;							// �˳�
	}
	case WM_CLOSE:							// �յ�Close��Ϣ?
	{
		PostQuitMessage(0);					// �����˳���Ϣ
		return 0;						// ����
	}
	case WM_KEYDOWN:						// �м�����ô?
	{
		g_keys[wParam] = TRUE;					// ����ǣ���ΪTRUE
		return 0;						// ����
	}
	case WM_KEYUP:							// �м��ſ�ô?
	{
		g_keys[wParam] = FALSE;					// ����ǣ���ΪFALSE
		return 0;						// ����
	}
	case WM_SIZE:							// ����OpenGL���ڴ�С
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));		// LoWord=Width,HiWord=Height
		return 0;							// ����
	}
	}
	// �� DefWindowProc��������δ�������Ϣ��
	return DefWindowProc(hWnd, uMsg, wParam, lParam);

}

int InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH);							// ������Ӱƽ��
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// ��ɫ����
	glClearDepth(1.0f);									// ������Ȼ���
	glEnable(GL_DEPTH_TEST);							// ������Ȳ���
	glDepthFunc(GL_LEQUAL);								// ������Ȳ��Ե�����
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// ����ϵͳ��͸�ӽ�������
	return TRUE;										// ��ʼ�� OK
}

#define LESSON		5
#define _DrawLesson(l)	DrawLesson##l();
#define DrawLesson(l)	_DrawLesson(l)

//lesson5.3D�ռ�
//����ʹ�ö���κ��ı��δ���3D���壬����һ������ǰ������α�Ϊ����Ľ�������״�����ı��α�Ϊ�����塣
//Q:Ϊʲô��ת���ٶ��봰�ڵĴ�С�й�ϵ??? �������������Ŵ��ڵı����ת�ٶ�Խ��Խ��
void DrawLesson5()
{
	static GLfloat	rtri(0.f);							// ���������εĽǶ�
	static GLfloat	rquad(0.f);							// �����ı��εĽǶ�

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();									// ����ģ�͹۲����
	glTranslatef(-1.5f, 0.0f, -6.0f);					// ���� 1.5 ��λ����������Ļ 6.0
	glRotatef(rtri, 1.0f, 0.0f, 0.0f);					// ��Y����ת������

	glBegin(GL_TRIANGLES);					// ��ʼ���ƽ������ĸ�����
	
	glColor3f(1.0f, 0.0f, 0.0f);			// ��ɫ
	glVertex3f(0.0f, 1.0f, 0.0f);			// �����ε��϶��� (ǰ����)
	glColor3f(0.0f, 1.0f, 0.0f);			// ��ɫ
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �����ε����¶��� (ǰ����)
	glColor3f(0.0f, 0.0f, 1.0f);			// ��ɫ
	glVertex3f(1.0f, -1.0f, 1.0f);			// �����ε����¶��� (ǰ����)
	
	glColor3f(1.0f, 0.0f, 0.0f);			// ��ɫ
	glVertex3f(0.0f, 1.0f, 0.0f);			// �����ε��϶��� (�Ҳ���)
	glColor3f(0.0f, 0.0f, 1.0f);			// ��ɫ
	glVertex3f(1.0f, -1.0f, 1.0f);			// �����ε����¶��� (�Ҳ���)
	glColor3f(0.0f, 1.0f, 0.0f);			// ��ɫ
	glVertex3f(1.0f, -1.0f, -1.0f);			// �����ε����¶��� (�Ҳ���)

	glColor3f(1.0f, 0.0f, 0.0f);			// ��ɫ
	glVertex3f(0.0f, 1.0f, 0.0f);			// �����ε��϶��� (�����)
	glColor3f(0.0f, 1.0f, 0.0f);			// ��ɫ
	glVertex3f(1.0f, -1.0f, -1.0f);			// �����ε����¶��� (�����)
	glColor3f(0.0f, 0.0f, 1.0f);			// ��ɫ
	glVertex3f(-1.0f, -1.0f, -1.0f);		// �����ε����¶��� (�����)

	glColor3f(1.0f, 0.0f, 0.0f);			// ��ɫ
	glVertex3f(0.0f, 1.0f, 0.0f);			// �����ε��϶��� (�����)
	glColor3f(0.0f, 0.0f, 1.0f);			// ��ɫ
	glVertex3f(-1.0f, -1.0f, -1.0f);		// �����ε����¶��� (�����)
	glColor3f(0.0f, 1.0f, 0.0f);			// ��ɫ
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �����ε����¶��� (�����)
	
	glEnd();								// ���������ƽ���

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -7.0f);		// ��������������Ļ
	glRotatef(rquad, 1.0f, 1.0f, 1.0f);		// ��XYZ������ת������

	glBegin(GL_QUADS);						// ��ʼ����������
	
	glColor3f(0.0f, 1.0f, 0.0f);			// ��ɫ��Ϊ��ɫ
	glVertex3f(1.0f, 1.0f, -1.0f);			// �ı��ε����϶��� (����)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// �ı��ε����϶��� (����)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// �ı��ε����¶��� (����)
	glVertex3f(1.0f, 1.0f, 1.0f);			// �ı��ε����¶��� (����)
	glColor3f(1.0f, 0.5f, 0.0f);			// ��ɫ�ĳɳ�ɫ
	glVertex3f(1.0f, -1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// �ı��ε����¶���(����)
	glVertex3f(1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)
	glColor3f(1.0f, 0.0f, 0.0f);			// ��ɫ�ĳɺ�ɫ
	glVertex3f(1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(ǰ��)
	glVertex3f(-1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(ǰ��)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(ǰ��)
	glVertex3f(1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(ǰ��)
	glColor3f(1.0f, 1.0f, 0.0f);			// ��ɫ�ĳɻ�ɫ
	glVertex3f(1.0f, -1.0f, -1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// �ı��ε����϶���(����)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// �ı��ε����¶���(����)
	glVertex3f(1.0f, 1.0f, -1.0f);			// �ı��ε����¶���(����)
	glColor3f(0.0f, 0.0f, 1.0f);			// ��ɫ�ĳ���ɫ
	glVertex3f(-1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, 1.0f, -1.0f);			// �ı��ε����϶���(����)
	glVertex3f(-1.0f, -1.0f, -1.0f);		// �ı��ε����¶���(����)
	glVertex3f(-1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(����)
	glColor3f(1.0f, 0.0f, 1.0f);			// ��ɫ�ĳ�������ɫ
	glVertex3f(1.0f, 1.0f, -1.0f);			// �ı��ε����϶���(����)
	glVertex3f(1.0f, 1.0f, 1.0f);			// �ı��ε����϶���(����)
	glVertex3f(1.0f, -1.0f, 1.0f);			// �ı��ε����¶���(����)
	glVertex3f(1.0f, -1.0f, -1.0f);			// �ı��ε����¶���(����)
	glEnd();								// ��������ƽ���

	rtri += 0.05f;							// ���������ε���ת����
	rquad -= 0.05f;							// �����ı��ε���ת����
}

//lesson4.��ת
//����һ����ҽ��̻��������ת�����κ��ı��Ρ���ͼ�е���������Y����ת���ı�������X����ת��
void DrawLesson4()
{
	static GLfloat	rtri(0.f);							// ���������εĽǶ�
	static GLfloat	rquad(0.f);							// �����ı��εĽǶ�
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// �����Ļ����Ȼ���
	glLoadIdentity();									// ����ģ�͹۲����
	glTranslatef(-1.5f, 0.0f, -6.0f);					// ���� 1.5 ��λ����������Ļ 6.0
	glRotatef(rtri, 0.0f, 1.0f, 0.0f);					// ��Y����ת������
	
	glBegin(GL_TRIANGLES);					// ����������
	glColor3f(1.0f, 0.0f, 0.0f);			// ���õ�ǰɫΪ��ɫ
	glVertex3f(0.0f, 1.0f, 0.0f);			// �϶���
	glColor3f(0.0f, 1.0f, 0.0f);			// ���õ�ǰɫΪ��ɫ
	glVertex3f(-1.0f, -1.0f, 0.0f);			// ����
	glColor3f(0.0f, 0.0f, 1.0f);			// ���õ�ǰɫΪ��ɫ
	glVertex3f(1.0f, -1.0f, 0.0f);			// ����
	glEnd();								// �����λ��ƽ���
	
	glLoadIdentity();						// ����ģ�͹۲����
	glTranslatef(1.5f, 0.0f, -6.0f);		// ����1.5��λ,��������Ļ 6.0
	glRotatef(rquad, 1.0f, 0.0f, 0.0f);		//  ��X����ת�ı���
	glColor3f(0.5f, 0.5f, 1.0f);			// һ���Խ���ǰɫ����Ϊ��ɫ
	glBegin(GL_QUADS);						// ����������
	glVertex3f(-1.0f, 1.0f, 0.0f);			// ����
	glVertex3f(1.0f, 1.0f, 0.0f);			// ����
	glVertex3f(1.0f, -1.0f, 0.0f);			// ����
	glVertex3f(-1.0f, -1.0f, 0.0f);			// ����
	glEnd();								// �����λ��ƽ���
	rtri += 0.1f;							// ���������ε���ת����
	rquad -= 0.05f;							// �����ı��ε���ת����

}

//lesson3.�����ɫ
//��Ϊ�ڶ��ε���չ���ҽ��������ʹ����ɫ���㽫���������ɫģʽ������ͼ�У��������õ��ǹ⻬��ɫ���ı����õ���ƽ����ɫ��
void DrawLesson3()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// �����Ļ����Ȼ���
	glLoadIdentity();										// ����ģ�͹۲����
	glTranslatef(-1.5f, 0.0f, -6.0f);						// ���� 1.5 ��λ����������Ļ 6.0

	glBegin(GL_TRIANGLES);						// ����������
	glColor3f(1.0f, 0.0f, 0.0f);				// ���õ�ǰɫΪ��ɫ
	glVertex3f(0.0f, 1.0f, 0.0f);				// �϶���
	glColor3f(0.0f, 1.0f, 0.0f);				// ���õ�ǰɫΪ��ɫ
	glVertex3f(-1.0f, -1.0f, 0.0f);				// ����
	glColor3f(0.0f, 0.0f, 1.0f);				// ���õ�ǰɫΪ��ɫ
	glVertex3f(1.0f, -1.0f, 0.0f);				// ����
	glEnd();									// �����λ��ƽ���

	glTranslatef(3.0f, 0.0f, 0.0f);				// ����3��λ
	glColor3f(0.5f, 0.5f, 1.0f);				// һ���Խ���ǰɫ����Ϊ��ɫ
	glBegin(GL_QUADS);							// ����������
	glVertex3f(-1.0f, 1.0f, 0.0f);				// ����
	glVertex3f(1.0f, 1.0f, 0.0f);				// ����
	glVertex3f(1.0f, -1.0f, 0.0f);				// ����
	glVertex3f(-1.0f, -1.0f, 0.0f);				// ����
	glEnd();									// �����λ��ƽ���
}

//lesson2.��ĵ�һ�������
//�ڵ�һ���̵̳Ļ����ϣ����������һ�������κ�һ���ı��Ρ�Ҳ������Ϊ��ܼ򵥣������Ѿ�������һ�󲽣�Ҫ֪���κ���OpenGL�л��Ƶ�ģ�Ͷ��ᱻ�ֽ�Ϊ�����ּ򵥵�ͼ�Ρ�
//��������һ�Σ����ѧ������ڿռ����ģ�ͣ����һ�֪����Ȼ���ĸ��
void DrawLesson2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// �����Ļ����Ȼ���
	glLoadIdentity();										// ���õ�ǰ��ģ�͹۲����
	
	glTranslatef(-1.5f, 0.0f, -6.0f);						// ���� 1.5 ��λ����������Ļ 6.0
	glBegin(GL_TRIANGLES);									// ����������
	glVertex3f(0.0f, 1.0f, 0.0f);							// �϶���
	glVertex3f(-1.0f, -1.0f, 0.0f);							// ����
	glVertex3f(1.0f, -1.0f, 0.0f);							// ����
	glEnd();												// �����λ��ƽ���

	glTranslatef(3.0f, 0.0f, 0.0f);							// ����3��λ
	glBegin(GL_QUADS);										// ����������
	glVertex3f(-1.0f, 1.0f, 0.0f);							// ����
	glVertex3f(1.0f, 1.0f, 0.0f);							// ����
	glVertex3f(1.0f, -1.0f, 0.0f);							// ����
	glVertex3f(-1.0f, -1.0f, 0.0f);							// ����
	glEnd();												// �����λ��ƽ���

}

//lesson1.����һ��OpenGL����
//������̳���, �ҽ�������Windows�����д���OpenGL����.������ʾһ���յ�OpenGL����, �����ڴ��ں�ȫ��ģʽ���л�, ��ESC�˳�.���������Ժ�Ӧ�ó���Ŀ��.
//���OpenGL��ι����ǳ���Ҫ��������ڽ̵̳�ĩβ����Դ���򣬵���ǿ�ҽ��������ٶ�һ��̳̣�Ȼ���ٿ�ʼ���.
void DrawLesson1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// �����Ļ����Ȼ���
	glLoadIdentity();							// ���õ�ǰ��ģ�͹۲����
}

int DrawGLScene(GLvoid)	// �˹����а������еĻ��ƴ���
{
	DrawLesson(LESSON);
	return TRUE;		// һ�� OK
}

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)
{
	if (height == 0)						// ��ֹ�����
	{
		height = 1;							// ��Height��Ϊ1
	}

	glViewport(0, 0, width, height);		// ���õ�ǰ���ӿ�
	
	glMatrixMode(GL_PROJECTION);			// ѡ��ͶӰ����
	glLoadIdentity();						// ����ͶӰ����
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);	// �����ӿڵĴ�С
	
	glMatrixMode(GL_MODELVIEW);				// ѡ��ģ�͹۲����
	glLoadIdentity();						// ����ģ�͹۲����

}

BOOL CreateGLWindow(TCHAR* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;	// �������ƥ��Ľ��
	WNDCLASS	wc;				// ������ṹ
	DWORD		dwStyle;		// ���ڷ��
	DWORD		dwExStyle;		// ��չ���ڷ��
	RECT		WindowRect;		// ȡ�þ��ε����ϽǺ����½ǵ�����ֵ
	WindowRect.left = (long)0;			// ��Left   ��Ϊ 0
	WindowRect.right = (long)width;		// ��Right  ��ΪҪ��Ŀ��
	WindowRect.top = (long)0;			// ��Top    ��Ϊ 0
	WindowRect.bottom = (long)height;	// ��Bottom ��ΪҪ��ĸ߶�

	g_fullscreen = fullscreenflag;		// ����ȫ��ȫ����־

	g_hInstance = GetModuleHandle(NULL);	// ȡ�����Ǵ��ڵ�ʵ��

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		// �ƶ�ʱ�ػ�����Ϊ����ȡ��DC
	wc.lpfnWndProc = (WNDPROC)WndProc2;					// WndProc������Ϣ
	wc.cbClsExtra = 0;									// �޶��ⴰ������
	wc.cbWndExtra = 0;									// �޶��ⴰ������
	wc.hInstance = g_hInstance;							// ����ʵ��
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);				// װ��ȱʡͼ��
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// װ�����ָ��
	wc.hbrBackground = NULL;							// GL����Ҫ����
	wc.lpszMenuName = NULL;								// ����Ҫ�˵�
	wc.lpszClassName = TEXT("OpenG");							// �趨������
	if (!RegisterClass(&wc))							// ����ע�ᴰ����
	{
		MessageBox(NULL, _T("ע�ᴰ��ʧ��"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		ErrorExit(TEXT("RegisterClass"));
		return FALSE;
	}

	if (g_fullscreen)	// Ҫ����ȫ��ģʽ��?
	{
		DEVMODE dmScreenSettings;									// �豸ģʽ
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));		// ȷ���ڴ����Ϊ��
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);			// Devmode �ṹ�Ĵ�С
		dmScreenSettings.dmPelsWidth = width;						// ��ѡ��Ļ���
		dmScreenSettings.dmPelsHeight = height;						// ��ѡ��Ļ�߶�
		dmScreenSettings.dmBitsPerPel = bits;						// ÿ������ѡ��ɫ�����
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		
		// ����������ʾģʽ�����ؽ����ע: CDS_FULLSCREEN ��ȥ��״̬����
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// ��ģʽʧ�ܣ��ṩ����ѡ��˳����ڴ��������С�
			if (MessageBox(NULL, _T("ȫ��ģʽ�ڵ�ǰ�Կ�������ʧ�ܣ�\nʹ�ô���ģʽ��"), _T("NeHe G"), MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				g_fullscreen = FALSE;	// ѡ�񴰿�ģʽ(Fullscreen=FALSE)
			}
			else
			{
				// ����һ���Ի��򣬸����û��������
				MessageBox(NULL, _T("���򽫱��ر�"), _T("����"), MB_OK | MB_ICONSTOP);
				return FALSE;
			}
		}
	}

	if (g_fullscreen)								// �Դ���ȫ��ģʽ��?
	{
		dwExStyle = WS_EX_APPWINDOW;			// ��չ������
		dwStyle = WS_POPUP;						// ������
		ShowCursor(FALSE);						// �������ָ��
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;	// ��չ������
		dwStyle = WS_OVERLAPPEDWINDOW;					//  ������
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);	// �������ڴﵽ����Ҫ��Ĵ�С

	if (!(g_hWnd = CreateWindowEx(dwExStyle,				// ��չ������
								_T("OpenG"),				// ������
								title,					// ���ڱ���
								WS_CLIPSIBLINGS |		// ����Ĵ���������
								WS_CLIPCHILDREN |		// ����Ĵ���������
								dwStyle,				// ѡ��Ĵ�������
								0, 0,					// ����λ��
								WindowRect.right - WindowRect.left,	// ��������õĴ��ڿ��
								WindowRect.bottom - WindowRect.top,	// ��������õĴ��ڸ߶�
								NULL,					// �޸�����
								NULL,					// �޲˵�
								g_hInstance,				// ʵ��
								NULL))					// ����WM_CREATE�����κζ���
		)
	{
		KillGLWindow();	// ������ʾ��
		MessageBox(NULL, _T("���ܴ���һ�������豸������"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		ErrorExit(TEXT("CreateWindowEx"));
		return FALSE;
	}

	// pfd ���ߴ���������ϣ���Ķ�����������ʹ�õ����ظ�ʽ
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// ������ʽ�������Ĵ�С
		1,								// �汾��
		PFD_DRAW_TO_WINDOW |			// ��ʽ֧�ִ���
		PFD_SUPPORT_OPENGL |			// ��ʽ����֧��OpenGL
		PFD_DOUBLEBUFFER,				// ����֧��˫����
		PFD_TYPE_RGBA,					// ���� RGBA ��ʽ
		bits,							// ѡ��ɫ�����
		0, 0, 0, 0, 0, 0,				// ���Ե�ɫ��λ
		0,								// ��Alpha����
		0,								// ����Shift Bit
		0,								// ���ۼӻ���
		0, 0, 0, 0,						// ���Ծۼ�λ
		16,								// 16λ Z-���� (��Ȼ���)
		0,								// ���ɰ建��
		0,								// �޸�������
		PFD_MAIN_PLANE,					// ����ͼ��
		0,								// Reserved
		0, 0, 0							// ���Բ�����
	};

	if (!(g_hDC = GetDC(g_hWnd)))		// ȡ���豸��������ô?
	{
		KillGLWindow();					// ������ʾ��
		MessageBox(NULL, _T("���ܴ���һ����ƥ������ظ�ʽ"),_T( "����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;					// ���� FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(g_hDC, &pfd)))	// Windows �ҵ���Ӧ�����ظ�ʽ����?
	{
		KillGLWindow();	// ������ʾ��
		MessageBox(NULL, _T("�����������ظ�ʽ"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!SetPixelFormat(g_hDC, PixelFormat, &pfd))	// �ܹ��������ظ�ʽô?
	{
		KillGLWindow();	// ������ʾ��
		MessageBox(NULL, _T("�����������ظ�ʽ"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!(g_hRC = wglCreateContext(g_hDC)))		// �ܷ�ȡ����ɫ������?
	{
		KillGLWindow();	// ������ʾ��
		MessageBox(NULL, _T("���ܴ���OpenGL��Ⱦ������"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	if (!wglMakeCurrent(g_hDC, g_hRC))		// ���Լ�����ɫ������
	{
		KillGLWindow();	// ������ʾ��
		MessageBox(NULL, _T("���ܼ��ǰ��OpenGL��Ȼ������"), _T("����"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	ShowWindow(g_hWnd, SW_SHOW);				// ��ʾ����
	SetForegroundWindow(g_hWnd);				// ����������ȼ�
	SetFocus(g_hWnd);							// ���ü��̵Ľ������˴���

	ReSizeGLScene(width, height);				// ����͸�� GL ��Ļ
	
	if (!InitGL())								// ��ʼ���½���GL����
	{
		KillGLWindow();							// ������ʾ��
		MessageBox(NULL, _T("Initialization Failed."), _T("ERROR"), MB_OK | MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;								// �ɹ�
}

GLvoid KillGLWindow(GLvoid)
{
	if (g_fullscreen)							// ���Ǵ���ȫ��ģʽ��?
	{
		ChangeDisplaySettings(NULL, 0);			// �ǵĻ����л�������
		ShowCursor(TRUE);						// ��ʾ���ָ��
	}
	if (g_hRC)								// ����ӵ��OpenGL��Ⱦ��������?
	{
		if (!wglMakeCurrent(NULL, NULL))					// �����ܷ��ͷ�DC��RC������?
		{
			MessageBox(NULL, _T("�ͷ�DC��RCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		}
		if (!wglDeleteContext(g_hRC))					// �����ܷ�ɾ��RC?
		{
			MessageBox(NULL, _T("�ͷ�RCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		}
		g_hRC = NULL;							// ��RC��Ϊ NULL
	}
	if (g_hDC && !ReleaseDC(g_hWnd, g_hDC))					// �����ܷ��ͷ� DC?
	{
		MessageBox(NULL, _T("�ͷ�DCʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		g_hDC = NULL;							// �� DC ��Ϊ NULL
	}
	if (g_hWnd && !DestroyWindow(g_hWnd))					// �ܷ����ٴ���?
	{
		MessageBox(NULL, _T("�ͷŴ��ھ��ʧ�ܡ�"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		g_hWnd = NULL;							// �� g_hWnd ��Ϊ NULL
	}
	if (!UnregisterClass(_T("OpenG"), g_hInstance))				// �ܷ�ע����?
	{
		MessageBox(NULL, _T("����ע�������ࡣ"), _T("�رմ���"), MB_OK | MB_ICONINFORMATION);
		g_hInstance = NULL;							// �� g_hInstance ��Ϊ NULL
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

int WINAPI _tWinMain2(	HINSTANCE	hInstance,				// ��ǰ����ʵ��
						HINSTANCE	hPrevInstance,			// ǰһ������ʵ�� always NULL
						LPTSTR		lpCmdLine,				// �����в���
						int			nCmdShow)				// ������ʾ״̬
{
	MSG		msg;			// Windowsx��Ϣ�ṹ
	BOOL	done = FALSE;	// �����˳�ѭ����Bool ����

	// ��ʾ�û�ѡ������ģʽ
	//if (MessageBox(NULL, _T("������ȫ��ģʽ������ô��"), _T("����ȫ��ģʽ"), MB_YESNO | MB_ICONQUESTION) == IDNO)
	{
		g_fullscreen = FALSE;	// FALSEΪ����ģʽ
	}

	// ����OpenGL����
	// CreateGLWindow�����Ĳ�������Ϊ���⡢��ȡ��߶ȡ�ɫ����ȣ��Լ�ȫ����־��
	if (!CreateGLWindow(_T("NeHe's OpenGL������"), 640, 480, 16, g_fullscreen))
	{
		return 0;	// ʧ���˳�
	}

	while (!done)	// ����ѭ��ֱ�� done=TRUE
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))	// ����Ϣ�ڵȴ���?
		{
			if (msg.message == WM_QUIT)					// �յ��˳���Ϣ?
			{
				done = TRUE;							// �ǣ���done=TRUE
			}
			else										// ���ǣ���������Ϣ
			{
				TranslateMessage(&msg);					// ������Ϣ
				DispatchMessage(&msg);					// ������Ϣ
			}
		}
		else											// ���û����Ϣ
		{
			// ���Ƴ���������ESC��������DrawGLScene()���˳���Ϣ
			if (g_active)								// ���򼤻��ô?
			{
				if (g_keys[VK_ESCAPE])					// ESC ������ô?
				{
					done = TRUE;						// ESC �����˳��ź�
				}
				else									// �����˳���ʱ��ˢ����Ļ
				{
					DrawGLScene();						// ���Ƴ���
					SwapBuffers(g_hDC);					// �������� (˫����)
				}
			}

			if (g_keys[VK_F1])							// F1��������ô?
			{
				g_keys[VK_F1] = FALSE;					// ���ǣ�ʹ��Ӧ��Key�����е�ֵΪ FALSE
				KillGLWindow();							// ���ٵ�ǰ�Ĵ���
				g_fullscreen = !g_fullscreen;			// �л� ȫ�� / ���� ģʽ
				
				// �ؽ� OpenGL ����
				if (!CreateGLWindow(_T("NeHe's OpenGL ������"), 640, 480, 16, g_fullscreen))
				{
					return 0; // �������δ�ܴ����������˳�
				}
			}
		}
	}

	// �رճ���
	KillGLWindow();			// ���ٴ���
	return (msg.wParam);	// �˳�����
}
