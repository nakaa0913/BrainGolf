

#include<iostream>
#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "gamedata.h"
#include "mission.h"
#include "effect.h"
#include "savedata.h"
#include "gimmick_description.h"
#include "camera.h"




GIMMICKDESCRIPTION g_GimmickDescription[MAX_GIMMICKDESCRIPTION];

int GimmickDescription_x = -1;		// 現在マウスカーソルがあるところの座標
int GimmickDescription_y = -1;

int GimmickDescriptionCool = 30;

void InitGimmickDescription()
{
	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{

		g_GimmickDescription[i].x = -1;
		g_GimmickDescription[i].y = -1;

		g_GimmickDescription[i].background_EffectArray = -1;
		g_GimmickDescription[i].text_EffectArray = -1;
		g_GimmickDescription[i].pickupBlock_EffectArray = -1;

		g_GimmickDescription[i].GeneratedTime = 0;

		g_GimmickDescription[i].isUse = false;
	}

	GimmickDescription_x = -1;
	GimmickDescription_y = -1;

	GimmickDescriptionCool = 30;

	return;
}

void UninitGimmickDescription()
{

	return;
}

// ゲーム中(とうかくず)での説明を出すやつ
void UpdateGimmickDescription_Game()
{
	CAMERA* p_Camera = GetCamera();

	//マウスの座標を取得
	float mouse_pos_X = GetMousePosX();
	float mouse_pos_Y = GetMousePosY();
	bool mouse_Rclick = GetMouseRClick();

	bool mouseuse = false;

	// 1フレーム前のポジションの保存。この後キー操作などで変更があった場合のみエフェクトを更新させる
	int OldGimmickDescription_x = GimmickDescription_x;
	int OldGimmickDescription_y = GimmickDescription_y;

	//float interval_x = DRAW_MAP_CHIP_SIZE_X;
	//float interval_y = DRAW_MAP_CHIP_SIZE_Y;
	float interval_x = 80.0f;
	float interval_y = 40.0f;



	// マウスの座標から今どのブロックの上にカーソルがあるのかの計算
	for (int x = 0; x < MAP_X; x++)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			float draw_gap_up = 20.0f;					// テクスチャとのずれ,細かい調整に使ってもよし
			float draw_gap_down = -20.0f;

			float a = 0.5f;								// sin30°のこと y = ax + b のa
			float camera_gap_x = a * p_Camera->pos.x;
			float camera_gap_y = p_Camera->pos.y;
			float b_up = 460.0f + draw_gap_up + camera_gap_y + camera_gap_x;			// 右上がりの線のy軸でのy				 y = ax + b のb
			float b_down = -380.0f + draw_gap_down + camera_gap_y - camera_gap_x;		// 左下がりの線のy軸でのy				 y = ax + b のb

			// 右上がりの二つの線の間ならば、xが決まる
			if (mouse_pos_Y > -a * mouse_pos_X + b_up + interval_y * (x + 0) &&
				mouse_pos_Y < -a * mouse_pos_X + b_up + interval_y * (x + 1))
			{
				// 右下がりの二つの線の間ならば、yが決まる
				if (mouse_pos_Y > a * mouse_pos_X + b_down + interval_y * (y + 0) &&
					mouse_pos_Y < a * mouse_pos_X + b_down + interval_y * (y + 1))
				{
					mouseuse = true;

					GimmickDescription_x = x;
					GimmickDescription_y = y;

					break;
				}


			}
		}
	}

	// マウスカーソルがブロックにあってない場合
	if (mouseuse == false)
	{
		GimmickDescription_x = -1;
		GimmickDescription_y = -1;
	}

	SetScore2(GimmickDescription_x);
	SetScore3(GimmickDescription_y);

	bool DrawRequest = false;

	// 右クリックでその座標を使って表示など GimmickDescriptionCool
	if (GimmickDescriptionCool <= 0)
	{
		if (mouseuse && mouse_Rclick)
		{
			GimmickDescriptionCool = 30;
			DrawRequest = true;

		}
	}


	// 今あるものの消す処理とカウントを進める処理
	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{
		if (g_GimmickDescription[i].isUse == true)
		{
			// カメラ移動によるピックアップ部分の更新
			GimmickDescriptionPickupUpdata(i);

			if (g_GimmickDescription[i].GeneratedTime > GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME + GIMMICKDESCRIPTION_FADEOUT)
			{
				g_GimmickDescription[i].isUse = false;
			}
			else
				g_GimmickDescription[i].GeneratedTime++;		// 消さないものはカウントを進める
		}
	}


	// 表示の要請があった場合に表示と前回のを消す作業
	if (DrawRequest == true)
	{
		// DrawRequest = false;		// グローバル変数じゃなくてローカルでそもそも初期化してた

		// 座標から何のブロックかを調べる
		int block_data = CheckBlockdata(GimmickDescription_x, GimmickDescription_y);


		// ブロックデータが0(床)or壁ブロック(1)だった場合クールタイムを0にして終わる
		if (block_data == 0 || block_data == 1)
		{
			GimmickDescriptionCool = 0;
		}
		else
		{
			// 前回使われていた(1個しか表示させないので、一度全ての)ギミック説明のエフェクトを消す
			DeleteGimmickDescription();

			// ギミック説明のエフェクトを作成する
			GenerateGimmickDescription(block_data, GimmickDescription_x, GimmickDescription_y);
		}







	}




	if (GimmickDescriptionCool > 0)
		GimmickDescriptionCool--;


	return;
}




