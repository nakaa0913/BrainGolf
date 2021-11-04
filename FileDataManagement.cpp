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

void LoadMapdataMain(char* fileName)
{
	//// stagedataに出力していくので、ポインターで持ってきておく
	//STAGEDATA* p_Stagedata = GetStagedata();

	FILE* fp; // FILE型構造体

	// ファイル読み込むで開く
	fopen_s(&fp, fileName, "r");

	// 開くのに失敗した場合の処理。強制終了させている
	if (fp == NULL)
	{
		printf("%s file not open!\n", fileName);
		exit(2);		// ファイルを開いたりするときに出たエラーは(2)
		return;
	}

	char loadchar[4] = "";				// 読み込まれた文字列。読み込むたびに上書きされている。今回の場合1文字(半角)しか入らない
	char now_strings[256] = "";			// 読み込んでいった文字列を連結させている。
	int pattern = PATTERN_NULL;			// 読み込んだ文字列から、今何を読み込んでいるかを判別するためのもの。

	while (pattern == PATTERN_NULL)
	{
		// ファイルを1文字ずつ読み込む	fscanfは返り値として読み込んだ数(%sとか%dの数)を返すが、今回は無視するので(void)をつける
		(void)fscanf(fp, "%1s", loadchar);

		// 文字を繋げていく
		strcat(now_strings, loadchar);


		// 特定文字列が来たらその文字列に応じたパターンに分かれていく。

		// strstr は文字列①の中に②があるかを検索(部分検索)できる。戻り値は、成功:①で最初に出現した②へのポインタ。失敗:NULL
		// ようするにNULLでなければ成功している。
		// MapdataStart の場合マップデータの読み込みが始まる
		if (strstr(now_strings, "MapdataStart") != NULL)
		{
			pattern = PATTERN_MAP;

			// now_stringsを初期化する
			strcpy(now_strings, "");
		}
		// PlayerdataStart の場合プレイヤーがどこに配置されているかと、どんな動きをするかの読み込みが始まる
		if (strstr(now_strings, "PlayerdataStart") != NULL)
		{
			pattern = PATTERN_PLAYER;

			// now_stringsを初期化する
			strcpy(now_strings, "");
		}
		// PlayerdataStart の場合プレイヤーがどこに配置されているかと、どんな動きをするかの読み込みが始まる
		if (strstr(now_strings, "EndLoadFile") != NULL)
		{
			pattern = PATTERN_END;

			// now_stringsを初期化する
			strcpy(now_strings, "");
		}


		// パターンに応じた処理

		if (pattern == PATTERN_MAP)
		{
			pattern = LoadMapdata(fp);			// 関数が終了した時戻り値でPATTERN_NULLをもらう
		}

		if (pattern == PATTERN_PLAYER)
		{
			// pattern = LoadMapdata(fp);
		}



		// 50文字以上の文字列になってしまったらエラーとみなし強制終了させる
		if (strlen(now_strings) > 50)
		{
			fclose(fp); // ファイルを閉じる
			exit(5);
		}
	}

	// 終了の処理
	fclose(fp); // ファイルを閉じる
	return;
}


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





// // fgetc(1文字ずつ) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedataに出力していくので、ポインターで持ってきておく
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE型構造体
//	int max_line = 20;			// 読み込むファイルのデータの行数
//	int mapdata_max = MAP_X * MAP_Y;		// 読み込むマップデータの数
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
//	int tessss = 0;
//
//	int strnum = 0;	// 文字列の数
//	int i = 0;		// y
//	int j = 0;		// x
//	//char getc = 'a';
//	//char loadchar[1] = "";		// 64バイトまでの文字を入れることができる箱
//	char loadchar[1] = "";		// 64バイトまでの文字を入れることができる箱
//	//char *p_loadchar;		// 64バイトまでの文字を入れることができる箱
//	//p_loadchar = &loadchar;		// ポインターでアドレスを入れておく
//	char now_string[256] = "";		// 64バイトまでの文字を入れることができる箱
//
//	// fgetc は1文字だけ読み込む
//	// 1文字読み込みの fgetc 「, 」か「改行」か「EOF」が来るまで繰り返す
//	while (1)
//	{
//		loadchar[0] = fgetc(fp);
//
//		//p_loadchar = &loadchar;
//		// 
//		// カンマだったら次の文字の検索へ
//		if (loadchar[0] == ',')
//			j++;
//
//		strcat(now_string, loadchar);
//
//
//		int cmp = 0;
//		cmp = strcmp(now_string, "1");
//		//{
//		//	tessss++;
//		//}
//
//
//
//		//// 改行文字だったら次の行の処理へ
//		//if (loadchar == '\n')
//		//{
//		//	i++;
//		//	j = 0;
//		//}
//
//		//// EOFだったらブレイクさせる
//		//if (loadchar == EOF)
//		//	break;
//
//		//// 文字(%c)の数字から値(%d)の数字へ変換
//		// int mapdata = charToint(loadchar);
//
//
//	 //  // 上手くいってる場合は現在のステージデータの更新を行う。
//		//p_Stagedata->maparray[i][j] = mapdata;
//		i++;
//		int aaaaa = 0;
//
//	}
//
//	fclose(fp); // ファイルを閉じる
//
//	return;
//}




