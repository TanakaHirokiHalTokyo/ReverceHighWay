//===================================================================================================
//		リザルト.cpp
//																	
//===================================================================================================

#include "main.h"

static int Time = 0;
static bool Clear = false;
static int Score = 0;		//Score は表示するときに割ったりするので変動してしまう
static int g_Score = 0;		//Score の元の値を保存　不変的変数
static int fade = 255;
static int SafeTime = SAFE_TIME;
static int SafeMode = false;

void InitResult(void)
{
	fade = 255;
	SafeTime = SAFE_TIME;
	SafeMode = false;
	//BGM 再生
	PlaySound(SOUND_RESULTBGM);
}
void UninitResult(void)
{
	fade = 255;
	g_Score = 0;
	Score = 0;

	StopSound();
}
void UpdateResult(void)
{
	if (!SafeMode)
	{
		if (fade > 1)
		{
			fade -= 2;
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			PlaySound(SOUND_OK);
			SafeMode = true;
			
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
			ChangeScene(SCENE_RANKING);
		}
	}
	//ゲームクリア時のスコアに
	Score = g_Score;
	

	
}
void DrawResult(void)
{
	//-------------Result 背景表示--------------------------------------------
	DrawPolygon(TEXTURE_RESULT, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 800, 600);
	//-------------------------------------------------------------------------
	//-------------Result 文字表示---------------------------------------------
	DrawPolygon(TEXTURE_RESULTWORD, D3DCOLOR_RGBA(255, 255, 255, 255), 100.0f, 30.0f, 400.0f, 250.0f, 0, 0, 800, 600);
	//-------------------------------------------------------------------------

	//------------クリア　しているなら-----------------------------------------
	if (Clear == true)
	{
		DrawPolygon(TEXTURE_RESULTTIME, D3DCOLOR_RGBA(255, 255, 255, 255), 20.0f, 300.0f, 400.0f, 250.0f, 0, 0, 800, 600);

		for (int i = 0; i < 7; i++)
		{
			//score == 1234567 --> 123456・・・7
			int n = Score % 10;
			Score /= 10;		//--> 1234567 -> 123456

			if (n <= 9 && n >= 0)
			{
				DrawPolygon(n, D3DCOLOR_RGBA(231, 255, 122, 255), 600.0f - (30.0f * i), 390.0f, 30.0f, 80.0f, 0, 0, 29, 31);
			}
			if (Score == 0)
			{
				break;
			}
		}
	}
	//----------------------------------------------------------------------------
	//--------------クリア　していない　げーむおーばー----------------------------
	else
	{
		DrawPolygon(TEXTURE_DIED, D3DCOLOR_RGBA(255, 0, 0, 255), 20.0f, 300.0f, 400.0f, 250.0f, 0, 0, 800, 600);
	}
	//----------------------------------------------------------------------------

	DrawPEnter();
	//---------------Fade 表示-------------------------------------------------------------------
	DrawPolygon(TEXTURE_FADE, D3DCOLOR_RGBA(0, 0, 0, fade), 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 800, 600);
	//-------------------------------------------------------------------------------------------
}
void TimeResult(int score)
{
	Score = score;
	g_Score = Score;
}
void ClearResult(bool clear)
{
	Clear = clear;
}