GIMMICKDESCRIPTION* GetGimmickDescription(void)
{
	return &g_GimmickDescription[0];
}




// ギミック説明の画像チップの場所(sx,sy)を返す
float CheckGimmickDescriptionChipPos(int block_data, int XorY)
{
	// 1マスの幅と高さ
	float tx = 0.25f;
	float ty = 0.25f;

	// 初期
	float sx = 0.0f;
	float sy = 0.0f;



	switch (block_data)
	{
	case 0:					// 床(なし)
		sx = tx * 0;
		sy = ty * 0;
		break;
	case 1:					// ブロック(なし)
		sx = tx * 0;
		sy = ty * 0;
		break;
	case 2:					// ゴール
		sx = tx * 1;
		sy = ty * 1;
		break;
	case 3:					// 加速版
	case 4:					
	case 5:					
	case 6:					
	case 7:					
	case 8:					
	case 9:					
	case 10:					
		sx = tx * 1;
		sy = ty * 0;
		break;
	case 11:					// ワープホール
	case 12:
		sx = tx * 3;
		sy = ty * 0;
		break;
	case 13:					// バンカー
		sx = tx * 0;
		sy = ty * 1;
		break;
	case 14:					// すいっち
		sx = tx * 2;
		sy = ty * 1;
		break;
	case 15:					// 反射板
		sx = tx * 2;
		sy = ty * 0;
		break;

	default:
		break;
	}



	if (XorY == 0)
		return sx;
	else
		return sy;

}


void GenerateGimmickDescription(int block_data, int x, int y)
{
	// ブロックデータからチップのどこの部分を使うかを調べる
	float tx = 0.25f;					// エフェクトのIDだと68がギミック説明のチップ画像
	float ty = 0.25f;
	float background_sx = tx * 0;		// ふきだしのUV値(背景)
	float background_sy = ty * 0;
	float text_sx = CheckGimmickDescriptionChipPos(block_data, 0);		// ブロック説明のUV値
	float text_sy = CheckGimmickDescriptionChipPos(block_data, 1);

	float size_x = 400;
	float size_y = size_x / 1.5f;		// 縦横比 1.5:1 (横長)	直接値を入れてもいいがこっちのがxだけ入力でいいので楽

	float pos_x = 300.0f;				// 表示座標(真ん中がここに来る)
	float pos_y = 200.0f;

	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{
		// 使われていないものを見つけて使う
		if (g_GimmickDescription[i].isUse == false)
		{
			// 座標の保存
			g_GimmickDescription[i].x = x;
			g_GimmickDescription[i].y = y;

			// ふきだし(背景)
			g_GimmickDescription[i].background_EffectArray =
				SetEffect(68, D3DXVECTOR2(pos_x, pos_y), D3DXVECTOR2(pos_x, pos_y), 0,
					D3DXVECTOR2(0, 0), D3DXVECTOR2(size_x, size_y), 1,
					0.0f, 1.0f, GIMMICKDESCRIPTION_FADEIN, GIMMICKDESCRIPTION_DRAWTIME, GIMMICKDESCRIPTION_FADEOUT, 18,
					0.0f, 0.0f, 0,
					tx, ty, background_sx, background_sy);

			// テキストとアイコン
			g_GimmickDescription[i].text_EffectArray =
				SetEffect(68, D3DXVECTOR2(pos_x, pos_y), D3DXVECTOR2(pos_x, pos_y), 0,
					D3DXVECTOR2(0, 0), D3DXVECTOR2(size_x, size_y), 1,
					0.0f, 1.0f, GIMMICKDESCRIPTION_FADEIN, GIMMICKDESCRIPTION_DRAWTIME, GIMMICKDESCRIPTION_FADEOUT, 18,
					0.0f, 0.0f, 0,
					tx, ty, text_sx, text_sy);

			// 選択しているブロックの強調表示の原点(レフトトップ以外で何でずれてるかわからない；；；；)
			float pickuporigin_x = GAME_ORIGIN_POINT_X + 80.0f * 1 + 40.0f;
			float pickuporigin_y = GAME_ORIGIN_POINT_Y + 40.0f * 5 + 0.0f;

			CAMERA* p_Camera = GetCamera();
			float slanted_x = pickuporigin_x + x * (DRAW_MAP_CHIP_SIZE_X / 2) - y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
			float slanted_y = pickuporigin_y + y * (DRAW_MAP_CHIP_SIZE_Y / 2) + x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;
			g_GimmickDescription[i].pickupBlock_EffectArray =
				SetEffect(69, D3DXVECTOR2(slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y), D3DXVECTOR2(slanted_x - MAP_CHIP3D_GAP_X, slanted_y - MAP_CHIP3D_GAP_Y), 0,
					D3DXVECTOR2(MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y), D3DXVECTOR2(MAP_CHIP3D_SIZE_X, MAP_CHIP3D_SIZE_Y), 0,
					0.0f, 1.0f, GIMMICKDESCRIPTION_FADEIN, GIMMICKDESCRIPTION_DRAWTIME, GIMMICKDESCRIPTION_FADEOUT, 18,
					0.0f, 0.0f, 0,
					1.0f, 1.0f, 0.0f, 0.0f);


			// 生成されてからの時間の設定
			g_GimmickDescription[i].GeneratedTime = 0;

			g_GimmickDescription[i].isUse = true;

			return;		// 1こ生成したので終わる
		}
	}

	exit(40);		// 全て使われていたらエラー
}



