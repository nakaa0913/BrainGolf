
#include<iostream>
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

//ステージ選択の背景
static int stage_select1_15;// 15
static int stage_select2_16;// 16
static int stage_select3_17;// 17
static int stage_select4_18;// 18
static int stage_select5_19;// 19
//ステージ選択の四角いやつ
static int stage_choice1_20;// 20
static int stage_choice2_21;// 21
static int stage_choice3_22;// 22
static int stage_choice4_23;// 23
static int stage_choice5_24;// 24
//ステージ選択のミッション
static int stage_mission_background_25;// 25
static int stage_mission0_26;// 26
static int stage_mission1_27;// 27
static int stage_mission2_28;// 28
static int stage_mission3_29;// 29
static int stage_mission4_30;// 30
static int stage_mission5_31;// 31
static int stage_mission6_32;// 32
static int stage_mission7_33;// 33
static int stage_mission8_34;// 34
static int stage_mission9_35;// 35
static int stage_mission10_36;// 36
static int stage_mission11_37;// 37
static int stage_mission12_38;// 38
static int stage_mission13_39;// 39
static int stage_mission14_40;// 40 
static int stage_mission15_41;// 41
static int stage_mission16_42;// 42
static int stage_mission17_43;// 43
static int stage_mission18_44;// 44
static int stage_mission19_45;// 45

// 数字の表示
static int number_46;		// 46

static int next_47;			// 47
static int white_48;		// 48
static int mapback_49;		// 49
//static int maparrow_50;	// 50 使わない
//static int maptext_51;	// 51 使わない

// placementで使うやつ
static int pickup_green_52; // 52
static int pickup_red_53;	// 53
static int batten_red_54;	// 54

// ゲームオーバー
static int gameover_55;		 // 55
static int restart_56;		 // 56
static int stagename_57;	 // 57
static int gameover_back_58; // 58
static int gameover_place_59;// 59

static int titleback_60;	// 60
static int worldback_61;	// 61

//　ポーズ画面
static int pause_62;			// 62
static int commentary_63;		// 62
static int above_64;			// 64
static int retry_65;			// 65
static int pause_mission_66;	// 66
static int pause_stageselect_67;// 67

// ギミック説明チップ
static int GimmickDescriptionChip_68;// 68
static int pickup_GimmickDescription_69;// 69

static int batu_70;	// 70

//クラブの種類
static int rollball_71;
static int flyball_72;

//ポーズ画面の外枠
static int around_73;

//リザルト画面追加
static int note_74;
static int MAPButton1_75;
static int MAPButton2_76;
static int NEXTSTAGE1_77;
static int NEXTSTAGE2_78;
static int RETRY1_79;
static int RETRY2_80;
static int Ribon_81;
static int NoJewlry_82;
static int RedJewlry_83;
static int BlueJewlry_84;
static int YellowJewlry_85;

// ステージ選択画面
static int mission_waku_1_86;
static int pin_87;
static int botan_waku_1_88;

static int senntaku_haikei_1_89;
static int senntaku_haikei_2_90;
static int botan_1_91;
static int botan_2_92;

// タイトル
static int title_click_93;
static int title_logo_94;
static int title_bokashi_95;

// リザルト
static int result_go_96;
static int kekkahappyou_97;
static int kekkahappyou_2_98;
static int haiti_99;
static int haiti_2_100;
static int chara_101;

// ポーズ
static int migi_102;
static int hidari_103;

// リザルトのクリアタイムの表示の時の数字
static int number_104;

// ポーズとマウス操作のやつ
static int pozu_105;
static int pozu_2_106;
static int utu_107;
static int wejji_108;
static int doraiba_109;

// 配置画面の時使うもの
static int play_botan_0_110;
static int play_botan_1_111;
static int home_botan_0_112;
static int home_botan1_113;
static int mob_placement_114;

//ポーズ画面追加
static int ue_115;
static int ue_2_116;
static int mission_117;
static int mission_2_118;

// number追加
static int number_2_119;
static int number_3_120;
static int nobasibou_121;

//タイトルに戻るボタン
static int title_botan_122;
static int title_botan2_123;

