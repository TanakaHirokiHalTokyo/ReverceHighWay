//===================================================================================================
//		エフェクトヘッダー
//																	
//===================================================================================================
#ifndef _EFFECT_H_
#define _EFFECT_H_


#define EFFECT_MAX		(1024)		//Effect数
#define EFFECT_WIDTH	(32)		//幅
#define EFFECT_HEIGHT	(32)		//高
#define EFFECT_LIMIT	(10)

typedef struct
{
	D3DXVECTOR2 vPos;			//Effect 座標
	bool bEffect;				//Effect 使用しているか
	D3DXCOLOR color;			//Effect 色
	int nLimit;					//Effect 寿命
	int nBirth;					//Effect 生成時時間（誕生日）
}EFFECT;

static EFFECT Effect[EFFECT_MAX];
static int g_nFrameCount = 0;	//Effect のグローバル時間保存　変数

void InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void CreateEffect(float x,float y,D3DXCOLOR color,int nLimit);


#endif