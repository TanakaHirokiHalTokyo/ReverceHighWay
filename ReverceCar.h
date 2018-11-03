//==============================================================================================================
//
//		対向車ヘッダー
//
//==============================================================================================================

#ifndef _REVERCECAR_H_
#define _REVERCECAR_H_

#define REVCAR_WIDTH	(64)
#define REVCAR_HEIGHT	(64)
#define REVCAR_NUM		(3)
#define REVCAR_SPEED	(1.5f)


typedef struct
{
	D3DXVECTOR2 g_vPos;
	int Type;			//車の色の種類	1:Blue 2:Red 3:Cyan
	bool Alive;			//生きているか
	int CoolTime;		//復活までのクールタイム
	float g_speed;
}REVCAR;

static REVCAR revcar[REVCAR_NUM];

void InitRevCar(void);
void UninitRevCar(void);
void UpdateRevCar(float speed);
void DrawRevCar(void);
void CreateRevCar(int i);
void DestroyRevCar(int index);
bool AliveRevCar(int index);
D3DXVECTOR2 GetPosRevCar(int index);
float ReturnRevSpeed(int index);

#endif