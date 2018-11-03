//=============================================================================
//
// �T�E���h���� [sound.h]
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

//*****************************************************************************
// �T�E���h�t�@�C��
//*****************************************************************************
typedef enum
{
	SOUND_GAMEBGM = 0,		// GameBGM0
	SOUND_TITLEBGM,			// TitleBGM
	SOUND_RESULTBGM,		// ResultBGM
	SOUND_BRAKE,			// �u���[�L���ʉ�
	SOUND_TRUCK,			// �g���b�N���ʉ�
	SOUND_EXPLOSION,		// �������ʉ�
	SOUND_HEAL,				// �񕜌��ʉ�
	SOUND_SELECT,			//SelectSE
	SOUND_OK,				//OKSE
	SOUND_RANKING,			//RankingBGM
	SOUND_STARTGAME,
	SOUND_MAX,
} SOUND_LABEL;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);
HRESULT PlaySound(SOUND_LABEL label);
void StopSound(SOUND_LABEL label);
void StopSound(void);

#endif