void InitEffect(void)
{
	//テクスチャの名前
	ao_0 = LoadTexture("data/TEXTURE/ao.png");
	aka_1 = LoadTexture("data/TEXTURE/result/advice.png");
	//tako_2 = LoadTexture("data/TEXTURE/result/tako.png");
	title_3 = LoadTexture("data/TEXTURE/title/title_effect.png");
	black_4 = LoadTexture("data/TEXTURE/other_effect/black.png");
	clear_5 = LoadTexture("data/TEXTURE/result/CLEAR.png");
	select_6 = LoadTexture("data/TEXTURE/select/1.png");
	select2_7 = LoadTexture("data/TEXTURE/select/2.png");
	mission_8 = LoadTexture("data/TEXTURE/select/mission.png");
	selectstar_9 = LoadTexture("data/TEXTURE/select/selectstar.png");
	selectlock_10 = LoadTexture("data/TEXTURE/select/selectlock.png");
	clear_star1_11 = LoadTexture("data/TEXTURE/result/clear_star_1.png");
	clear_star2_12 = LoadTexture("data/TEXTURE/result/clear_star_2.png");
	clear_star3_13 = LoadTexture("data/TEXTURE/result/clear_star_3.png");
	clear_star4_14 = LoadTexture("data/TEXTURE/result/clear_star_black_1.png");

	stage_select1_15 = LoadTexture("data/TEXTURE/select/1aka.png");
	stage_select2_16 = LoadTexture("data/TEXTURE/select/2yellow.png");
	stage_select3_17 = LoadTexture("data/TEXTURE/select/3green.png");
	stage_select4_18 = LoadTexture("data/TEXTURE/select/4orange.png");
	stage_select5_19 = LoadTexture("data/TEXTURE/select/5blue.png");

	stage_choice1_20 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice2_21 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice3_22 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice4_23 = LoadTexture("data/TEXTURE/select/1.png");
	stage_choice5_24 = LoadTexture("data/TEXTURE/select/1.png");

	stage_mission_background_25 = LoadTexture("data/TEXTURE/select/mission/mission_background.png");
	stage_mission0_26 = LoadTexture("data/TEXTURE/select/mission/mission_0.png");
	stage_mission1_27 = LoadTexture("data/TEXTURE/select/mission/mission_1.png");
	stage_mission2_28 = LoadTexture("data/TEXTURE/select/mission/mission_2.png");
	stage_mission3_29 = LoadTexture("data/TEXTURE/select/mission/mission_3.png");
	stage_mission4_30 = LoadTexture("data/TEXTURE/select/mission/mission_4.png");
	stage_mission5_31 = LoadTexture("data/TEXTURE/select/mission/mission_5.png");
	stage_mission6_32 = LoadTexture("data/TEXTURE/select/mission/mission_6.png");
	stage_mission7_33 = LoadTexture("data/TEXTURE/select/mission/mission_7.png");
	stage_mission8_34 = LoadTexture("data/TEXTURE/select/mission/mission_8.png");
	stage_mission9_35 = LoadTexture("data/TEXTURE/select/mission/mission_9.png");
	stage_mission10_36 = LoadTexture("data/TEXTURE/select/mission/mission_10.png");
	stage_mission11_37 = LoadTexture("data/TEXTURE/select/mission/mission_11.png");
	stage_mission12_38 = LoadTexture("data/TEXTURE/select/mission/mission_12.png");
	stage_mission13_39 = LoadTexture("data/TEXTURE/select/mission/mission_13.png");
	stage_mission14_40 = LoadTexture("data/TEXTURE/select/mission/mission_14.png");
	stage_mission15_41 = LoadTexture("data/TEXTURE/select/mission/mission_15.png");
	stage_mission16_42 = LoadTexture("data/TEXTURE/select/mission/mission_16.png");
	stage_mission17_43 = LoadTexture("data/TEXTURE/select/mission/mission_17.png");
	stage_mission18_44 = LoadTexture("data/TEXTURE/select/mission/mission_18.png");
	stage_mission19_45 = LoadTexture("data/TEXTURE/select/mission/mission_19.png");

	number_46 = LoadTexture("data/TEXTURE/result/number_02.png");
	next_47 = LoadTexture("data/TEXTURE/result/allnext.png");
	white_48 = LoadTexture("data/TEXTURE/result/fade_white.png");
	mapback_49 = LoadTexture("data/TEXTURE/result/map_back.png");
	//maparrow_50 = LoadTexture("data/TEXTURE/result/map_arrow.png");
	//maptext_51 = LoadTexture("data/TEXTURE/result/map_text.png");

	pickup_green_52 = LoadTexture("data/TEXTURE/placement/pickup_green.png");
	pickup_red_53 = LoadTexture("data/TEXTURE/placement/pickup_red.png");
	batten_red_54 = LoadTexture("data/TEXTURE/placement/batten_red.png");

	gameover_55 = LoadTexture("data/TEXTURE/result/gameover/OVER.png");
	restart_56 = LoadTexture("data/TEXTURE/result/gameover/restart.png");
	stagename_57 = LoadTexture("data/TEXTURE/result/gameover/stagename.png");
	gameover_back_58 = LoadTexture("data/TEXTURE/result/gameover/gameover_back.png");
	gameover_place_59 = LoadTexture("data/TEXTURE/result/gameover/gameover_place.png");

	titleback_60 = LoadTexture("data/TEXTURE/select/titleback.png");
	worldback_61 = LoadTexture("data/TEXTURE/select/worldback.png");

	pause_62 = LoadTexture("data/TEXTURE/pause/pause.png");
	commentary_63 = LoadTexture("data/TEXTURE/pause/commentary.png");
	above_64 = LoadTexture("data/TEXTURE/pause/above.png");
	retry_65 = LoadTexture("data/TEXTURE/pause/retry.png");
	pause_mission_66 = LoadTexture("data/TEXTURE/pause/mission.png");
	pause_stageselect_67 = LoadTexture("data/TEXTURE/pause/stageselect.png");

	GimmickDescriptionChip_68 = LoadTexture("data/TEXTURE/game/GimmickDescription/gimmick.png");
	pickup_GimmickDescription_69 = LoadTexture("data/TEXTURE/game/GimmickDescription/pickup_GimmickDescription.png");
	
	batu_70 = LoadTexture("data/TEXTURE/pause/batu.png");

	rollball_71 = LoadTexture("data/TEXTURE/select/2.png");
	flyball_72 = LoadTexture("data/TEXTURE/select/1.png");

	around_73 = LoadTexture("data/TEXTURE/pause/around.png");

	note_74 = LoadTexture("data/TEXTURE/result/note.png");
	MAPButton1_75 = LoadTexture("data/TEXTURE/result/1MAP_button.png");
	MAPButton2_76 = LoadTexture("data/TEXTURE/result/2MAP_button.png");
	NEXTSTAGE1_77 = LoadTexture("data/TEXTURE/result/1NEXTSTAGE_button.png");
	NEXTSTAGE2_78 = LoadTexture("data/TEXTURE/result/2NEXTSTAGE_button.png");
	RETRY1_79 = LoadTexture("data/TEXTURE/result/1RETRY_button.png");
	RETRY2_80 = LoadTexture("data/TEXTURE/result/2RETRY_button.png");
	Ribon_81 = LoadTexture("data/TEXTURE/result/ribon.png");
	NoJewlry_82 = LoadTexture("data/TEXTURE/result/jewelry_nasi.png");
	RedJewlry_83 = LoadTexture("data/TEXTURE/result/jewelry_Red.png");
	BlueJewlry_84 = LoadTexture("data/TEXTURE/result/jewelry_Blue.png");
	YellowJewlry_85 = LoadTexture("data/TEXTURE/result/jewelry_Yellow.png");

	mission_waku_1_86 = LoadTexture("data/TEXTURE/select/mission_waku_1.png");
	pin_87 = LoadTexture("data/TEXTURE/select/pin.png");
	botan_waku_1_88 = LoadTexture("data/TEXTURE/select/botan_waku_1.png");

	senntaku_haikei_1_89 = LoadTexture("data/TEXTURE/select/senntaku_haikei_1a.jpg");
	senntaku_haikei_2_90 = LoadTexture("data/TEXTURE/select/senntaku_haikei_2a.jpg");
	botan_1_91 = LoadTexture("data/TEXTURE/select/botan_1.png");
	botan_2_92 = LoadTexture("data/TEXTURE/select/botan_2.png");

	title_click_93 = LoadTexture("data/TEXTURE/title/title_click.png");
	title_logo_94 = LoadTexture("data/TEXTURE/title/titlerogo_4.png");
	title_bokashi_95 = LoadTexture("data/TEXTURE/select/senntaku_haikei_3a.jpg");

	result_go_96 = LoadTexture("data/TEXTURE/result/result.png");
	kekkahappyou_97 = LoadTexture("data/TEXTURE/result/kekkahappyou.png");
	kekkahappyou_2_98 = LoadTexture("data/TEXTURE/result/kekkahappyou_2.png");
	haiti_99 = LoadTexture("data/TEXTURE/result/haiti.png");
	haiti_2_100 = LoadTexture("data/TEXTURE/result/haiti_2.png");
	chara_101 = LoadTexture("data/TEXTURE/result/ribon_chara.png");

	migi_102 = LoadTexture("data/TEXTURE/pause/migi.png");
	hidari_103 = LoadTexture("data/TEXTURE/pause/hidari.png");

	number_104 = LoadTexture("data/TEXTURE/other_effect/number.png");

	pozu_105 = LoadTexture("data/TEXTURE/pause/pozu.png");
	pozu_2_106 = LoadTexture("data/TEXTURE/pause/pozu_2.png");
	utu_107 = LoadTexture("data/TEXTURE/pause/utu.png");
	wejji_108 = LoadTexture("data/TEXTURE/pause/wejji.png");
	doraiba_109 = LoadTexture("data/TEXTURE/pause/doraiba.png");

	play_botan_0_110 = LoadTexture("data/TEXTURE/placement/play_botan_0.png");
	play_botan_1_111 = LoadTexture("data/TEXTURE/placement/play_botan_1.png");
	home_botan_0_112 = LoadTexture("data/TEXTURE/placement/home_botan_0.png");
	home_botan1_113 = LoadTexture("data/TEXTURE/placement/home_botan_1.png");
	mob_placement_114 = LoadTexture("data/TEXTURE/placement/mob_placement.png");

	ue_115 = LoadTexture("data/TEXTURE/pause/ue.png");
	ue_2_116 = LoadTexture("data/TEXTURE/pause/ue_2.png");
	mission_117 = LoadTexture("data/TEXTURE/pause/mission.png");
	mission_2_118 = LoadTexture("data/TEXTURE/pause/mission_2.png");

	number_2_119 = LoadTexture("data/TEXTURE/other_effect/number_2.png");
	number_3_120 = LoadTexture("data/TEXTURE/other_effect/number_3.png");
	nobasibou_121 = LoadTexture("data/TEXTURE/other_effect/nobasibou.png");


	title_botan_122 = LoadTexture("data/TEXTURE/select/title_botan.png");
	title_botan2_123 = LoadTexture("data/TEXTURE/select/title_botan_2.png");

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

		g_Effect[i].color = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_Effect[i].Clarity);

		// UV値の設定。デフォだと全て表示
		g_Effect[i].tx = 1.0f;
		g_Effect[i].ty = 1.0f;
		g_Effect[i].sx = 0.0f;
		g_Effect[i].sy = 0.0f;

		g_Effect[i].isUse = false;

	}
	InitScore();
}

void ClearEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].isUse = false;
	}
}

void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_Effect[i].isUse = false;
	}
	// UninitScore();
	//UnloadTexture("data/TEXTURE/ao.png");
	//UnloadTexture("data/TEXTURE/result/advice.png");
	//UnloadTexture("data/TEXTURE/title/title_effect.png");
	//UnloadTexture("data/TEXTURE/other_effect/black.png");
	//UnloadTexture("data/TEXTURE/select/1.png");
	//UnloadTexture("data/TEXTURE/select/2.png");
	//UnloadTexture("data/TEXTURE/select/mission.png");
	//UnloadTexture("data/TEXTURE/select/selectstar.png");
	//UnloadTexture("data/TEXTURE/select/selectlock.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_1.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_2.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_3.png");
	//UnloadTexture("data/TEXTURE/result/clear_star_black_1.png");
	//UnloadTexture("data/TEXTURE/other_effect/number.png");

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






			

			// 時間経過による破壊処理		== にすることで999の処理が楽になる
			if (g_Effect[i].now_count == g_Effect[i].fadeIn_count
				+ g_Effect[i].all_count + g_Effect[i].fadeOut_count)
			{
				// 無制限に表示させたい場合の処理.all_count == 999だったら無制限に表示
				if (g_Effect[i].all_count == 999)
				{
					// g_Effect[i].now_count = g_Effect[i].fadeIn_count + 998;　こんなことしなくていい
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
			g_Effect[i].color = D3DXCOLOR(g_Effect[i].color.r, g_Effect[i].color.g, g_Effect[i].color.b, g_Effect[i].Clarity);
			DrawSpriteColorRotate(g_Effect[i].id, g_Effect[i].drawpos.x, g_Effect[i].drawpos.y, g_Effect[i].size.x, g_Effect[i].size.y, g_Effect[i].sx, g_Effect[i].sy, g_Effect[i].tx, g_Effect[i].ty, g_Effect[i].color, g_Effect[i].rot);
		}
	}
	DrawScore();
}

EFFECT* GetEffect(void)
{
	return &g_Effect[0];
}


// all_count == 999だったら無制限に表示
int SetEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, float tx, float ty, float sx, float sy)
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
			g_Effect[i].use_array_num = i;

			g_Effect[i].tx = tx;					// テクスチャ1マスの幅
			g_Effect[i].ty = ty;					// テクスチャ1マスの高さ
			g_Effect[i].sx = sx;					// テクスチャのスタート位置x
			g_Effect[i].sy = sy;					// テクスチャのスタート位置y

			g_Effect[i].isUse = true;

			g_Effect[i].id = GetTextureData(id);

			if (fadeIn_count == 0)
			{
				g_Effect[i].Clarity = g_Effect[i].Clarity_max;
			}

			// 最後にdrawposに直す
			g_Effect[i].drawpos = g_Effect[i].pos;

			// 透明度の変化の処理を行う。
			Fadeprocess(i);

			return i;
		}

	}

	// MAX_EFFECT を超えた数エフェクトを作成しようとするとゲームが落ちる
	exit(1);
}


