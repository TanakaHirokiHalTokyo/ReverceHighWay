//===================================================================================================
//		ゲーム終了時シーン
//																	
//===================================================================================================

#include "main.h"

static bool Clear = false;
static bool SpawnWord = false;
static bool bRate = false;
static float WidthRate = 3.0f;
static float HeightRate = 3.0f;
static int nSelectWord = FINISH_GOAL;

void InitFinishGame(void)
{
	WidthRate = 3.0f;
	HeightRate = 3.0f;
	nSelectWord = FINISH_GOAL;
}
void UninitFinishGame(void)
{
	SpawnWord = false;
	bRate = false;
	WidthRate = 3.0f;
	HeightRate = 3.0f;
	nSelectWord = FINISH_GOAL;
}
void UpdateFinishGame(void)
{
	if (SpawnWord && !bRate)
	{
		//横倍率
		if (WidthRate > 1.0f)
		{
			WidthRate -= START_RATE;
		}

		//縦倍率
		if (HeightRate > 1.0f)
		{
			HeightRate -= START_RATE;
		}
		//1.0f以下になってしまった場合　等倍にもどす
		if (WidthRate < 1.0f)
		{
			WidthRate = 1.0f;
			bRate = true;
		}
		if (HeightRate < 1.0f)
		{
			HeightRate = 1.0f;
			bRate = true;
		}
	}
	

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		ChangeScene(SCENE_RESULT);
	}
}
void DrawFinishGame(void)
{
	DrawBackground();	//Background Draw
	DrawItem();
	DrawPlayer();		//Player Draw
	DrawRevCar();		//対向車描画
	DrawExplosion();	//爆発描画
	DrawHeal();			//Heal描画
	DrawDanger();		//危険予測描画
	DrawTime((float)(SCREEN_WIDTH - NUMBER_WIDTH), (float)(SCREEN_HEIGHT - NUMBER_HEIGHT));			//時間描画
	DrawProgress();		//進行度描画
	if (Clear == true)
	{
		DrawPolygon(TEXTURE_GOAL, D3DCOLOR_RGBA(255, 255, 0, 255), (float)(SCREEN_WIDTH - START_WORD_WIDTH) / 2,
			(float)(SCREEN_HEIGHT - START_WORD_HEIGHT) / 2, START_WORD_WIDTH, START_WORD_HEIGHT, 0, 0, 800, 600);
	}
	else
	{
		DrawPolygon(TEXTURE_DIED, D3DCOLOR_RGBA(255, 0, 0, 255), (float)(SCREEN_WIDTH - START_WORD_WIDTH) / 2,
			(float)(SCREEN_HEIGHT - START_WORD_HEIGHT) / 2, START_WORD_WIDTH, START_WORD_HEIGHT, 0, 0, 800, 600);
	}
	DrawPEnter();
}
void ClearFinishGame(bool clear)
{
	SpawnWord = true;
	Clear = clear;
}