//===================================================================================================
//		ÉQÅ[ÉÄÉVÅ[Éì
//																	
//===================================================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

typedef enum
{
	SCENE_NONE = -1,
	SCENE_TITLE,
	SCENE_EXPLAIN,
	SCENE_STARTGAME,
	SCENE_GAME,
	SCENE_FINISHGAME,
	SCENE_RANKING,
	SCENE_RESULT,
	SCENE_MAX
}SCENE_ID;



void InitScene(void);
void UninitScene(void);
void UpdateScene(void);
void DrawScene(void);

SCENE_ID ChangeScene(SCENE_ID id);

#endif