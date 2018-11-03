//==============================================================================================================
//
//		Number.cpp
//
//==============================================================================================================

#include "main.h"

//============================================================================
//
//		Number描画
//			n  -> 0〜9までの表示する数字	x,y -> 表示座標	
//
//============================================================================
void DrawNumber(int n, float x, float y, D3DCOLOR color)
{
	if (n <= 9 && n >= 0)
	{
		DrawPolygon(n, color, x, y, NUMBER_WIDTH, NUMBER_HEIGHT, 0, 0, 29, 31);
	}
}