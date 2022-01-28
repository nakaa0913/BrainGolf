/*==============================================================================

   �e�N�X�`���̕`�� [main.cpp]
                                                         Author : 
                                                         Date   : 
--------------------------------------------------------------------------------

==============================================================================*/
#include "main.h"
#include <time.h>
#include "renderer.h"
#include "input.h"
#include "sound.h"
#include "texture.h"
#include "scene.h"
#include "fade.h"
#include "sprite.h"
#include "keyboard.h"
#include "Keylogger.h"
#include "mouse.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CLASS_NAME			"GameWindow"			// �E�C���h�E�̃N���X��
#define WINDOW_CAPTION		"�v���g�^�C�v"			// �E�C���h�E�̃L���v�V������

//*****************************************************************************
// �\���̒�`
//*****************************************************************************

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// �O���[�o���ϐ�:
//*****************************************************************************

// �}�E�X�g������
long g_MouseX = 0;
long g_MouseY = 0;
bool g_MouseLClick = false;
bool g_MouseRClick = false;
bool g_MouseScroll = false;

static int g_Tex_cursor;	// �}�E�X�J�[�\���̃e�N�X�`���p
bool cursor_isUse = true;	// �}�E�X�J�[�\���̕\���p
int cursor_fade_state = 0;	// �}�E�X�J�[�\���̃t�F�[�h�C�������ǂ���,0:�t�F�[�h������Ȃ�,1:�t�F�[�h�C����,2�t�F�[�h�A�E�g��
int cursor_fade_count = 0;	// �}�E�X�J�[�\���̃t�F�[�h���̏ꍇ�̃J�E���g
int cursor_fadetime = 0;	// �t�F�[�h����ꍇ���ꂾ�������ăt�F�[�h����
float cursor_Clarity = 1.0f;		// �J�[�\���̓����x

#ifdef _DEBUG
int		g_CountFPS;							// FPS�J�E���^
char	g_DebugStr[2048] = WINDOW_CAPTION;	// �f�o�b�O�����\���p
#endif

											//=============================================================================
// ���C���֐�
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j
	UNREFERENCED_PARAMETER(lpCmdLine);		// �����Ă��ǂ����ǁA�x�����o��i���g�p�錾�j

	//�����_���V�[�h�̏�����
	srand((unsigned int)time(NULL));

	// ���Ԍv���p
	DWORD dwExecLastTime;
	DWORD dwFPSLastTime;
	DWORD dwCurrentTime;
	DWORD dwFrameCount;
	
	WNDCLASSEX	wcex = {
		sizeof(WNDCLASSEX),
		CS_CLASSDC,
		WndProc,
		0,
		0,
		hInstance,
		NULL,
		LoadCursor(NULL, IDC_ARROW),
		(HBRUSH)(COLOR_WINDOW+1),
		NULL,
		CLASS_NAME,
		NULL
	};
	HWND		hWnd;
	MSG			msg;
	
	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̍쐬
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// �E�B���h�E�̍����W
						CW_USEDEFAULT,																		// �E�B���h�E�̏���W
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// �E�B���h�E����
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// �E�B���h�E�c��
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectX�̏�����(�E�B���h�E���쐬���Ă���s��)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// �t���[���J�E���g������
	timeBeginPeriod(1);	// ����\��ݒ�
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// �V�X�e���������~���b�P�ʂŎ擾
	dwCurrentTime = dwFrameCount = 0;
	
	// �E�C���h�E�̕\��(Init()�̌�ɌĂ΂Ȃ��Ƒʖ�)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// ���b�Z�[�W���[�v
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()���Ă΂ꂽ�烋�[�v�I��
				break;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			dwCurrentTime = timeGetTime();					// �V�X�e���������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1�b���ƂɎ��s
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;							// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / 60))	// 1/60�b���ƂɎ��s
			{
				dwExecLastTime = dwCurrentTime;	// ��������������ۑ�

#ifdef _DEBUG	// �f�o�b�O�ł̎�����FPS��\������
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// �X�V����
				Draw();				// �`�揈��

#ifdef _DEBUG	// �f�o�b�O�ł̎������\������
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " MX:%d MY:%d LClick:%d RClick:%d Scroll:%d", GetMousePosX(), GetMousePosY(), GetMouseLClickNum(), GetMouseRClickNum(), GetMouseScrollNum());
				SetWindowText(hWnd, g_DebugStr);
#endif



				CheckScene();		//�V�[���ڍs�̃`�F�b�N

				dwFrameCount++;		// �����񐔂̃J�E���g�����Z
			}
		}
	}
	
	timeEndPeriod(1);				// ����\��߂�

	// �I������
	Uninit();

	// �E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// �v���V�[�W��
