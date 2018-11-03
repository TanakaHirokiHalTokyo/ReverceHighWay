//=============================================================================================================================
//
//		BACKGROUND.cpp
//
//=============================================================================================================================

#include "main.h"

static float g_speed;

void InitBackground(void)
{

}
void UninitBackground(void)
{

}
void UpdateBackground(float speed)
{
	g_speed += SPEED_DEF + speed;
	if (g_speed >= 1200.0f)
	{
		g_speed = 0.0f;
	}
}
void DrawBackground(void)
{
	DrawPolygon(TEXTURE_DOURO2, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f + g_speed, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
	DrawPolygon(TEXTURE_DOURO1, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, -600.0f + g_speed, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
	DrawPolygon(TEXTURE_DOURO2, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, -1200.0f + g_speed, BACKGROUND_WIDTH, BACKGROUND_HEIGHT, 0, 0, BACKGROUND_WIDTH, BACKGROUND_HEIGHT);
}