//// fgets(1行ずつ) + sscanf
//void LoadMapdata(char* fileName)
//{
//	// stagedataに出力していくので、ポインターで持ってきておく
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE型構造体
//	char max_bite[256];			// 1行の最大文字数(バイト数)
//	int max_line = 20;			// 読み込むファイルのデータの行数
//	//int x[14]{};					// 1行にある、読み込む、データの数
//	char x[14][length]{};					// 1行にある、読み込む、データの数
//
//	// ファイル読み込むで開く
//	//fp = fopen(fileName, "r");
//	fopen_s(&fp, fileName, "r");
//
//	// 開くのに失敗した場合の処理。強制終了させている
//	if (fp == NULL)
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// ファイルを開いたりするときに出たエラーは(2)
//		return;
//	}
//
//	int loadnum = 0;
//
//	int i = 0;
//	//while (loadnum = fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d, ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
//	while (loadnum = fscanf(fp, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,], ", &x[0], &x[1], &x[2], &x[3], &x[4], &x[5], &x[6], &x[7], &x[8], &x[9], &x[10], &x[11], &x[12], &x[13]) != EOF)
//	{
//
//
//
		//// 文字(%c)の数字から値(%d)の数字へ変換
		//for (int j = 0; j < 14; j++)
		//{
		//	int len = strlen(x[j]);
		//	if (len == 1)
		//	{
		//		int mapdata = charToint(x[j][0]);
		//		p_Stagedata->maparray[i][j] = mapdata;
		//	}
		//	if (len == 2)
		//	{
		//		int mapdata = 10 * charToint(x[j][0]) + charToint(x[j][1]);
		//		p_Stagedata->maparray[i][j] = mapdata;
		//		int aaada = 0;
		//	}
		//	if (len == 3)
		//	{
		//		int mapdata = 100 * charToint(x[j][0]) + 10 * charToint(x[j][1]) + charToint(x[j][2]);
		//		p_Stagedata->maparray[i][j] = mapdata;
		//	}
		//}
//
//		// 次のエラー発見のために一度初期化する。
//		for (int j = 0; j < 14; j++)
//		{
//			x[j][0] = 'f';
//		}
//
//		// 次の行へ進む。
//		i++;
//
//		// 予定の最大行以上になろうとしたらブレイクする
//		if (i >= max_line)
//			break;
//
//	}
//
//	int sadadad = 1;
//	fclose(fp); // ファイルを閉じる
//
//	return;
//}