// 配列の逆から入れていく
int SetEffectInReverse(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, float tx, float ty, float sx, float sy)
{
	for (int i = MAX_EFFECT - 1; i > 0; i--)
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
			g_Effect[i].use_array_num = i;

			g_Effect[i].tx = tx;					// テクスチャ1マスの幅
			g_Effect[i].ty = ty;					// テクスチャ1マスの高さ
			g_Effect[i].sx = sx;					// テクスチャのスタート位置x
			g_Effect[i].sy = sy;					// テクスチャのスタート位置y

			g_Effect[i].isUse = true;

			g_Effect[i].id = GetTextureData(id);

			if (fadeIn_count == 0)
			{
				g_Effect[i].Clarity = g_Effect[i].Clarity_max;
			}

			// 最後にdrawposに直す
			g_Effect[i].drawpos = g_Effect[i].pos;

			// 透明度の変化の処理を行う。
			Fadeprocess(i);

			return i;
		}

	}

	// MAX_EFFECT を超えた数エフェクトを作成しようとするとゲームが落ちる
	exit(1);
}

// 正の整数のみ対応
void SetEffectNumber(int num,int* back_array, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, bool vertical, float interval_magnification, int id)
{

	// 貰った数字は実際には使わずにクローンを使って計算
	int number = num;

	// もらった数字が何桁かの計算
	int digit = 0;
	while (number != 0)
	{
		number = number / 10;
		digit++;
	}
	// 0単体の場合上のワイル分だと桁数0になるので、あとでdigitを1にしてあげる
	if (num == 0)
		digit = 1;

	// 桁数の真ん中を調べる。ここが座標の中心となる
	int middle_digit = digit / 2;

	int serial = 0;
	int nextnum = -1;

	int last_i = -1;

	bool kakutei = false;

	for (int i = 0; i < MAX_EFFECT; i++)
	{

		if (g_Effect[i].isUse == false)
		{
			last_i = i;		// 開いてるとこの最初を見つけたら保存する。

			for (int j = last_i; j < last_i + digit; j++)
			{
				// 使われているものがあったらjのfor文を抜けて探しなおす
				if (g_Effect[i].isUse == true)
					break;

				// 最後まで行ったら確定する。
				if (j == last_i + digit - 1)
				{
					kakutei = true;
					break;
				}
			}
		}

		if (kakutei == true)
		{
			break;
		}

		// 最後までいって開いてなかったらエラー
		if (i == MAX_EFFECT - 1)
			exit(25);
	}

	int sn = last_i;
	// 引数のnumを改めて入れておく
	number = num;

	// セットエフェクトする処理
	for (int i = 0; i < digit; i++)
	{
		//g_Effect[i + sn].id = id;	下で引数で入力した値によってテクスチャを変更している
		g_Effect[i + sn].pos = pos1;
		g_Effect[i + sn].pos1 = pos1;
		g_Effect[i + sn].pos2 = pos2;
		g_Effect[i + sn].pos_moving_pattern = pos_moving_pattern;
		g_Effect[i + sn].size = size1;
		g_Effect[i + sn].size1 = size1;
		g_Effect[i + sn].size2 = size2;
		g_Effect[i + sn].size_moving_pattern = size_moving_pattern;
		g_Effect[i + sn].Clarity_min = Clarity_min;
		g_Effect[i + sn].Clarity_max = Clarity_max;
		g_Effect[i + sn].Clarity = g_Effect[i + sn].Clarity_min;
		g_Effect[i + sn].fadeIn_count = fadeIn_count;
		g_Effect[i + sn].all_count = all_count;
		g_Effect[i + sn].fadeOut_count = fadeOut_count;
		g_Effect[i + sn].now_count = 0;
		g_Effect[i + sn].moving_count = moving_count;
		g_Effect[i + sn].rot = AngleToRadian(rot_angle1);
		g_Effect[i + sn].rot_angle = rot_angle1;
		g_Effect[i + sn].rot_angle1 = rot_angle1;
		g_Effect[i + sn].rot_angle2 = rot_angle2;
		g_Effect[i + sn].rot_moving_pattern = rot_moving_pattern;
		g_Effect[i + sn].rot_count = 0;

		g_Effect[i + sn].drawpos = g_Effect[i + sn].pos1;
		g_Effect[i + sn].use_array_num = i + sn;
		g_Effect[i + sn].isUse = true;

		//g_Effect[i + sn].id = GetTextureData(46);		// Numberは46番に設定されてる
		//g_Effect[i + sn].id = GetTextureData(119);		// Numberは46番に設定されてる

		g_Effect[i + sn].id = GetTextureData(id);		// でふぉだと119に設定されてる



		// 桁が小さい方から描かれていく。右から左に向かって描いていく
		// 今回表示する桁の数字
		int nownum = number % 10;

		// 数字の感覚の倍率 interval_magnification でふぉだと0.7f

		// 縦書き表示出ないならxをいじる。縦書き表示ならyをいじる
		if (!vertical)
		{
			// 桁数が奇数の場合と偶数の場合で表示方法を場合分けする
			if (digit % 2 == 0)
			{
				// 偶数の場合			真ん中の桁数と次の数の間に真ん中が来る
				// スコアの位置やテクスチャー座標を反映
				g_Effect[i + sn].pos.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification - (size1.x * interval_magnification / 2);
				g_Effect[i + sn].pos1.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification - (size1.x * interval_magnification / 2);
				g_Effect[i + sn].pos2.x = pos2.x + (middle_digit - i) * size2.x * interval_magnification - (size2.x * interval_magnification / 2);
			}
			else
			{
				// 奇数の場合		指定した座標が真ん中の桁数の中心に来る
				// スコアの位置やテクスチャー座標を反映
				g_Effect[i + sn].pos.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification;
				g_Effect[i + sn].pos1.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification;
				g_Effect[i + sn].pos2.x = pos2.x + (middle_digit - i) * size2.x * interval_magnification;
			}
		}
		else
		{
			if (digit % 2 == 0)
			{
				// 偶数の場合			真ん中の桁数と次の数の間に真ん中が来る
				// スコアの位置やテクスチャー座標を反映
				g_Effect[i + sn].pos.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification - (size1.y * interval_magnification / 2);
				g_Effect[i + sn].pos1.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification - (size1.y * interval_magnification / 2);
				g_Effect[i + sn].pos2.y = pos2.y + (middle_digit - i) * size2.y * interval_magnification - (size2.y * interval_magnification / 2);
			}
			else
			{
				// 奇数の場合		指定した座標が真ん中の桁数の中心に来る
				// スコアの位置やテクスチャー座標を反映
				g_Effect[i + sn].pos.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification;
				g_Effect[i + sn].pos1.y = pos1.y + (middle_digit - i) * size1.y * interval_magnification;
				g_Effect[i + sn].pos2.y = pos2.y + (middle_digit - i) * size2.y * interval_magnification;
			}
		}

		// ポジションの再調整(ポジションムービングカウントが0なら動かないので最初からpos2に調整する)
		if (pos_moving_pattern == 0)
		{
			g_Effect[i + sn].pos.x = g_Effect[i + sn].pos2.x;
			g_Effect[i + sn].pos1.x = g_Effect[i + sn].pos2.x;

			g_Effect[i + sn].pos.y = g_Effect[i + sn].pos2.y;
			g_Effect[i + sn].pos1.y = g_Effect[i + sn].pos2.y;
		}

		g_Effect[i + sn].tx = 1.0f / 10;						// テクスチャ1マスの幅
		g_Effect[i + sn].ty = 1.0f / 2;						// テクスチャ1マスの高さ
		g_Effect[i + sn].sx = g_Effect[i + sn].tx * nownum;			// テクスチャのスタート位置x
		g_Effect[i + sn].sy = 0.0f;							// テクスチャのスタート位置y

		if (fadeIn_count == 0)
		{
			g_Effect[i + sn].Clarity = g_Effect[i + sn].Clarity_max;
		}

		// 最後にdrawposに直す
		g_Effect[i + sn].drawpos = g_Effect[i + sn].pos;


		// 透明度の変化の処理を行う。
		Fadeprocess(i + sn);

		// 次の桁へ
		number /= 10;
	}
	// スタート位置と連番が何個かを返す
	back_array[0] = sn;
	back_array[1] = digit;
}

