//===================================================================================================
//
//		StartGame.h
//
//===================================================================================================

#ifndef _STARTGAME_H_
#define _STARTGAME_H_

#define START_WORD_WIDTH	(SCREEN_WIDTH * WidthRate)
#define START_WORD_HEIGHT	(SCREEN_HEIGHT * HeightRate)
#define START_RATE			(0.015f)

enum START_WORD
{
	START_READY = 1,
	START_GO,
	START_MAX
};

void InitStartGame(void);
void UninitStartGame(void);
void UpdateStartGame(void);
void DrawStartGame(void);

#endif // !_STARTGAME_H_
