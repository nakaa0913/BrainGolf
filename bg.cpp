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

MAP_DATA_T g_MapInfo[16] =
{
	{ {0.25f , 0.0f}, 0},//なにもなし		0
	{ {0.125f, 0.125f}, 1},//block			1
	{ {0.375f, 0.125f}, 1},//goal			2
	{ {0.625f, 0.125f}, 1},//speedup上		3
	{ {0.625f, 0.25f}, 1},//speedup下		4
	{ {0.625f, 0.375f}, 1},//speedup右		5
	{ {0.625f, 0.5f}, 1},//speedup左		6
	{ {0.875f, 0.25f}, 1},//speedup右上		7
	{ {0.875f, 0.375f}, 1},//speedup右下	8
	{ {0.75f , 0.375f}, 1},//speedup左下	9
	{ {0.75f , 0.25f}, 1},//speedup左上		10
	{ {0.25f , 0.125f}, 1},//warp			11
	{ {0.25f , 0.125f}, 1},//warp			12
	{ {0.75f , 0.0f}, 1},//bunker			13
	{ {0.75f , 0.125f}, 1},//switch			14
	{ {0.5f  , 0.125f}, 1},//hansya			15
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
static int tex_mapchip_3d = 0;		// 背景用テクスチャ情報

static int tex_floor = 0;		// 背景用テクスチャ情報
static int tex_floor_mozinasi = 0;		// 背景用テクスチャ情報
static int tex_floor_huchinasi = 0;		// 背景用テクスチャ情報

static int tex_base_wall = 0;		// 背景用テクスチャ情報
static int tex_base_wall_center = 0;		// 背景用テクスチャ情報
static int tex_base_wall_left = 0;		// 背景用テクスチャ情報
static int tex_base_wall_right = 0;		// 背景用テクスチャ情報



static int g_CurrentPos = 0;	// 現在のマップ座標

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(void)
{
	//g_Ground = LoadTexture("data/TEXTURE/basechip.png");
	g_Ground = LoadTexture("data/TEXTURE/basechip_test.png");
	tex_mapchip_3d = LoadTexture("data/TEXTURE/mapchip_3d.png");

	tex_floor = LoadTexture("data/TEXTURE/floor.png");
	tex_floor_mozinasi = LoadTexture("data/TEXTURE/floor_mozinasi.png");
	tex_floor_huchinasi = LoadTexture("data/TEXTURE/floor_huchinasi.png");

	tex_base_wall = LoadTexture("data/TEXTURE/base_wall.png");
	tex_base_wall_center = LoadTexture("data/TEXTURE/base_wall_center.png");
	tex_base_wall_left = LoadTexture("data/TEXTURE/base_wall_left.png");
	tex_base_wall_right = LoadTexture("data/TEXTURE/base_wall_right.png");

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
	for (int x = 0; x < MAP_X + 1; x++)
	{
		for(int y = 0; y < MAP_Y + 1; y++)
		{
			float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2);
			float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2);

			// テスト用に3種類のテクスチャ
			// tex_floor
			// tex_floor_mozinasi
			// tex_floor_huchinasi
			// tex_base_wall

			if (x < MAP_X && y < MAP_Y)
			{
				// 等角図での床の描写
				DrawSpriteLeftTop(tex_floor_huchinasi, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
				// DrawSpriteColorRotate(tex_floor_huchinasi, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);


				// 上から視点。今までの
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);

			}


			//// 手前(見えてる側面)の壁の描写
			//if (x == MAP_X || y == MAP_Y)
			//{
			//	// tex_base_wall
			//	// tex_base_wall_center
			//	// tex_base_wall_left
			//	// tex_base_wall_right

			//	// 真ん中	(x == MAP_X && y == MAP_Y)		// 左端	(x == 0 && y == MAP_Y)		// 右端	(x == MAP_X && y == 0)		// 他全て
			//	if (x == MAP_X && y == MAP_Y)
			//		DrawSpriteLeftTop(tex_base_wall_center, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//	else if (x == 0 && y == MAP_Y)
			//		DrawSpriteLeftTop(tex_base_wall_left, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//	else if (x == MAP_X && y == 0)
			//		DrawSpriteLeftTop(tex_base_wall_right, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//	else
			//		DrawSpriteLeftTop(tex_base_wall, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			//}

		

			//switch (p_Stagedata->maparray[y][x])
			//{
			//case 0://草原
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 1://道
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 2://ゴール
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 3://加速
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 4://ワープ
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 5://ワープ
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 6://砂
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 7://switch
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//case 8://hansya
			//	DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
			//	break;
			//default:
			//	exit(4);			// ふつうここに来ることはないのでエラーとして強制しておく
			//						// 下の背景オブジェクトの設定をしていないと、case10とか11とかを設定しても反映されない。
			//	break;
			//}
		}
	}

	PLAYER *p_player = GetPlayer();

	// ブロックの色の設定
	D3DXCOLOR color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// 背景オブジェクトの表示
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			MAP_DATA_T mapchip;
			mapchip = g_MapInfo[p_Stagedata->maparray[y][x]];

			

			// マップのデータが0の場合何も表示しないし計算もしない。
			if (p_Stagedata->maparray[y][x] != 0)
			{
				float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2);
				float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2);

				float mapchip3d_size_x = 240;
				float mapchip3d_size_y = 400;

				float mapchip3d_gap_x = 80;
				float mapchip3d_gap_y = 360;

				

				// ブロックの描写
				DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - mapchip3d_gap_x, slanted_y - mapchip3d_gap_y, mapchip3d_size_x, mapchip3d_size_y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f, color);

				// ブロックの透明度のリセット
				color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// 今までの上からの視点
				DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
			}

			// プレイヤーやバレットやエフェクト等ブロックとの表示順が大事な奴の処理
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				if (p_player[i].use)
				{
					// マップでの座標に変換する
					D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
					// 変換した座標の小数点を切り捨てる
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					if (x == mappos_x && y == mappos_y - 1)
					{
						// ブロックの透明度を下げる設定
						color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					}

					// 描写するタイミングだったら描写する
					if (x == mappos_x && y == mappos_y)
					{
						DrawPlayerSpecifyNum(i);

						// ブロックの透明度を下げる設定
						color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					}



					if (x == mappos_x && y == mappos_y + 1)
					{
						// ブロックの透明度を下げる設定
						color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
					}

					int ada = 0;
				}
				
			}


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

D3DXVECTOR2 PosToMappos(D3DXVECTOR2 pos)
{
	D3DXVECTOR2 mappos;
	mappos.x = pos.x / MAP_CHIP_SIZE_X;
	mappos.y = pos.y / MAP_CHIP_SIZE_Y;

	return mappos;
}

D3DXVECTOR2 MapposToPos(D3DXVECTOR2 mappos)
{
	D3DXVECTOR2 pos;
	pos.x = mappos.x * MAP_CHIP_SIZE_X;
	pos.y = mappos.y * MAP_CHIP_SIZE_Y;

	return pos;
}
