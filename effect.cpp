
#include "effect.h"
#include "Texture.h"
#include "sprite.h"
#include "score.h"
#include "scene.h"
#include "bg.h"
#include "camera.h"

EFFECT g_Effect[MAX_EFFECT];

//テクスチャの名前定義
static int ao_0;		 // 0
static int aka_1;		 // 1
//static int tako_2;	 // 2
static int title_3;		 // 3
static int black_4;		 // 4
static int clear_5;		 // 5
static int select_6;	 // 6
static int select2_7;    // 7
static int mission_8;    // 8
static int selectstar_9; // 9
static int selectlock_10;// 10
static int clear_star1_11;// 11
static int clear_star2_12;// 12
static int clear_star3_13;// 13
static int clear_star4_14;// 14

void InitEffect(void)
{
	//テクスチャの名前
	ao_0 = LoadTexture("data/TEXTURE/ao.png");
	aka_1 = LoadTexture("data/TEXTURE/aka.png");
	//tako_2 = LoadTexture("data/TEXTURE/result/tako.png");
	title_3 = LoadTexture("data/TEXTURE/title_effect.png");
	black_4 = LoadTexture("data/TEXTURE/black.png");
	/*clear_5 = LoadTexture("data/TEXTURE/result/clear.png");*/
	select_6 = LoadTexture("data/TEXTURE/1.png");
	select2_7 = LoadTexture("data/TEXTURE/2.png");
	mission_8 = LoadTexture("data/TEXTURE/mission.png");
	selectstar_9 = LoadTexture("data/TEXTURE/selectstar.png");
	selectlock_10 = LoadTexture("data/TEXTURE/selectlock.png");
	clear_star1_11 = LoadTexture("data/TEXTURE/result/clear_star_1.png");
	clear_star2_12 = LoadTexture("data/TEXTURE/result/clear_star_2.png");
	clear_star3_13 = LoadTexture("data/TEXTURE/result/clear_star_3.png");
	clear_star4_14 = LoadTexture("data/TEXTURE/result/clear_star_black_1.png");



	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].id = ao_0;
		g_Effect[i].pos = D3DXVECTOR2(0, 0);
		g_Effect[i].pos1 = D3DXVECTOR2(0, 0);
		g_Effect[i].pos2 = D3DXVECTOR2(0, 0);
		g_Effect[i].pos_moving_pattern = 0;
		g_Effect[i].size = D3DXVECTOR2(100, 100);
		g_Effect[i].size1 = D3DXVECTOR2(100, 100);
		g_Effect[i].size2 = D3DXVECTOR2(100, 100);
		g_Effect[i].size_moving_pattern = 0;
		g_Effect[i].Clarity_min = 0.0f;
		g_Effect[i].Clarity_max = 1.0f;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min;
		g_Effect[i].fadeIn_count = 100;
		g_Effect[i].all_count = 100;
		g_Effect[i].fadeOut_count = 100;
		g_Effect[i].now_count = 300;
		g_Effect[i].moving_count = 0;
		g_Effect[i].rot = 0.0f;
		g_Effect[i].rot_angle = 0;
		g_Effect[i].rot_angle1 = 0;
		g_Effect[i].rot_angle2 = 90;
		g_Effect[i].rot_moving_pattern = 0;
		g_Effect[i].rot_count = 0;

		g_Effect[i].drawpos = g_Effect[i].pos;
		g_Effect[i].drawsize = g_Effect[i].size;

		g_Effect[i].drawpos = g_Effect[i].pos1;
		g_Effect[i].isUse = false;

	}
	InitScore();
}

void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].isUse = false;
	}
	// UninitScore();
	UnloadTexture("data/TEXTURE/ao.png");
	UnloadTexture("data/TEXTURE/aka.png");
	UnloadTexture("data/TEXTURE/title_effect.png");
	UnloadTexture("data/TEXTURE/black.png");
	UnloadTexture("data/TEXTURE/1.png");
	UnloadTexture("data/TEXTURE/2.png");
	UnloadTexture("data/TEXTURE/mission.png");
	UnloadTexture("data/TEXTURE/selectstar.png");
	UnloadTexture("data/TEXTURE/selectlock.png");
	UnloadTexture("data/TEXTURE/result/clear_star_1.png");
	UnloadTexture("data/TEXTURE/result/clear_star_2.png");
	UnloadTexture("data/TEXTURE/result/clear_star_3.png");
	UnloadTexture("data/TEXTURE/result/clear_star_black_1.png");

}

