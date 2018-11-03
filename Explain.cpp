
#include "main.h"

static int ExplainPage = EX_PAGE_1;
static int SafeTime = SAFE_TIME;
static bool SafeMode = false;
static int fade = 255;

void InitExplain(void)
{
	ExplainPage = EX_PAGE_1;
	SafeTime = SAFE_TIME;
	SafeMode = false;
	fade = 255;

}
void UninitExplain(void)
{
	ExplainPage = EX_PAGE_1;
	SafeTime = SAFE_TIME;
	SafeMode = false;
	fade = 255;

}
void UpdateExplain(void)
{
	if (!SafeMode)
	{
		if (fade > 1)
		{
			fade -= 2;
		}

		switch (ExplainPage)
		{
		case EX_PAGE_1: if (GetKeyboardTrigger(DIK_RETURN)) { PlaySound(SOUND_OK); ExplainPage = EX_PAGE_2; } break;
		case EX_PAGE_2: if (GetKeyboardTrigger(DIK_RETURN)) { PlaySound(SOUND_OK); SafeMode = true; }		break;
		default:
			break;
		}
	}
	else if (SafeMode)
	{
		if (fade < 254)
		{
			fade += 2;
		}

		SafeTime--;
		if (SafeTime <= 0)
		{
			ChangeScene(SCENE_STARTGAME);
		}
	}
	
}
void DrawExplain(void)
{
	if (ExplainPage == EX_PAGE_1)
	{
		DrawPolygon(TEXTURE_EXPLAIN1, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 800, 600);
	}
	else
	{
		DrawPolygon(TEXTURE_EXPLAIN2, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 800, 600);
	}
	DrawPEnter();

	DrawPolygon(TEXTURE_FADE, D3DCOLOR_RGBA(0, 0, 0, fade), 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 800, 600);

}