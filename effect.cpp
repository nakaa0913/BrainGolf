
#include "effect.h"
#include "Texture.h"
#include "sprite.h"

EFFECT g_effect[MAX_EFFECT];

//テクスチャの名前定義
static int ao_0;		// 0
static int aka_1;		// 1
static int tako_2;		// 2
static int title_3;		// 3
static int black_4;		// 4
void InitEffect(void)
{
	//テクスチャの名前
	ao_0 = LoadTexture("data/TEXTURE/ao.png");
	aka_1 = LoadTexture("data/TEXTURE/aka.png");
	tako_2 = LoadTexture("data/TEXTURE/tako.png");
	title_3 = LoadTexture("data/TEXTURE/title.png");
	black_4 = LoadTexture("data/TEXTURE/black.png");

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
			

			//0～fadeIn
			if (g_effect[i].now_count < 0 + g_effect[i].fadeIn_count)
			{
				float oneframe = 1.0f / g_effect[i].fadeIn_count;
				g_effect[i].Clarity = oneframe * g_effect[i].now_count;
			}

			//fadeIn～all
			if(g_effect[i].now_count >= 0 + g_effect[i].fadeIn_count && 
				g_effect[i].now_count < g_effect[i].fadeIn_count + g_effect[i].all_count)
			{
				g_effect[i].Clarity = 1.0f;
			}

			//all～fadeOut
			if (g_effect[i].now_count >= g_effect[i].fadeIn_count + g_effect[i].all_count && 
				g_effect[i].now_count < g_effect[i].fadeIn_count + g_effect[i].all_count + g_effect[i].fadeOut_count)
			{
				float oneframe = 1.0f / g_effect[i].fadeOut_count;
				g_effect[i].Clarity = oneframe * ((g_effect[i].fadeIn_count + g_effect[i].all_count + g_effect[i].fadeOut_count) - g_effect[i].now_count);
			}

			// 時間経過による破壊処理
			if (g_effect[i].now_count > g_effect[i].fadeIn_count
				+ g_effect[i].all_count + g_effect[i].fadeOut_count)
			{
				// 無制限に表示させたい場合の処理.all_count == 999だったら無制限に表示
				if (g_effect[i].all_count == 999)
				{
					g_effect[i].now_count = g_effect[i].fadeIn_count + g_effect[i].all_count;
				}
				else
					g_effect[i].isUse = false;
			}

			// 毎フレームごとにカウントを進める
			g_effect[i].now_count++;
			
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
			// D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			DrawSpriteColorRotate(g_effect[i].id, g_effect[i].pos.x, g_effect[i].pos.y, g_effect[i].size.x, g_effect[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f, col, 0.0f);
			int aaaa = 0;
		}
	}
}

EFFECT* GetEffect(void)
{
	return nullptr;
}


// all_count == 999だったら無制限に表示
void SetEffect(int id, D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 vel, int fadeIn_count, int all_count, int fadeOut_count, int direction)
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
		if (id == 1)
			g_effect[i].id = aka_1;
		if (id == 2)
			g_effect[i].id = tako_2;
		if (id == 3)
			g_effect[i].id = title_3;
		if (id == 4)
			g_effect[i].id = black_4;


		return;
		}

	}

	exit(1);
}

