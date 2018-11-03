//===================================================================================================
//		アイテムヘッダー
//																	
//===================================================================================================
#ifndef _ITEM_H_
#define _ITEM_H_

#define ITEM_WIDTH		(64)
#define ITEM_HEIGHT		(64)
#define ITEM_COOLTIME	(140)
#define ITEM_NUM		(1)
#define ITEM_SPEED		(1.0f)

typedef struct
{
	D3DXVECTOR2 g_vPos;
	int cooltime;
	bool Alive;
	int type;
	float speed;
}ITEM;

enum Item
{
	ITEM_HEART,
	ITEM_MAX
};

static ITEM item[ITEM_MAX];

void InitItem(void);
void UninitItem(void);
void UpdateItem(float speed);
void DrawItem(void);
void CreateItem(int index);
void DestroyItem(int index);
bool AliveItem(int index);
D3DXVECTOR2 GetPosItem(int index);
float ReturnItemSpeed(int index);

#endif
