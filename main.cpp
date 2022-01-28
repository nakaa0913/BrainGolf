/*==============================================================================

   テクスチャの描画 [main.cpp]
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
// マクロ定義
//*****************************************************************************
#define CLASS_NAME			"GameWindow"			// ウインドウのクラス名
#define WINDOW_CAPTION		"プロトタイプ"			// ウインドウのキャプション名

//*****************************************************************************
// 構造体定義
//*****************************************************************************

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
void Uninit(void);
void Update(void);
void Draw(void);


//*****************************************************************************
// グローバル変数:
//*****************************************************************************

// マウス使う処理
long g_MouseX = 0;
long g_MouseY = 0;
bool g_MouseLClick = false;
bool g_MouseRClick = false;
bool g_MouseScroll = false;

static int g_Tex_cursor;	// マウスカーソルのテクスチャ用
bool cursor_isUse = true;	// マウスカーソルの表示用
int cursor_fade_state = 0;	// マウスカーソルのフェードイン中がどうか,0:フェード中じゃない,1:フェードイン中,2フェードアウト中
int cursor_fade_count = 0;	// マウスカーソルのフェード中の場合のカウント
int cursor_fadetime = 0;	// フェードする場合これだけかけてフェードする
float cursor_Clarity = 1.0f;		// カーソルの透明度

#ifdef _DEBUG
int		g_CountFPS;							// FPSカウンタ
char	g_DebugStr[2048] = WINDOW_CAPTION;	// デバッグ文字表示用
#endif

											//=============================================================================
// メイン関数
//=============================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);	// 無くても良いけど、警告が出る（未使用宣言）
	UNREFERENCED_PARAMETER(lpCmdLine);		// 無くても良いけど、警告が出る（未使用宣言）

	//ランダムシードの初期化
	srand((unsigned int)time(NULL));

	// 時間計測用
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
	
	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの作成
	hWnd = CreateWindow(CLASS_NAME,
						WINDOW_CAPTION,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT,																		// ウィンドウの左座標
						CW_USEDEFAULT,																		// ウィンドウの上座標
						SCREEN_WIDTH + GetSystemMetrics(SM_CXDLGFRAME)*2,									// ウィンドウ横幅
						SCREEN_HEIGHT + GetSystemMetrics(SM_CXDLGFRAME)*2+GetSystemMetrics(SM_CYCAPTION),	// ウィンドウ縦幅
						NULL,
						NULL,
						hInstance,
						NULL);

	// DirectXの初期化(ウィンドウを作成してから行う)
	if(FAILED(Init(hInstance, hWnd, true)))
	{
		return -1;
	}

	// フレームカウント初期化
	timeBeginPeriod(1);	// 分解能を設定
	dwExecLastTime = dwFPSLastTime = timeGetTime();	// システム時刻をミリ秒単位で取得
	dwCurrentTime = dwFrameCount = 0;
	
	// ウインドウの表示(Init()の後に呼ばないと駄目)
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	
	// メッセージループ
	while(1)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if(msg.message == WM_QUIT)
			{// PostQuitMessage()が呼ばれたらループ終了
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
			dwCurrentTime = timeGetTime();					// システム時刻を取得

			if ((dwCurrentTime - dwFPSLastTime) >= 1000)	// 1秒ごとに実行
			{
#ifdef _DEBUG
				g_CountFPS = dwFrameCount;
#endif
				dwFPSLastTime = dwCurrentTime;				// FPSを測定した時刻を保存
				dwFrameCount = 0;							// カウントをクリア
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000.0f / 60))	// 1/60秒ごとに実行
			{
				dwExecLastTime = dwCurrentTime;	// 処理した時刻を保存

#ifdef _DEBUG	// デバッグ版の時だけFPSを表示する
				wsprintf(g_DebugStr, WINDOW_CAPTION);
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " FPS:%d", g_CountFPS);
				SetWindowText(hWnd, g_DebugStr);
#endif

				Update();			// 更新処理
				Draw();				// 描画処理

#ifdef _DEBUG	// デバッグ版の時だけ表示する
				wsprintf(&g_DebugStr[strlen(g_DebugStr)], " MX:%d MY:%d LClick:%d RClick:%d Scroll:%d", GetMousePosX(), GetMousePosY(), GetMouseLClickNum(), GetMouseRClickNum(), GetMouseScrollNum());
				SetWindowText(hWnd, g_DebugStr);
#endif



				CheckScene();		//シーン移行のチェック

				dwFrameCount++;		// 処理回数のカウントを加算
			}
		}
	}
	
	timeEndPeriod(1);				// 分解能を戻す

	// 終了処理
	Uninit();

	// ウィンドウクラスの登録を解除
	UnregisterClass(CLASS_NAME, wcex.hInstance);

	return (int)msg.wParam;
}

//=============================================================================
// プロシージャ
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
		case VK_ESCAPE:					// [ESC]キーが押された
			DestroyWindow(hWnd);		// ウィンドウを破棄するよう指示する
			break;
		}
		break;

	case WM_MOUSEMOVE:
		g_MouseX = LOWORD(lParam);		// マウスのX座標を取得
		g_MouseY = HIWORD(lParam);		// マウスのY座標を取得
		break;

	case WM_LBUTTONDOWN:
		g_MouseLClick = true;			// 左クリックでtrue
		break;

	case WM_LBUTTONUP:
		g_MouseLClick = false;			// 左クリックしていないとfalse
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
		g_MouseX = LOWORD(lParam);		// マウスのX座標を取得
		g_MouseY = HIWORD(lParam);		// マウスのY座標を取得
	}

	return 0;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	// レンダリング処理の初期化
	InitRenderer(hInstance, hWnd, bWindow);

	// 入力処理の初期化
	InitInput(hInstance, hWnd);
	Mouse_Initialize(hWnd);
	Keyboard_Initialize();

	// サウンド処理の初期化
	InitSound(hWnd);

	// フェード処理の初期化
	InitFade();

	// スプライトの初期化
	InitSprite();

	//シーンの初期化（チームロゴからスタート
	SetFadeColor(0.0f, 0.0f, 0.0f);
	SceneFadeIn(SCENE_LOGO);

	// マウスの初期化
	//g_Tex_cursor = LoadTexture("data/TEXTURE/other_effect/cursor.png");
	g_Tex_cursor = LoadTexture("data/TEXTURE/other_effect/cursor.png");
	//g_Tex_cursor = LoadTexture("data/TEXTURE/other_effect/black.png");

	cursor_isUse = true;	// マウスカーソルの表示用
	cursor_fade_state = 0;	// マウスカーソルのフェードイン中がどうか,0:フェード中じゃない,1:フェードイン中,2フェードアウト中
	cursor_fade_count = 0;	// マウスカーソルのフェード中の場合のカウント
	cursor_fadetime = 0;	// フェードする場合これだけかけてフェードする
	cursor_Clarity = 1.0f;

	// 初期設定
	//SetCursorState(true, 2, 180);	// いきなり透明にしておく


	return S_OK;
}


//=============================================================================
// 終了処理
//=============================================================================
void Uninit(void)
{
	// スプライトの終了処理
	UninitSprite();

	// 頂点管理の終了処理
	UninitFade();

	// テクスチャの解放
	UninitTexture();

	// サウンドの終了処理
	StopSoundAll();
	UninitSound();

	// 入力の終了処理
	UninitInput();

	// レンダリングの終了処理
	UninitRenderer();
}

//=============================================================================
// 更新処理
//=============================================================================
void Update(void)
{
	//入力系の更新処理
	UpdateInput();

	// マウスカーソルのアップデート処理
	//UpdataCursor();

	//シーンの更新
	UpdateScene();
}

//=============================================================================
// 描画処理
//=============================================================================
void Draw(void)
{
	// バックバッファクリア
	Clear();

	// マトリクス設定
	SetWorldViewProjection2D();//座標の2D変換

	// 2D描画なので深度無効
	SetDepthEnable(false);

	// シーンの描画処理
	DrawScene();

	// カーソルの処理
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

	// バックバッファ、フロントバッファ入れ替え
	Present();
}


float frand(void)
{
	return (float)rand() / RAND_MAX;
}

// マウスの処理
long GetMousePosX(void)
{


	//return g_MouseX * 3 / 4;						// フルスクリーン(1920 * 1080)ならこっち
	return g_MouseX * SCREEN_WIDTH_MOUSEGAP;		// ウィンドウモード(1440 * 810)ならこっち

	// 1440x810
	// 1920x1080 フルスクリーン ↑の1.33333倍, 4/3倍
	// 逆に言うと 1920 * 3 / 4 ＝1440
}


long GetMousePosY(void)
{
	//return g_MouseY * 3 / 4;						// フルスクリーン(1920 * 1080)ならこっち
	return g_MouseY * SCREEN_HEIGHT_MOUSEGAP;		// ウィンドウモード(1440 * 810)ならこっち
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

// 表示するかどうか、フェードインかアウトか(0,1,2)、フェードする場合何フレームかけてフェードするか
void SetCursorState(bool isUse, int fade_state, int fadetime)
{
	//cursor_isUse = isUse;				// マウスカーソルの表示用
	//cursor_fade_state = fade_state;		// マウスカーソルのフェードイン中がどうか,0:フェード中じゃない,1:フェードイン中,2フェードアウト中
	//cursor_fade_count = 0;				// マウスカーソルのフェード中の場合のカウント
	//cursor_fadetime = fadetime;			// フェードする場合これだけかけてフェードする

	return;
}

void UpdataCursor(void)
{
	//// カーソルのアップデート
	//if (cursor_fade_state == 1)
	//{
	//	// フェードイン
	//	int oneframe = 1.0f / cursor_fadetime;
	//	cursor_Clarity = oneframe * cursor_fade_count;
	//	if (cursor_fade_count >= cursor_fadetime)
	//	{
	//		// フェード処理を終了する
	//		cursor_Clarity = 1.0f;
	//		cursor_fade_state = 0;
	//	}
	//	else if (cursor_Clarity >= 1.0f)
	//		cursor_Clarity = 1.0f;

	//	cursor_fade_count++;
	//}
	//if (cursor_fade_state == 2)
	//{
	//	// フェードアウト
	//	int oneframe = 1.0f / cursor_fadetime;
	//	cursor_Clarity = 1.0f - oneframe * cursor_fade_count;
	//	if (cursor_fade_count >= cursor_fadetime)
	//	{
	//		// フェード処理を終了する
	//		cursor_Clarity = 0.0f;
	//		cursor_fade_state = 0;
	//	}
	//	else if (cursor_Clarity <= 0.0f)
	//		cursor_Clarity = 0.0f;

	//	cursor_fade_count++;
	//}

	return;
}