void UpdateEffect(void)
{
	CAMERA* p_Camera = GetCamera();

	int effectnum = 0;
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse)
		{
			// FadeInからアウトまでの処理
			Fadeprocess(i);

			// pos_moveingの処理
			PosMovingPattern(i);

			// size_moveingの処理
			SizeMovingPattern(i);

			// rot_moveingの処理
			RotMovingPattern(i);






			

			// 時間経過による破壊処理
			if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count
				+ g_Effect[i].all_count + g_Effect[i].fadeOut_count)
			{
				// 無制限に表示させたい場合の処理.all_count == 999だったら無制限に表示
				if (g_Effect[i].all_count == 999)
				{
					g_Effect[i].now_count = g_Effect[i].fadeIn_count + g_Effect[i].all_count - 998;
				}
				else
				{
					g_Effect[i].isUse = false;
				}
					
			}

			// 毎フレームごとにカウントを進める
			g_Effect[i].now_count++;
			effectnum++;


			// pos を drawpos に変換	エフェクトの場合、drawposから
			g_Effect[i].drawpos = g_Effect[i].pos;
			// g_Effect[i].drawsize = g_Effect[i].size * p_Camera->magnification;






		}
	}
	SetScore(effectnum);
	UpdateScore();
}

void DrawEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == true)
		{
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Effect[i].Clarity);
			DrawSpriteColorRotate(g_Effect[i].id, g_Effect[i].drawpos.x, g_Effect[i].drawpos.y, g_Effect[i].size.x, g_Effect[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f, col, g_Effect[i].rot);
		}
	}
	DrawScore();
}

EFFECT* GetEffect(void)
{
	return &g_Effect[0];
}


// all_count == 999だったら無制限に表示
void SetEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
			   float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
			   float rot_angle1, float rot_angle2, int rot_moving_pattern)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == false)
		{
		//g_Effect[i].id = id;	下で引数で入力した値によってテクスチャを変更している
		g_Effect[i].pos = pos1;
		g_Effect[i].pos1 = pos1;
		g_Effect[i].pos2 = pos2;
		g_Effect[i].pos_moving_pattern = pos_moving_pattern;
		g_Effect[i].size = size1;
		g_Effect[i].size1 = size1;
		g_Effect[i].size2 = size2;
		g_Effect[i].size_moving_pattern = size_moving_pattern;
		g_Effect[i].Clarity_min = Clarity_min;
		g_Effect[i].Clarity_max = Clarity_max;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min;
		g_Effect[i].fadeIn_count = fadeIn_count;
		g_Effect[i].all_count = all_count;
		g_Effect[i].fadeOut_count = fadeOut_count;
		g_Effect[i].now_count = 0;
		g_Effect[i].moving_count = moving_count;
		g_Effect[i].rot = AngleToRadian(rot_angle1);
		g_Effect[i].rot_angle = rot_angle1;
		g_Effect[i].rot_angle1 = rot_angle1;
		g_Effect[i].rot_angle2 = rot_angle2;
		g_Effect[i].rot_moving_pattern = rot_moving_pattern;
		g_Effect[i].rot_count = 0;

		g_Effect[i].drawpos = g_Effect[i].pos1;
		g_Effect[i].isUse = true;
		
		if(id == 0)
			g_Effect[i].id = ao_0;
		if (id == 1)
			g_Effect[i].id = aka_1;
		/*if (id == 2)
			g_Effect[i].id = tako_2;*/
		if (id == 3)
			g_Effect[i].id = title_3;
		if (id == 4)
			g_Effect[i].id = black_4;
		/*if (id == 5)
			g_Effect[i].id = clear_5;*/
		if (id == 6)
			g_Effect[i].id = select_6;
		if (id == 7)
			g_Effect[i].id = select2_7;
		if (id == 8)
			g_Effect[i].id = mission_8;
		if (id == 9)
			g_Effect[i].id = selectstar_9;
		if (id == 10)
			g_Effect[i].id = selectlock_10;
		if (id == 11)
			g_Effect[i].id = clear_star1_11;
		if (id == 12)
			g_Effect[i].id = clear_star2_12;
		if (id == 13)
			g_Effect[i].id = clear_star3_13;
		if (id == 14)
			g_Effect[i].id = clear_star4_14;

		return;
		}

	}

	// MAX_EFFECT を超えた数エフェクトを作成しようとするとゲームが落ちる
	 exit(1);
}

