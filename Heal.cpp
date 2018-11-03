//==============================================================================================================
//
//		ヒールcpp
//
//==============================================================================================================

#include "main.h"

static bool g_bHeal = false;
static D3DXVECTOR2 g_vPos(0.0f, 0.0f);		//staticがついていればほかのファイルにあっても使える
static int g_nAnimPattern = 0;
static int g_nAnimCount = 0;

static TEXPATTERN tex;

void InitHeal(void)
{
	g_vPos.x = 0.0f;
	g_vPos.y = 0.0f;
	g_bHeal = false;
	g_nAnimPattern = 0;
	g_nAnimCount = 0;
}
void UninitHeal(void)
{
	g_vPos.x = 0.0f;
	g_vPos.y = 0.0f;
	g_bHeal = false;
	g_nAnimPattern = 0;
	g_nAnimCount = 0;
}
void UpdateHeal(void)
{
	if (tex.patternNum >= HEAL_PATTERN - 1)
	{
		tex.patternNum = 0;
		g_nAnimCount = 0;
		g_bHeal = false;
	}

	if (g_bHeal)
	{
		g_nAnimCount++;
		g_vPos = GetPosPlayer();
		tex = PatternPolygon(g_nAnimCount, HEAL_SPEED, HEAL_WNUM, HEAL_HNUM, 192, 192);
	}
}
void DrawHeal(void)
{
	if (g_bHeal)
	{
		DrawPolygon(TEXTURE_EFFECT_H, D3DCOLOR_RGBA(255, 255, 255, 255), g_vPos.x, g_vPos.y, HEAL_WIDTH, HEAL_HEIGHT, tex.tcx, tex.tcy, 192, 192);
	}
}
void CreateHeal(float x, float y)
{
	g_vPos.x = x;
	g_vPos.y = y;
	g_bHeal = true;
}