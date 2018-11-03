//=============================================================================
//
//		StartGame.cpp
//
//=============================================================================

#include "main.h"

static float WidthRate = 3.0f;			//テクスチャの幅の割合		初期値３倍
static float HeightRate = 3.0f;			//テクスチャの高さの割合	初期値３倍
static int nSelectWord = START_READY;

void InitStartGame(void)
{
	PlaySound(SOUND_STARTGAME);
	WidthRate = 3.0f;
	HeightRate = 3.0f;
	nSelectWord = START_READY;
}
void UninitStartGame(void)
{
	StopSound();
	WidthRate = 3.0f;
	HeightRate = 3.0f;
	nSelectWord = START_READY;
}
void UpdateStartGame(void)
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
	}
	if (HeightRate < 1.0f)
	{
		HeightRate = 1.0f;
	}

	//倍率　等倍率になったらワード変更　倍率も３倍に戻す
	if (WidthRate <= 1.0f)
	{
		PlaySound(SOUND_STARTGAME);
		nSelectWord++;
		WidthRate = 1.5f;
		HeightRate = 1.5f;
	}

	//シーン切り替え　ワードすべて切り替え終わったら
	if (nSelectWord >= START_MAX)
	{
		ChangeScene(SCENE_GAME);
	}

	

}
void DrawStartGame(void)
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
	DrawPolygon(TEXTURE_FADE, D3DCOLOR_RGBA(0,0,0,120),0.0f,0.0f,SCREEN_WIDTH,SCREEN_HEIGHT,0,0,800,600);
	if (nSelectWord == START_READY)
	{
		DrawPolygon(TEXTURE_START_READY, D3DCOLOR_RGBA(255, 255, 160, 255), (float)(SCREEN_WIDTH - START_WORD_WIDTH) / 2,
			(float)(SCREEN_HEIGHT - START_WORD_HEIGHT) / 2, START_WORD_WIDTH, START_WORD_HEIGHT, 0, 0, 800, 600);
	}
	else if (nSelectWord == START_GO)
	{
		DrawPolygon(TEXTURE_START_GO, D3DCOLOR_RGBA(255, 255, 160, 255), (float)(SCREEN_WIDTH - START_WORD_WIDTH) / 2,
			(float)(SCREEN_HEIGHT - START_WORD_HEIGHT) / 2, START_WORD_WIDTH, START_WORD_HEIGHT, 0, 0, 800, 600);
	}
	
}