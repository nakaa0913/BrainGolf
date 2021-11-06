///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////自作のプリミティブ達.cpp	便利な自作関数書いてるよ
////2021/10/28	柴田漱士
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <stdio.h>
#include <math.h>
#include "primitive.h"




// 2点間の距離を求めてfloat型で返す関数
float CalculationDistance(float point1pos1, float point1pos2, float point2pos1, float point2pos2)
{

	float a = point1pos1 - point2pos1;
	float b = point1pos2 - point2pos2;
	float c = sqrt(a * a + b * b);

	return c;
}
// 2点間の距離を求める    どっちでもいいが上使ってる。
//float CalculationDistance(float obj1pos1, float obj1pos2, float obj2pos1, float obj2pos2)
//{
//	float distance = sqrt(pow(obj1pos1 - obj2pos1, 2) +
//						  pow(obj1pos2 - obj2pos2, 2));
//	return distance;
//}


// 1つの点と1つの円の当たり判定。点と円の原点の距離<=円の半径なら当たっている。
bool OnCollisionPointAndCircle(Float2 point, Circle2D circle)
{
	float a = point.x - circle.x;
	float b = point.y - circle.y;
	float c = sqrt(a * a + b * b);

	if (c <= circle.r)
	{
		return true;
	}
	return false;
}

// peaceがallのどれだけの割合か返す。基本peaceの方が小さいので0~0.999が返る。1で同じ大きさ。magnificationは計算結果をその分倍にすることができる。誤差の計算途中で10000倍とかしてたら使。使わない場合は1
float CalculationRatio(float peace, float all, int magnification)
{
	float ratio;

	if (magnification != 1)
		ratio = magnification * peace / all;
	else
		ratio = peace / all;

	return ratio;
}

//// より正確な円の当たり判定を求める関数。円の原点の座標と当たっている点の座標から距離を計算して、10分割したmoveの中から最も近かった座標を返す
//Float2 MoreAccurateCircleCollision(float OriginX, float OriginY, float radius, float pointposX, float pointposY, Float2 onemove, int divnum)
//{
//	Float2 BestPos = { OriginX, OriginY };
//
//	// moveをdivnum個に分けて考える。多いほど正確だが処理は重くなるから多くても10くらいがおすすめ
//	for (int i = 0; i < divnum; i++)
//	{
//		BestPos.x = BestPos.x + onemove.x;
//		BestPos.y = BestPos.y + onemove.y;
//
//		float distance = CalculationDistance(BestPos.x, BestPos.y, pointposX, pointposY);
//		if (distance >= radius)
//			return BestPos;
//	}
//
//	Float2 BudPos = { -1.0f, -1.0f };
//
//	return BudPos;
//}

// より正確な円の当たり判定を求める関数。円の原点の座標と当たっている点の座標から距離を計算して、10分割したmoveの中から最も近かった座標を返す
Float2 MoreAccurateCircleCollision(float OriginX, float OriginY, float radius, float pointposX, float pointposY, Float2 onemove, int divnum)
{
	// 上の関数の二分岐検索バージョン！処理の速さがこっちのが早い。100個とかで分割してもそんなに重くない！

	Float2 BestPos = { OriginX, OriginY };

	int min = 0;
	int max = divnum;
	int middle;

	while (min <= max) 
	{
		middle = (min + max) / 2;

		if (CalculationDistance(OriginX + onemove.x * middle, OriginY + onemove.y * middle, pointposX, pointposY) >= radius)
		{
			if (CalculationDistance(OriginX + onemove.x * (middle - 1), OriginY + onemove.y * (middle - 1), pointposX, pointposY) < radius)
			{
				BestPos.x = BestPos.x + onemove.x * middle;
				BestPos.y = BestPos.y + onemove.y * middle;
				return BestPos;
			}
			else
			{
				max = middle - 1;
			}
		}
		else
		{
			min = middle + 1;
		}
	}

	Float2 BudPos = { -1.0f, -1.0f };

	return BudPos;
}

// 真ん中ではなく、左端、上端の座標を引数で呼ぶ。
bool CheckHit2DBoxBox(Float2 pos1, Float2 size1, Float2 pos2, Float2 size2)
{
	float L1 = pos1.x;      // 左
	float R1 = pos1.x + size1.x; // 右(左+横幅)
	float L2 = pos2.x;      // 左
	float R2 = pos2.x + size2.x; // 右(左+横幅)

	if (R1 < L2) return false; //< 線上も当たってることにする
	if (R2 < L1) return false; //< 線上も当たってることにする

	float U1 = pos1.y;			 // 上
	float D1 = pos1.y + size1.y; // 下(上+縦幅)
	float U2 = pos2.y;			// 上
	float D2 = pos2.y + size2.y; // 下(上+縦幅)

	if (D1 < U2) return false; //< 線上も当たってることにする
	if (D2 < U1) return false; //< 線上も当たってることにする

	// それ以外の場合は当たっている
	return true;
}

double DegreeToRadian(double degree)
{
	// 角度が360度以上の場合、0~360度になるように調整
	if (degree >= 360)
	{
		while (degree >= 360)
		{
			degree -= 360.0;
		}
	}
	// 角度が0度未満の場合、0~360度になるように調整
	if (degree < 0)
	{
		while (degree < 0)
		{
			degree += 360.0;
		}
	}

	// 角度 * 3.14 / 180.0 で角度からラジアンに変換できる
	return  degree * PI / 180.0;
}

double RadianToDegree(double radian)
{
	// atan2の場合。0度のスタート位置から反時計回りに0~3.14~-3.14~0となる。
	// まずラジアンがマイナスだった場合の調整
	if (radian < 0)
		radian += PI * 2;

	// ラジアン * 180.0 / 3.14 でラジアンから角度に変換できる
	return  radian * 180.0 / PI;
}

// 入力した角度の真逆の角度を返す(270度だったら90度)
double ReverseDegree(double degree)
{

	double new_degree = degree + 180.0;


	// 角度が360度以上の場合、0~360度になるように調整
	if (new_degree >= 360)
	{
		while (new_degree >= 360)
		{
			new_degree -= 360.0;
		}
	}
	// 角度が0度未満の場合、0~360度になるように調整
	if (new_degree < 0)
	{
		while (new_degree < 0)
		{
			new_degree += 360.0;
		}
	}

	return  new_degree;
}

// 2つの点から①の点から②を見た時のラジアンを計算する
double CalculateRadianFrom2Points(double point1x, double point1y, double point2x, double point2y)
{
	double distance_x = point2x - point1x;
	double distance_y = point2y - point1y;

	double radian = atan2(distance_y, distance_x);

	if (radian < 0)
		radian += PI * 2;

	int asdasd = 5;

	return radian;
}

// ラジアンをYだけ反転させる(X軸で反転)
double InversionYRadian(double radian)
{
	double newradian = -radian;

	if (newradian < 0)
		newradian += PI * 2;

	int asdads = 5;

	return newradian;
}