// ゲーム内でのエフェクトを使う場合はこっち。座標を自動的に斜めに修正してくれる。例えばゲーム内のボールに追従するとかの時便利
// all_count == 999だったら無制限に表示
void SetGameEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern)
{
	CAMERA* p_Camera = GetCamera();

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_Effect[i].isUse == false)
		{
			//g_Effect[i].id = id;	下で引数で入力した値によってテクスチャを変更している
			
			// pos を drawpos に変換 しているけど、エフェクトの場合posのままやる。


			g_Effect[i].pos.x = GAME_ORIGIN_POINT_Y + ((pos1.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((pos1.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
			g_Effect[i].pos.y = GAME_ORIGIN_POINT_Y + ((pos1.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((pos1.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);
			g_Effect[i].pos1 = g_Effect[i].pos;

			g_Effect[i].pos2.x = GAME_ORIGIN_POINT_X + ((pos2.x + DRAW_GAP_X) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_X / 2) - ((pos2.y - DRAW_GAP_X) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_X / 2);
			g_Effect[i].pos2.y = GAME_ORIGIN_POINT_Y + ((pos2.y - DRAW_GAP_Y) / MAP_CHIP_SIZE_Y) * (DRAW_MAP_CHIP_SIZE_Y / 2) + ((pos2.x + DRAW_GAP_Y) / MAP_CHIP_SIZE_X) * (DRAW_MAP_CHIP_SIZE_Y / 2);

			g_Effect[i].pos_moving_pattern = pos_moving_pattern;
			g_Effect[i].size = size1 * p_Camera->magnification;
			g_Effect[i].size1 = size1 * p_Camera->magnification;
			g_Effect[i].size2 = size2 * p_Camera->magnification;
			g_Effect[i].size_moving_pattern = size_moving_pattern;
			g_Effect[i].Clarity_min = Clarity_min;
			g_Effect[i].Clarity_max = Clarity_max;
			g_Effect[i].Clarity = g_Effect[i].Clarity_min;
			g_Effect[i].fadeIn_count = fadeIn_count;
			g_Effect[i].all_count = all_count;
			g_Effect[i].fadeOut_count = fadeOut_count;
			g_Effect[i].now_count = 0;
			g_Effect[i].moving_count = moving_count;
			g_Effect[i].rot = AngleToRadian(rot_angle1);
			g_Effect[i].rot_angle = rot_angle1;
			g_Effect[i].rot_angle1 = rot_angle1;
			g_Effect[i].rot_angle2 = rot_angle2;
			g_Effect[i].rot_moving_pattern = rot_moving_pattern;
			g_Effect[i].rot_count = 0;

			g_Effect[i].drawpos = g_Effect[i].pos1;
			g_Effect[i].isUse = true;

			if (id == 0)
				g_Effect[i].id = ao_0;
			if (id == 1)
				g_Effect[i].id = aka_1;
		/*	if (id == 2)
				g_Effect[i].id = tako_2;*/
			if (id == 3)
				g_Effect[i].id = title_3;
			if (id == 4)
				g_Effect[i].id = black_4;
			if (id == 5)
				g_Effect[i].id = clear_5;
			if (id == 6)
				g_Effect[i].id = select_6;
			if (id == 7)
				g_Effect[i].id = select2_7;
			if (id == 8)
				g_Effect[i].id = mission_8;
			if (id == 9)
				g_Effect[i].id = selectstar_9;
			if (id == 10)
				g_Effect[i].id = selectlock_10;

			return;
		}

	}

	// MAX_EFFECT を超えた数エフェクトを作成しようとするとゲームが落ちる
	exit(1);
}


void Fadeprocess(int i)
{
	//0〜fadeIn
	if (g_Effect[i].now_count < 0 + g_Effect[i].fadeIn_count)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeIn_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * g_Effect[i].now_count;
	}
	//fadeIn〜all
	if (g_Effect[i].now_count >= 0 + g_Effect[i].fadeIn_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count)
	{
		g_Effect[i].Clarity = g_Effect[i].Clarity_max;
	}
	//all〜fadeOut
	if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count + g_Effect[i].all_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeOut_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * ((g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count) - g_Effect[i].now_count);
	}
}


void PosMovingPattern(int i)
{
	// この関数はisUseがtrueの場合しか呼ばれない場所で呼ぶ

	// 現在のカウントが moving_count より小さい間だけ実行される
	if (g_Effect[i].now_count < g_Effect[i].moving_count)
	{
		// 0	pos1から移動しない。
		if (g_Effect[i].pos_moving_pattern == 0)
		{
			g_Effect[i].pos = g_Effect[i].pos1;
		}

		// 1	pos1からpos2まで直線的な移動をする
		if (g_Effect[i].pos_moving_pattern == 1)
		{
			D3DXVECTOR2 onemove = (g_Effect[i].pos2 - g_Effect[i].pos1) / g_Effect[i].moving_count;
			D3DXVECTOR2 newpos = g_Effect[i].pos + onemove * g_Effect[i].now_count;
			g_Effect[i].pos = g_Effect[i].pos1 + onemove * g_Effect[i].now_count;
			// g_Effect[i].pos = g_Effect[i].pos2;

			// 誤差が出るので動く最後のフレームでpos2丁度になるように調整
			if (g_Effect[i].now_count == g_Effect[i].moving_count - 1)
				g_Effect[i].pos = g_Effect[i].pos2;
		}
		// ここにパターンを書き足していく




	}
	
	return;
}

void SizeMovingPattern(int i)
{
	// この関数はisUseがtrueの場合しか呼ばれない場所で呼ぶ

	// 現在のカウントが moving_count より小さい間だけ実行される
	if (g_Effect[i].now_count < g_Effect[i].moving_count)
	{
		// 0	pos1から移動しない。
		if (g_Effect[i].size_moving_pattern == 0)
		{
			g_Effect[i].size = g_Effect[i].size1;
		}

		// 1	size1からsize2まで直線的な移動をする
		if (g_Effect[i].size_moving_pattern == 1)
		{
			D3DXVECTOR2 onemove = (g_Effect[i].size2 - g_Effect[i].size1) / g_Effect[i].moving_count;
			D3DXVECTOR2 newpos = g_Effect[i].size + onemove * g_Effect[i].now_count;
			g_Effect[i].size = g_Effect[i].size1 + onemove * g_Effect[i].now_count;
			// g_Effect[i].size = g_Effect[i].size2;

			// 誤差が出るので動く最後のフレームでsize2丁度になるように調整
			if (g_Effect[i].now_count == g_Effect[i].moving_count - 1)
				g_Effect[i].size = g_Effect[i].size2;
		}
		// ここにパターンを書き足していく




	}

	return;
}

void RotMovingPattern(int i)
{
	// この関数はisUseがtrueの場合しか呼ばれない場所で呼ぶ

	// 現在のカウントが moving_count より小さい間だけ実行される
	// もしくはrot_moving_pattern が 2 の時は時間が切れても無限に回転するので実行される
	if (g_Effect[i].now_count < g_Effect[i].moving_count || g_Effect[i].rot_moving_pattern == 2)
	{
		// まず角度angleからラジアンrotに変換する
		float rot = AngleToRadian(g_Effect[i].rot_angle);
		float rot1 = AngleToRadian(g_Effect[i].rot_angle1);
		float rot2 = AngleToRadian(g_Effect[i].rot_angle2);


		// 0	rot_angle1から移動しない。
		if (g_Effect[i].rot_moving_pattern == 0)
		{
			g_Effect[i].rot = AngleToRadian(g_Effect[i].rot_angle);
		}

		// 1	rot_angle1からrot_angle2まで直線的な移動をする
		if (g_Effect[i].rot_moving_pattern == 1)
		{
			float onemove = (g_Effect[i].rot_angle2 - g_Effect[i].rot_angle1) / g_Effect[i].moving_count;
			g_Effect[i].rot_angle = g_Effect[i].rot_angle1 + onemove * g_Effect[i].now_count;
			g_Effect[i].rot		  = AngleToRadian(g_Effect[i].rot_angle);

			// 誤差が出るので動く最後のフレームでrot_angle2に丁度になるように調整
			if (g_Effect[i].now_count == g_Effect[i].moving_count - 1)
			{
				g_Effect[i].rot_angle = g_Effect[i].rot_angle2;
				g_Effect[i].rot		  = AngleToRadian(g_Effect[i].rot_angle);
			}
		}

		// 2	rot_angle1からrot_angle2 まで直線的な回転をする。 1とは違い、moving_countが終わっても回転し続ける。
		if (g_Effect[i].rot_moving_pattern == 2)
		{
			float onemove = (g_Effect[i].rot_angle2 - g_Effect[i].rot_angle1) / g_Effect[i].moving_count;
			g_Effect[i].rot_angle = g_Effect[i].rot_angle1 + onemove * g_Effect[i].rot_count;
			g_Effect[i].rot		  = AngleToRadian(g_Effect[i].rot_angle);
		}
		// ここにパターンを書き足していく




	}

	g_Effect[i].rot_count++;

	return;
}

float AngleToRadian(float angle)
{
	float radian = angle * (D3DX_PI / 180);
	return  radian;
}