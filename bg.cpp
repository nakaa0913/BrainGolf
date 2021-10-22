//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 
//
//=============================================================================
#include "bg.h"
#include "texture.h"
#include "sprite.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
struct MAP_DATA_T 
{
	D3DXVECTOR2 uv;		//UV値
	int			stop;	//侵入可能フラグ(1は進入禁止)

};

MAP_DATA_T g_MapInfo[3] =
{
	{ { 0.25f,   0.0f}, 0},//なにもなし
	{ {  0.0f, 0.625f}, 1},//木
	{ {0.625f, 0.625f}, 1},//切り株
};


//*****************************************************************************
// グローバル変数
//*****************************************************************************
int g_map_base[MAP_Y][MAP_X] = {
	//マップ０
	{0,0,0,2,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0},
	////マップ１
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
	//{1,1,1,1,1,1,1,1,1,1},
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
	//{0,0,0,0,0,1,0,0,0,0},
};

int g_map_obj[MAP_Y][MAP_X] = {
	//マップ０
	{1,1,1,2,1,1,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1},

	////マップ１
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,1,0,1,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,1,0,1,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
	//{0,0,0,0,0,0,0,0,0,0},
};

//マップの当たり判定用データ
int g_map_hitchk[2][MAP_Y][MAP_X] =
{
	{//マップ０
		{1,1,1,2,1,1,1},
		{1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1}, 
		{1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1},
		{1,1,1,1,1,1,1},
	},
	//{//マップ１
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,1,0,1,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,1,0,1,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//	{0,0,0,0,0,0,0,0,0,0,0,0},
	//},
};



static int g_Ground = 0;		// 背景用テクスチャ情報
static int g_CurrentPos = 0;	// 現在のマップ座標

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(void)
{
	g_Ground = LoadTexture("data/TEXTURE/basechip.png");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{

}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBG(void)
{

}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBG(void)
{
	float offset_y;

	if (g_CurrentPos == 0)
		offset_y = 0.0f;
	else
		offset_y = -560.0f;

	//レイヤー０の表示
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			switch (g_map_base[y][x])
			{
			case 0://草原
				DrawSpriteLeftTop(g_Ground, 0.0f + x * 80.0f, offset_y + y * 80.0f, 80.0f, 80.0f,   0.0f, 0.0f, 0.125f, 0.125f);
				break;
			case 1://道
				DrawSpriteLeftTop(g_Ground, 0.0f + x * 80.0f, offset_y + y * 80.0f, 80.0f, 80.0f, 0.625f, 0.0f, 0.125f, 0.125f);
				break;
			case 2://ゴール
				DrawSpriteLeftTop(g_Ground, 0.0f + x * 80.0f, offset_y + y * 80.0f, 80.0f, 80.0f, 0.625f, 0.0f, 0.125f, 0.125f);
				break;
			}
		}
	}

	//背景オブジェクトの表示
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			MAP_DATA_T mapchip;
			mapchip = g_MapInfo[ g_map_obj[y][x] ];

			DrawSpriteLeftTop(g_Ground, 0.0f + x * 80.0f, offset_y + y * 80.0f, 80.0f, 80.0f, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
		}
	}
}

int GetMapEnter(D3DXVECTOR2 pos)
{
	int x, y;
	x = (int)(pos.x / 80.0f);//座標をマップチップ一つの大きさで割る
	y = (int)(pos.y / 80.0f);

	return g_map_hitchk[g_CurrentPos][y][x];
}

void SetCurrentMap(int next)
{
	g_CurrentPos = next;
}
