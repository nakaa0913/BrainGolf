//=============================================================================
//
// 背景処理 [bg.cpp]
// Author : 
//
//=============================================================================
#include "bg.h"
#include "texture.h"
#include "sprite.h"
#include "stagedata.h"
#include "FileDataManagement.h"


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

MAP_DATA_T g_MapInfo[9] =
{
	{ { 0.25f,   0.0f}, 0},//なにもなし
	{ {  0.125f, 0.125f}, 1},//block
	{ {0.375f, 0.125f}, 1},//goal
	{ {0.625f, 0.125f}, 1},//speedup
	{ {0.25f, 0.125f}, 1},//warp
	{ {0.25f, 0.125f}, 1},//warp
	{ {0.75f, 0.0f}, 1},//bunker
	{ {0.75f, 0.125f}, 1},//switch
	{ {0.5f, 0.125f}, 1},//hansya
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
		{1,1,1,1,1,1,2, 1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,3,0,0,0, 0,3,3,3,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0, 0,0,0,0,3,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,6,6,6,0,0,0, 0,0,0,0,0,5,1},
		{1,1,1,1,1,1,1, 1,1,1,1,1,1,1}

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
		{1,1,1,1,1,1,2, 1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,3,0,0,0, 0,3,3,3,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,1,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,1,1,1,1,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0, 0,0,0,0,3,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,1,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0, 0,0,0,0,0,0,1},
		{1,6,6,6,0,0,0, 0,0,0,0,0,5,1},
		{1,1,1,1,1,1,1, 1,1,1,1,1,1,1}
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
	//g_Ground = LoadTexture("data/TEXTURE/basechip.png");
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
	STAGEDATA* p_Stagedata = GetStagedata();

	float offset_y;

	if (g_CurrentPos == 0)
		offset_y = 0.0f;
	else
		offset_y = -560.0f;

	int asdddddd = 0;

	//レイヤー０の表示
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			switch (p_Stagedata->maparray[y][x])
			{
			case 0://草原
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				break;
			case 1://道
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				break;
			case 2://ゴール
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				break;
			case 3://加速
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				break;
			case 4://ワープ
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				break;
			case 5://ワープ
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				break;
			case 6://砂
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				break;
			default:
				//exit(4);			// ふつうここに来ることはないのでエラーとして強制しておく
				//					// 下の背景オブジェクトの設定をしていないと、case10とか11とかを設定しても反映されない。
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
			mapchip = g_MapInfo[p_Stagedata->maparray[y][x]];

			DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
		}
	}
}

int GetMapEnter(D3DXVECTOR2 pos)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	int x, y;
	x = (int)(pos.x / MAP_CHIP_SIZE_X);//座標をマップチップ一つの大きさで割る
	y = (int)(pos.y / MAP_CHIP_SIZE_Y);

	return p_Stagedata->maparray[y][x];
}

void SetCurrentMap(int next)
{
	g_CurrentPos = next;
}

int CheckBlockdata(int BlockX, int BlockY)
{
	//int BlockData = 0;
	//BlockData = g_map_hitchk[0][BlockY][BlockX];
	////BlockData = p_Stagedata->maparray[y][x];

	//return BlockData;

	STAGEDATA* p_Stagedata = GetStagedata();

	int BlockData = 0;
	BlockData = p_Stagedata->maparray[BlockY][BlockX];

	return BlockData;
}

//////////////////////////////////////////////////stagedataにあわせてここから追加したやつ


//int GetMapEnter2(D3DXVECTOR2 pos)
//{
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	int x, y;
//	x = (int)(pos.x / MAP_CHIP_SIZE_X);//座標をマップチップ一つの大きさで割る
//	y = (int)(pos.y / MAP_CHIP_SIZE_Y);
//
//	return p_Stagedata->maparray[y][x];
//}

//int CheckBlockdata2(int BlockX, int BlockY)
//{
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	int BlockData = 0;
//	BlockData = p_Stagedata->maparray[BlockY][BlockX];
//
//	return BlockData;
//}