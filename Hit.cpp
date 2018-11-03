//==============================================================================================================
//
//		Hit.cpp			当たり判定
//
//==============================================================================================================

#include "main.h"


bool Hit(float ax, float ay, float ar, float bx, float by, float br)
{
	//ax - ax
	//ay - ay
	float x = bx - ax;
	float y = by - ay;

	float l = x * x + y * y;			//円と円の中心座標を結んだ距離　ルートはおもいため　半径のほうで２乗する

	return l < (ar + br) * (ar + br);	//当たっているときreturn
}