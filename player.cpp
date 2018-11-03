//==============================================================================================================
//
//		PLAYER.cpp
//
//==============================================================================================================

#include "main.h"


static float g_Speed = 0.0f;

void InitPlayer(void)
{
	player.g_vPos.x = 70.0f;
	player.g_vPos.y = (float)SCREEN_HEIGHT - (PLAYER_HEIGHT + 10.0f);
	player.AnimSpeed = 0.0f;
	player.NowMove = false;		//���E�Ɉړ������ǂ���	�ړ����Ă�����@���E�ɂ͈ړ��ł��Ȃ�
	player.MoveVec = 0;				//1:Left 2:Right �����Ɉړ�
	player.SideSpeed = 0.0f;		//�J�E���g�Ɏg���ϐ��@�Q�O�O�J�E���g������Ƃ߂�
	player.CoolTime = 0;
	player.Alive = true;
	player.Life = HEART_NUM;
	player.InvicibleTime = 0;
	player.Invicible = false;
	player.NowShot = false;
	player.CoolShot = 0;
	player.bCoolShot = true;		//�N�[���^�C�����I����Ă���
	player.M_pos.x = player.g_vPos.x;
	player.M_pos.y = player.g_vPos.y;
	g_Speed = 0.05f;

	player.DeadNum = 0;

	PlaySound(SOUND_TRUCK);
}
void UninitPlayer(void)
{
	player.g_vPos.x = 70.0f;
	player.g_vPos.y = (float)SCREEN_HEIGHT - (PLAYER_HEIGHT + 10.0f);
	player.AnimSpeed = 0.0f;
	player.NowMove = false;		//���E�Ɉړ������ǂ���	�ړ����Ă�����@���E�ɂ͈ړ��ł��Ȃ�
	player.MoveVec = 0;				//1:Left 2:Right �����Ɉړ�
	player.SideSpeed = 0.0f;		//�J�E���g�Ɏg���ϐ��@�Q�O�O�J�E���g������Ƃ߂�
	player.CoolTime = 0;
	player.Alive = true;
	player.Life = HEART_NUM;
	player.InvicibleTime = 0;
	player.Invicible = false;
	player.NowShot = false;
	player.CoolShot = 0;
	player.bCoolShot = true;	//�N�[���^�C�����I����Ă���
	player.M_pos.x = player.g_vPos.x;
	player.M_pos.y = player.g_vPos.y;
	g_Speed = 0.05f;

	player.DeadNum = 0;

	StopSound();
}
void UpdatePlayer(void)
{
	if (AlivePlayer())
	{
		//---------�~�T�C��-------------------
		//   SPACE�������Ƃ�
		if (GetKeyboardPress(DIK_SPACE) && !player.NowMove && player.bCoolShot)
		{
			bCoolShot();		//�N�[���^�C���J�E���g�J�n

			if (player.NowShot == false)
			{
				player.M_pos = GetPosPlayer();

				player.M_pos.x = player.M_pos.x + MISSILE_WIDTH / 2;
				player.M_pos.y = player.M_pos.y - MISSILE_HEIGHT;

				player.NowShot = true;
			}
		}

		if (player.NowShot == false)
		{
			player.M_pos = GetPosPlayer();

			player.M_pos.x = player.M_pos.x + MISSILE_WIDTH / 2;
			player.M_pos.y = player.M_pos.y - MISSILE_HEIGHT;
		}

		

		//------------------------------------

		//---------�㉺�X�s�[�h---------------
		if (GetKeyboardPress(DIK_W))
		{
			g_Speed += PLAYER_SPEEDUP;
		}
		if (GetKeyboardPress(DIK_S))
		{
			PlaySound(SOUND_BRAKE);

			g_Speed += PLAYER_SPEEDDOWN;
		}
		//-------------------------------------

		//---------���E�ړ�--------------------
		if (!player.NowMove)
		{
			if (GetKeyboardTrigger(DIK_A))
			{
				player.NowMove = true;
				player.MoveVec = VEC_LEFT;
			}
		}

		if (!player.NowMove)
		{
			if (GetKeyboardTrigger(DIK_D))
			{
				player.NowMove = true;
				player.MoveVec = VEC_RIGHT;
			}
		}

		if (player.NowMove)
		{
			//�������̈ړ�����
			if (player.MoveVec == VEC_LEFT)
			{
				player.SideSpeed -= PLAYER_SPEED;
				player.g_vPos.x -= PLAYER_SPEED;

				if (player.SideSpeed <= -200)
				{
					player.NowMove = false;
					player.SideSpeed = 0;
				}
				if (player.g_vPos.x < 70.0f)
				{
					player.g_vPos.x = 70.0f;
					player.NowMove = false;
				}
			}
			//�E�����̈ړ�����
			if (player.MoveVec == VEC_RIGHT)
			{
				player.SideSpeed += PLAYER_SPEED;
				player.g_vPos.x += PLAYER_SPEED;

				if (player.SideSpeed >= 200)
				{
					player.NowMove = false;
					player.SideSpeed = 0;
				}
				if (player.g_vPos.x > 670.0f)
				{
					player.g_vPos.x = 670.0f;
					player.NowMove = false;
				}
			}
		}
		//--------------------------------------
	}
	else if (!AlivePlayer())
	{
		player.CoolTime++;

		if (player.CoolTime > 60)
		{
			player.Alive = true;
			player.Invicible = true;
			player.CoolTime = 0;
		}
	}
	if (player.NowShot)
	{
		//�~�T�C���̈ʒu�̍X�V
		player.M_pos.y -= MISSILE_SPEED;
	}

	if (player.bCoolShot == false)
	{
		player.CoolShot++;
		if (player.CoolShot >= PLAYER_COOLSHOT)
		{
			player.bCoolShot = true;
			player.NowShot = false;
			player.CoolShot = 0;
		}
	}

	//���G�������ꍇ
	if (ReturnInvicible())
	{
		//���G���ԃJ�E���g
		player.InvicibleTime++;
		if (player.InvicibleTime > PLAYER_INVINCIBLE)
		{
			player.Invicible = false;
			player.InvicibleTime = 0;
		}
	}

	//�X�s�[�h��0.05�������Ȃ�		����������������
	if (g_Speed < 0.05f)
	{
		g_Speed = 0.05f;
	}
	if ((float)player.M_pos.y + MISSILE_HEIGHT < -100.0f)
	{
		DestroyMissile();
	}
	
}
void DrawPlayer(void)
{
	//���C�t�\��
	DrawLife();
	//�~�T�C���\��
	DrawMissile();

	//���G�łȂ��Ƃ��̃v���C���[�\��
	if (AlivePlayer() && !ReturnInvicible())
	{
		DrawPolygon(TEXTURE_PLAYER, D3DCOLOR_RGBA(255, 255, 255, 255), player.g_vPos.x, player.g_vPos.y, PLAYER_WIDTH, PLAYER_HEIGHT, 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);
	}
	//���G�̎��̃v���C���[�\��
	else if (AlivePlayer() && ReturnInvicible())
	{
		DrawPolygon(TEXTURE_PLAYER, D3DCOLOR_RGBA(221, 255, 57,128), player.g_vPos.x, player.g_vPos.y, PLAYER_WIDTH, PLAYER_HEIGHT, 0, 0, PLAYER_WIDTH, PLAYER_HEIGHT);
	}

}
float ReturnSpeed(void)
{
	return g_Speed;
}
bool AlivePlayer(void)
{
	return player.Alive;
}
void DestroyPlayer(void)
{
	player.Alive = false;
	g_Speed *= 0.45f;
	
	player.Life--;

	player.DeadNum++;
}
D3DXVECTOR2 GetPosPlayer(void)
{
	return player.g_vPos;
}
void DrawLife(void)
{
	for (int i = 0; i < player.Life; i++)
	{
		DrawPolygon(TEXTURE_HEART, D3DCOLOR_RGBA(255, 255, 255, 255), (float)HEART_WIDTH,(float)(SCREEN_HEIGHT - HEART_HEIGHT - 10) - HEART_HEIGHT * i,HEART_WIDTH,HEART_HEIGHT,0,0,756,756);
	}
}
void DrawMissile(void)
{
	if (player.NowShot)
	{
		DrawPolygon(TEXTURE_MISSILE, D3DCOLOR_RGBA(255, 255, 255, 255), (float)player.M_pos.x, (float)player.M_pos.y, (float)MISSILE_WIDTH, (float)MISSILE_HEIGHT, 0, 0, 163, 309);
		CreateEffect((float)player.M_pos.x, (float)player.M_pos.y + PLAYER_HEIGHT / 4, D3DXCOLOR((float)128 / 255, (float)64 / 255, (float)64 / 255, (float)64 / 255), EFFECT_LIMIT);
		CreateEffect((float)player.M_pos.x, (float)player.M_pos.y + PLAYER_HEIGHT / 4, D3DXCOLOR((float)128 / 255, (float)128 / 255, (float)64 / 255, (float)64 / 255), EFFECT_LIMIT);
	}
	
	if (player.bCoolShot == true)
	{
		DrawPolygon(TEXTURE_MISSILE, D3DCOLOR_RGBA(255, 255, 255, 255), (float)SCREEN_WIDTH - (GAUGE_WIDTH + 10), (float)0.0f, (float)MISSILE_WIDTH, (float)MISSILE_HEIGHT * 1.5f, 0, 0, 163, 309);
		DrawPolygon(TEXTURE_GAUGE, D3DCOLOR_RGBA(255, 255, 0, 255), (float)SCREEN_WIDTH - (GAUGE_WIDTH + 10), (float)MISSILE_HEIGHT * 1.5f, (float)GAUGE_WIDTH, (float)GAUGE_HEIGHT,0,0,30,100);
	}
	else if (player.bCoolShot == false)
	{
		float rate = (float)player.CoolShot / PLAYER_COOLSHOT;
		DrawPolygon(TEXTURE_MISSILE, D3DCOLOR_RGBA(255, 255, 255, 255), (float)SCREEN_WIDTH - (GAUGE_WIDTH + 10), (float)0.0f, (float)MISSILE_WIDTH, (float)MISSILE_HEIGHT * 1.5f, 0, 0, 163, 309);
		DrawPolygon(TEXTURE_GAUGE, D3DCOLOR_RGBA(255, 0, 0, 255), (float)SCREEN_WIDTH - (GAUGE_WIDTH + 10), (float)MISSILE_HEIGHT * 1.5f, (float)GAUGE_WIDTH, (float)GAUGE_HEIGHT, 0, 0, 30, 100);
		DrawPolygon(TEXTURE_GAUGE, D3DCOLOR_RGBA(0, 0, 0, 255), (float)SCREEN_WIDTH - (GAUGE_WIDTH + 10), (float)MISSILE_HEIGHT * 1.5f, (float)GAUGE_WIDTH, (float)GAUGE_HEIGHT - GAUGE_HEIGHT * rate, 0, 0, 30, 100);
	}
	
}
bool ReturnInvicible(void)
{
	return player.Invicible;
}
int ReturnPlayerLife(void)
{
	return player.Life;
}
D3DXVECTOR2 GetPosMissile(void)
{
	return player.M_pos;
}
void DestroyMissile(void)
{
	player.NowShot = false;
}
bool NowShot(void)
{
	return player.NowShot;
}
void bCoolShot(void)
{
	player.bCoolShot = false;
}
void LifeHeal(void)
{
	if (player.Life < HEART_NUM)
	{
		player.Life++;
	}
}
int ReturnDeadNum(void)
{
	return player.DeadNum;
}