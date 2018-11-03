//==============================================================================================================
//
//		Explosion.cpp			爆発
//
//==============================================================================================================

#include "main.h"


static bool g_bExplosion = false;
static D3DXVECTOR2 g_vPos(0.0f, 0.0f);		//staticがついていればほかのファイルにあっても使える
static int g_nAnimPattern = 0;
static int g_nAnimCount = 0;

static TEXPATTERN tex;
void InitExplosion(void)
{
	g_vPos.x = 0.0f;
	g_vPos.y = 0.0f;
	g_bExplosion = false;
	g_nAnimPattern = 0;
	g_nAnimCount = 0;
}
void UninitExplosion(void)
{
	g_vPos.x = 0.0f;
	g_vPos.y = 0.0f;
	g_bExplosion = false;
	g_nAnimPattern = 0;
	g_nAnimCount = 0;
}
void UpdateExplosion(void)
{
	if (tex.patternNum >= EXPLOSION_PATTERN - 1)
	{
		tex.patternNum = 0;
		g_nAnimCount = 0;
		g_bExplosion = false;
	}

	if (g_bExplosion)
	{
		g_nAnimCount++;
		tex = PatternPolygon(g_nAnimCount, EXPLOSION_SPEED, EXPLOSION_PATTERN, 1, 240, 240);
	}

}
void DrawExplosion(void)
{
	if (g_bExplosion)
	{
		DrawPolygon(TEXTURE_EXPLOSION, D3DCOLOR_RGBA(255, 255, 255, 255), g_vPos.x, g_vPos.y, EXPLOSION_WIDTH, EXPLOSION_HEIGHT, tex.tcx, tex.tcy, 240, 240);

	}
}
void CreateExplosion(float x, float y)
{
	g_vPos.x = x;
	g_vPos.y = y;
	g_bExplosion = true;
}