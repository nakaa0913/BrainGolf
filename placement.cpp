
#include "game.h"
#include "main.h"
#include "input.h"
#include "fade.h"
#include "player.h"
#include "collision.h"
#include "sound.h"
#include "score.h"
#include "bg.h"
#include "camera.h"
#include "predictionbullet.h"
#include "gamedata.h"
#include "placement.h"
#include "keyboard.h"
#include "mouse.h"
#include "effect.h"
#include "stagedata.h"

/*------------------------------------------------------------------------------
   定数定義
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   構造体宣言
------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------*/


/*------------------------------------------------------------------------------
   グローバル変数の定義
------------------------------------------------------------------------------*/
int placement_frame_time = 0;

PLACEMENT g_Placement[PLACEMENT_MAX];

POS nowchoice;

int MoveKeyCool = 0;
int PushKeyCool = PUSHKEY_COOLTIME;

int placement_pickup_EffectArray = -1;		// pickup_greenのエフェクト用

bool ViewAbove = true;

/*------------------------------------------------------------------------------
   初期化関数
------------------------------------------------------------------------------*/
void InitPlacement(void)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	placement_frame_time = 0;


	//InitPlayer();
	//InitScore();
	//InitBG();
	InitCamera();
	//InitGamedata();

	// 現在の配置情報を使ってプレイヤーを配置する	0番目は主人公がすでにいるので無視して1番目から

	// 主人公以外のプレイヤーを消す
	DeletePlacementPlayer();
	// ステージによって配置できる人数が違うのでそこまで読み込む
	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		// 設定されていたら新たにセットする
		if (g_Placement[i].isUse)
		{
			g_Placement[i].UsePlayerArray =
				SetPlayerForPlacement(g_Placement[i].placement_x, g_Placement[i].placement_y);
		}
	}

	// 選んでいるところを初期化で真ん中にする
	nowchoice.x = MAP_X / 2;
	nowchoice.y = MAP_Y / 2;

	MoveKeyCool = MOVEKEY_COOLTIME;
	PushKeyCool = PUSHKEY_COOLTIME;
	ViewAbove = true;


	// placementでは1個の選択中のエフェクトを動かして使う
	// 選択している場所の表示の時の原点となる場所
	float	origin_x = TO_CENTER + (MAP_CHIP_SIZE_X / 2);			    // xの原点(0,0を選択しているとき)
	float	origin_y = MAP_CHIP_SIZE_Y / 2;			    // yの原点(0,0を選択しているとき)
	// 選択している場所の表示の時の1個離れたらこれだけ離れるよってやつ
	float interval_x = MAP_CHIP_SIZE_X;
	float interval_y = MAP_CHIP_SIZE_Y;
	// エフェクトをセットする
	placement_pickup_EffectArray =
		SetEffect(52, D3DXVECTOR2(origin_x + nowchoice.x * interval_x, origin_y + nowchoice.y * interval_y), D3DXVECTOR2(0, 0), 0,
			D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y), D3DXVECTOR2(200.0f, 200.0f), 0,
			1.0f, 1.0f, 0, 999, 0, 0,
			0.0f, 0.0f, 0);


}

/*------------------------------------------------------------------------------
   終了処理をする関数
------------------------------------------------------------------------------*/
void UninitPlacement()
{
	//初期化とは逆順に終了処理を行う
	//UninitGamedata();
	UninitCamera();
	//UninitBG();
	//UninitScore();
	//UninitPlayer();
}

