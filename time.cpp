//==============================================================================================================
//
//		時間.cpp
//
//==============================================================================================================

#include "main.h"

static int g_nTimer = 0;
static int g_nCount = 0;		//60Countしたら0に戻す

void InitTime(void)
{
	g_nTimer = 0;
}
void UninitTime(void)
{
	g_nTimer = 0;
}
void UpdateTime(void)
{
	g_nCount++;
	//1秒計測
	if (g_nCount >= 60)
	{
		g_nTimer++;	
		g_nCount = 0;
	}
}
void DrawTime(float x, float y)
{
	int Time = g_nTimer;
	for (int i = 0; i < 7; i++)
	{
		//score == 1234567 --> 123456・・・7
		int n = Time % 10;
		Time /= 10;		//--> 1234567 -> 123456

		DrawNumber(n, x - NUMBER_WIDTH * i, y,D3DCOLOR_RGBA(255,255,100,255));
		if (Time == 0)
		{
			break;
		}
	}
}
int ReturnTime(void)
{
	return g_nTimer;
}