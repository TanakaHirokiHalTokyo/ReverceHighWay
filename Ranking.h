//=============================================================================
//
//		Ranking.h
//
//=============================================================================

#ifndef  _RANKING_H_
#define  _RANKING_H_

#define RANKING_MAX				(15)				//�����L���O���ʐ�	
#define RANKING_WORD_WIDTH		(400.0f * 0.8f)		//Ranking Word width
#define RANKING_WORD_HEIGHT		(300.0f * 0.8f)		//ranking Word height
#define RANKING_DOKURO_WIDTH	(32.0f)
#define RANKING_DOKURO_HEIGHT	(32.0f)
#define RANKING_DOG_WIDTH		(200.0f)
#define RANKING_DOG_HEIGHT		(200.0f)
#define RANKING_YOUR_WIDTH		(200.0f)
#define RANKING_YOUR_HEIGHT		(150.0f)
#define RANKING_FILENAME		"resource/Ranking.bin"

void InitRanking(void);
void UninitRanking(void);
void DrawRanking(void);
void UpdateRanking(void);

void SaveRanking(void);
void LoadRanking(void);
void Ranking(void);
void InputScore(int Score, int Death);
void DrawScore(int nScore, int dig, bool bZero, float fXpos, float fYpos, D3DCOLOR color);
void RankingClear(bool clear);

typedef struct
{
	int nLank; //�����N
	int nScore;//�X�R�A
	int nDeath;
	D3DXVECTOR2 pos; //�����L���O�̈ʒu
	D3DCOLOR color;  //�J���[
}RANKING;



#endif //_RANKING_H_
