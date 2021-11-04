#pragma once

#include "player.h"

// ファイル読み込み中に、今何のデータを読んでいるかの判別するためのパターン
#define		PATTERN_NULL		(-1)
#define		PATTERN_MAP			(0)
#define		PATTERN_PLAYER		(1)
#define		PATTERN_END			(999)

// ファイル読み込み中の、プレイヤーの配置データのどこを読んでいるかの判別するためのパターン
#define		PATTERN_PLAYER_NULL			(-1)
#define		PATTERN_PLAYER_POS			(0)
#define		PATTERN_PLAYER_NEXTPOS		(1)
#define		PATTERN_PLAYER_MOVESPEED	(2)


void LoadMapdataMain(char* fileName);

int LoadMapdata(FILE* fp);
int LoadPlayerdata(FILE* fp);

int charToint(char c);
float charTofloat(char* strings, int num);
char intTochar(int num);
void applyMapArray(int x, int y, char strings[]);
void SetMAPCHIP_POS_STRUCT(MAPCHIP_POS_STRUCT* s_mapchip_pos, char strings[], int order, int XorY);
float SetMoveSpeed(int decimal_point, char strings[]);