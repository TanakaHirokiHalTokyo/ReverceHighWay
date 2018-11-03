//===================================================================================================
//		タイトル.cpp
//																	
//===================================================================================================

#include "main.h"

static float speed = 0.0f;
static float pitch = 0.0f;
static bool pitchV = false;
static float speed_rev = 0.0f;
static int fade = 255;
static int g_nTitleMode = 0;
static int SafeTime = SAFE_TIME;
static int SafeMode = false;

void InitTitle(void)
{
	speed = 0.0f;
	speed_rev = 0.0f;
	pitch = 0.0f;
	pitchV = false;
	fade = 255;
	g_nTitleMode = TITLE_PLAY;
	SafeTime = SAFE_TIME;
	SafeMode = false;

	//BGM再生
	PlaySound(SOUND_TITLEBGM);
}
void UninitTitle(void)
{
	speed = 0.0f;
	speed_rev = 0.0f;
	pitch = 0.0f;
	pitchV = false;
	fade = 255;
	g_nTitleMode = TITLE_PLAY;
	SafeTime = SAFE_TIME;
	SafeMode = false;

	StopSound();
}
void UpdateTitle(void)
{
	if (!SafeMode)
	{
		if (fade > 1)
		{
			fade-= 2;
		}
		//----------------------------------------------
		if (GetKeyboardTrigger(DIK_W))
		{
			if (g_nTitleMode > TITLE_PLAY)
			{
				g_nTitleMode--;
				PlaySound(SOUND_SELECT);
			}
		}
		if (GetKeyboardTrigger(DIK_S))
		{
			if (g_nTitleMode < TITLE_END)
			{
				g_nTitleMode++;
				PlaySound(SOUND_SELECT);
			}
		}
		if (GetKeyboardTrigger(DIK_RETURN))
		{
			switch (g_nTitleMode)
			{
			case TITLE_PLAY:
				PlaySound(SOUND_OK);
				SafeMode = true;
				break;
			case TITLE_RANKING:
				PlaySound(SOUND_OK);
				SafeMode = true;
				break;
			case TITLE_END: PlaySound(SOUND_OK); EndLoop(); break;
			default:
				break;
			}
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
			if (g_nTitleMode == TITLE_PLAY)
			{
				ChangeScene(SCENE_EXPLAIN);
			}
			else if (g_nTitleMode == TITLE_RANKING)
			{
				ChangeScene(SCENE_RANKING);
			}
		}
	}

	//-------------空の移動処理---------------------
	speed += SKY_SPEED;

	if (speed >= SCREEN_WIDTH)
	{
		speed = 0.0f;
	}
	//----------------------------------------------

	//--------------車の揺れ更新--------------------
	if (pitchV == false)
	{//下方向の揺れ
		pitch += PITCH_SPEED;
		if (pitch >= 10.0f)
		{
			pitchV = true;
		}
	}
	else if (pitchV == true)
	{//上方向の揺れ
		pitch -= PITCH_SPEED;
		if (pitch <= 0.0f)
		{
			pitchV = false;
		}
	}

	//----------------------------------------------

	//--------------対向車の移動処理----------------

	speed_rev += REV_SPEED;
	if (speed_rev >= (float)SCREEN_WIDTH * 4)
	{
		speed_rev = 0.0f;
	}

	
}
void DrawTitle(void)
{
	//----------------空　表示-------------------------------------------------------------------
	DrawPolygon(TEXTURE_SKY2, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 800, 600);
	DrawPolygon(TEXTURE_SKY, D3DCOLOR_RGBA(255, 255, 255, 255),0.0f + speed,0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT,0,0,800,300);
	DrawPolygon(TEXTURE_SKYRE, D3DCOLOR_RGBA(255, 255, 255, 255), -800.0f + speed, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 800, 300);
	//-------------------------------------------------------------------------------------------

	//---------------対向車　表示----------------------------------------------------------------

	DrawPolygon(TEXTURE_TITLE_CAR_B, D3DCOLOR_RGBA(255, 255, 255, 255), (float)-300.0f + speed_rev, (float)SCREEN_HEIGHT - (TITLE_REVCAR_H + 30) + pitch, TITLE_REVCAR_W, TITLE_REVCAR_H, 0, 0, 402, 125);
	DrawPolygon(TEXTURE_TITLE_CAR_CY, D3DCOLOR_RGBA(255, 255, 255, 255), (float)-1500.0f + speed_rev, (float)SCREEN_HEIGHT - (TITLE_REVCAR_H + 30) + pitch, TITLE_REVCAR_W, TITLE_REVCAR_H, 0, 0, 402, 125);
	DrawPolygon(TEXTURE_TITLE_CAR_R, D3DCOLOR_RGBA(255, 255, 255, 255), (float)-2000.0f + speed_rev, (float)SCREEN_HEIGHT - (TITLE_REVCAR_H + 30) + pitch, TITLE_REVCAR_W, TITLE_REVCAR_H, 0, 0, 402, 125);
	//-------------------------------------------------------------------------------------------

	//---------------PLAYER　表示----------------------------------------------------------------

	DrawPolygon(TEXTURE_TITLE_PLAYER, D3DCOLOR_RGBA(255, 255, 255, 255), (float)SCREEN_WIDTH - (TITLE_PLAYER_W + 30), (float)SCREEN_HEIGHT - (TITLE_PLAYER_H + 30) + pitch, TITLE_PLAYER_W, TITLE_PLAYER_H, 0, 0, 282, 178);

	//-------------------------------------------------------------------------------------------

	DrawPolygon(TEXTURE_TITLE, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 50.0f, 800, 300, 0, 0, 600, 300);

	switch (g_nTitleMode)
	{
	case TITLE_PLAY:DrawPolygon(TEXTURE_PLAY, D3DCOLOR_RGBA(0, 0, 0, 255), 16.0f, (float)SCREEN_HEIGHT - TITLEPAUSE_HEIGHT * 2.0f + 23, (float)TITLEPAUSE_WIDTH, (float)TITLEPAUSE_HEIGHT, 0, 0, 800, 200); break;
	case TITLE_RANKING:DrawPolygon(TEXTURE_TITLE_RANKING, D3DCOLOR_RGBA(0, 0, 0, 255), 16.0f, (float)SCREEN_HEIGHT - TITLEPAUSE_HEIGHT * 1.5f + 23, (float)TITLEPAUSE_WIDTH, (float)TITLEPAUSE_HEIGHT, 0, 0, 800, 200); break;
	case TITLE_END: DrawPolygon(TEXTURE_END, D3DCOLOR_RGBA(0, 0, 0, 255), 9.0f, (float)SCREEN_HEIGHT - TITLEPAUSE_HEIGHT + 23, (float)TITLEPAUSE_WIDTH, (float)TITLEPAUSE_HEIGHT, 0, 0, 800, 200); break;
	default:
		break;
	}
	DrawPolygon(TEXTURE_PLAY, D3DCOLOR_RGBA(255, 0, 0, 255), 13.0f, (float)SCREEN_HEIGHT - TITLEPAUSE_HEIGHT * 2.0f + 20, (float)TITLEPAUSE_WIDTH, (float)TITLEPAUSE_HEIGHT, 0, 0, 800, 200);
	DrawPolygon(TEXTURE_TITLE_RANKING, D3DCOLOR_RGBA(255, 0, 0, 255), 13.0f, (float)SCREEN_HEIGHT - TITLEPAUSE_HEIGHT * 1.5f + 20, (float)TITLEPAUSE_WIDTH, (float)TITLEPAUSE_HEIGHT, 0, 0, 800, 200);
	DrawPolygon(TEXTURE_END, D3DCOLOR_RGBA(255, 0, 0, 255), 5.0f, (float)SCREEN_HEIGHT - TITLEPAUSE_HEIGHT + 20, (float)TITLEPAUSE_WIDTH, (float)TITLEPAUSE_HEIGHT, 0, 0, 800, 200);

	DrawPEnter();
	//---------------Fade 表示-------------------------------------------------------------------
	DrawPolygon(TEXTURE_FADE, D3DCOLOR_RGBA(0, 0, 0, fade), 0.0f, 0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0, 0, 800, 600);
	//-------------------------------------------------------------------------------------------

}