/*------------------------------------------------------------------------------
   更新処理をする関数
------------------------------------------------------------------------------*/
void UpdatePlacement(void)
{

	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Lclick = GetMouseLClick();
	bool mouseuse = false;

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	int OldnowchoiceX = nowchoice.x;
	int OldnowchoiceY = nowchoice.y;


	// 選択している場所の表示の時の原点となる場所
	float	origin_x = TO_CENTER + (MAP_CHIP_SIZE_X / 2);			    // xの原点(0,0を選択しているとき)
	float	origin_y = MAP_CHIP_SIZE_Y / 2;								 // yの原点(0,0を選択しているとき)
	// 選択している場所の表示の時の1個離れたらこれだけ離れるよってやつ
	float interval_x = MAP_CHIP_SIZE_X;
	float interval_y = MAP_CHIP_SIZE_Y;

	// エンターキーでゲームスタート
	if ((Keyboard_IsKeyDown(KK_ENTER)) && GetFadeState() == FADE_NONE)
	{
		SceneTransition(SCENE_GAME);
	}

	if (PushKeyCool <= 0)
	{
		// Mキーが押されたらマップ表示切替+上から視点での操作を完全に無効にする
		if (Keyboard_IsKeyDown(KK_M))
		{
			ViewAbove = !ViewAbove;
			if(ViewAbove)
				ChangeEffectClarity(placement_pickup_EffectArray, 1.0f);
			else
				ChangeEffectClarity(placement_pickup_EffectArray, 0.0f);
			PushKeyCool = PUSHKEY_COOLTIME;
		}
	}


	if (ViewAbove == true)
	{

		// キー入力による移動
		if (MoveKeyCool <= 0)
		{
			if (Keyboard_IsKeyDown(KK_RIGHT))
			{
				nowchoice.x++;
			}
			if (Keyboard_IsKeyDown(KK_LEFT))
			{
				nowchoice.x--;
			}
			if (Keyboard_IsKeyDown(KK_UP))
			{
				nowchoice.y--;
			}
			if (Keyboard_IsKeyDown(KK_DOWN))
			{
				nowchoice.y++;
			}
		}

		// マウスの座標からどのブロックに触れているかを調べる処理
		for (int x = 0; x < MAP_X + 1; x++)
		{
			for (int y = 0; y < MAP_Y + 1; y++)
			{
				if (x < MAP_X && y < MAP_Y)
				{
					float block_left  = 0.0f + x * MAP_CHIP_SIZE_X + TO_CENTER;
					float block_right = MAP_CHIP_SIZE_X + x * MAP_CHIP_SIZE_X + TO_CENTER;
					float block_up    = 0.0f + y * MAP_CHIP_SIZE_Y;
					float block_down  = MAP_CHIP_SIZE_Y + y * MAP_CHIP_SIZE_Y;

					// マウスの座標がそこにあるなら
					if (mouse_pos_X > block_left && mouse_pos_X < block_right && mouse_pos_Y > block_up && mouse_pos_Y < block_down)
					{
						nowchoice.x = x;
						nowchoice.y = y;

						break;
					}
				}
			}
		}




		// 限界値の処理
		if (nowchoice.x < 0)
			nowchoice.x = MAP_X - 1;
		if (nowchoice.x >= MAP_X)
			nowchoice.x = 0;
		if (nowchoice.y < 0)
			nowchoice.y = MAP_Y - 1;
		if (nowchoice.y >= MAP_Y)
			nowchoice.y = 0;





		// 前回より変更があった場合の処理
		if (OldnowchoiceX != nowchoice.x || OldnowchoiceY != nowchoice.y)
		{
			// 前の座標を保存(もらって)して次の座標をセットしてチェンジエフェクトで更新する
			D3DXVECTOR2 oldpos = GetEffectPos(placement_pickup_EffectArray);
			D3DXVECTOR2 nextpos = D3DXVECTOR2(origin_x + interval_x * nowchoice.x, origin_y + interval_y * nowchoice.y);
			ChangeEffect(placement_pickup_EffectArray, 52, D3DXVECTOR2(oldpos.x, oldpos.y), D3DXVECTOR2(nextpos.x, nextpos.y), 1,
				D3DXVECTOR2(MAP_CHIP_SIZE_X, MAP_CHIP_SIZE_Y), D3DXVECTOR2(200.0f, 200.0f), 0,
				1.0f, 1.0f, 0, 999, 0, 6,
				0.0f, 0.0f, 0);

			MoveKeyCool = MOVEKEY_COOLTIME;
		}

		// 選択しているところが置けないところの場合テクスチャを変える
		if (DontPlaceForCharacter(nowchoice.x, nowchoice.y) || 
			DontPlaceForBlock(nowchoice.x, nowchoice.y)		||
			DontPlaceForNumberofPeople()						)
			ChangeEffectTexture(placement_pickup_EffectArray, 53);
		else
			ChangeEffectTexture(placement_pickup_EffectArray, 52);


		// スペースキーが押されたらプレイヤーを配置する
		if (PushKeyCool <= 0)
		{
			if (Keyboard_IsKeyDown(KK_SPACE) || mouse_Lclick)
			{
				PushKeyCool = PUSHKEY_COOLTIME;
				// プレイヤーの配置するときに被っていなければそのまま配置、被っていたら取り除く処理
				// SetPlacementAndPlayerの中でさらにブロックがあったり主人公がいたりで配置できないときの処理。
				if (!SamePlacement(nowchoice.x, nowchoice.y))
					SetPlacementAndPlayer(nowchoice.x, nowchoice.y);
			}
		}


		//// 選択している場所の表示の時の原点となる場所
		//float	origin_x = TO_CENTER + (MAP_CHIP_SIZE_X / 2);			    // xの原点(0,0を選択しているとき)
		//float	origin_y = MAP_CHIP_SIZE_Y / 2;			    // yの原点(0,0を選択しているとき)
		//// 選択している場所の表示の時の1個離れたらこれだけ離れるよってやつ
		//float interval_x = MAP_CHIP_SIZE_X;
		//float interval_y = MAP_CHIP_SIZE_Y;

	}

	UpdateCamera();
	//UpdateBG();
	////UpdatePlayer();
	//UpdateScore();

	//UpdateGamedata();

	// 配置開始してからのフレーム時間を+1する
	placement_frame_time++;

	// キー入力クールタイムのカウントを下げる
	if (MoveKeyCool > 0)
		MoveKeyCool--;
	if (PushKeyCool > 0)
		PushKeyCool--;
}

