#include "main.h"

static float RankingYpos = (float)SCREEN_HEIGHT;

static RANKING g_Ranking[RANKING_MAX] =
{
{ 1,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 1),D3DCOLOR_RGBA(255,255,255,255)},
{ 2,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 2),D3DCOLOR_RGBA(255,255,255,255)},
{ 3,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 3),D3DCOLOR_RGBA(255,255,255,255)},
{ 4,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 4),D3DCOLOR_RGBA(255,255,255,255)},
{ 5,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 5),D3DCOLOR_RGBA(255,255,255,255)},
{ 6,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 6),D3DCOLOR_RGBA(255,255,255,255)},
{ 7,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 7),D3DCOLOR_RGBA(255,255,255,255)},
{ 8,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 8),D3DCOLOR_RGBA(255,255,255,255)},
{ 9,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 9),D3DCOLOR_RGBA(255,255,255,255)},
{ 10,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 10),D3DCOLOR_RGBA(255,255,255,255)},
{ 11,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 11),D3DCOLOR_RGBA(255,255,255,255) },
{ 12,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 12),D3DCOLOR_RGBA(255,255,255,255) },
{ 13,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 13),D3DCOLOR_RGBA(255,255,255,255) },
{ 14,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 14),D3DCOLOR_RGBA(255,255,255,255) },
{ 15,0,0,D3DXVECTOR2((FLOAT)350.0f,(FLOAT)32.0f * 15),D3DCOLOR_RGBA(255,255,255,255) },
};

//初期pos
static D3DXVECTOR2 pos[] =
{
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 1))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 2))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 3))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 4))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 5))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 6))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 7))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 8))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 9))},
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 10)) },
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 11)) },
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 12)) },
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 13)) },
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 14)) },
	{ D3DXVECTOR2((FLOAT)350.0f,(FLOAT)(32.0f * 15)) },
};

static int g_nPlayerScore = -1;
static int g_nPlayerDeath = 0;
static bool g_bClear = false;

void InitRanking(void)
{
	//binファイル読み込み
	LoadRanking();
	
	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_Ranking[i].pos.x = pos[i].x;
		g_Ranking[i].pos.y = pos[i].y;
		if (i == 0)
		{
			g_Ranking[i].color = D3DCOLOR_RGBA(0, 255, 0, 255);
		}
		else if (i == 1)
		{
			g_Ranking[i].color = D3DCOLOR_RGBA(0, 255, 167, 255);
		}
		else if (i == 2)
		{
			g_Ranking[i].color = D3DCOLOR_RGBA(95, 255, 167, 255);
		}
		else
		{
			g_Ranking[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
		}
	}
	//ランキング整理
	Ranking();
	RankingYpos = (float)SCREEN_HEIGHT;
	PlaySound(SOUND_RANKING);
}

