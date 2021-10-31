//effect.h
#include "main.h"
#include "renderer.h"

#define MAX_EFFECT (100)

typedef struct 
{
	int		id;				//エフェクト番号
	D3DXVECTOR2	pos;		// 位置
	D3DXVECTOR2	drawpos;	// 位置
	D3DXVECTOR2	vel;		// 速度
	D3DXVECTOR2	size;		// サイズ
	int		fadeIn_count;	//エフェクト消去用カウント
	int		all_count;		//エフェクト消去用カウント
	int		fadeOut_count;	//エフェクト消去用カウント
	int		now_count;		//生成されてからのカウント
	int		direction;		//エフェクトの方向
	float	Clarity;		//透明度
	bool	isUse;			//使用フラグ
}EFFECT;

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);

EFFECT* GetEffect(void);

void SetEffect(int id, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 vel, int fadeIn_count, int all_count, int fadeOut_count, int direction);