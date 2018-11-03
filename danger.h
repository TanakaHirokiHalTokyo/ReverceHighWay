//==============================================================================================================
//
//		�댯�\���w�b�_�[
//
//==============================================================================================================

#ifndef _DANGER_H_
#define _DANGER_H_

#define DANGER_WIDTH		(64)
#define DANGER_HEIGHT		(64)
#define DANGER_TIME			(40)
#define DANGER_NUM			(REVCAR_NUM)	//�Ό��Ԃ��o�������Ƃ��ɕ\������̂őΌ��ԕ������p�ӂ���΂���
#define SPEEDDOWN_HEIGHT	(150)
#define SPEEDDOWN_WIDTH		(200)
#define SPEEDDOWN_SPEED		(20)
#define SPEEDDOWN_DRAWTIME	(900)

typedef struct
{
	D3DXVECTOR2 g_vPos;
	int time;
	bool bUse;
}DANGER;

static DANGER danger[DANGER_NUM];			

void InitDanger(void);
void UninitDanger(void);
void UpdateDanger(void);
void DrawDanger(void);
void CreateDanger(int a, int index);

#endif