void UninitRanking(void)
{
	g_nPlayerScore = -1;
	g_nPlayerDeath = 0;

	//ランキング情報　座標　色　初期化
	for (int i = 0; i < RANKING_MAX; i++)
	{
		g_Ranking[i].pos.x = pos[i].x;
		g_Ranking[i].pos.y = pos[i].y;
		g_Ranking[i].color = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	g_bClear = false;
	//ランキング　セーブ　binファイル　書き込み
	SaveRanking();
	StopSound();
	RankingYpos = (float)SCREEN_HEIGHT;
}

void DrawRanking(void)
{
	DrawPolygon(TEXTURE_RESULT, D3DCOLOR_RGBA(255, 255, 255, 255), 0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 800, 600);
	DrawPolygon(TEXTURE_RANKING,D3DCOLOR_RGBA(255,255,0,255),-20.0f,-50.0f,RANKING_WORD_WIDTH,RANKING_WORD_HEIGHT,0.0f,0.0f,400,300);
	DrawPolygon(TEXTURE_DOG,D3DCOLOR_RGBA(255,255,255,255),10.0f,(float)SCREEN_HEIGHT - RANKING_DOG_HEIGHT, RANKING_DOG_WIDTH,RANKING_DOG_HEIGHT,0,0,225,225);
	//自身のスコア　表示
	if (g_bClear)	//クリア時　自分のスコアが標示される
	{
		DrawPolygon(TEXTURE_YOUR_SCORE, D3DCOLOR_RGBA(255, 0, 0, 255), 10.0f, (float)SCREEN_HEIGHT - RANKING_DOG_HEIGHT - RANKING_YOUR_HEIGHT - NUMBER_HEIGHT - 50.0f,
			RANKING_YOUR_WIDTH, RANKING_YOUR_HEIGHT, 0, 0, 400, 300);
		DrawScore(g_nPlayerScore, 5, TRUE, 50.0f, SCREEN_HEIGHT - RANKING_DOG_HEIGHT - RANKING_YOUR_HEIGHT + 30.0f, D3DCOLOR_RGBA(255, 255, 0, 255));
		DrawPolygon(TEXTURE_DOKURO, D3DCOLOR_RGBA(255, 255, 255, 255), 100.0f - RANKING_DOKURO_WIDTH, SCREEN_HEIGHT - RANKING_DOG_HEIGHT - RANKING_YOUR_HEIGHT + 60.0f + NUMBER_HEIGHT, RANKING_DOKURO_WIDTH, RANKING_DOKURO_HEIGHT, 0, 0, 300, 300);
		DrawScore(g_nPlayerDeath, 2, FALSE, 100.0f, SCREEN_HEIGHT - RANKING_DOG_HEIGHT - RANKING_YOUR_HEIGHT + 60.0f + NUMBER_HEIGHT, D3DCOLOR_RGBA(255, 255, 0, 255));
	}
	for (int i = 0; i < RANKING_MAX; i++)
	{
		DrawScore(g_Ranking[i].nScore, 5, TRUE, g_Ranking[i].pos.x, g_Ranking[i].pos.y + RankingYpos,g_Ranking[i].color);
		DrawScore(g_Ranking[i].nLank,2,FALSE,(float)g_Ranking[i].pos.x - 100.0f, (float)g_Ranking[i].pos.y + RankingYpos, g_Ranking[i].color);
		DrawPolygon(TEXTURE_DOKURO,D3DCOLOR_RGBA(255,255,255,255), (float)g_Ranking[i].pos.x + 200.0f - RANKING_DOKURO_WIDTH, (float)g_Ranking[i].pos.y + RankingYpos, RANKING_DOKURO_WIDTH, RANKING_DOKURO_HEIGHT,0,0,300,300);
		DrawScore(g_Ranking[i].nDeath, 2, FALSE, (float)g_Ranking[i].pos.x + 200.0f, (float)g_Ranking[i].pos.y + RankingYpos, g_Ranking[i].color);
	}
	DrawPEnter();
 }

void UpdateRanking(void)
{
	if (RankingYpos > 0)
	{
		RankingYpos-= 4.0f;
	}

	if (GetKeyboardTrigger(DIK_RETURN))
	{
		ChangeScene(SCENE_TITLE);
	}
}

void SaveRanking(void)
{
	FILE *pFile;
	fopen_s(&pFile, RANKING_FILENAME, "wb");

	if (pFile != NULL)
	{
		fseek(pFile, 0L, SEEK_SET);
		fwrite(&g_Ranking[0], sizeof(RANKING), RANKING_MAX, pFile);
		fclose(pFile);
	}
}

void LoadRanking(void)
{
	FILE *pFile;
	fopen_s(&pFile, RANKING_FILENAME, "rb+");

	//読み取れたとき
	if (pFile != NULL)
	{
		fread(&g_Ranking[0], sizeof(RANKING), RANKING_MAX, pFile);
		fclose(pFile);
	}
	//読み取れないとき
	else
	{
		fopen_s(&pFile, RANKING_FILENAME, "wb");
		if (pFile != NULL)
		{
			fseek(pFile, 0L, SEEK_SET);
			fwrite(&g_Ranking[0], sizeof(RANKING), RANKING_MAX, pFile);
			fclose(pFile);
		}
	}
}

void Ranking(void)
{
	int nCount = RANKING_MAX - 1;
	//Ranking入れ替え先　探す
	for (nCount; nCount >= 0;)
	{
		if (g_Ranking[nCount].nScore < g_nPlayerScore)
		{
			if (nCount == 0) break;
			nCount--;
		}
		else if (g_Ranking[nCount].nScore == g_nPlayerScore)
		{
			//スコアが一緒の時死んだ回数で判断　ランキングのほうが多い場合　ランキング入れ替え
			if (g_Ranking[nCount].nDeath > g_nPlayerDeath)
			{
				if (nCount == 0) break;
				nCount--;
			}
			else
			{
				nCount++;
				break;
			}
		}
		//
		else
		{
			nCount ++;
			break;
		}
	}

	//スコア入れ替え
	if (nCount < RANKING_MAX - 1)
	{
		for (int nRankingCount = RANKING_MAX - 1; nRankingCount > nCount; nRankingCount--)
		{
			if (nCount == RANKING_MAX - 1) break;
			g_Ranking[nRankingCount].nScore = g_Ranking[nRankingCount - 1].nScore;
			g_Ranking[nRankingCount].nDeath = g_Ranking[nRankingCount - 1].nDeath;
		}

		if (nCount != RANKING_MAX - 1)
		{
			g_Ranking[nCount].nScore = g_nPlayerScore;
			g_Ranking[nCount].nDeath = g_nPlayerDeath;
			g_Ranking[nCount].color = D3DCOLOR_RGBA(255, 255, 0, 255);
		}

	}
}
void InputScore(int Score,int Death)
{
	g_nPlayerScore = Score;
	g_nPlayerDeath = Death;
}
void DrawScore(int nScore, int dig, bool bZero, float fXpos, float fYpos, D3DCOLOR color)
{
	//カンスト値
	int maxScore = 10;

	for (int i = 0; i < dig; i++)
	{
		maxScore *= 10;
	}
	maxScore -= 1;

	nScore = min(maxScore, nScore);

	for (int i = dig - 1; i >= 0; i--)
	{
		//score = 1234567
		int n = nScore % 10;
		//score /= 10;
		//score = 234567 or 123456
		DrawNumber(n,fXpos + i * NUMBER_WIDTH,fYpos, color);
		nScore /= 10;

		if (!bZero && nScore == 0)
		{
			break;
		}
	}
}
void RankingClear(bool clear)
{
	g_bClear = clear;
}