// 設置エフェクトナンバーの00:00のように分と秒で表示する。引き数では秒でもらう。
void SetEffectTimeNumber(int num, int* back_array, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern)
{
	int min = num / 60;
	int second = num - min * 60;

	int num1 = min / 10;		// 00;00の左から1番目
	int num2 = min % 10;
	int num3 = second / 10;
	int num4 = second % 10;

	int digit = 5;		// 5で固定(00:00)

	// 桁数の真ん中を調べる。ここが座標の中心となる
	int middle_digit = digit / 2;

	int serial = 0;
	int nextnum = -1;

	int last_i = -1;
	bool kakutei = false;

	for (int i = 0; i < MAX_EFFECT; i++)
	{

		if (g_Effect[i].isUse == false)
		{
			last_i = i;		// 開いてるとこの最初を見つけたら保存する。

			for (int j = last_i; j < last_i + digit; j++)
			{
				// 使われているものがあったらjのfor文を抜けて探しなおす
				if (g_Effect[i].isUse == true)
					break;

				// 最後まで行ったら確定する。
				if (j == last_i + digit - 1)
				{
					kakutei = true;
					break;
				}
			}
		}

		if (kakutei == true)
		{
			break;
		}

		// 最後までいって開いてなかったらエラー
		if (i == MAX_EFFECT - 1)
			exit(25);
	}

	int sn = last_i;		// startnum

	// セットエフェクトする処理
	for (int i = 0; i < digit; i++)
	{
		//g_Effect[i + sn].id = id;	下で引数で入力した値によってテクスチャを変更している
		g_Effect[i + sn].pos = pos1;
		g_Effect[i + sn].pos1 = pos1;
		g_Effect[i + sn].pos2 = pos2;
		g_Effect[i + sn].pos_moving_pattern = pos_moving_pattern;
		g_Effect[i + sn].size = size1;
		g_Effect[i + sn].size1 = size1;
		g_Effect[i + sn].size2 = size2;
		g_Effect[i + sn].size_moving_pattern = size_moving_pattern;
		g_Effect[i + sn].Clarity_min = Clarity_min;
		g_Effect[i + sn].Clarity_max = Clarity_max;
		g_Effect[i + sn].Clarity = g_Effect[i + sn].Clarity_min;
		g_Effect[i + sn].fadeIn_count = fadeIn_count;
		g_Effect[i + sn].all_count = all_count;
		g_Effect[i + sn].fadeOut_count = fadeOut_count;
		g_Effect[i + sn].now_count = 0;
		g_Effect[i + sn].moving_count = moving_count;
		g_Effect[i + sn].rot = AngleToRadian(rot_angle1);
		g_Effect[i + sn].rot_angle = rot_angle1;
		g_Effect[i + sn].rot_angle1 = rot_angle1;
		g_Effect[i + sn].rot_angle2 = rot_angle2;
		g_Effect[i + sn].rot_moving_pattern = rot_moving_pattern;
		g_Effect[i + sn].rot_count = 0;

		g_Effect[i + sn].drawpos = g_Effect[i + sn].pos1;
		g_Effect[i + sn].use_array_num = i + sn;
		g_Effect[i + sn].isUse = true;

		//g_Effect[i + sn].id = GetTextureData(104);		// Numberは46番に設定されてる
		g_Effect[i + sn].id = GetTextureData(119);		// Numberは46番に設定されてる


		// 桁が小さい方から描かれていく。右から左に向かって描いていく

		float interval_magnification = 0.8f;		// 数字の感覚の倍率

		// 桁数が奇数の場合と偶数の場合で表示方法を場合分けする
		if (digit % 2 == 0)
		{
			// 偶数の場合			真ん中の桁数と次の数の間に真ん中が来る
			// スコアの位置やテクスチャー座標を反映
			g_Effect[i + sn].pos.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification - (size1.x * interval_magnification / 2);
			g_Effect[i + sn].pos1.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification - (size1.x * interval_magnification / 2);
			g_Effect[i + sn].pos2.x = pos2.x + (middle_digit - i) * size2.x * interval_magnification - (size2.x * interval_magnification / 2);
		}
		else
		{
			// 奇数の場合		指定した座標が真ん中の桁数の中心に来る
			// スコアの位置やテクスチャー座標を反映
			g_Effect[i + sn].pos.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification;
			g_Effect[i + sn].pos1.x = pos1.x + (middle_digit - i) * size1.x * interval_magnification;
			g_Effect[i + sn].pos2.x = pos2.x + (middle_digit - i) * size2.x * interval_magnification;
		}
		int UVxNum = 0;
		int UVyNum = 0;
		switch (i)
		{
		case 0:
			UVxNum = num4;
			break;
		case 1:
			UVxNum = num3;
			break;
		case 2:
			UVxNum = 2;			// : の表示
			UVyNum = 1;
			break;
		case 3:
			UVxNum = num2;
			break;
		case 4:
			UVxNum = num1;
			break;
		default:
			break;
		}

		g_Effect[i + sn].tx = 1.0f / 10;						// テクスチャ1マスの幅
		g_Effect[i + sn].ty = 1.0f / 2;							// テクスチャ1マスの高さ

		g_Effect[i + sn].sx = g_Effect[i + sn].tx * UVxNum;			// テクスチャのスタート位置x(ここでテクスチャのUV値設定)
		g_Effect[i + sn].sy = g_Effect[i + sn].ty * UVyNum;							// テクスチャのスタート位置y

		if (fadeIn_count == 0)
		{
			g_Effect[i + sn].Clarity = g_Effect[i + sn].Clarity_max;
		}

		// 最後にdrawposに直す
		g_Effect[i + sn].drawpos = g_Effect[i + sn].pos;

		// 透明度の変化の処理を行う。
		Fadeprocess(i + sn);

		// 次の桁へ
	}
	// スタート位置と連番が何個かを返す
	back_array[0] = sn;
	back_array[1] = digit;
}

