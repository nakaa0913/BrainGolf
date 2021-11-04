#include "main.h"
#include "bg.h"

#define MAX_STAGE (30)			//最大ステージ

typedef struct {
	int stagenum;				//ステージ番号
	int maparray[MAP_Y][MAP_X];	// マップの配列データ
	int mission1;				//ミッションは何か
	int mission2;
	int mission3;
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