// ギミック説明の今出てるすべてのものをフェードアウトで消す(この処理の後に新しいものを生成をすれば問題ない)
void DeleteGimmickDescription()
{
	for (int i = 0; i < MAX_GIMMICKDESCRIPTION; i++)
	{
		// 使われているものの中から探す
		if (g_GimmickDescription[i].isUse == true)
		{
			// もし-1が入っていたら最初の読み込みとかなので消す作業を実行せずに終わる
			if (g_GimmickDescription[i].background_EffectArray == -1)
				return;

			// now_countをいじって消すようにする。もう消えかかってる状態ならなにもしない
			int now = GetEffectnow_count(g_GimmickDescription[i].background_EffectArray);
			if (now > GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME)
				return;

			// ふきだし(背景)
			ChangeEffectCount(g_GimmickDescription[i].background_EffectArray, GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME);

			// テキストとアイコン
			ChangeEffectCount(g_GimmickDescription[i].text_EffectArray, GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME);

			// 強調表示
			ChangeEffectCount(g_GimmickDescription[i].pickupBlock_EffectArray, GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME);


			// 生成されてからの時間の設定
			g_GimmickDescription[i].GeneratedTime = GIMMICKDESCRIPTION_FADEIN + GIMMICKDESCRIPTION_DRAWTIME;
		}
	}


}

// 強調表示のカメラ移動による更新
void GimmickDescriptionPickupUpdata(int i)
{
	CAMERA* p_Camera = GetCamera();

	// 前回からカメラが動いているかどうか、動いていたら実行する
	if (CameraPosChanged() == true)
	{
		// 選択しているブロックの強調表示の原点(レフトトップ以外で何でずれてるかわからない；；；；)
		//float pickuporigin_x = GAME_ORIGIN_POINT_X + 80.0f * 1 + 40.0f;
		//float pickuporigin_y = GAME_ORIGIN_POINT_Y + 40.0f * 5 + 0.0f;

		float pickuporigin_x = GAME_ORIGIN_POINT_X + 80.0f * 0 + 40.0f;
		float pickuporigin_y = GAME_ORIGIN_POINT_Y - 40.0f * 4 + 0.0f;

		// カメラ移動によるピックアップ部分の更新
		float newpos_x = pickuporigin_x + g_GimmickDescription[i].x * (DRAW_MAP_CHIP_SIZE_X / 2) - g_GimmickDescription[i].y * (DRAW_MAP_CHIP_SIZE_X / 2) + p_Camera->pos.x;
		float newpos_y = pickuporigin_y + g_GimmickDescription[i].y * (DRAW_MAP_CHIP_SIZE_Y / 2) + g_GimmickDescription[i].x * (DRAW_MAP_CHIP_SIZE_Y / 2) + p_Camera->pos.y;

		ChangeEffectPos(g_GimmickDescription[i].pickupBlock_EffectArray, newpos_x, newpos_y);
	}
}