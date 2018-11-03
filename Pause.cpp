//===================================================================================================
//
//		Pause.cpp
//
//===================================================================================================

#include "main.h"


void InitPause(void)
{
	g_bPause = false;
	g_nPauseMode = PAUSE_RESUME;
}
void UninitPause(void)
{
	g_bPause = false;
	g_nPauseMode = PAUSE_RESUME;
}
void UpdatePause(void)
{
	if (!g_bPause)
	{

		if (GetKeyboardTrigger(DIK_P))
		{
			g_bPause = true;
		}
	}
	else
	{
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			switch (g_nPauseMode)
			{
			case PAUSE_TITLE: ChangeScene(SCENE_TITLE); break;
			case PAUSE_RESUME: g_bPause = false; break;
			default:
				break;
			}
		}

		if (GetKeyboardTrigger(DIK_A))
		{
			if (g_nPauseMode > PAUSE_RESUME)
			{
				g_nPauseMode--;
			}
		}
		if (GetKeyboardTrigger(DIK_D))
		{
			if (g_nPauseMode < PAUSE_TITLE)
			{
				g_nPauseMode++;
			}
		}
		if (GetKeyboardTrigger(DIK_P))
		{
			g_bPause = false;
		}
	}
	
}
void DrawPause(void)
{

	if (g_bPause)
	{
		//Pause ”wŒiF
		DrawPolygon(TEXTURE_FADE, D3DCOLOR_RGBA(0, 0, 0, FADE_PAUSE), 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 800.0f, 600.0f);
		
		//Pause‰æ–Ê•\Ž¦
		DrawPolygon(TEXTURE_FADE,D3DCOLOR_RGBA(0,0,0,150),(float)(SCREEN_WIDTH - PAUSEMENU_WIDTH) / 2,(float)(SCREEN_HEIGHT - PAUSEMENU_HEIGHT) / 2,(float)PAUSEMENU_WIDTH, (float)PAUSEMENU_HEIGHT,0,0,800,600);
		
		//Pause‰æ–Ê@•¶Žš•\Ž¦
		DrawPolygon(TEXTURE_PAUSE, D3DCOLOR_RGBA(255, 255, 255, 255), (float)(SCREEN_WIDTH - PAUSE_WIDTH) / 2.0f, (float)(SCREEN_HEIGHT - PAUSE_HEIGHT) / 2.0f, (float)PAUSE_WIDTH, (float)PAUSE_HEIGHT, 0, 0, 800, 600);

		switch (g_nPauseMode)
		{
		case PAUSE_RESUME:DrawPolygon(TEXTURE_PAUSE_RESUME, D3DCOLOR_RGBA(0, 255, 255, 255), (float)(SCREEN_WIDTH / 4) - (PAUSEFONT_WIDTH / 2) + 33, (float)SCREEN_HEIGHT - PAUSEFONT_HEIGHT / 2 - 63.0f, (float)PAUSEFONT_WIDTH, (float)PAUSEFONT_HEIGHT / 2, 0, 0, 200, 100); break;
		case PAUSE_TITLE: DrawPolygon(TEXTURE_PAUSE_TITLE, D3DCOLOR_RGBA(0, 255, 255, 255), (float)(SCREEN_WIDTH)-(PAUSEFONT_WIDTH * 1.5f)- 33,(float)SCREEN_HEIGHT - PAUSEFONT_HEIGHT / 2 - 63.0f, (float)PAUSEFONT_WIDTH, (float)PAUSEFONT_HEIGHT / 2, 0, 0, 200, 100); break;
		default:
			break;
		}

		DrawPolygon(TEXTURE_PAUSE_RESUME, D3DCOLOR_RGBA(255, 255, 255, 255), (float)(SCREEN_WIDTH / 4) - (PAUSEFONT_WIDTH / 2) + 30, (float)SCREEN_HEIGHT - PAUSEFONT_HEIGHT / 2 - 60.0f, (float)PAUSEFONT_WIDTH, (float)PAUSEFONT_HEIGHT / 2, 0, 0, 200, 100);
		DrawPolygon(TEXTURE_PAUSE_TITLE, D3DCOLOR_RGBA(255, 255, 255, 255), (float)(SCREEN_WIDTH ) - (PAUSEFONT_WIDTH * 1.5f) - 30, (float)SCREEN_HEIGHT - PAUSEFONT_HEIGHT / 2 - 60.0f, (float)PAUSEFONT_WIDTH, (float)PAUSEFONT_HEIGHT / 2, 0, 0, 200, 100);
		
	}
}
bool ReturnPause(void)
{
	return g_bPause;
}
