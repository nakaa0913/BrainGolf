#pragma once

// 登録シーン一覧
enum SCENE
{
	SCENE_NONE,		//シーン処理なし
	SCENE_LOGO,     //チームロゴ
	SCENE_TITLE,	//タイトル
	SCENE_GAME,		//ゲーム
	SCENE_SELECT,	//選択画面
	SCENE_RESULT,	//リザルト
	SCENE_MAX		//最後だとわかる奴をいれる
};

void InitScene(SCENE index);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

void SetScene(SCENE index);
void CheckScene(void);
