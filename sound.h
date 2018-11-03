//=============================================================================
//
// サウンド処理 [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_GAMEBGM = 0,		// GameBGM0
	SOUND_TITLEBGM,			// TitleBGM
	SOUND_RESULTBGM,		// ResultBGM
	SOUND_BRAKE,			// ブレーキ効果音
	SOUND_TRUCK,			// トラック効果音
	SOUND_EXPLOSION,		// 爆発効果音
	SOUND_HEAL,				// 回復効果音
	SOUND_SELECT,			//SelectSE
	SOUND_OK,				//OKSE
	SOUND_RANKING,			//RankingBGM
	SOUND_STARTGAME,
	SOUND_MAX,
} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
