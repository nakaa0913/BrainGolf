#pragma once

#include "main.h"
#include "renderer.h"

#define PREDICTION_MAX		(7)		// 予測弾のMax数

#define PREDICTION_SIZE		(20)	// 予測弾のベースのサイズ


// 予測弾構造体 
struct PREDICTION
{
	
	D3DXVECTOR2				size;					// 幅と高さ
	D3DXVECTOR2				pos;					// 予測弾の座標

	D3DXVECTOR2				drawpos;				// 表示する際の座標
	D3DXVECTOR2				drawsize;				// 表示する際のサイズ

	float					angle;					// 角度
	D3DXVECTOR2				vector;					// ベクトル
	float					shotpower;				// 球の力の倍率

	int						tex;					// 何番目のテクスチャーを使用するのか
	bool					isUse;					// true:使っている  false:未使用

};


HRESULT InitPrediction(void);
void UninitPrediction(void);
void UpdatePrediction(void);
void DrawPrediction(void);
void DrawPredictionSpecifyNum(int i);

PREDICTION* GetPrediction(void);

void PredictionUseTrue();
void PredictionUseFalse();