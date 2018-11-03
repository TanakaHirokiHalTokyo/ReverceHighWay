//=============================================================================
//
//		StartGame.cpp
//
//=============================================================================

#include "main.h"

static float WidthRate = 3.0f;			//�e�N�X�`���̕��̊���		�����l�R�{
static float HeightRate = 3.0f;			//�e�N�X�`���̍����̊���	�����l�R�{
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
	//���{��
	if (WidthRate > 1.0f)
	{
		WidthRate -= START_RATE;
	}
	
	//�c�{��
	if (HeightRate > 1.0f)
	{
		HeightRate -= START_RATE;
	}
	//1.0f�ȉ��ɂȂ��Ă��܂����ꍇ�@���{�ɂ��ǂ�
	if (WidthRate < 1.0f)
	{
		WidthRate = 1.0f;
	}
	if (HeightRate < 1.0f)
	{
		HeightRate = 1.0f;
	}

	//�{���@���{���ɂȂ����烏�[�h�ύX�@�{�����R�{�ɖ߂�
	if (WidthRate <= 1.0f)
	{
		PlaySound(SOUND_STARTGAME);
		nSelectWord++;
		WidthRate = 1.5f;
		HeightRate = 1.5f;
	}

	//�V�[���؂�ւ��@���[�h���ׂĐ؂�ւ��I�������
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
	DrawRevCar();		//�Ό��ԕ`��
	DrawExplosion();	//�����`��
	DrawHeal();			//Heal�`��
	DrawDanger();		//�댯�\���`��
	DrawTime((float)(SCREEN_WIDTH - NUMBER_WIDTH), (float)(SCREEN_HEIGHT - NUMBER_HEIGHT));			//���ԕ`��
	DrawProgress();		//�i�s�x�`��
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