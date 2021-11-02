#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "bullet.h"
#include "score.h"
#include "sound.h"
#include "bg.h"
#include "FileDataManagement.h"
#include "stagedata.h"

#define	length (3)


// fgets(1行ずつ) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedataに出力していくので、ポインターで持ってきておく
//	STAGEDATA *p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE型構造体
//	char max_bite[256];			// 1行の最大文字数(バイト数)
//	int max_line = 20;			// 読み込むファイルのデータの行数
//	char x[14]{};					// 1行にある、読み込む、データの数
//
//	// ファイル読み込むで開く
//	fp = fopen(fileName, "r");
//
//	// 開くのに失敗した場合の処理。強制終了させている
//	if (fp == NULL) 
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// ファイルを開いたりするときに出たエラーは(2)
//		return;
//	}
//
//
//	int i = 0;
//	while (fgets(max_bite, max_line, fp) != NULL)
//	{
//		int loadnum = 0;
//		// sscanfは戻り値として読み取った個数を返すが必要ないので前に(void)を付けてあげるとエラーが出なくなる。
//		//loadnum = sscanf(max_bite, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]);
//		loadnum = sscanf(max_bite, "%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]);
//
//		int asasdafggg = 4;
//
//		 // 読み取った個数が14個でない場合エラーとする
//		//if (loadnum != 14)
//		//{
//		//	exit(3);			// 読み取った個数がおかしいのでエラー
//		//}
//
//		// 上手くいってる場合は現在のステージデータの更新を行う。
//		for (int j = 0; j < 14; j++)
//		{
//			p_Stagedata->maparray[i][j] = x[j];
//		}
//
//		// 次の行へ進む。
//		i++;
//	}
//
//	fclose(fp); // ファイルを閉じる
//
//	return;
//}





 // fgetc(1文字ずつ) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedataに出力していくので、ポインターで持ってきておく
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE型構造体
//	int max_line = 20;			// 読み込むファイルのデータの行数
//
//
//	// ファイル読み込むで開く
//	fp = fopen(fileName, "r");
//
//	// 開くのに失敗した場合の処理。強制終了させている
//	if (fp == NULL)
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// ファイルを開いたりするときに出たエラーは(2)
//		return;
//	}
//
//
//	int i = 0;		// y
//	int j = 0;		// x
//	//char getc = 'a';
//
//	// fgetc は1文字だけ読み込む
//	// 1文字読み込みの fgetc 「, 」か「改行」か「EOF」が来るまで繰り返す
//	while (char getc = fgetc(fp) != NULL)
//	{
//
//		// 改行文字だったら次の行の処理へ
//		if (getc == '\n')
//		{
//			i++;
//			j = 0;
//		}
//		// カンマだったら次の文字の検索へ
//		if (getc == ',')
//			j++;
//
//		// EOFだったらブレイクさせる
//		if (getc == EOF)
//			break;
//
//		// 読み込みたい最大行数まで来たらブレイク(もしくは処理の変化をさせるとか)
//		if (i == max_line)
//			break;
//
//		// 文字(%c)の数字から値(%d)の数字へ変換
//		 int mapdata = charToint(getc);
//
//
//	   // 上手くいってる場合は現在のステージデータの更新を行う。
//		p_Stagedata->maparray[i][j] = mapdata;
//		int aaaaa = 0;
//
//	}
//
//	fclose(fp); // ファイルを閉じる
//
//	return;
//}




// fgets(1行ずつ) + sscanf
void LoadMapdata(char* fileName)
{
	// stagedataに出力していくので、ポインターで持ってきておく
	STAGEDATA* p_Stagedata = GetStagedata();

	FILE* fp; // FILE型構造体
	char max_bite[256];			// 1行の最大文字数(バイト数)
	int max_line = 20;			// 読み込むファイルのデータの行数
	//int x[14]{};					// 1行にある、読み込む、データの数
	char x[14][length]{};					// 1行にある、読み込む、データの数

	// ファイル読み込むで開く
	//fp = fopen(fileName, "r");
	fopen_s(&fp, fileName, "r");

	// 開くのに失敗した場合の処理。強制終了させている
	if (fp == NULL)
	{
		printf("%s file not open!\n", fileName);
		exit(2);		// ファイルを開いたりするときに出たエラーは(2)
		return;
	}

	int loadnum = 0;

	int i = 0;
	//while (loadnum = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
	while (loadnum = fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,], ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
	{



		// 文字(%c)の数字から値(%d)の数字へ変換
		for (int j = 0; j < 14; j++)
		{
			int len = strlen(x[j]);
			if (len == 1)
			{
				int mapdata = charToint(x[j][0]);
				p_Stagedata->maparray[i][j] = mapdata;
			}
			if (len == 2)
			{
				int mapdata = 10 * charToint(x[j][0]) + charToint(x[j][1]);
				p_Stagedata->maparray[i][j] = mapdata;
				int aaada = 0;
			}
			if (len == 3)
			{
				int mapdata = 100 * charToint(x[j][0]) + 10 * charToint(x[j][1]) + charToint(x[j][2]);
				p_Stagedata->maparray[i][j] = mapdata;
			}
		}

		// 次のエラー発見のために一度初期化する。
		for (int j = 0; j < 14; j++)
		{
			x[j][0] = 'f';
		}

		// 次の行へ進む。
		i++;

		// 予定の最大行以上になろうとしたらブレイクする
		if (i >= max_line)
			break;

	}

	int sadadad = 1;
	fclose(fp); // ファイルを閉じる

	return;
}



// char型の数字(1桁のみ)からint型の数字へ
int charToint(char c) 
{
	switch (c) 
	{
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: 
		// 正しいマップの書き方になっていなくて十分な数(14)が読み込まれなかった場合やへんに文字が紛れ込んでいた場合
		exit(3);			// 強制終了。エラー3
		return 0;
	}
}

// char型の数字(1桁のみ)からint型の数字へ
//int shortToint(char c)
//{
//	switch (c)
//	{
//	case "0": return 0;
//	case '1': return 1;
//	case '2': return 2;
//	case '3': return 3;
//	case '4': return 4;
//	case '5': return 5;
//	case '6': return 6;
//	case '7': return 7;
//	case '8': return 8;
//	case '9': return 9;
//	default: 
		// 正しいマップの書き方になっていなくて十分な数(14)が読み込まれなかった場合やへんに文字が紛れ込んでいた場合
	//exit(3);			// 強制終了。エラー3
	//return 0;
//	}
//}





