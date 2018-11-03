//===================================================================================================
//		�i�s�x.cpp
//																	
//===================================================================================================

#include "main.h"
#include "ranking.h"

static float progress = 0.0f;		//�Q�[���̐i�s�x
static float rate = 0.0f;
static bool clear = false;			//�Q�[���N���A������
static int Score = 0;
static int ClearTime = 0;
static int ClearLife = 0;

void InitProgress(void)
{
	progress = 0.0f;
	clear = false;
	Score = 0;
	ClearTime = 0;
	ClearLife = 0;
}
void UninitProgress(void)
{
	progress = 0.0f;
	clear = false;
}
void UpdateProgress(void)
{
	static float speed;

	//Player SPeed Return
	speed = ReturnSpeed();

	//�i�s�x�X�V
	progress += speed;

	rate = (float)progress / PROGRESS;
	rate = 1.0f - rate;

	if (progress >= PROGRESS)
	{
		//=======================================
		//		Score �v�Z
		//=======================================
		ClearTime = ReturnTime();
		ClearLife = ReturnPlayerLife();
		Score = (1000 - ClearTime) * TIME_SCORE;
		Score += ClearLife * LIFE_SCORE;
		int dead = ReturnDeadNum();
		Score -= dead * DEAD_POINT;
		TimeResult(Score);
		//========================================

		clear = true;
		ClearFinishGame(clear);
		ClearResult(clear);
		RankingClear(clear);
		InputScore(Score, ReturnDeadNum());
		ChangeScene(SCENE_FINISHGAME);
	}
	else if (ReturnPlayerLife() <= 0)
	{
		clear = false;
		ClearFinishGame(clear);
		ClearResult(clear);
		RankingClear(clear);
		ChangeScene(SCENE_FINISHGAME);
	}
}
void DrawProgress(void)
{
	DrawPolygon(TEXTURE_GAUGE,D3DCOLOR_RGBA(0,128,0,128),(float)SCREEN_WIDTH - (GAUGE_WIDTH / 3) - 10,(float)SCREEN_HEIGHT - NUMBER_HEIGHT - GAUGE_HEIGHT - 50,(float)GAUGE_WIDTH / 3,(float)GAUGE_HEIGHT,0,0,30,100);
	DrawPolygon(TEXTURE_PLAYER, D3DCOLOR_RGBA(255, 255, 255, 255), (float)SCREEN_WIDTH - (GAUGE_WIDTH / 3) - 15, (float)SCREEN_HEIGHT - NUMBER_HEIGHT - GAUGE_HEIGHT - 50 + (GAUGE_HEIGHT * rate), (float)PLAYER_WIDTH / 3, (float)PLAYER_HEIGHT / 3, 0, 0, 64, 64);

}
