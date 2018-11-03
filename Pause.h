//===================================================================================================
//		ポーズヘッダー
//																	
//===================================================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#define PAUSEMENU_WIDTH		(400)
#define PAUSEMENU_HEIGHT	(600)

#define PAUSEFONT_HEIGHT	(200 * 0.6f)
#define PAUSEFONT_WIDTH		(500 * 0.4f)

#define PAUSE_WIDTH			(800.0f * 0.8f)
#define PAUSE_HEIGHT		(600.0f * 0.8f)

#define FADE_PAUSE			(180)

typedef enum
{
	PAUSE_RESUME = 0,
	PAUSE_TITLE,
	PAUSE_MAX
}PAUSE_MODE;

static bool g_bPause = false;
static int g_nPauseMode = PAUSE_RESUME;

void InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
bool ReturnPause(void);

#endif