// fgetcで1文字ずつ読もうとしたら"1ﾌﾌﾌﾌﾌ,1ﾌﾌﾌﾌﾌ"となってしまうのでやめた原因分からない
// fscanf(フォーマット指定)を使って1文字ずつ	"%1s"	とすることで1文字ずつ読める。
// 改行文字,半角空白等はスキップされる。全角スペース等は読み込めない文字として"繰"みたいな文字で読まれてしまうから無視するように書く。
// テキストの終わりすらも読めず、最期の文字を読み込んだ状態で止まってしまうのでそれの対策もエラーで書いておく。
// 全角文字は全て使えない。エラーになるので絶対使ってはいけない。もしくはそれを無視する処理を書く。
//void LoadMapdata(char* fileName)
//{
//	// stagedataに出力していくので、ポインターで持ってきておく
//	STAGEDATA* p_Stagedata = GetStagedata();
//
//	FILE* fp; // FILE型構造体
//
//	// ファイル読み込むで開く
//	fopen_s(&fp, fileName, "r");
//
//	// 開くのに失敗した場合の処理。強制終了させている
//	if (fp == NULL)
//	{
//		printf("%s file not open!\n", fileName);
//		exit(2);		// ファイルを開いたりするときに出たエラーは(2)
//		return;
//	}
//
//	char loadchar[4] = "";
//	char now_strings[256] = "";
//	char decision_strings[256] = "";
//	bool decision = false;
//
//	int x = 0;
//	int y = 0;
//	while (1)
//	{
//		// ファイルを1文字ずつ読み込む	fscanfは返り値として読み込んだ数(%sとか%dの数)を返すが、今回は無視するので(void)をつける
//		(void)fscanf(fp,"%1s", loadchar);
//
//		// カンマが来たら文字列を確定させて次の文字列へ		// strcmpは比較して等しいと0を返す。
//		if (strcmp(loadchar, ",") == 0)
//		{
//			// 確定した文字列を数字に変換しマップデータに反映させる処理
//			applyMapArray(x, y, now_strings);
//
//			// now_stringsを初期化する
//			strcpy(now_strings, "");
//
//			// 次の文字へ
//			x++;
//			// 次の行へ		xがマップの横幅分まで来たら次はy+1のところへ
//			if (x == MAP_X)
//			{
//				y++;
//				x = 0;
//				// マップ配列分文字を読み終わったら個々のループを抜け出す
//				if (y == MAP_Y)
//					break;
//			}
//		}
//		else
//		{
//			// カンマでなければ文字を繋げていく
//			strcat(now_strings, loadchar);
//		}
//
//
//		// 50文字以上の文字列になってしまったらエラーとみなし強制終了させる
//		if (strlen(now_strings) > 50)
//		{
//			exit(5);
//		}
//
//
//	}
//
//
//	fclose(fp); // ファイルを閉じる
//
//	return;
//}


int LoadMapdata(FILE* fp)
{
	// stagedataに出力していくので、ポインターで持ってきておく
	STAGEDATA* p_Stagedata = GetStagedata();

	char loadchar[4] = "";
	char now_strings[256] = "";
	char decision_strings[256] = "";
	bool decision = false;

	int x = 0;
	int y = 0;
	while (1)
	{
		// ファイルを1文字ずつ読み込む	fscanfは返り値として読み込んだ数(%sとか%dの数)を返すが、今回は無視するので(void)をつける
		(void)fscanf(fp, "%1s", loadchar);

		// カンマが来たら文字列を確定させて次の文字列へ		// strcmpは比較して等しいと0を返す。
		if (strcmp(loadchar, ",") == 0)
		{
			// 確定した文字列を数字に変換しマップデータに反映させる処理
			applyMapArray(x, y, now_strings);

			// now_stringsを初期化する
			strcpy(now_strings, "");

			// 次の文字へ
			x++;
			// 次の行へ		xがマップの横幅分まで来たら次はy+1のところへ
			if (x == MAP_X)
			{
				y++;
				x = 0;
				// マップ配列分文字を読み終わったら終了とみなしてNULLを返す
				if (y == MAP_Y)
				{
					return PATTERN_NULL;
				}
			}
		}
		else
		{
			// カンマでなければ文字を繋げていく
			strcat(now_strings, loadchar);
		}

		// PlayerdataEND を見つけた場合処理は終了とみなしてNULLを返す
		if (strstr(now_strings, "PlayerdataEnd") != NULL)
		{
			// now_stringsを初期化する
			strcpy(now_strings, "");

			return PATTERN_NULL;
		}

		// 50文字以上の文字列になってしまったらエラーとみなし強制終了させる
		if (strlen(now_strings) > 50)
		{
			int aaaaa = 5;
			//exit(5);
		}


	}



	return PATTERN_NULL;
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


void applyMapArray(int x, int y, char strings[])
{
	// stagedataに出力していくので、ポインターで持ってきておく
	STAGEDATA* p_Stagedata = GetStagedata();

	// 文字列が何文字か調べ、文字数に応じて数字に変換したときの桁数を変える
	int len = strlen(strings);
	if (len == 1)
	{
		int mapdata = charToint(strings[0]);
		p_Stagedata->maparray[y][x] = mapdata;
		int fassa = 4;
	}
	if (len == 2)
	{
		int mapdata = 10 * charToint(strings[0]) + charToint(strings[1]);
		p_Stagedata->maparray[y][x] = mapdata;
		int aaada = 0;
	}
	if (len == 3)
	{
		int mapdata = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);
		p_Stagedata->maparray[y][x] = mapdata;
	}

	return;
}


