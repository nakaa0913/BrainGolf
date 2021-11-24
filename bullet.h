//=============================================================================
//
// バレット処理 [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BULLET_MAX		(3)		// バレットのMax数
#define BULLET_SPEED	(4.0f)		// バレットの移動スピード
#define COL_COOL		(3)			// CollicionCoolの長さ


// バレット構造体
struct BULLET
{
	bool					use;					// true:使っている  false:未使用
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// バレットの座標
	D3DXVECTOR2				nextpos;				// バレットの座標
	D3DXVECTOR2				oldpos;					// バレットの座標

	float					flying_height;			// 球の飛んでいる高さ。(3次元でいうとy軸の高さ)
	bool					on_the_ground;			// 地面にボールがついている状態かどうか

	D3DXVECTOR2				drawpos;				// 表示する際の座標
	D3DXVECTOR2				drawsize;				// 表示する際のサイズ

	float					rot;					// バレットの回転量
	D3DXVECTOR2				move;					// バレットの移動量
	int						texNo;					// 何番目のテクスチャーを使用するのか
	float					friction;				// 減速処理
	float					angle;					// 角度
	D3DXVECTOR2				vector;					// ベクトル
	float					shotpower;				// 球の力の倍率
	int						CollicionCool;			// 球がブロックに当たった時のクールタイム
	int						accboardcool;			// 加速のクールタイム
	int						warpcool;				// ワープのクールタイム
	int						shottime;				// 弾が発射されてからの時間
	int						collisiontime;			// 弾が当たっている時間

	int						club_pattern;			// 球の飛び方

};

struct SHADOWBULLET
{
	float					w, h;					// 幅と高さ
	D3DXVECTOR2				pos;					// バレットの座標

	D3DXVECTOR2				drawpos;				// 表示する際の座標
	D3DXVECTOR2				drawsize;				// 表示する際のサイズ

	int						tex;					// 何番目のテクスチャーを使用するのか
};


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

BULLET* GetBullet(void);

D3DXVECTOR2 AngleToVector2(float angle);
void SetBullet(D3DXVECTOR2 pos, float angle, int ShotPower, int club_pattern);
float CalculateCornerDistanceX(int CornerNum, float size_x, float size_y);
float CalculateCornerDistanceY(int CornerNum, float size_x, float size_y);
void CalculateNewVecAng(int i, float bulletposX, float bulletposY, float CornerPosX, float CornerPosY);
void InversionVecAng(int i, int XorY);
void DrawBulletSpecifyNum(int i);
float Bounce(float maxhight, int nowframe, int bounce1frame, int bounce2frame, int bounce3frame, int bounce4frame);