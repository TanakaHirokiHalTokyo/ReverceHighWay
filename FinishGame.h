//===================================================================================================
//		ゲーム終了時シーン
//																	
//===================================================================================================
#ifndef _FINISHGAME_H_
#define _FINISHGAME_H_

#define GOAL_HEIGHT	(300)
#define GOAL_WIDTH	(600)

#define FINISH_WORD_WIDTH	(SCREEN_WIDTH * WidthRate)
#define FINISH_WORD_HEIGHT	(SCREEN_HEIGHT * HeightRate)

enum FINISH_WORD
{
	FINISH_GOAL = 1,
	FINISH_DEAD,
	FINISH_MAX
};


void InitFinishGame(void);
void UninitFinishGame(void);
void UpdateFinishGame(void);
void DrawFinishGame(void);
void ClearFinishGame(bool clear);

#endif