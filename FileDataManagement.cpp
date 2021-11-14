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
#include "savedata.h"

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

	while (pattern != PATTERN_END)
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
		// MissiondataStart の場合ミッションに関する読み込みが開始される
		if (strstr(now_strings, "MissiondataStart") != NULL)
		{
			pattern = PATTERN_MISSION;

			// now_stringsを初期化する
			strcpy(now_strings, "");
		}


		// ファイル読み込み終了を読み取る終了処理
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
			pattern = LoadPlayerdata(fp);
		}
		if (pattern == PATTERN_MISSION)
		{
			pattern = LoadMissiondata(fp);
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




void LoadSavedata(char* fileName)
{
	// セーブデータに読み込む
	SAVEDATA* p_Savedata = GetSavedata();

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
	int pattern = PATTERN_SAVEDATA_NULL;			// 読み込んだ文字列から、今何を読み込んでいるかを判別するためのもの。

	int load_num = 0;					// 現在読み込んでいる場所0~2:ミッション,3クリアタイム

	int now_load_stage = 0;

	while (pattern != PATTERN_END)
	{
		// ファイルを1文字ずつ読み込む	fscanfは返り値として読み込んだ数(%sとか%dの数)を返すが、今回は無視するので(void)をつける
		(void)fscanf(fp, "%1s", loadchar);

		// ステージの番号を読み込むフェーズなら
		if (pattern == PATTERN_SAVEDATA_STAGENUM)
		{
			// カンマが来たら読み込むステージを確定させる
			if (strcmp(loadchar, ",") == 0)
			{
				// テキストファイルにはステージ1~50で書かれているので、0~49に修正するために-1する
				now_load_stage = StringsToInt(now_strings) - 1;
				pattern = PATTERN_SAVEDATA_NULL;

				strcpy(now_strings, "");
				continue;
			}
			else
			{
				// カンマでなければ文字を繋げていく
				strcat(now_strings, loadchar);
			}
		}

		// NULLのフェーズなら(ステージ選択以外はこれ)
		if (pattern == PATTERN_SAVEDATA_NULL)
		{
			// "s"がきたら、読み込むステージをそれに更新し、削除して次の文字の検索へ。
			if (strcmp(loadchar, "s") == 0)
			{
				pattern = PATTERN_SAVEDATA_STAGENUM;
				strcpy(now_strings, "");
				continue;
			}

			// カンマが来たら文字列を確定させる
			if (strcmp(loadchar, ",") == 0)
			{
				// 現在の文字列がカンマだけだった場合、削除して次の文字の検索へ。これをすることによって、(,1)とかの心配がなくなる
				if (strcmp(now_strings, ",") == 0)
				{
					strcpy(now_strings, "");
					continue;
				}

				// ミッションなのか時間なのか
				if (load_num < 3)
				{
					// ミッションの読み込み	0or1で帰ってくる,1がクリア
					p_Savedata[now_load_stage].mission_clear[load_num] = StringsToInt(now_strings);
					strcpy(now_strings, "");
					load_num++;					// 読み込み個所を+1する
				}
				else if (load_num == 3)
				{
					// 時間の読みこみ
					p_Savedata[now_load_stage].clear_time = StringsToInt(now_strings);
					strcpy(now_strings, "");
					// すべての要素を読み込んだのでloadnumを0にする
					load_num = 0;
				}

				continue;
			}
			else
			{
				// カンマでなければ文字を繋げていく
				strcat(now_strings, loadchar);
			}
		}

		// ファイル読み込み終了を読み取る終了処理
		if (strstr(now_strings, "EndLoadFile") != NULL)
		{
			pattern = PATTERN_END;

			// now_stringsを初期化する
			strcpy(now_strings, "");
		}

		// 50文字以上の文字列になってしまったらエラーとみなし強制終了させる
		if (strlen(now_strings) > 50)
		{
			int dad = 0;
			fclose(fp); // ファイルを閉じる
			exit(5);
		}
	}

	// 終了の処理
	fclose(fp); // ファイルを閉じる
	return;
}






// 一部だけ書き換える処理が存在しないので全てを上書きしなければならない
void WriteSavedata(char* fileName)
{
	// 現在のセーブデータを読み込む
	SAVEDATA* p_Savedata = GetSavedata();
	STAGEDATA* p_Stagedata = GetStagedata();

	FILE* fp; // FILE型構造体

	// ファイル書き込みで開く
	fopen_s(&fp, fileName, "w");

	// 開くのに失敗した場合の処理。強制終了させている
	if (fp == NULL)
	{
		printf("%s file not open!\n", fileName);
		exit(2);		// ファイルを開いたりするときに出たエラーは(2)
		return;
	}

	char bases[4] = "s";

	char stagenum[20] = "";
	char mission0char[20] = "";
	char mission1char[20] = "";
	char mission2char[20] = "";
	char cleartimechar[20] = "";

	for (int i = 0; i < MAX_STAGE; i++)
	{
		// 全てのデータをchar型に直す処理
		strcpy(stagenum, intTostrings(i + 1));
		strcpy(mission0char, intTostrings(p_Savedata[i].mission_clear[0]));
		strcpy(mission1char, intTostrings(p_Savedata[i].mission_clear[1]));
		strcpy(mission2char, intTostrings(p_Savedata[i].mission_clear[2]));
		strcpy(cleartimechar, intTostrings(p_Savedata[i].clear_time));

		// 書き込む処理
		fprintf(fp, "%s%s,%s,%s,%s,%s,\n", bases, stagenum, mission0char, mission1char, mission2char, cleartimechar);
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
			// 現在の文字列がカンマだけだった場合、削除して次の文字の検索へ。これをすることによって、(,1)とかの心配がなくなる
			if (strcmp(now_strings, ",") == 0)
			{
				strcpy(now_strings, "");
				continue;
			}

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

		// MapdataEnd を見つけた場合処理は終了とみなしてNULLを返す
		if (strstr(now_strings, "MapdataEnd") != NULL)
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

int LoadPlayerdata(FILE* fp)
{
	// stagedataに出力していくので、ポインターで持ってきておく
	STAGEDATA* p_Stagedata = GetStagedata();

	// 構造体を作って、そのポインタも用意しておく
	MAPCHIP_POS_STRUCT s_mapchip_pos{};
	MAPCHIP_POS_STRUCT* p_mapchip_pos = &s_mapchip_pos;

	// 構造体の初期化(-1)を入れる
	for (int num = 0; num < ORDER_MAX; num++)
	{
		s_mapchip_pos.mapchip_pos_x[num] = -1;
		s_mapchip_pos.mapchip_pos_y[num] = -1;
	}

	char loadchar[4] = "";
	char now_strings[256] = "";

	int order = 0;		// 動いていく順番	最大ORDER_MAX(5)
	int XorY = 0;		// 0:X,1:Y	今がXかYどっちの座標に値を入れようとしているか
	float movespeed = PLAYER_MOVE_SPEED;
	int decimal_point = 0;		// 小数点の位置が左から何番目にあるか
	bool decision_decima = false;		// 小数点の位置を決定したかどうか

	int pattern = PATTERN_PLAYER_NULL;			// 読み込んだ文字列から、今何を読み込んでいるかを判別するためのもの。

	int x = 0;
	int y = 0;

	// Setplayerでセットするのは、pの設定中に新しいpが読み込まれた時と、最期終了文字を見た時の2パターンある。

	while (1)
	{
		// ファイルを1文字ずつ読み込む	fscanfは返り値として読み込んだ数(%sとか%dの数)を返すが、今回は無視するので(void)をつける
		(void)fscanf(fp, "%1s", loadchar);

		int fasf = 5;
		// 文字を発見したらパターン変更と初期化
		if (pattern == PATTERN_PLAYER_NULL)
		{
			// NULLの状態でpを見つけた場合(最初の1回目)
			if (strcmp(now_strings, "pos") == 0)
			{
				order = 0;
				XorY = 0;
				movespeed = PLAYER_MOVE_SPEED;
				decimal_point = 0;
				decision_decima = false;
				pattern = PATTERN_PLAYER_POS;
				strcpy(now_strings, "");
				continue;
			}
		}
		else
		{
			// 設定中に新しいposを見つけた場合(PATTERN_PLAYER_POSの時にもっかい来た場合,もしくはPATTERN_PLAYER_MOVESPEED中)
			if (strcmp(now_strings, "pos") == 0)
			{
				//if (pattern == PATTERN_PLAYER_MOVESPEED)
				//	movespeed = SetMoveSpeed(decimal_point, now_strings);
				// SetPlayerでセットしてから初期化
				SetPlayerUseFile(s_mapchip_pos, movespeed);
				// 構造体の初期化(-1)を入れる
				for (int num = 0; num < ORDER_MAX; num++)
				{
					s_mapchip_pos.mapchip_pos_x[num] = -1;
					s_mapchip_pos.mapchip_pos_y[num] = -1;
				}


				order = 0;
				XorY = 0;
				decimal_point = 0;
				decision_decima = false;
				movespeed = PLAYER_MOVE_SPEED;
				pattern = PATTERN_PLAYER_POS;
				strcpy(now_strings, "");
				continue;
			}
		}
		if (strcmp(now_strings, "nex") == 0)
		{
			order++;
			XorY = 0;
			// pattern = PATTERN_PLAYER_NEXTPOS;
			strcpy(now_strings, "");
			continue;
		}
		if (strcmp(now_strings, "spe") == 0)
		{
			pattern = PATTERN_PLAYER_MOVESPEED;
			strcpy(now_strings, "");
			continue;
		}

		// カンマが来たら文字列を確定させて次の文字列へ		// strcmpは比較して等しいと0を返す。
		if (strcmp(loadchar, ",") == 0)
		{
			// 現在の文字列がカンマだけだった場合、削除して次の文字の検索へ。これをすることによって、(,1)とかの心配がなくなる
			if (strcmp(now_strings, ",") == 0)
			{
				strcpy(now_strings, "");
				continue;
			}

			// 確定した文字列を数字に変換しデータに反映させる処理
			if (pattern == PATTERN_PLAYER_POS)
			{
				// 構造体の中身をセット(SetPlayerで渡すためのデータの保存と更新)
				SetMAPCHIP_POS_STRUCT(p_mapchip_pos, now_strings, order, XorY);
				// now_stringsを初期化する
				strcpy(now_strings, "");

				// Xの設定が終わったら次はYの設定なので+1しておく
				XorY++;
				int sffd = 4;
			}
			// if (pattern == PATTERN_PLAYER_MOVESPEED) はここでは何もしないので書かない

		}
		else
		{
			// カンマじゃない場合文字をつなげる前に、PATTERN_PLAYER_MOVESPEEDの処理中の場合の処理を行う
			if (pattern == PATTERN_PLAYER_MOVESPEED)
			{
				if (strcmp(loadchar, ".") == 0)
				{
					// .の場合、.を無視して入力を続ける。.が左から何個目にあったかだけ保存しておく
					decision_decima = true;
					continue;

				}
				else if (strcmpNumber(loadchar) != 0)
				{
					// 数字じゃない文字だった場合の処理
					//if (pattern == PATTERN_PLAYER_MOVESPEED)
				//	movespeed = SetMoveSpeed(decimal_point, now_strings);
				// SetPlayerでセットしてから初期化
					SetPlayerUseFile(s_mapchip_pos, movespeed);
					// 構造体の初期化(-1)を入れる
					for (int num = 0; num < ORDER_MAX; num++)
					{
						s_mapchip_pos.mapchip_pos_x[num] = -1;
						s_mapchip_pos.mapchip_pos_y[num] = -1;
					}
					// now_stringsを初期化する
					strcpy(now_strings, "");
					pattern = PATTERN_PLAYER_NULL;
				}
				else if (decision_decima == false)
					decimal_point++;
			}


			// カンマでなければ文字を繋げていく。p,n,sの場合ここまでたどり着かないので大丈夫。もしくは"."の場合もここには来ない
			strcat(now_strings, loadchar);
		}

		// PlayerdataEND を見つけた場合処理は終了とみなしてNULLを返す
		if (strstr(now_strings, "PlayerdataEnd") != NULL)
		{
			// PlayerdataEnd まで読み込んでしまってる状態なので、文字数分カットしてあげる
			int len = strlen(now_strings);
			strncpy(now_strings, now_strings, len - 13);

			//if (pattern == PATTERN_PLAYER_MOVESPEED)
			//	movespeed = SetMoveSpeed(decimal_point, now_strings);
			// SetPlayerでセットしてから初期化
			SetPlayerUseFile(s_mapchip_pos, movespeed);
			// 構造体の初期化(-1)を入れる
			for (int num = 0; num < ORDER_MAX; num++)
			{
				s_mapchip_pos.mapchip_pos_x[num] = -1;
				s_mapchip_pos.mapchip_pos_y[num] = -1;
			}

			return PATTERN_NULL;
		}

		// 50文字以上の文字列になってしまったらエラーとみなし強制終了させる
		if (strlen(now_strings) > 50)
		{
			int aaaaa = 5;
			exit(5);
		}


	}



	return PATTERN_NULL;
}

// ミッションデータの読み込み
int LoadMissiondata(FILE* fp)
{
	// stagedataに出力していくので、ポインターで持ってきておく
	STAGEDATA* p_Stagedata = GetStagedata();

	char loadchar[4] = "";
	char now_strings[256] = "";
	char decision_strings[256] = "";

	int addednumtime = 0;	// 読み込んで追加した回数

	int pattern = PATTERN_NULL;

	while (pattern != PATTERN_END)
	{
		// ファイルを1文字ずつ読み込む	fscanfは返り値として読み込んだ数(%sとか%dの数)を返すが、今回は無視するので(void)をつける
		(void)fscanf(fp, "%1s", loadchar);

		// カンマが来たら文字列を確定させて次の文字列へ		// strcmpは比較して等しいと0を返す。
		if (strcmp(loadchar, ",") == 0)
		{
			// 現在の文字列がカンマだけだった場合、削除して次の文字の検索へ。これをすることによって、(,1)とかの心配がなくなる
			if (strcmp(now_strings, ",") == 0)
			{
				strcpy(now_strings, "");
				continue;
			}

			// 確定した文字列を数字に変換しミッションにに反映させる処理。内容なのか使う値なのかの判別も処理
			applyMissionArray(addednumtime, now_strings);

			// now_stringsを初期化する
			strcpy(now_strings, "");

			// 確定したので追加した回数を+1回する
			addednumtime++;

			// マップ配列分文字を読み終わったら終了とみなしてNULLを返す
			if (addednumtime == MAX_MISSION * 2)
			{
				return PATTERN_NULL;
			}

		}
		else
		{
			// カンマでなければ文字を繋げていく
			strcat(now_strings, loadchar);
		}

		// MapdataEnd を見つけた場合処理は終了とみなしてNULLを返す
		if (strstr(now_strings, "MissiondataEnd") != NULL)
		{
			// now_stringsを初期化する
			strcpy(now_strings, "");

			return PATTERN_NULL;
		}

		// 50文字以上の文字列になってしまったらエラーとみなし強制終了させる
		if (strlen(now_strings) > 50)
		{
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
	case 'f': return 0;
	default: 
		// 正しいマップの書き方になっていなくて十分な数(14)が読み込まれなかった場合やへんに文字が紛れ込んでいた場合
		exit(3);			// 強制終了。エラー3
		return 0;
	}
}

// char型の数字(1桁のみ)からfloat型の数字へ
float charTofloat(char *strings, int num)
{
	if (strcmp(&strings[0], "0") == 0)
		return 0.0f;
	if (strcmp(&strings[0], "1") == 0)
		return 1.0f;
	if (strcmp(&strings[0], "2") == 0)
		return 2.0f;
	if (strcmp(&strings[0], "3") == 0)
		return 3.0f;
	if (strcmp(&strings[0], "4") == 0)
		return 4.0f;
	if (strcmp(&strings[0], "5") == 0)
		return 5.0f;
	if (strcmp(&strings[0], "6") == 0)
		return 6.0f;
	if (strcmp(&strings[0], "7") == 0)
		return 7.0f;
	if (strcmp(&strings[0], "8") == 0)
		return 8.0f;
	if (strcmp(&strings[0], "9") == 0)
		return 9.0f;
	if (strcmp(&strings[0], "f") == 0)
		return 0.0f;

	return 0.0f;
}

// int型の数字(1桁のみ)からchar型の数字の文字へ
char intTochar(int num)
{
	switch (num)
	{
	case 0: return '0';
	case 1: return '1';
	case 2: return '2';
	case 3: return '3';
	case 4: return '4';
	case 5: return '5';
	case 6: return '6';
	case 7: return '7';
	case 8: return '8';
	case 9: return '9';
	}
	exit(6);
	return 'e';
}


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

float SetMoveSpeed(int decimal_point, char strings[])
{

	float speed = 0.0f;
	int below = 0;
	int len = strlen(strings);

	char* p_str = strings;

	// 小数点より上の計算
	for (int num = 0; num < decimal_point; num++)
	{
		float movespeeddata = charTofloat(p_str, num);
		speed = speed + (movespeeddata * (pow(10, decimal_point - num)));
	}
	// 小数点以下の計算
	for (int num = decimal_point; num < len; num++)
	{
		float movespeeddata = charTofloat(p_str, num);
		speed = speed + (movespeeddata * (pow(0.1, below + 1)));
		below++;
	}

	return speed;
}

void SetMAPCHIP_POS_STRUCT(MAPCHIP_POS_STRUCT * s_mapchip_pos, char strings[] , int order, int XorY)
{
	// 文字列が何文字か調べ、文字数に応じて数字に変換したときの桁数を変える
	int len = strlen(strings);
	if (len == 1)
	{
		int mapchip_pos = charToint(strings[0]);

		if(XorY == 0)
			s_mapchip_pos->mapchip_pos_x[order] = mapchip_pos;
		else
			s_mapchip_pos->mapchip_pos_y[order] = mapchip_pos;
	}
	if (len == 2)
	{
		int mapchip_pos = 10 * charToint(strings[0]) + charToint(strings[1]);

		if (XorY == 0)
			s_mapchip_pos->mapchip_pos_x[order] = mapchip_pos;
		else
			s_mapchip_pos->mapchip_pos_y[order] = mapchip_pos;
	}
	if (len == 3)
	{
		int mapchip_pos = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);

		if (XorY == 0)
			s_mapchip_pos->mapchip_pos_x[order] = mapchip_pos;
		else
			s_mapchip_pos->mapchip_pos_y[order] = mapchip_pos;
	}

	return;
}

// nowstringsからミッションに追加する処理
void applyMissionArray(int addednumtime, char strings[])
{
	// addednumtimeから何番目のミッションに追加するかを調べておく
	int missionnum = addednumtime / 2;		// 2で割るので、0,1=0 2,3=1 4,5 = 2 となる


	// stagedataに出力していくので、ポインターで持ってきておく
	STAGEDATA* p_Stagedata = GetStagedata();

	// 文字列が何文字か調べ、文字数に応じて数字に変換したときの桁数を変える
	int len = strlen(strings);
	if (len == 1)
	{
		int data = charToint(strings[0]);
		if (addednumtime % 2 == 0)
			p_Stagedata->mission_ContentsNum[missionnum] = data;
		else
			p_Stagedata->mission_JudgeNum[missionnum] = data;
	}
	if (len == 2)
	{
		int data = 10 * charToint(strings[0]) + charToint(strings[1]);
		if (addednumtime % 2 == 0)
			p_Stagedata->mission_ContentsNum[missionnum] = data;
		else
			p_Stagedata->mission_JudgeNum[missionnum] = data;
	}
	if (len == 3)
	{
		int data = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);
		if (addednumtime % 2 == 0)
			p_Stagedata->mission_ContentsNum[missionnum] = data;
		else
			p_Stagedata->mission_JudgeNum[missionnum] = data;
	}
	return;
}

// もらった文字列(1,2,3桁の整数型の数字のみ対応)をint型にして返す
int StringsToInt(char strings[])
{
	int back_num = 0;

	// 文字列が何文字か調べ、文字数に応じて数字に変換したときの桁数を変える
	int len = strlen(strings);
	if (len == 1)
	{
		int data = charToint(strings[0]);
		back_num = data;
	}
	if (len == 2)
	{
		int data = 10 * charToint(strings[0]) + charToint(strings[1]);
		back_num = data;
	}
	if (len == 3)
	{
		int data = 100 * charToint(strings[0]) + 10 * charToint(strings[1]) + charToint(strings[2]);
		back_num = data;
	}

	return back_num;
}


// もらったint型(正の数3桁まで)を文字列(1,2,3桁の整数型の数字のみ対応)にして返す
char* intTostrings(int num)
{
	int number = num;
	int digit = 0;

	int digitnum[3] = { 0,0,0 };

	// もらった数字が何桁かの計算
	while (number != 0)
	{
		number = number / 10;
		digit++;
	}
	// 0単体の場合上のワイル分だと桁数0になるので、あとでdigitを1にしてあげる
	if (num == 0)
		digit = 1;

	// 返す文字列
	char data[4] = "";
	char back_strings[20] = "";


	// 文字列が何文字か調べ、文字数に応じて数字に変換したときの桁数を変える
	if (digit == 1)
	{
		digitnum[0] = num;
		data[0] = intTochar(digitnum[0]);

		strcat(back_strings, data);
		strcpy(data, "");
	}
	if (digit == 2)
	{
		digitnum[0] = num / 10;
		digitnum[1] = num - digitnum[0] * 10;

		data[0] = intTochar(digitnum[0]);
		strcat(back_strings, data);
		strcpy(data, "");
		data[0] = intTochar(digitnum[1]);
		strcat(back_strings, data);
		strcpy(data, "");
	}
	if (digit == 3)
	{
		digitnum[0] = num / 100;
		digitnum[1] = (num - digitnum[0] * 100) / 10;
		digitnum[2] = num - digitnum[0] * 100 - digitnum[1] * 10;

		data[0] = intTochar(digitnum[0]);
		strcat(back_strings, data);
		strcpy(data, "");
		data[0] = intTochar(digitnum[1]);
		strcat(back_strings, data);
		strcpy(data, "");
		data[0] = intTochar(digitnum[2]);
		strcat(back_strings, data);
		strcpy(data, "");
	}

	int dad = 0;
	return back_strings;
}

// 読み込んだ１文字が数字であるかどうか.数字であれば0を返すそれ以外は-1を返す
int strcmpNumber(char* strings)
{
	if (strcmp(&strings[0], "0") == 0)
		return 0;
	if (strcmp(&strings[0], "1") == 0)
		return 0;
	if (strcmp(&strings[0], "2") == 0)
		return 0;
	if (strcmp(&strings[0], "3") == 0)
		return 0;
	if (strcmp(&strings[0], "4") == 0)
		return 0;
	if (strcmp(&strings[0], "5") == 0)
		return 0;
	if (strcmp(&strings[0], "6") == 0)
		return 0;
	if (strcmp(&strings[0], "7") == 0)
		return 0;
	if (strcmp(&strings[0], "8") == 0)
		return 0;
	if (strcmp(&strings[0], "9") == 0)
		return 0;

	return -1;
}