/*------------------------------------------------------------------------------
   描画処理をする関数
------------------------------------------------------------------------------*/
void DrawPlacement(void)
{
	// とうかくず視点
	DrawBGsideForPlacement();

	// 上から視点
	if (ViewAbove)
	{
		DrawBGaboveForPlacement();
		DrawPlayerForPlacement();
	}

	DrawScore();

}





PLACEMENT* GetPlacement(void)
{
	return &g_Placement[0];
}


// Initとは別で構造体の中身を初期化する
// ゲームをクリアして次の選択をしたときや
// ステージ選択でステージを選んだ時	などにこれを使って初期化する
//　いニットと分けている理由は、ゲームオーバーになった時などに戻ってきたときに配置が初期化されないようにするため
void ResetPlacementArray(void)
{
	for (int i = 0; i < PLACEMENT_MAX; i++)
	{
		g_Placement[i].placement_x = -1;
		g_Placement[i].placement_y = -1;

		g_Placement[i].UsePlayerArray = -1;

		g_Placement[i].isUse = false;
	}
}

// Placement構造体にでーたをいれつつセットプレイヤーも行う。その際どこに入っているかの情報も貰う,配置出来たらtrue
bool SetPlacementAndPlayer(int x, int y)
{
	STAGEDATA * p_Stagedata = GetStagedata();

	// 主人公がいて設置できない処理,被っていたらtrueが返ってくるのでこうかく
	if (DontPlaceForCharacter(x, y))
		return false;
	// ブロックがあって設置できない処理,被っていたらtrueが返ってくるのでこうかく
	if(DontPlaceForBlock(x, y))
		return false;

	// ステージによって配置できる人数が違うのでそこまでで探す
	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		// 使われていないものから使う
		if (g_Placement[i].isUse == false)
		{
			g_Placement[i].placement_x = x;
			g_Placement[i].placement_y = y;

			g_Placement[i].UsePlayerArray =
				SetPlayerForPlacement(x, y);

			g_Placement[i].isUse = true;

			return true;			// 1人セットしたので終了する
		}
	}

	// 人数がいっぱいだった場合falseを返す
	return false;
}




// 既に使われているところにもう一度配置しようとしたら逆にプレイヤーを外すことができる
bool SamePlacement(int x, int y)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		if (g_Placement[i].isUse == true)
		{
			if (x == g_Placement[i].placement_x && y == g_Placement[i].placement_y)
			{

				DeletePlayer(g_Placement[i].UsePlayerArray);
				g_Placement[i].isUse = false;

				return true;			// 1人取り除いたので終了する
			}
		}
	}
	// そこの場所に誰もいなかった場合取り除かずに終了
	return false;
}


// 主人公がいて設置できない処理,被っていたらtrue
bool DontPlaceForCharacter(int x, int y)
{
	PLAYER* p_player = GetPlayer();

	// もし主人公と被っているなら
	if (x == p_player[0].Mapchip_Pos_Struct.mapchip_pos_x[0] && y == p_player[0].Mapchip_Pos_Struct.mapchip_pos_y[0])
		return true;

	return false;
}

// ブロックがあって設置できない処理,被っていたらtrue
bool DontPlaceForBlock(int x, int y)
{
	STAGEDATA* p_Stagedata = GetStagedata();

	// もしブロックと被っているなら,0以外のブロックなら被っている判定
	if(p_Stagedata->maparray[y][x] != 0 )
		return true;

	return false;
}

// プレイヤーを最大まで配置しておいて設置できない処理,できないならtrue
bool DontPlaceForNumberofPeople()
{
	STAGEDATA* p_Stagedata = GetStagedata();

	// もしブロックと被っているなら,0以外のブロックなら被っている判定
	for (int i = 0; i < p_Stagedata->NumberofPeople; i++)
	{
		if (g_Placement[i].isUse == false)
		{
			// 最大配置までしていないならfalseを返す
			return false;
		}
	}

	// もう最大まで配置していているなら配置できないのでtrueを返す
	return true;

}