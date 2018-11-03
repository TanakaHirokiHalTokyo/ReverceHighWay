//===================================================================================================
//		アイテム.cpp
//																	
//===================================================================================================

#include "main.h"

void InitItem(void)
{
	for (int i = 0; i < ITEM_NUM; i++)
	{
		int a;
		a = rand() % 4;

		item[i].g_vPos.x = (float)200 * a + 70.0f;
		item[i].g_vPos.y = (float)-800 + (rand() % 600);
		item[i].Alive = false;
		item[i].cooltime = 0;
		item[i].speed = 0;
		item[i].type = rand() % ITEM_MAX;
	}
}
void UninitItem(void)
{
	for (int i = 0; i < ITEM_NUM; i++)
	{
		item[i].g_vPos.x = 0.0f;
		item[i].g_vPos.y = 0.0f;
		item[i].Alive = false;
		item[i].cooltime = 0;
		item[i].speed = 0;
		item[i].type = rand() % ITEM_MAX;
	}
}
void UpdateItem(float speed)
{
	for (int i = 0; i < ITEM_NUM; i++)
	{
		//クールタイムカウント
		if (!item[i].Alive)
		{
			item[i].cooltime++;
		}
		else
		{
			item[i].speed += ITEM_SPEED + speed;
		}
		//クールタイム終えた処理
		if (item[i].cooltime > ITEM_COOLTIME)
		{
			CreateItem(i);
		}

		if (item[i].g_vPos.y + item[i].speed > SCREEN_HEIGHT)
		{
			DestroyItem(i);
			item[i].speed = 0.0f;
		}

	}
}
void DrawItem(void)
{
	for (int i = 0; i < ITEM_NUM; i++)
	{
		if (AliveItem(i))
		{
			if (item[i].type == ITEM_HEART)
			{
				DrawPolygon(TEXTURE_HEAL,D3DCOLOR_RGBA(255,255,255,255),(float)item[i].g_vPos.x,(float)item[i].g_vPos.y + item[i].speed,ITEM_WIDTH,ITEM_HEIGHT,0,0,64,64);
				//DebugText(32, 32, "アイテム座標 x = %.2f, y = %.2f\n", item[0].g_vPos.x, item[0].speed);
			}
		}
	}
}
void CreateItem(int index)
{
	int a;

	a = rand() % 4;
	item[index].g_vPos.x = (float)200 * a + 70.0f;
	item[index].g_vPos.y = (float)-800 + (rand() % 600);
	item[index].type = rand() % ITEM_MAX;
	item[index].Alive = true;
	item[index].cooltime = 0;
}
void DestroyItem(int index)
{
	item[index].Alive = false;
}
bool AliveItem(int index)
{
	return item[index].Alive;
}
D3DXVECTOR2 GetPosItem(int index)
{
	return item[index].g_vPos;
}
float ReturnItemSpeed(int index)
{
	return item[index].speed;
}