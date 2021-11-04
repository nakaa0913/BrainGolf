#pragma once



// ファイル読み込み中に、今何のデータを読んでいるかの判別するためのパターン
#define		PATTERN_NULL		(-1)
#define		PATTERN_MAP			(0)
#define		PATTERN_PLAYER		(1)
#define		PATTERN_END			(999)


void LoadMapdataMain(char* fileName);

int LoadMapdata(FILE* fp);
int charToint(char c);
void applyMapArray(int x, int y, char strings[]);