// ゲーム内でのエフェクトを使う場合はこっち。座標を自動的に斜めに修正してくれる。例えばゲーム内のボールに追従するとかの時便利
// all_count == 999だったら無制限に表示
int SetGameEffect(int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
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
			g_Effect[i].use_array_num = i;
			g_Effect[i].isUse = true;

			g_Effect[i].id = GetTextureData(id);

			// 透明度の変化の処理を行う。
			Fadeprocess(i);


			return i;
		}

	}

	// MAX_EFFECT を超えた数エフェクトを作成しようとするとゲームが落ちる
	exit(1);
}


void Fadeprocess(int i)
{
	////0～fadeIn
	//if (g_Effect[i].now_count < 0 + g_Effect[i].fadeIn_count)
	//{
	//	float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeIn_count;
	//	g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * g_Effect[i].now_count;
	//}
	////fadeIn～all
	//if (g_Effect[i].now_count >= 0 + g_Effect[i].fadeIn_count &&
	//	g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count)
	//{
	//	g_Effect[i].Clarity = g_Effect[i].Clarity_max;
	//}
	////all～fadeOut
	//if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count + g_Effect[i].all_count &&
	//	g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count)
	//{
	//	float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeOut_count;
	//	g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * ((g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count) - g_Effect[i].now_count);
	//}

	int sadef = 0;
	//0～fadeIn
	if (g_Effect[i].now_count < g_Effect[i].fadeIn_count && g_Effect[i].fadeIn_count != 0)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeIn_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * g_Effect[i].now_count;
		if (g_Effect[i].id == 84)
			sadef = 1;
	}
	//fadeIn～all
	else if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count)
	{
		g_Effect[i].Clarity = g_Effect[i].Clarity_max;
		if (g_Effect[i].id == 84)
			sadef = 2;
	}
	//all～fadeOut
	else if (g_Effect[i].now_count >= g_Effect[i].fadeIn_count + g_Effect[i].all_count &&
		g_Effect[i].now_count < g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count)
	{
		float oneframe = (g_Effect[i].Clarity_max - g_Effect[i].Clarity_min) / g_Effect[i].fadeOut_count;
		g_Effect[i].Clarity = g_Effect[i].Clarity_min + oneframe * ((g_Effect[i].fadeIn_count + g_Effect[i].all_count + g_Effect[i].fadeOut_count) - g_Effect[i].now_count);
		if (g_Effect[i].id == 84)
			sadef = 3;
	}
	if (g_Effect[i].id == 84)
	{
		if (g_Effect[i].all_count != 999)
			int sdef = 3434;
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

int GetTextureData(int id)
{

	switch (id)
	{
	case 0:
		return ao_0;
		break;
	case 1:
		return aka_1;
		break;
	//case 2:
	//	return tako_2;
	//	break;
	case 3:
		return title_3;
		break;
	case 4:
		return black_4;
		break;
	case 5:
		return clear_5;
		break;
	case 6:
		return select_6;
		break;
	case 7:
		return select2_7;
		break;
	case 8:
		return mission_8;
		break;
	case 9:
		return selectstar_9;
		break;
	case 10:
		return selectlock_10;
		break;
	case 11:
		return clear_star1_11;
		break;
	case 12:
		return clear_star2_12;
		break;
	case 13:
		return clear_star3_13;
		break;
	case 14:
		return clear_star4_14;
		break;
	case 15:
		return stage_select1_15;
		break;
	case 16:
		return stage_select2_16;
		break;
	case 17:
		return stage_select3_17;
		break;
	case 18:
		return stage_select4_18;
		break;
	case 19:
		return stage_select5_19;
		break;
	case 20:
		return stage_choice1_20;
		break;
	case 21:
		return stage_choice2_21;
		break;
	case 22:
		return stage_choice3_22;
		break;
	case 23:
		return stage_choice4_23;
		break;
	case 24:
		return stage_choice5_24;
		break;
	case 25:
		return stage_mission_background_25;
		break;
	case 26:
		return stage_mission0_26;
		break;
	case 27:
		return stage_mission1_27;
		break;
	case 28:
		return stage_mission2_28;
		break;
	case 29:
		return stage_mission3_29;
		break;
	case 30:
		return stage_mission4_30;
		break;
	case 31:
		return stage_mission5_31;
		break;
	case 32:
		return stage_mission6_32;
		break;
	case 33:
		return stage_mission7_33;
		break;
	case 34:
		return stage_mission8_34;
		break;
	case 35:
		return stage_mission9_35;
		break;
	case 36:
		return stage_mission10_36;
		break;
	case 37:
		return stage_mission11_37;
		break;
	case 38:
		return stage_mission12_38;
		break;
	case 39:
		return stage_mission13_39;
		break;
	case 40:
		return stage_mission14_40;
		break;
	case 41:
		return stage_mission15_41;
		break;
	case 42:
		return stage_mission16_42;
		break;
	case 43:
		return stage_mission17_43;
		break;
	case 44:
		return stage_mission18_44;
		break;
	case 45:
		return stage_mission19_45;
		break;
	case 46:
		return number_46;
		break;
	case 47:
		return next_47;
		break;
	case 48:
		return white_48;
		break;
	case 49:
		return mapback_49;
		break;
	//case 50:
	//	return maparrow_50;
	//	break;
	//case 51:
	//	return maptext_51;
	//	break;
	case 52:
		return pickup_green_52;
		break;
	case 53:
		return pickup_red_53;
		break;
	case 54:
		return batten_red_54; 
			break;
	case 55:
		return gameover_55;
		break;		
	case 56:
		return restart_56;
		break;
	case 57:
		return stagename_57;
		break;
	case 58:
		return gameover_back_58;
		break;
	case 59:
		return gameover_place_59;
		break;
	case 60:
		return titleback_60;
		break;
	case 61:
		return worldback_61;
		break;
	case 62:
		return pause_62;
		break;
	case 63:
		return commentary_63;
		break;
	case 64:
		return above_64;
		break;
	case 65:
		return retry_65;
		break;
	case 66:
		return pause_mission_66;
		break;
	case 67:
		return pause_stageselect_67;
		break;
	case 68:
		return GimmickDescriptionChip_68;
		break;
	case 69:
		return pickup_GimmickDescription_69;
		break;
	case 70:
		return batu_70;
		break;
	case 71:
		return rollball_71;
		break;
	case 72:
		return flyball_72;
		break;
	case 73:
		return around_73;
		break;
	case 74:
		return note_74;
		break;
	case 75:
		return MAPButton1_75;
		break;
	case 76:
		return MAPButton2_76;
		break;
	case 77:
		return NEXTSTAGE1_77;
		break;
	case 78:
		return NEXTSTAGE2_78;
		break;
	case 79:
		return RETRY1_79;
		break;
	case 80:
		return RETRY2_80;
		break;
	case 81:
		return Ribon_81;
		break;
	case 82:
		return NoJewlry_82;
		break;
	case 83:
		return RedJewlry_83;
		break;
	case 84:
		return BlueJewlry_84;
		break;
	case 85:
		return YellowJewlry_85;
		break;
	case 86:
		return mission_waku_1_86;
		break;
	case 87:
		return pin_87;
		break;
	case 88:
		return botan_waku_1_88;
		break;
	case 89:
		return senntaku_haikei_1_89;
		break;
	case 90:
		return senntaku_haikei_2_90;
		break;
	case 91:
		return botan_1_91;
		break;
	case 92:
		return botan_2_92;
		break;
	case 93:
		return title_click_93;
		break;
	case 94:
		return title_logo_94;
		break;
	case 95:
		return title_bokashi_95;
		break;
	case 96:
		return result_go_96;
		break;
	case 97:
		return kekkahappyou_97;
		break;
	case 98:
		return kekkahappyou_2_98;
		break;
	case 99:
		return haiti_99;
		break;
	case 100:
		return haiti_2_100;
		break;
	case 101:
		return chara_101;
		break;
	case 102:
		return migi_102;
		break;
	case 103:
		return hidari_103;
		break;
	case 104:
		return number_104;
		break;
	case 105:
		return pozu_105;
		break;
	case 106:
		return pozu_2_106;
		break;
	case 107:
		return utu_107;
		break;
	case 108:
		return wejji_108;
		break;
	case 109:
		return doraiba_109;
		break;
	case 110:
		return play_botan_0_110;
		break;
	case 111:
		return play_botan_1_111;
		break;
	case 112:
		return home_botan_0_112;
		break;
	case 113:
		return home_botan1_113;
		break;
	case 114:
		return mob_placement_114;
		break;
	case 115:
		return ue_115;
		break;
	case 116:
		return ue_2_116;
		break;
	case 117:
		return mission_117;
		break;
	case 118:
		return mission_2_118;
		break;
	case 119:
		return number_2_119;
		break;
	case 120:
		return number_3_120;
		break;
	case 121:
		return nobasibou_121;
		break;
	case 122:
		return title_botan_122;
		break;
	case 123:
		return title_botan2_123;
		break;
	}
	
	// どこにもたどり着かなかった場合
	exit(21);
	return -1;
}

// id = -1 でテクスチャそのまま。最初にuse_array_numが必要だが、そのuse_array_numのエフェクトを途中でも変更できる,SerialNumberはデフォルト関数でデフォ=1, 引き数のpos1が99999ならば、今のエフェクトの座標からpos2の分だけ移動する設定。
void ChangeEffect(int use_array_num, int id, D3DXVECTOR2 pos1, D3DXVECTOR2 pos2, int pos_moving_pattern, D3DXVECTOR2 size1, D3DXVECTOR2 size2, int size_moving_pattern,
	float Clarity_min, float Clarity_max, int fadeIn_count, int all_count, int fadeOut_count, int moving_count,
	float rot_angle1, float rot_angle2, int rot_moving_pattern, int SerialNumber)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(29);*/
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;


	int PlaySerial = 0;			// 連番をちゃんと数えているかどうか

	for (int i = 0; i < SerialNumber; i++)
	{
		int new_array_num = use_array_num + i;
		//g_Effect[new_array_num].id = id;	下で引数で入力した値によってテクスチャを変更している
		if (pos1.x >= 99998)			// 引き数のpos1が99999ならば、今のエフェクトの座標からpos2の分だけ移動する設定。
		{
			//g_Effect[new_array_num].pos = g_Effect[new_array_num].pos;
			g_Effect[new_array_num].pos1 = g_Effect[new_array_num].pos;
			g_Effect[new_array_num].pos2 = g_Effect[new_array_num].pos + pos2;
		}
		else
		{
			g_Effect[new_array_num].pos = pos1;
			g_Effect[new_array_num].pos1 = pos1;
			g_Effect[new_array_num].pos2 = pos2;
		}
		g_Effect[new_array_num].pos_moving_pattern = pos_moving_pattern;
		if (size1.x >= 99998)			// 引き数のsize1が99999ならば、今のエフェクトのサイズからsize2のサイズをたす設定。
		{
			//g_Effect[new_array_num].size = g_Effect[new_array_num].size;
			g_Effect[new_array_num].size1 = g_Effect[new_array_num].size;
			g_Effect[new_array_num].size2 = g_Effect[new_array_num].size + size2;
		}
		else
		{
			g_Effect[new_array_num].size = size1;
			g_Effect[new_array_num].size1 = size1;
			g_Effect[new_array_num].size2 = size2;
		}
		g_Effect[new_array_num].size_moving_pattern = size_moving_pattern;
		g_Effect[new_array_num].Clarity_min = Clarity_min;
		g_Effect[new_array_num].Clarity_max = Clarity_max;
		if(fadeIn_count == 0)									// アップデートエフェクトの中のフェードプロセスがこの後実行されればよいが、EffectUpdataのがチェンジエフェクトより遅かったりした場合行われないので。
			g_Effect[new_array_num].Clarity = g_Effect[new_array_num].Clarity_max;
		else
			g_Effect[new_array_num].Clarity = g_Effect[new_array_num].Clarity_min;
		g_Effect[new_array_num].fadeIn_count = fadeIn_count;
		g_Effect[new_array_num].all_count = all_count;
		g_Effect[new_array_num].fadeOut_count = fadeOut_count;
		g_Effect[new_array_num].now_count = 0;
		g_Effect[new_array_num].moving_count = moving_count;
		g_Effect[new_array_num].rot = AngleToRadian(rot_angle1);
		g_Effect[new_array_num].rot_angle = rot_angle1;
		g_Effect[new_array_num].rot_angle1 = rot_angle1;
		g_Effect[new_array_num].rot_angle2 = rot_angle2;
		g_Effect[new_array_num].rot_moving_pattern = rot_moving_pattern;
		g_Effect[new_array_num].rot_count = 0;

		g_Effect[new_array_num].drawpos = g_Effect[new_array_num].pos1;
		//g_Effect[new_array_num].new_array_num = 
		g_Effect[new_array_num].isUse = true;

		if (id == -1)
			g_Effect[new_array_num].id = g_Effect[new_array_num].id;
		else
			g_Effect[new_array_num].id = GetTextureData(id);

		// 透明度の変化の処理を行う。
		Fadeprocess(new_array_num);

		PlaySerial++;

		// 連番の分終わったらリターンで関数を抜ける
		if(PlaySerial == SerialNumber)
			return;


	}

	// MAX_EFFECT を超えた数エフェクトを作成しようとするとゲームが落ちる
	exit(1);
}


