//===================================================================================================
//		�G�t�F�N�g�w�b�_�[
//																	
//===================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_


#define EFFECT_MAX		(1024)		//Effect��
#define EFFECT_WIDTH	(32)		//��
#define EFFECT_HEIGHT	(32)		//��
#define EFFECT_LIMIT	(10)

typedef struct
{
	D3DXVECTOR2 vPos;			//Effect ���W
	bool bEffect;				//Effect �g�p���Ă��邩
	D3DXCOLOR color;			//Effect �F
	int nLimit;					//Effect ����
	int nBirth;					//Effect ���������ԁi�a�����j
}EFFECT;

static EFFECT Effect[EFFECT_MAX];
static int g_nFrameCount = 0;	//Effect �̃O���[�o�����ԕۑ��@�ϐ�

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void CreateEffect(float x,float y,D3DXCOLOR color,int nLimit);


#endif