//==============================================================================================================
//
//		Danger.cpp			ŠëŒ¯—\‘ª
//
//==============================================================================================================

#include "main.h"

static float Speed = 0.0f;
static bool bSpeed = false;
static int SpeedCount = 0;

void InitDanger(void)
{
	for (int i = 0; i < DANGER_NUM; i++)
	{
		danger[i].bUse = false;
		danger[i].g_vPos.x = 0.0f;
		danger[i].g_vPos.y = 0.0f;
		danger[i].time = 0;
	}
}
void UninitDanger(void)
{
	for (int i = 0; i < DANGER_NUM; i++)
	{
		danger[i].bUse = false;
		danger[i].g_vPos.x = 0.0f;
		danger[i].g_vPos.y = 0.0f;
		danger[i].time = 0;
	}
}
void UpdateDanger(void)
{
	if (!bSpeed && ReturnSpeed() > SPEEDDOWN_SPEED)
	{
		bSpeed = true;
	}
	else if (ReturnSpeed() <= SPEEDDOWN_SPEED)
	{
		bSpeed = false;
		SpeedCount = 0;
		Speed = 0.0f;
	}
	if (bSpeed)
	{
		Speed += 1.0f;
		SpeedCount++;
	}
	if (SpeedCount > SPEEDDOWN_DRAWTIME)
	{
		bSpeed = false;
		SpeedCount = 0;
		Speed = 0.0f;
	}

	for (int i = 0; i < DANGER_NUM; i++)
	{
		if (danger[i].bUse)
		{
			danger[i].time++;
		}
		if (danger[i].time > DANGER_TIME)
		{
			danger[i].bUse = false;
			danger[i].time = 0;
		}

	}
}
void DrawDanger(void)
{
	for (int i = 0; i < DANGER_NUM; i++)
	{
		if (danger[i].bUse)
		{
			DrawPolygon(TEXTURE_DANGER,D3DCOLOR_RGBA(255,255,255,255),danger[i].g_vPos.x,danger[i].g_vPos.y,DANGER_WIDTH,DANGER_HEIGHT,
						0,0,g_aTextureFileNames[TEXTURE_DANGER].width, g_aTextureFileNames[TEXTURE_DANGER].height);
		}
	}
	float speed = ReturnSpeed();
	if (bSpeed)
	{
		DrawPolygon(TEXTURE_SPEEDDOWN, D3DCOLOR_RGBA(255, 255, 255, 255), SCREEN_WIDTH - Speed,(SCREEN_HEIGHT / 2) - SPEEDDOWN_HEIGHT,SPEEDDOWN_WIDTH,SPEEDDOWN_HEIGHT,0,0, 400, 300);
	}
}
void CreateDanger(int a,int index)
{
	if (a == 0)
	{
		danger[index].g_vPos.x = 70.0f;
		danger[index].g_vPos.y = (float)DANGER_HEIGHT - 10;
		danger[index].bUse = true;
	}
	else if (a == 1)
	{
		danger[index].g_vPos.x = 270.0f;
		danger[index].g_vPos.y = (float)DANGER_HEIGHT - 10;
		danger[index].bUse = true;
	}
	else if (a == 2)
	{
		danger[index].g_vPos.x = 470.0f;
		danger[index].g_vPos.y = (float)DANGER_HEIGHT - 10;
		danger[index].bUse = true;
	}
	else if (a == 3)
	{
		danger[index].g_vPos.x = 670.0f;
		danger[index].g_vPos.y = (float)DANGER_HEIGHT - 10;
		danger[index].bUse = true;
	}
}