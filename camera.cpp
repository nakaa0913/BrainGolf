#include "bg.h"
#include "texture.h"
#include "sprite.h"
#include "stagedata.h"
#include "FileDataManagement.h"
#include "bullet.h"
#include "camera.h"
#include "input.h"

CAMERA g_Camera;

void InitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.movespeed = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.magnification = 1.0f;
	g_Camera.zoomspeed = 0.0f;

}

void UninitCamera(void)
{
	g_Camera.pos = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.move = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.movespeed = D3DXVECTOR2(0.0f, 0.0f);
	g_Camera.magnification = 1.0f;
	g_Camera.zoomspeed = 0.0f;

}

void UpdateCamera(void)
{




	// キー入力をしたら移動する処理
	// L 右
	// J 左
	// I 上
	// K 下
	float movespeed_base = 0.5f;
	bool use_movekey_x = false;
	bool use_movekey_y = false;
	// 右に移動
	if (GetKeyboardPress(DIK_L))
	{
		g_Camera.movespeed.x += movespeed_base;
		use_movekey_x = true;
	}
	// 左に移動
	if (GetKeyboardPress(DIK_J))
	{
		g_Camera.movespeed.x -= movespeed_base;
		use_movekey_x = true;
	}
	// 下に移動
	if (GetKeyboardPress(DIK_K))
	{
		g_Camera.movespeed.y += movespeed_base;
		use_movekey_y = true;
	}
	// 上に移動
	if (GetKeyboardPress(DIK_I))
	{
		g_Camera.movespeed.y -= movespeed_base;
		use_movekey_y = true;
	}



	// 何もキーを押していない場合にカメラの移動速度を低下させる処理
	float rejectemovespeed = 1.0f;
	if (!use_movekey_x)
	{
		if (g_Camera.movespeed.x > 0)
		{
			g_Camera.movespeed.x -= rejectemovespeed;
			if (g_Camera.movespeed.x < 0)
				g_Camera.movespeed.x = 0;
		}
		if (g_Camera.movespeed.x < 0)
		{
			g_Camera.movespeed.x += rejectemovespeed;
			if (g_Camera.movespeed.x > 0)
				g_Camera.movespeed.x = 0;
		}
	}
	if (!use_movekey_y)
	{
		if (g_Camera.movespeed.y > 0)
		{
			g_Camera.movespeed.y -= rejectemovespeed;
			if (g_Camera.movespeed.y < 0)
				g_Camera.movespeed.y = 0;
		}
		if (g_Camera.movespeed.y < 0)
		{
			g_Camera.movespeed.y += rejectemovespeed;
			if (g_Camera.movespeed.y > 0)
				g_Camera.movespeed.y = 0;
		}
	}


	// 最大速度に合わせる処理
	if (g_Camera.movespeed.x > CAMERA_SPEED_MAX_X)
		g_Camera.movespeed.x = CAMERA_SPEED_MAX_X;
	if (g_Camera.movespeed.x < -CAMERA_SPEED_MAX_X)
		g_Camera.movespeed.x = -CAMERA_SPEED_MAX_X;
	if (g_Camera.movespeed.y > CAMERA_SPEED_MAX_Y)
		g_Camera.movespeed.y = CAMERA_SPEED_MAX_Y;
	if (g_Camera.movespeed.y < -CAMERA_SPEED_MAX_Y)
		g_Camera.movespeed.y = -CAMERA_SPEED_MAX_Y;


	// 移動スピードをカメラのポジションに適用させる処理
	g_Camera.pos.x += g_Camera.movespeed.x;
	g_Camera.pos.y += g_Camera.movespeed.y;







	// 拡大率の処理	======================================================


	// キー入力をしたら拡大率が変わる処理
	// U ズームイン
	// H ズームアウト
	float zoomspeed_base = 0.05f;
	bool use_zoomkey = false;
	if (GetKeyboardPress(DIK_U))
	{
		g_Camera.zoomspeed += zoomspeed_base;
		use_zoomkey = true;
	}
	if (GetKeyboardPress(DIK_H))
	{
		g_Camera.zoomspeed -= zoomspeed_base;
		use_zoomkey = true;
	}


	// 何もキーを押していない場合にカメラの移動速度を低下させる処理
	float rejectezoomspeed = 0.01f;
	if (!use_zoomkey)
	{
		if (g_Camera.zoomspeed > 0)
		{
			g_Camera.zoomspeed -= rejectezoomspeed;
			if (g_Camera.zoomspeed < 0)
				g_Camera.zoomspeed = 0;
		}
		if (g_Camera.zoomspeed < 0)
		{
			g_Camera.zoomspeed += rejectezoomspeed;
			if (g_Camera.zoomspeed > 0)
				g_Camera.zoomspeed = 0;
		}
	}

	// 最大速度に合わせる処理
	if (g_Camera.zoomspeed > CAMERA_ZOOMSPEED_MAX)
		g_Camera.zoomspeed = CAMERA_ZOOMSPEED_MAX;
	if (g_Camera.zoomspeed < -CAMERA_ZOOMSPEED_MAX)
		g_Camera.zoomspeed = -CAMERA_ZOOMSPEED_MAX;

	// ズームスピードを拡大率に適用させる処理
	g_Camera.magnification += g_Camera.zoomspeed;

	// 拡大率の最大と最低を超えないようにする処理
	if (g_Camera.magnification > CAMERA_MAGNIFICATION_MAX)
		g_Camera.magnification = CAMERA_MAGNIFICATION_MAX;
	if (g_Camera.magnification < CAMERA_MAGNIFICATION_MIN)
		g_Camera.magnification = CAMERA_MAGNIFICATION_MIN;



	// 拡大率を加味したカメラのポジションの計算	===================================

	// 拡大縮小したときに、ずれに追従するような動きにしたい。
	// おそらくだけど、とうかくずだから30度の角度での動きになる。
	
	//float 
	//g_Camera.pos.x = g_Camera.pos.x + 
	//g_Camera.pos.y = g_Camera.movespeed.y;


	// ステージを動かすイメージなのか、ゲームをプレイしている人がカメラを持っていてそのカメラを動かすイメージなのかどっち？
	// それでカメラの移動方向のプラスマイナスが決まる


}


CAMERA* GetCamera(void)
{
	return &g_Camera;
}


