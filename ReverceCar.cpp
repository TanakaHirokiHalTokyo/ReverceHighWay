//==============================================================================================================
//
//		ReverceCar.cpp			‘ÎŒüÔ
//
//==============================================================================================================

#include "main.h"

static float g_speed = 0.0f;

void InitRevCar(void)
{
	int a = 1;
	for (int i = 0; i < REVCAR_NUM; i++)
	{
		CreateRevCar(i);
	}
}
void UninitRevCar(void)
{
	for (int i = 0; i < REVCAR_NUM; i++)
	{
		DestroyRevCar(i);
	}
}
void UpdateRevCar(float speed)
{

	for (int i = 0; i < REVCAR_NUM; i++)
	{
		revcar[i].g_speed += REVCAR_SPEED + speed;

		if (AliveRevCar(i) && revcar[i].g_vPos.y + revcar[i].g_speed > SCREEN_HEIGHT)
		{
			DestroyRevCar(i);
			revcar[i].g_speed = 0;
		}

		if (!AliveRevCar(i))
		{
			revcar[i].CoolTime++;
		}
		if (!AliveRevCar(i) && revcar[i].CoolTime > 60)		//1•bŒã@•œŠˆ
		{
			CreateRevCar(i);
		}
	}
}
void DrawRevCar(void)
{
	for (int i = 0; i < REVCAR_NUM; i++)
	{
		if (AliveRevCar(i))
		{
			if (revcar[i].Type == 1)
			{
				DrawPolygon(TEXTURE_CAR_B, D3DCOLOR_RGBA(255, 255, 255, 255), revcar[i].g_vPos.x, revcar[i].g_vPos.y + revcar[i].g_speed, REVCAR_WIDTH, REVCAR_HEIGHT, 0, 0, REVCAR_WIDTH, REVCAR_HEIGHT);
			}
			else if (revcar[i].Type == 2)
			{
				DrawPolygon(TEXTURE_CAR_R, D3DCOLOR_RGBA(255, 255, 255, 255), revcar[i].g_vPos.x, revcar[i].g_vPos.y + revcar[i].g_speed, REVCAR_WIDTH, REVCAR_HEIGHT, 0, 0, REVCAR_WIDTH, REVCAR_HEIGHT);
			}
			else if (revcar[i].Type == 3)
			{
				DrawPolygon(TEXTURE_CAR_CY, D3DCOLOR_RGBA(255, 255, 255, 255), revcar[i].g_vPos.x, revcar[i].g_vPos.y + revcar[i].g_speed, REVCAR_WIDTH, REVCAR_HEIGHT, 0, 0, REVCAR_WIDTH, REVCAR_HEIGHT);
			}
		}
	
	}
}
void CreateRevCar(int i)
{
	int a;

	a = rand() % 4;
	revcar[i].g_vPos.x = (float)200 * a + 70.0f;
	revcar[i].g_vPos.y = (float)-800 + (rand() % 600);
	revcar[i].Type = rand() % 3 + 1;
	revcar[i].Alive = true;
	revcar[i].CoolTime = 0;
	revcar[i].g_speed = 0;
	CreateDanger(a,i);
}
void DestroyRevCar(int index)
{
	revcar[index].Alive = false;
}
bool AliveRevCar(int index)
{
	return revcar[index].Alive;
}
D3DXVECTOR2 GetPosRevCar(int index)
{
	return revcar[index].g_vPos;
}
float ReturnRevSpeed(int index)
{
	return revcar[index].g_speed;
}