// use_array_numのエフェクトのnow_countだけを設定できる,SerialNumberはデフォルト関数でデフォ=1
void ChangeEffectCount(int use_array_num, int setcount, int SerialNumber)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(30);*/
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].now_count = setcount;

		// 透明度の変化の処理を行う。
		Fadeprocess(use_array_num);
	}
	return;
}


// 座標だけを変えれる(ただしpos1,pos2ともに固定されてしまう)
void ChangeEffectPos(int use_array_num, float setpos_x, float setpos_y, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(31);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].pos = D3DXVECTOR2(setpos_x, setpos_y);
		g_Effect[use_array_num].pos1 = D3DXVECTOR2(setpos_x, setpos_y);
		g_Effect[use_array_num].pos2 = D3DXVECTOR2(setpos_x, setpos_y);
	}
	return;
}

// テクスチャだけを変えれる
void ChangeEffectTexture(int use_array_num, int setTexid, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(32);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].id = GetTextureData(setTexid);
	}
	return;
}

// 色だけを変えれる
void ChangeEffectColor(int use_array_num, float r, float g, float b, int SerialNumber)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(33);

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].color = D3DXCOLOR(r, g, b, g_Effect[use_array_num].Clarity);

		// 透明度の変化の処理を行う。
		Fadeprocess(use_array_num);
	}
	return;
}

