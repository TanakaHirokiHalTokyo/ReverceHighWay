
#include "main.h"

//void(*pFunc)(void) = InitTitle;				//アドレスの後に()がつけられると実行される。	pFunc()するとInitTitle関数が実行される。
typedef void(*SceneFunc)(void);

//関数ポインタ配列
static const SceneFunc g_pInit[] = {
	//enumと同等の順番にするとよい
	InitTitle,
	InitExplain,
	InitStartGame,
	InitGame,
	InitFinishGame,
	InitRanking,
	InitResult,
};

static const SceneFunc g_pUninit[] = {
	//enumと同等の順番にするとよい
	UninitTitle,
	UninitExplain,
	UninitStartGame,
	UninitGame,
	UninitFinishGame,
	UninitRanking,
	UninitResult,
};
static const SceneFunc g_pUpdate[] = {
	//enumと同等の順番にするとよい
	UpdateTitle,
	UpdateExplain,
	UpdateStartGame,
	UpdateGame,
	UpdateFinishGame,
	UpdateRanking,
	UpdateResult,
};
static const SceneFunc g_pDraw[] = {
	//enumと同等の順番にするとよい
	DrawTitle,
	DrawExplain,
	DrawStartGame,
	DrawGame,
	DrawFinishGame,
	DrawRanking,
	DrawResult,
};

static SCENE_ID g_nID = SCENE_TITLE;			//現在のシーンID
static SCENE_ID g_nNextID = SCENE_TITLE;		//次になりたいシーンID

void InitScene(void)
{
	g_pInit[g_nID]();
}
void UninitScene(void)
{
	g_pUninit[g_nID]();
}
void UpdateScene(void)
{
	g_pUpdate[g_nID]();
}
void DrawScene(void)
{
	g_pDraw[g_nID]();
	if (g_nNextID != g_nID)
	{
		UninitScene();
		g_nID = g_nNextID;
		InitScene();
	}
}
SCENE_ID ChangeScene(SCENE_ID id)
{
	g_nNextID = id;
	return g_nID;
}