//===================================================================================================
//
//		PressEnter.cpp
//
//===================================================================================================
#include "main.h"

static bool DrawEnter = true; //Enter•`‰æ‰Šúó‘Ô@true •\¦’†
static int DrawTimeEnter = ENTER_DRAWTIME;

void InitPEnter(void)
{
	DrawEnter = true;
	DrawTimeEnter = ENTER_DRAWTIME;
}
void UninitPEnter(void)
{
	DrawEnter = true;
	DrawTimeEnter = ENTER_DRAWTIME;
}
void UpdatePEnter(void)
{
	DrawTimeEnter--;
	
	if (DrawTimeEnter <= 0)
	{
		if (DrawEnter)
		{
			DrawEnter = false;
		}
		else
		{
			DrawEnter = true;
		}
		DrawTimeEnter = ENTER_DRAWTIME;
	}
}
void DrawPEnter(void)
{
	if (DrawEnter)
	{
		DrawPolygon(TEXTURE_P_ENTER,D3DCOLOR_RGBA(255,255,255,2550), (float)(SCREEN_WIDTH - ENTER_WIDTH) / 2,(float)SCREEN_HEIGHT - ENTER_HEIGHT + 10.0f,(float)ENTER_WIDTH,(float)ENTER_HEIGHT,0,0,400,300);
	}
}