#include "main.h"
#include "bg.h"

#define MAX_STAGE	(30)		//最大ステージ
#define MAX_MISSION (3)			//ミッション数の最大(最後尾)3つ固定

typedef struct {
	int stagenum;				//ステージ番号
	int maparray[MAP_Y][MAP_X];	// マップの配列データ
	int mission_ContentsNum[MAX_MISSION];				//ミッションの内容	ミッションは3つ固定なので3
	int mission_UseNum[MAX_MISSION];					//ミッションの内容で使われる数字

	//bool clear1;				//ミッションをクリアしたか
	//bool clear2;				// これはプレイヤーのセーブデータの方で管理
	//bool clear3;
	//float cleartime;			//クリアタイム
}STAGEDATA;


void InitStagedata();
void UninitStagedata();
void UpdateStagedata();

STAGEDATA* GetStagedata();

void SetStageData(int stagenum);