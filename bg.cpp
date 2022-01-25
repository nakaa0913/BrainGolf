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
#include "bullet.h"
#include "camera.h"
#include "predictionbullet.h"
#include "placement.h"
#include "gimmick_description.h"
#include "stageselect.h"


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

MAP_DATA_T g_MapInfo[42] =
{
	{ {0.25f , 0.0f}, 0},	//なにもなし		 0
	{ {0.125f, 0.125f}, 1},	//block			     1
	{ {0.375f, 0.125f}, 1},	//goal			     2
	{ {0.625f, 0.125f}, 1},	//speedup上		     3
	{ {0.625f, 0.25f}, 1},	//speedup下		     4
	{ {0.625f, 0.375f}, 1},	//speedup右		     5
	{ {0.625f, 0.5f}, 1},	//speedup左	         6
	{ {0.875f, 0.25f}, 1},	//speedup右上		 7 
	{ {0.875f, 0.375f}, 1},	//speedup右下	     8
	{ {0.75f , 0.375f}, 1},	//speedup左下	     9
	{ {0.75f , 0.25f}, 1},	//speedup左上		 10
	{ {0.25f , 0.125f}, 1},	//warp1-1		     11
	{ {0.25f , 0.125f}, 1},	//warp1-2		     12
	{ {0.75f , 0.0f}, 1},	//bunker			 13
	{ {0.75f , 0.125f}, 1},	//switch			 14
	{ {0.5f  , 0.125f}, 1},	//hansya	         15
	{ {0.25f  , 0.25f}, 1},	//針			     16 
	{ {0.375f , 0.25f}, 1},	//針の穴?            17 
	{ {0.875f, 0.125f}, 1},	//スイッチ押した後   18 
	{ {0.75f, 0.5f}, 1},	//赤ブロック		 19 
	{ {0.875f , 0.5f}, 0},	//赤ブロックの床	 20
	{ {0.0f , 0.5f}, 0},	//消える床(ひびなし) 21
	{ {0.125f , 0.25f}, 1},	//消える床(穴)		 22
	{ {0.5f , 0.25f}, 0},	//配置できないエリア 23
	{ {0.0f , 0.375f}, 1},	//ワープ2-1          24
	{ {0.0f , 0.375f}, 1},	//ワープ2-2			 25
	{ {0.125f , 0.375f}, 1},//ワープ3-1			 26
	{ {0.125f , 0.375f}, 1},//ワープ3-2		     27
	{ {0.25f , 0.375f}, 1},	//ワープ4-1		     28
	{ {0.25f , 0.375f}, 1},	//ワープ4-2		     29
	{ {0.375f , 0.375f}, 1},//ワープ5-1		     30
	{ {0.375f , 0.375f}, 1},//ワープ5-2		     31
	{ {0.5f , 0.375f}, 1},	//ワープ6-1		     32
	{ {0.5f , 0.375f}, 1},	//ワープ6-2		     33
	{ {0.5f , 0.875f}, 1},	//池			     34
	{ {0.75f , 0.625f}, 1},	//青ブロック		 35
	{ {0.875f , 0.625f}, 0},//青ブロックの床	 36
	{ {0.0f  , 0.25f}, 0},	//消える床(ひびあり) 37
	{ {0.375f , 0.375f}, 1},//ワープ7-1		     38
	{ {0.375f , 0.375f}, 1},//ワープ7-2		     39
	{ {0.5f , 0.375f}, 1},	//ワープ8-1		     40
	{ {0.5f , 0.375f}, 1},	//ワープ8-2		     41

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
static int g_Ground_ice = 0;		// 背景用テクスチャ情報
static int g_Ground_hell = 0;		// 背景用テクスチャ情報

static int tex_mapchip_3d = 0;		// 背景用テクスチャ情報

static int tex_mapchip_3d_01 = 0;
static int tex_mapchip_3d_02 = 0;
static int tex_mapchip_3d_03 = 0;

static int tex_floor = 0;		// 背景用テクスチャ情報
static int tex_floor_mozinasi = 0;		// 背景用テクスチャ情報
static int tex_floor_huchinasi = 0;		// 背景用テクスチャ情報
static int tex_yuka = 0;		        // 背景用テクスチャ情報
static int tex_yuka_ice = 0;			// 背景用テクスチャ情報
static int tex_yuka_hell = 0;			// 背景用テクスチャ情報

static int tex_base_wall = 0;		// 背景用テクスチャ情報
static int tex_base_wall_center = 0;		// 背景用テクスチャ情報
static int tex_base_wall_left = 0;		// 背景用テクスチャ情報
static int tex_base_wall_right = 0;		// 背景用テクスチャ情報

static int g_BG_01 = 0;			// 背景用テクスチャ情報
static int g_BG_02 = 0;			// 背景用テクスチャ情報
static int g_BG_03 = 0;			// 背景用テクスチャ情報



static int g_CurrentPos = 0;	// 現在のマップ座標

static bool Background_Unuse = false;
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitBG(void)
{
	Background_Unuse = false;

	//g_Ground = LoadTexture("data/TEXTURE/basechip.png");
	g_Ground = LoadTexture("data/TEXTURE/game/above/basechip_wood.png");
	g_Ground_ice = LoadTexture("data/TEXTURE/game/above/basechip_ice_kai.png");
	g_Ground_hell = LoadTexture("data/TEXTURE/game/above/basechip_hell.png");
	//tex_mapchip_3d = LoadTexture("data/TEXTURE/game/side/mapchip_3d1.png");

	tex_mapchip_3d_01 = LoadTexture("data/TEXTURE/game/side/mapchip_3d_wood.png");
	tex_mapchip_3d_02 = LoadTexture("data/TEXTURE/game/side/mapchip_3d_ice.png");
	tex_mapchip_3d_03 = LoadTexture("data/TEXTURE/game/side/mapchip_3d_hell.png");

	tex_floor = LoadTexture("data/TEXTURE/game/side/floor.png");
	tex_floor_mozinasi = LoadTexture("data/TEXTURE/game/side/floor_mozinasi.png");
	tex_floor_huchinasi = LoadTexture("data/TEXTURE/game/side/floor_huchinasi.png");

	tex_yuka = LoadTexture("data/TEXTURE/game/side/yuka.png");
	tex_yuka_ice = LoadTexture("data/TEXTURE/game/side/yuka_ice_kai.png");
	tex_yuka_hell = LoadTexture("data/TEXTURE/game/side/yuka_hell.png");

	tex_base_wall = LoadTexture("data/TEXTURE/game/side/base_wall.png");
	tex_base_wall_center = LoadTexture("data/TEXTURE/game/side/base_wall_center.png");
	tex_base_wall_left = LoadTexture("data/TEXTURE/game/side/base_wall_left.png");
	tex_base_wall_right = LoadTexture("data/TEXTURE/game/side/base_wall_right.png");

	g_BG_01 = LoadTexture("data/TEXTURE/game/side/Back_image_1.png");
	g_BG_02 = LoadTexture("data/TEXTURE/game/side/Back_image_2.png");
	g_BG_03 = LoadTexture("data/TEXTURE/game/side/Back_image_3.png");

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBG(void)
{
	UnloadTexture("data/TEXTURE/game/above/basechip_test1.png");
	UnloadTexture("data/TEXTURE/game/side/mapchip_3d1.png");
	UnloadTexture("data/TEXTURE/game/side/floor.png");
	UnloadTexture("data/TEXTURE/game/side/floor_mozinasi.png");
	UnloadTexture("data/TEXTURE/game/side/floor_huchinasi.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall_center.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall_left.png");
	UnloadTexture("data/TEXTURE/game/side/base_wall_right.png");

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

	bool draw[PREDICTION_MAX];
	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		draw[i] = false;
	}

	if (GetNowChoiceStageNum() <= 10)
	{
		// 平和背景の表示
		DrawSpriteLeftTop(g_BG_01, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		tex_mapchip_3d = tex_mapchip_3d_01;
	}
	else if (GetNowChoiceStageNum() <= 15)
	{
		// 雪原背景の表示
		DrawSpriteLeftTop(g_BG_02, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		tex_mapchip_3d = tex_mapchip_3d_02;
	}
	else if (GetNowChoiceStageNum() <= 20)
	{
		// 地獄背景の表示
		DrawSpriteLeftTop(g_BG_03, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		tex_mapchip_3d = tex_mapchip_3d_03;
	}

	STAGEDATA* p_Stagedata = GetStagedata();
	CAMERA* p_Camera = GetCamera();

	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouse_Rclick = GetMouseRClick();

	float offset_y;

	if (g_CurrentPos == 0)
		offset_y = 0.0f;
	else
		offset_y = -560.0f;

	//レイヤー０の表示
	for (int x = 0 - 1; x < MAP_X + 1; x++)
	{
		for (int y = 0 - 1; y < MAP_Y + 1; y++)
		{

			float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

			// テスト用に3種類のテクスチャ
			// tex_floor
			// tex_floor_mozinasi
			// tex_floor_huchinasi
			// tex_base_wall

			// 床の描写
			if (x < MAP_X + 1 && y < MAP_Y + 1)
			{
				// 等角図での床の描写
				//DrawSpriteLeftTop(tex_yuka, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
				if (GetNowChoiceStageNum() <= 10)
				{
					// 平和背景の表示
					DrawSpriteLeftTop(tex_yuka, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
				}
				else if (GetNowChoiceStageNum() <= 15)
				{
					// 雪原背景の表示
					DrawSpriteLeftTop(tex_yuka_ice, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
				}
				else if (GetNowChoiceStageNum() <= 20)
				{
					// 地獄背景の表示
					DrawSpriteLeftTop(tex_yuka_hell, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
				}
				
				// DrawSpriteColorRotate(tex_floor_huchinasi, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), 0.0f);


				// 上から視点での床の描写
				//DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);

			}
		}
	}


	// ゲッターでポインタを受け取る
	PLAYER		*p_player		 = GetPlayer();
	BULLET		*p_bullet	 	 = GetBullet();
	PREDICTION  * p_Prediction	 = GetPrediction();
	GIMMICKDESCRIPTION* p_GimmickDescription = GetGimmickDescription();


	// ブロックの色の設定(リセット)		順番的に(0,0)は透明度は変えられない。けど問題ない。
	D3DXCOLOR color[10 * (MAP_Y + 1) + (MAP_X + 1)];
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			// 色データのリセット。
			color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

	// 背景オブジェクトの表示	外周ブロックのために-1と+1
	for (int x = 0 - 1; x < MAP_X + 1; x++)
	{
		for (int y = 0 - 1; y < MAP_Y + 1; y++)
		{
			MAP_DATA_T mapchip;
			// そこに何のブロックがあるかを調べるための箱を用意
			int mapchipdata;

			// 外周のブロックの場合は壁ブロックを設定する。-1の部分はここで描写、+1の部分は透明の設定もあるので後で描写
			if (x == -1 || y == -1 || x == MAP_X || y == MAP_Y)
			{
				mapchipdata = 1;
				mapchip = g_MapInfo[1];
				if (mapchipdata == 1)							// 壁ブロックをうすくする処理
					mapchip.uv = D3DXVECTOR2(0.75f, 0.875f);

				if (x == -1 || y == -1)
				{
					float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
					float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

					// とうかくず視点
					DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

					// 今までの上からの視点
					//DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);

					continue;
				}
			}
			else
			{
				mapchipdata = p_Stagedata->maparray[y][x];
				mapchip = g_MapInfo[mapchipdata];
				if (mapchipdata == 1)							// 壁ブロックをうすくする処理
					mapchip.uv = D3DXVECTOR2(0.75f, 0.875f);

			}

			// マップのデータが0の場合何も表示しないし計算もしない。
			if (mapchipdata != 0)
			{

				// 色(透明度の初期化)
				color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
				float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

				// ブロックだった場合見やすくするために半透明にする
				if(mapchipdata == 1)
					color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// プレイヤー周りにいるかの検索とその時ブロックを透明にする処理
				for (int i = 0; i < PLAYER_MAX; i++)
				{
					if (p_player[i].use)
					{
						// マップでの座標に変換する
						D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
						// 変換した座標の小数点を切り捨てる
						int mappos_x = mappos.x;
						int mappos_y = mappos.y;

						// ブロックの周りにプレイヤーがいた場合透明度を下げる
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
					}
				}
				// バレットが周りにいるかの検索とその時ブロックを透明にする処理
				for (int i = 0; i < BULLET_MAX; i++)
				{
					if (p_bullet[i].use)
					{
						// マップでの座標に変換する
						D3DXVECTOR2 mappos = PosToMappos(p_bullet[i].pos);
						// 変換した座標の小数点を切り捨てる
						int mappos_x = mappos.x;
						int mappos_y = mappos.y;

						// ブロックの周りに弾がいた場合透明度を下げる
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
							
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
						}
						// ボールのみボールの近く全範囲
						if (x == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
						}
						if (x == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
						}
						if (x + 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
						}
						if (x + 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}
						}
						if (x + 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
							if (mapchipdata == 1)							// ボールが当たった時壁ブロックを高く見せる処理
							{
								color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
								D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
								float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
								float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
								// とうかくず視点
								//mapchip = g_MapInfo[1];
								DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);
							}

						}

						




					}
				}
				// 強調表示が周りにいるかの検索とその時ブロックを透明にする処理
				for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
				{
					if (p_GimmickDescription[i].isUse)
					{
						// マップでの座標に変換する
						int mappos_x = p_GimmickDescription[i].x;
						int mappos_y = p_GimmickDescription[i].y;

						// ブロックの周りに強調表示がいた場合透明度を下げる
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
					}
				}
				bool warp = false;
				if (mapchipdata >= 24 && mapchipdata <= 33)
					warp = true;
				if (mapchipdata == 11 || mapchipdata == 12)
					warp = true;
				float sizebairitu = 0.5f;
				float GAP_X = MAP_CHIP3D_GAP_X * sizebairitu - 18.0f;
				float GAP_Y = MAP_CHIP3D_GAP_Y * sizebairitu - 10.0f;
				// 床以外のブロックの描写
				// とうかくず視点
				// ワープは小さくする
				if (warp)
					DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - GAP_X, slanted_y - GAP_Y, MAP_CHIP3D_SIZE_X * sizebairitu, MAP_CHIP3D_SIZE_Y * sizebairitu, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f, color[10 * y + x]);
				else
					DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f, color[10 * y + x]);

				// 今までの上からの視点
				//DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X, offset_y + y * MAP_CHIP_SIZE_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
			}

			// プレイヤーの表示、表示順が大事
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				if (p_player[i].use)
				{
					// マップでの座標に変換する
					D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
					// 変換した座標の小数点を切り捨てる
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					// 描写するタイミングだったら描写する
					if (x == mappos_x && y == mappos_y)
					{
						DrawPlayerSpecifyNum(i);			// iのプレイヤーが描かれるかどうか(使われてるかどうか)は、これらの関数の中で検索される。
					}
				}
			}
			// バレットの表示
			for (int i = 0; i < BULLET_MAX; i++)
			{
				if (p_bullet[i].use)
				{
					// マップでの座標に変換する
					D3DXVECTOR2 mappos = PosToMappos(p_bullet[i].pos);
					// 変換した座標の小数点を切り捨てる
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					// 描写するタイミングだったら描写する
					if (x == mappos_x && y == mappos_y)
					{
						DrawBulletSpecifyNum(i);			// iのバレットが描かれるかどうか(使われてるかどうか)は、これらの関数の中で検索される。
					}
				}
			}
			// 予測弾の表示
			for (int i = 0; i < PREDICTION_MAX; i++)
			{
				// マップでの座標に変換する
				D3DXVECTOR2 mappos = PosToMappos(p_Prediction[i].pos);
				// 変換した座標の小数点を切り捨てる
				int mappos_x = mappos.x;
				int mappos_y = mappos.y;

				// 描写するタイミングだったら描写する
				if (x == mappos_x && y == mappos_y)
				{
					draw[i] = true;
					DrawPredictionSpecifyNum(i);			// iの予測弾が描かれるかどうか(使われてるかどうか)は、これらの関数の中で検索される。
				}
			}
			

		}
	}

	// 予測弾の表示(外まではみ出て表示できてないやつ)
	for (int i = 0; i < PREDICTION_MAX; i++)
	{
		if(draw[i] == false)
			DrawPredictionSpecifyNum(i);			// iの予測弾が描かれるかどうか(使われてるかどうか)は、これらの関数の中で検索される。
	}


	// 外周の-1の壁ブロックの球が近い時透明で表示させる処理
	// マップでの座標に変換する
	D3DXVECTOR2 mappos = PosToMappos(p_bullet[0].pos);
	// 変換した座標の小数点を切り捨てる
	int mappos_x = mappos.x;
	int mappos_y = mappos.y;

	if (mappos_x - 1 == -1)
	{
		int nx = -1;
		int ny = 0;
		for (int k = -1; k < 2; k++)
		{
			ny = mappos_y + k;
			D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			float slanted_x = GAME_ORIGIN_POINT_X + nx * (DRAW_MAP_CHIP_SIZE_X / 2) - ny * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = GAME_ORIGIN_POINT_Y + ny * (DRAW_MAP_CHIP_SIZE_Y / 2) + nx * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
			// とうかくず視点
			//mapchip = g_MapInfo[1];
			DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);

		}
	}
	if (mappos_y - 1 == -1)
	{
		int nx = 0;
		int ny = -1;
		for (int k = -1; k < 2; k++)
		{
			nx = mappos_x + k;
			D3DXCOLOR Ncolor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);
			float slanted_x = GAME_ORIGIN_POINT_X + nx * (DRAW_MAP_CHIP_SIZE_X / 2) - ny * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = GAME_ORIGIN_POINT_Y + ny * (DRAW_MAP_CHIP_SIZE_Y / 2) + nx * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
			// とうかくず視点
			//mapchip = g_MapInfo[1];
			DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, 0.125f, 0.125f, 0.125f, 0.125f, Ncolor);

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

void SetBackground()
{
	Background_Unuse = true;

	return;
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

// numがminとmaxの値からはみ出た場合minかnumに調整してくれる
int LimitRange(int num, int min, int max)
{
	if (num < min)
		num = min;
	if (num > max)
		num = max;

	return num;
}



// プレイヤー配置フェーズ用上から視点
void DrawBGaboveForPlacement(void)
{
	if (GetNowChoiceStageNum() <= 10)
	{
		// 平和背景の表示
		if (Background_Unuse == false)
		{
			DrawSpriteLeftTop(g_BG_01, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
		}
	}
	else if (GetNowChoiceStageNum() <= 15)
	{
		// 雪原背景の表示
		DrawSpriteLeftTop(g_BG_02, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	}
	else if (GetNowChoiceStageNum() <= 20)
	{
		// 地獄背景の表示
		DrawSpriteLeftTop(g_BG_03, 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f, 1.0f);
	}

	// ゲッターでポインタを受け取る
	PLAYER* p_player = GetPlayer();
	BULLET* p_bullet = GetBullet();
	PREDICTION* p_Prediction = GetPrediction();
	STAGEDATA* p_Stagedata = GetStagedata();
	CAMERA* p_Camera = GetCamera();

	// 草原の表示
	for (int x = 0; x < MAP_X + 1; x++)
	{
		for (int y = 0; y < MAP_Y + 1; y++)
		{
			if (x < MAP_X && y < MAP_Y)
			{
				// 上から視点。今までの
				//DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				if (GetNowChoiceStageNum() <= 10)
				{
					// 平和背景の表示
					DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				}
				else if (GetNowChoiceStageNum() <= 15)
				{
					// 雪原背景の表示
					DrawSpriteLeftTop(g_Ground_ice, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				}
				else if (GetNowChoiceStageNum() <= 20)
				{
					// 地獄背景の表示
					DrawSpriteLeftTop(g_Ground_hell, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 0.125f, 0.125f);
				}
			}
		}
	}

	// 背景オブジェクトの表示
	for (int x = 0 - 1; x < MAP_X + 1; x++)
	{
		for (int y = 0 - 1; y < MAP_Y  + 1; y++)
		{
			MAP_DATA_T mapchip;
			int mapchipdata;

			// 外周のブロックの場合は壁ブロックを設定する。-1の部分はここで描写、+1の部分は透明の設定もあるので後で描写
			if (x == -1 || y == -1 || x == MAP_X || y == MAP_Y)
			{
				mapchipdata = 1;
				mapchip = g_MapInfo[1];
			}
			else
			{
				mapchipdata = p_Stagedata->maparray[y][x];
				mapchip = g_MapInfo[mapchipdata];

			}
			// マップのデータが0の場合何も表示しないし計算もしない。
			if (mapchipdata != 0)
			{
				if (GetNowChoiceStageNum() <= 10)
				{
					// 平和背景の表示
					DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
				}
				else if (GetNowChoiceStageNum() <= 15)
				{
					// 雪原背景の表示
					DrawSpriteLeftTop(g_Ground_ice, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
				}
				else if (GetNowChoiceStageNum() <= 20)
				{
					// 地獄背景の表示
					DrawSpriteLeftTop(g_Ground_hell, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
				}
				// 今までの上からの視点
				//DrawSpriteLeftTop(g_Ground, 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER_X, y * MAP_CHIP_SIZE_Y + TO_CENTER_Y, MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f);
			}
		}
	}
}


// プレイヤー配置フェーズ用横から視点
void DrawBGsideForPlacement(void)
{
	STAGEDATA* p_Stagedata = GetStagedata();
	CAMERA* p_Camera = GetCamera();

	if (GetNowChoiceStageNum() <= 10)
	{
		// 平和背景の表示
		tex_mapchip_3d = tex_mapchip_3d_01;
	}
	else if (GetNowChoiceStageNum() <= 15)
	{
		// 雪原背景の表示
		tex_mapchip_3d = tex_mapchip_3d_02;
	}
	else if (GetNowChoiceStageNum() <= 20)
	{
		// 地獄背景の表示
		tex_mapchip_3d = tex_mapchip_3d_03;
	}


	//レイヤー０の表示
	for (int x = 0; x < MAP_X + 1; x++)
	{
		for (int y = 0; y < MAP_Y + 1; y++)
		{

			float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

			if (x < MAP_X && y < MAP_Y)
			{
				// 等角図での床の描写
				DrawSpriteLeftTop(tex_floor_huchinasi, slanted_x, slanted_y, DRAW_MAP_CHIP_SIZE_X, DRAW_MAP_CHIP_SIZE_Y, 0.0f, 0.0f, 1.0f, 1.0f);
			}
		}
	}


	// ゲッターでポインタを受け取る
	PLAYER* p_player = GetPlayer();
	BULLET* p_bullet = GetBullet();
	PREDICTION* p_Prediction = GetPrediction();


	// ブロックの色の設定(リセット)		順番的に(0,0)は透明度は変えられない。けど問題ない。
	D3DXCOLOR color[10 * MAP_Y + MAP_X];
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			// 色データのリセット。
			color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		}
	}

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
				// 色(透明度の初期化)
				color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				float slanted_x = GAME_ORIGIN_POINT_X + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
				float slanted_y = GAME_ORIGIN_POINT_Y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

				// プレイヤー周りにいるかの検索とその時ブロックを透明にする処理
				for (int i = 0; i < PLAYER_MAX; i++)
				{
					if (p_player[i].use)
					{
						// マップでの座標に変換する
						D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
						// 変換した座標の小数点を切り捨てる
						int mappos_x = mappos.x;
						int mappos_y = mappos.y;

						// ブロックの周りにプレイヤーがいた場合透明度を下げる
						if (x - 1 == mappos_x && y == mappos_y - 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 0)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x - 1 == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
						if (x == mappos_x && y == mappos_y + 1)
						{
							color[10 * y + x] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f);
						}
					}
				}
				// ブロックの描写
				DrawSpriteLeftTopColor(tex_mapchip_3d, slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y, MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y, mapchip.uv.x, mapchip.uv.y, 0.125f, 0.125f, color[10 * y + x]);
			}

			// プレイヤーの表示、表示順が大事
			for (int i = 0; i < PLAYER_MAX; i++)
			{
				if (p_player[i].use)
				{
					// マップでの座標に変換する
					D3DXVECTOR2 mappos = PosToMappos(p_player[i].pos);
					// 変換した座標の小数点を切り捨てる
					int mappos_x = mappos.x;
					int mappos_y = mappos.y;

					// 描写するタイミングだったら描写する
					if (x == mappos_x && y == mappos_y)
					{
						DrawPlayerSpecifyNumForPlacement(i);			// iのプレイヤーが描かれるかどうか(使われてるかどうか)は、これらの関数の中で検索される。
					}
				}
			}
		}
	}
}


