//==============================================================================================================
//
//		ヒールヘッダー
//
//==============================================================================================================

#ifndef _HEAL_H_
#define _HEAL_H_

#define HEAL_HEIGHT		(64)
#define HEAL_WIDTH		(64)

#define HEAL_PATTERN	(15)
#define HEAL_SPEED		(3)
#define HEAL_WNUM		(5)
#define HEAL_HNUM		(3)

void InitHeal(void);
void UninitHeal(void);
void UpdateHeal(void);
void DrawHeal(void);
void CreateHeal(float x, float y);

#endif