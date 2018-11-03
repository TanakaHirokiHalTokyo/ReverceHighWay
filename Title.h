//===================================================================================================
//		タイトルシーン
//																	
//===================================================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#define SKY_SPEED		(0.3f)
#define PITCH_SPEED		(0.2f)
#define REV_SPEED		(5.0f)
#define TITLE_PLAYER_W	(200)
#define TITLE_PLAYER_H	(120)
#define TITLE_REVCAR_W	(250)
#define TITLE_REVCAR_H	(80)

#define TITLEPAUSE_WIDTH		(400.0f * 0.8f)
#define TITLEPAUSE_HEIGHT		(200.0f * 0.8f)

#define SAFE_TIME	(255 / 2)


typedef enum
{
	TITLE_PLAY = 0,
	TITLE_RANKING,
	TITLE_END,
	TITLE_MAX
}TITLE_MODE;

void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);

#endif