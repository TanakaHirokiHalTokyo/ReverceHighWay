//==============================================================================================================
//
//		BACKGROUNDÉwÉbÉ_Å[
//
//==============================================================================================================

#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#define BACKGROUND_WIDTH	(800)
#define BACKGROUND_HEIGHT	(600)

#define SPEED_DEF			(1.0f)

void InitBackground(void);
void UninitBackground(void);
void UpdateBackground(float speed);
void DrawBackground(void);
#endif