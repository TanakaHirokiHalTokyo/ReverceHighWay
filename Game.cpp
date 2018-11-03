//===================================================================================================
//		ゲーム.cpp
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

	//サウンド再生
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

		//バックグラウンド更新
		UpdateBackground(speed);
		//アイテム更新
		UpdateItem(speed);
		//対向車Update
		UpdateRevCar(speed);
		//ヒール更新
		UpdateHeal();
		//危険予測更新
		UpdateDanger();
		//時間更新
		UpdateTime();
		//進行度更新
		UpdateProgress();
		//Effect
		UpdateEffect();
		//PlayerUpdate
		UpdatePlayer();
		//爆発更新
		UpdateExplosion();
		

		//----------------------------------------------当たり判定---------------------------------------------------------------------------------------------------------
		for (int i = 0; i < REVCAR_NUM; i++)
		{
			for (int j = 0; j < ITEM_NUM; j++)
			{
				//PLAYERと対向車
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

				//MISSILEと対向車
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

				//LIFEとPLAYER
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
	DrawRevCar();		//対向車描画
	DrawHeal();			//Heal描画
	DrawDanger();		//危険予測描画
	DrawTime((float)(SCREEN_WIDTH - NUMBER_WIDTH), (float)(SCREEN_HEIGHT - NUMBER_HEIGHT));			//時間描画
	DrawProgress();		//進行度描画
	DrawEffect();
	DrawPlayer();		//Player Draw
	DrawExplosion();	//爆発描画
	DrawPause();
}