// 透明度だけを変えれる,minとmaxも変わるので注意
void ChangeEffectClarity(int use_array_num, float clarity, int SerialNumber)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(34);*/

	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;

	for (int i = 0; i < SerialNumber; i++)
	{
		g_Effect[use_array_num].Clarity = clarity;
		g_Effect[use_array_num].Clarity_min = clarity;
		g_Effect[use_array_num].Clarity_max = clarity;

		// 透明度の変化の処理を行う。
		Fadeprocess(use_array_num);
	}
	return;
}

// 配列の何番目かを指定してエフェクトを消す,SerialNumberはデフォルト関数でデフォ=1
void EffectBreak(int use_array_num, int SerialNumber)
{
	// 初期値やエラーである-1だった場合もしくはマックスエフェクトを超えた値だった場合なにもしない。エラー
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return;
		//exit(35);

	int PlaySerial = 0;			// 連番をちゃんと数えているかどうか


	for (int i = 0; i < SerialNumber; i++)
	{
		int new_array_num = use_array_num + i;

		if (use_array_num + i == 25)
			int fdffef = 4;

		g_Effect[use_array_num + i].isUse = false;
		g_Effect[use_array_num + i].use_array_num = -1;

		PlaySerial++;

		// 連番の分終わったらリターンで関数を抜ける
		if (PlaySerial == SerialNumber)
			return;
	}

	exit(35);
}

// 配列の何番目のエフェクトの今の座標を返す
D3DXVECTOR2 GetEffectPos(int use_array_num)
{
	/*if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(36);*/

	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		return D3DXVECTOR2(300.f, 300.f);

	return g_Effect[use_array_num].pos;
}

// 配列の何番目のエフェクトの今のサイズを返す
D3DXVECTOR2 GetEffectSize(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(37);

	return g_Effect[use_array_num].size;
}

// 配列の何番目のエフェクトの今の透明度を返す
float GetEffectClarity(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(38);

	return g_Effect[use_array_num].Clarity;
}

// 配列の何番目のエフェクトの今のnow_countを返す
int GetEffectnow_count(int use_array_num)
{
	if (use_array_num < 0 || use_array_num >= MAX_EFFECT)
		exit(39);

	return g_Effect[use_array_num].now_count;
}