//=============================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Keyboard_ProcessMessage(message, wParam, lParam);
	Mouse_ProcessMessage(message, wParam, lParam);

	switch( message )
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:					// [ESC]�L�[�������ꂽ
			DestroyWindow(hWnd);		// �E�B���h�E��j������悤�w������
			break;
		}
		break;

	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);		// �}�E�X��X���W���擾
		g_MouseY = HIWORD(lParam);		// �}�E�X��Y���W���擾
		break;

	case WM_LBUTTONDOWN:
		g_MouseLClick = true;			// ���N���b�N��true
		break;

	case WM_LBUTTONUP:
		g_MouseLClick = false;			// ���N���b�N���Ă��Ȃ���false
		break;

	case WM_RBUTTONDOWN:
		g_MouseRClick = true;
		break;

	case WM_RBUTTONUP:
		g_MouseRClick = false;
		break;

	case WM_MOUSEWHEEL:
		g_MouseScroll = true;
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		g_MouseX = LOWORD(lParam);		// �}�E�X��X���W���擾
		g_MouseY = HIWORD(lParam);		// �}�E�X��Y���W���擾
	}

	return 0;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// �����_�����O�����̏�����
	InitRenderer(hInstance, hWnd, bWindow);

	// ���͏����̏�����
	InitInput(hInstance, hWnd);
	Mouse_Initialize(hWnd);
	Keyboard_Initialize();

	// �T�E���h�����̏�����
	InitSound(hWnd);

	// �t�F�[�h�����̏�����
	InitFade();

	// �X�v���C�g�̏�����
	InitSprite();

	//�V�[���̏������i�`�[�����S����X�^�[�g
	SetFadeColor(0.0f, 0.0f, 0.0f);
	SceneFadeIn(SCENE_LOGO);

	// �}�E�X�̏�����
	//g_Tex_cursor = LoadTexture("data/TEXTURE/other_effect/cursor.png");
	g_Tex_cursor = LoadTexture("data/TEXTURE/other_effect/cursor.png");
	//g_Tex_cursor = LoadTexture("data/TEXTURE/other_effect/black.png");

	cursor_isUse = true;	// �}�E�X�J�[�\���̕\���p
	cursor_fade_state = 0;	// �}�E�X�J�[�\���̃t�F�[�h�C�������ǂ���,0:�t�F�[�h������Ȃ�,1:�t�F�[�h�C����,2�t�F�[�h�A�E�g��
	cursor_fade_count = 0;	// �}�E�X�J�[�\���̃t�F�[�h���̏ꍇ�̃J�E���g
	cursor_fadetime = 0;	// �t�F�[�h����ꍇ���ꂾ�������ăt�F�[�h����
	cursor_Clarity = 1.0f;

	// �����ݒ�
	//SetCursorState(true, 2, 180);	// �����Ȃ蓧���ɂ��Ă���


	return S_OK;
}


//=============================================================================
// �I������
//=============================================================================
void Uninit(void)
{
	// �X�v���C�g�̏I������
	UninitSprite();

	// ���_�Ǘ��̏I������
	UninitFade();

	// �e�N�X�`���̉��
	UninitTexture();

	// �T�E���h�̏I������
	StopSoundAll();
	UninitSound();

	// ���͂̏I������
	UninitInput();

	// �����_�����O�̏I������
	UninitRenderer();
}

//=============================================================================
// �X�V����
//=============================================================================
void Update(void)
{
	//���͌n�̍X�V����
	UpdateInput();

	// �}�E�X�J�[�\���̃A�b�v�f�[�g����
	//UpdataCursor();

	//�V�[���̍X�V
	UpdateScene();
}

