#pragma once

// 登録シーン一覧
enum SCENE
{
	SCENE_NONE,			//シーン処理なし
	SCENE_LOGO,		    //チームロゴ
	SCENE_TITLE,		//タイトル
	SCENE_GAME,			//ゲーム
	SCENE_WORLD_SELECT,	//ワールド選択画面
	SCENE_STAGE_SELECT,	//ステージ選択画面
	//SCENE_RESULT,	    //リザルト
	SCENE_MAX		    //最後だとわかる奴をいれる
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);

SCENE* GetScene(void);