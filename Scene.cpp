
#include "main.h"

//void(*pFunc)(void) = InitTitle;				//�A�h���X�̌��()��������Ǝ��s�����B	pFunc()�����InitTitle�֐������s�����B
typedef void(*SceneFunc)(void);

//�֐��|�C���^�z��
static const SceneFunc g_pInit[] = {
	//enum�Ɠ����̏��Ԃɂ���Ƃ悢
	InitTitle,
	InitExplain,
	InitStartGame,
	InitGame,
	InitFinishGame,
	InitRanking,
	InitResult,
};

static const SceneFunc g_pUninit[] = {
	//enum�Ɠ����̏��Ԃɂ���Ƃ悢
	UninitTitle,
	UninitExplain,
	UninitStartGame,
	UninitGame,
	UninitFinishGame,
	UninitRanking,
	UninitResult,
};
static const SceneFunc g_pUpdate[] = {
	//enum�Ɠ����̏��Ԃɂ���Ƃ悢
	UpdateTitle,
	UpdateExplain,
	UpdateStartGame,
	UpdateGame,
	UpdateFinishGame,
	UpdateRanking,
	UpdateResult,
};
static const SceneFunc g_pDraw[] = {
	//enum�Ɠ����̏��Ԃɂ���Ƃ悢
	DrawTitle,
	DrawExplain,
	DrawStartGame,
	DrawGame,
	DrawFinishGame,
	DrawRanking,
	DrawResult,
};

static SCENE_ID g_nID = SCENE_TITLE;			//���݂̃V�[��ID
static SCENE_ID g_nNextID = SCENE_TITLE;		//���ɂȂ肽���V�[��ID

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