//=============================================================================
// �`�揈��
//=============================================================================
void Draw(void)
{
	// �o�b�N�o�b�t�@�N���A
	Clear();

	// �}�g���N�X�ݒ�
	SetWorldViewProjection2D();//���W��2D�ϊ�

	// 2D�`��Ȃ̂Ő[�x����
	SetDepthEnable(false);

	// �V�[���̕`�揈��
	DrawScene();

	// �J�[�\���̏���
	if (cursor_isUse == true)
	{
		float mouse_pos_X = GetMousePosX();
		float mouse_pos_Y = GetMousePosY();

		//D3DXCOLOR Ccolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, cursor_Clarity);
		D3DXCOLOR Ccolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		float sizeX = 80.0f;
		float sizeY = 80.0f;
		float posX = mouse_pos_X;
		float posY = mouse_pos_Y;
		DrawSpriteLeftTopColor(g_Tex_cursor, posX, posY, sizeX, sizeY, 0.0f, 0.0f, 1.0f, 1.0f, Ccolor);
	}

	// �o�b�N�o�b�t�@�A�t�����g�o�b�t�@����ւ�
	Present();
}


float frand(void)
{
	return (float)rand() / RAND_MAX;
}

// �}�E�X�̏���
long GetMousePosX(void)
{


	//return g_MouseX * 3 / 4;						// �t���X�N���[��(1920 * 1080)�Ȃ炱����
	return g_MouseX * SCREEN_WIDTH_MOUSEGAP;		// �E�B���h�E���[�h(1440 * 810)�Ȃ炱����

	// 1440x810
	// 1920x1080 �t���X�N���[�� ����1.33333�{, 4/3�{
	// �t�Ɍ����� 1920 * 3 / 4 ��1440
}


long GetMousePosY(void)
{
	//return g_MouseY * 3 / 4;						// �t���X�N���[��(1920 * 1080)�Ȃ炱����
	return g_MouseY * SCREEN_HEIGHT_MOUSEGAP;		// �E�B���h�E���[�h(1440 * 810)�Ȃ炱����
}

bool GetMouseLClick(void)
{
	return g_MouseLClick;
}

bool GetMouseRClick(void)
{
	return g_MouseRClick;
}

int GetMouseLClickNum(void)
{
	if (g_MouseLClick)
		return 1;

	return 0;
}

int GetMouseRClickNum(void)
{
	if (g_MouseRClick)
		return 2;

	return 0;
}

bool GetMouseScroll(void)
{
	return g_MouseScroll;
}

bool GetMouseScrollFalse(void)
{
	return g_MouseScroll = false;
}

int GetMouseScrollNum(void)
{
	if (g_MouseScroll)
		return 2;

	return 0;
}

#ifdef _DEBUG
char* GetDebugStr(void)
{
	return g_DebugStr;
}
#endif

// �\�����邩�ǂ����A�t�F�[�h�C�����A�E�g��(0,1,2)�A�t�F�[�h����ꍇ���t���[�������ăt�F�[�h���邩
void SetCursorState(bool isUse, int fade_state, int fadetime)
{
	//cursor_isUse = isUse;				// �}�E�X�J�[�\���̕\���p
	//cursor_fade_state = fade_state;		// �}�E�X�J�[�\���̃t�F�[�h�C�������ǂ���,0:�t�F�[�h������Ȃ�,1:�t�F�[�h�C����,2�t�F�[�h�A�E�g��
	//cursor_fade_count = 0;				// �}�E�X�J�[�\���̃t�F�[�h���̏ꍇ�̃J�E���g
	//cursor_fadetime = fadetime;			// �t�F�[�h����ꍇ���ꂾ�������ăt�F�[�h����

	return;
}

void UpdataCursor(void)
{
	//// �J�[�\���̃A�b�v�f�[�g
	//if (cursor_fade_state == 1)
	//{
	//	// �t�F�[�h�C��
	//	int oneframe = 1.0f / cursor_fadetime;
	//	cursor_Clarity = oneframe * cursor_fade_count;
	//	if (cursor_fade_count >= cursor_fadetime)
	//	{
	//		// �t�F�[�h�������I������
	//		cursor_Clarity = 1.0f;
	//		cursor_fade_state = 0;
	//	}
	//	else if (cursor_Clarity >= 1.0f)
	//		cursor_Clarity = 1.0f;

	//	cursor_fade_count++;
	//}
	//if (cursor_fade_state == 2)
	//{
	//	// �t�F�[�h�A�E�g
	//	int oneframe = 1.0f / cursor_fadetime;
	//	cursor_Clarity = 1.0f - oneframe * cursor_fade_count;
	//	if (cursor_fade_count >= cursor_fadetime)
	//	{
	//		// �t�F�[�h�������I������
	//		cursor_Clarity = 0.0f;
	//		cursor_fade_state = 0;
	//	}
	//	else if (cursor_Clarity <= 0.0f)
	//		cursor_Clarity = 0.0f;

	//	cursor_fade_count++;
	//}

	return;
}