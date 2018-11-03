//===================================================================================================
//		�Q�[��.cpp
//																	
//===================================================================================================

#include "main.h"

static bool Pause = false;

void InitGame(void)
{
	InitBackground();
	InitItem();
	InitRevCar();
	InitHeal();
	InitDanger();
	InitTime();
	InitProgress();
	InitEffect();
	InitPlayer();
	InitExplosion();  
	InitPause();

	//�T�E���h�Đ�
	PlaySound(SOUND_GAMEBGM);

}
void UninitGame(void)
{
	UninitBackground();
	UninitItem();
	UninitRevCar();
	UninitHeal();
	UninitDanger();
	UninitTime();
	UninitProgress();
	UninitEffect();
	UninitPlayer();
	UninitExplosion();
	UninitPause();

	StopSound();
}
void UpdateGame(void)
{
	UpdatePause();
	Pause = ReturnPause();

	if (!Pause)
	{
		static float speed;
		//Player SPeed Return
		speed = ReturnSpeed();

		//�o�b�N�O���E���h�X�V
		UpdateBackground(speed);
		//�A�C�e���X�V
		UpdateItem(speed);
		//�Ό���Update
		UpdateRevCar(speed);
		//�q�[���X�V
		UpdateHeal();
		//�댯�\���X�V
		UpdateDanger();
		//���ԍX�V
		UpdateTime();
		//�i�s�x�X�V
		UpdateProgress();
		//Effect
		UpdateEffect();
		//PlayerUpdate
		UpdatePlayer();
		//�����X�V
		UpdateExplosion();
		

		//----------------------------------------------�����蔻��---------------------------------------------------------------------------------------------------------
		for (int i = 0; i < REVCAR_NUM; i++)
		{
			for (int j = 0; j < ITEM_NUM; j++)
			{
				//PLAYER�ƑΌ���
				if (AlivePlayer() && AliveRevCar(i) && !ReturnInvicible())
				{
					float RevSpeed = ReturnRevSpeed(i);

					bool bHit = Hit(GetPosRevCar(i).x + (float)(REVCAR_WIDTH / 2), (GetPosRevCar(i).y + RevSpeed) + (float)(REVCAR_HEIGHT / 2), (float)REVCAR_HEIGHT / 2,
						GetPosPlayer().x + (float)(PLAYER_WIDTH / 2), GetPosPlayer().y + (float)(PLAYER_WIDTH / 2), (float)PLAYER_HEIGHT / 2);

					if (bHit)
					{
						DestroyRevCar(i);
						DestroyPlayer();
						CreateExplosion((float)GetPosPlayer().x, (float)GetPosPlayer().y);
						PlaySound(SOUND_EXPLOSION);
					}
				}

				//MISSILE�ƑΌ���
				if (NowShot() && AliveRevCar(i))
				{
					float RevSpeed = ReturnRevSpeed(i);
					bool bHit = Hit(GetPosRevCar(i).x + (float)(REVCAR_WIDTH / 2), (GetPosRevCar(i).y + RevSpeed) + (float)(REVCAR_HEIGHT / 2), (float)REVCAR_HEIGHT / 2,
						GetPosMissile().x + (float)(MISSILE_WIDTH / 2), GetPosMissile().y + (float)(MISSILE_HEIGHT / 2), (float)MISSILE_HEIGHT / 2);
					if (bHit)
					{
						DestroyMissile();
						DestroyRevCar(i);
						CreateExplosion(GetPosMissile().x - (float)(MISSILE_WIDTH / 2), GetPosMissile().y);
						PlaySound(SOUND_EXPLOSION);
					}
				}

				//LIFE��PLAYER
				if (AliveItem(j) && AlivePlayer())
				{
					float speed = ReturnItemSpeed(j);

					bool bHit = Hit(GetPosItem(j).x + (float)(ITEM_WIDTH / 2), (GetPosItem(j).y + speed) + (float)(ITEM_HEIGHT / 2), (float)ITEM_HEIGHT / 2,
						GetPosPlayer().x + (float)(PLAYER_WIDTH / 2), GetPosPlayer().y + (float)(PLAYER_WIDTH / 2), (float)PLAYER_HEIGHT / 2);
					if (bHit)
					{
						DestroyItem(j);
						LifeHeal();
						CreateHeal((float)GetPosPlayer().x, (float)GetPosPlayer().y);
						PlaySound(SOUND_HEAL);
					}
				}
			}
		}
		//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
	}
	else
	{

	}
	
}
void DrawGame(void)
{
	DrawBackground();	//Background Draw
	DrawItem();
	DrawRevCar();		//�Ό��ԕ`��
	DrawHeal();			//Heal�`��
	DrawDanger();		//�댯�\���`��
	DrawTime((float)(SCREEN_WIDTH - NUMBER_WIDTH), (float)(SCREEN_HEIGHT - NUMBER_HEIGHT));			//���ԕ`��
	DrawProgress();		//�i�s�x�`��
	DrawEffect();
	DrawPlayer();		//Player Draw
	DrawExplosion();	//�����`��
	DrawPause();
}
