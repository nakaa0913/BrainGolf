
#include "effect.h"
#include "Texture.h"
#include "sprite.h"

EFFECT g_effect[MAX_EFFECT];

//テクスチャの名前定義
int ao_0;		// 0

void InitEffect(void)
{
	//テクスチャの名前
	ao_0 = LoadTexture("data/TEXTURE/ao.png");

	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_effect[i].id = 0;
		g_effect[i].pos = D3DXVECTOR2(0, 0);
		g_effect[i].drawpos = g_effect[i].pos;
		g_effect[i].vel = D3DXVECTOR2(0, 0);
		g_effect[i].size = D3DXVECTOR2(0, 0);
		g_effect[i].fadeIn_count = 0;
		g_effect[i].all_count = 0;
		g_effect[i].fadeOut_count = 0;
		g_effect[i].now_count = 0;
		g_effect[i].direction = 0;
		g_effect[i].Clarity = 0.0f;
		g_effect[i].isUse = false;
	}
}

void UninitEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		g_effect[i].isUse = false;
	}
}

void UpdateEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].isUse)
		{
			// 毎フレームごとにカウントを進める
			g_effect[i].now_count++;

			//0～fadeIn
			if (g_effect[i].now_count < 0 + g_effect[i].fadeIn_count)
			{
				float oneframe = 1.0f / g_effect[i].fadeIn_count;
				g_effect[i].Clarity = oneframe * g_effect[i].now_count;
			}

			//fadeIn～all
			if (g_effect[i].now_count < g_effect[i].fadeIn_count + g_effect[i].all_count)
			{
				g_effect[i].Clarity = 1.0f;
			}

			//all～fadeOut
			if (g_effect[i].now_count < g_effect[i].all_count + g_effect[i].fadeOut_count)
			{
				float oneframe = 1.0f / g_effect[i].fadeOut_count;
				g_effect[i].Clarity = 1.0f - (oneframe * g_effect[i].now_count);
			}

			// 時間経過による破壊処理
			if (g_effect[i].now_count > g_effect[i].fadeIn_count
				+ g_effect[i].all_count + g_effect[i].fadeOut_count)
			{
				g_effect[i].isUse = false;
			}

			// Draw用に調整
			g_effect[i].drawpos.x = g_effect[i].pos.x;
			g_effect[i].drawpos.y = g_effect[i].pos.y;
		}
	}
}

void DrawEffect(void)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].isUse == true)
		{
			D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, g_effect[i].Clarity);
			DrawSpriteColorRotate(g_effect[i].id, g_effect[i].pos.x, g_effect[i].pos.y, g_effect[i].size.x, g_effect[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
		}
	}
}

EFFECT* GetEffect(void)
{
	return nullptr;
}

void SetEffect(int id, D3DXVECTOR2 pos, D3DXVECTOR2 vel, D3DXVECTOR2 size, int fadeIn_count, int all_count, int fadeOut_count, int direction)
{
	for (int i = 0; i < MAX_EFFECT; i++)
	{
		if (g_effect[i].isUse == false)
		{
		//g_effect[i].id = id;
		g_effect[i].pos = pos;
		g_effect[i].drawpos = g_effect[i].pos;
		g_effect[i].vel = vel;
		g_effect[i].size = size;
		g_effect[i].fadeIn_count = fadeIn_count;
		g_effect[i].all_count = all_count;
		g_effect[i].fadeOut_count = fadeOut_count;
		g_effect[i].now_count = 0;
		g_effect[i].direction = direction;
		g_effect[i].Clarity = 0.0f;
		g_effect[i].isUse = true;
		
		if(id == 0)
			g_effect[i].id = ao_0;


		return;
		}

	}

	exit(1);
}