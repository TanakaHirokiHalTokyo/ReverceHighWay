//==============================================================================================================
//
//		îöî≠ÉwÉbÉ_Å[
//
//==============================================================================================================

#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

#define EXPLOSION_HEIGHT	(64)
#define EXPLOSION_WIDTH		(64)

#define EXPLOSION_PATTERN	(13)
#define EXPLOSION_SPEED		(3)

void InitExplosion(void);
void UninitExplosion(void);
void UpdateExplosion(void);
void DrawExplosion(void);
void CreateExplosion(float x, float y);

#endif