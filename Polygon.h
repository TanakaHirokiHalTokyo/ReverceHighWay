
//===================================================================================================
//		ポリゴン描画
//																	2017/06/05			田中　大輝
//===================================================================================================
#ifndef _POLYGON_H_
#define _POLYGON_H_


#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

typedef enum
{
	TEXTURE_0,
	TEXTURE_1,
	TEXTURE_2,
	TEXTURE_3,
	TEXTURE_4,
	TEXTURE_5,
	TEXTURE_6,
	TEXTURE_7,
	TEXTURE_8,
	TEXTURE_9,
	TEXTURE_PLAYER,
	TEXTURE_CAR_B,
	TEXTURE_CAR_R,
	TEXTURE_CAR_CY,
	TEXTURE_EXPLOSION,
	TEXTURE_EFFECT_H,		//ハートエフェクト
	TEXTURE_DOURO1,
	TEXTURE_DOURO2,
	TEXTURE_DANGER,
	TEXTURE_HEART,
	TEXTURE_SPEEDDOWN,
	TEXTURE_TITLE,
	TEXTURE_RESULT,
	TEXTURE_RESULTWORD,
	TEXTURE_RESULTTIME,
	TEXTURE_RESULTNUM,
	TEXTURE_HEAL,
	TEXTURE_MISSILE,
	TEXTURE_HATENA,
	TEXTURE_FADE,
	TEXTURE_GAUGE,
	TEXTURE_SKY,
	TEXTURE_SKYRE,
	TEXTURE_SKY2,
	TEXTURE_TITLE_CAR_B,
	TEXTURE_TITLE_CAR_CY,
	TEXTURE_TITLE_CAR_R,
	TEXTURE_TITLE_PLAYER,
	TEXTURE_GOAL,
	TEXTURE_DIED,
	TEXTURE_PAUSE,
	TEXTURE_PAUSE_TITLE,
	TEXTURE_PAUSE_RESUME,
	TEXTURE_END,
	TEXTURE_PLAY,
	TEXTURE_HELP,
	TEXTURE_EXPLAIN1,
	TEXTURE_EXPLAIN2,
	TEXTURE_EFFECT,
	TEXTURE_P_ENTER,
	TEXTURE_YOUR_SCORE,
	TEXTURE_DOKURO,
	TEXTURE_DOG,
	TEXTURE_RANKING,
	TEXTURE_TITLE_RANKING,
	TEXTURE_START_READY,
	TEXTURE_START_GO,
	TEXTURE_MAX
}TEXTURE_NUM;

typedef struct
{
	int patternNum;
	int patternW;
	int patternH;
	int tcx;
	int tcy;
}TEXPATTERN;


typedef struct
{
	int patternNum;
	int patternW;
	int patternH;
	int tcx;
	int tcy;
}PATTERN_P;

typedef struct
{
	D3DXVECTOR4 pos;
	D3DCOLOR color;
	D3DXVECTOR2 texcoord;
}VERTEX_2D;

typedef struct
{
	char fileName[256];
	int width;
	int height;
}TEXTURE;

static const TEXTURE g_aTextureFileNames[] = {
	{ "resource/texture/0.png",29,31 },
	{ "resource/texture/01.png",29,31 },
	{ "resource/texture/02.png",29,31 },
	{ "resource/texture/03.png",29,31 },
	{ "resource/texture/04.png",29,31 },
	{ "resource/texture/05.png",29,31 },
	{ "resource/texture/06.png",29,31 },
	{ "resource/texture/07.png",29,31 },
	{ "resource/texture/08.png",29,31 },
	{ "resource/texture/09.png",29,31 },
	{ "resource/texture/car.png",64,64 },
	{ "resource/texture/another_car.png",64,64 },
	{ "resource/texture/another_car_r.png",64,64 },
	{ "resource/texture/another_car_cy.png",64,64 },
	{ "resource/texture/pipo-mapeffect010.png",3120,240 },
	{ "resource/texture/pipo-btleffect157-min.png",960,576 },
	{ "resource/texture/douro1.png",800,600 },
	{ "resource/texture/douro2.png",800,600 },
	{ "resource/texture/danger.png",225,225 },
	{ "resource/texture/heart.png",756,756 },
	{ "resource/texture/speeddown.png",400,300 },
	{ "resource/texture/title.png",600,300 },
	{ "resource/texture/Result.png",800,600 },
	{ "resource/texture/ResultWord.png",800,600 },
	{ "resource/texture/ResultTime.png",800,600 },
	{ "resource/texture/result_num.png",800,400 },
	{ "resource/texture/heal.png",64,64 },
	{ "resource/texture/missile.png",163,309 },
	{ "resource/texture/hatena.png",64,64 },
	{ "resource/texture/fade.png",800,600 },
	{ "resource/texture/gauge.png",30,100 },
	{ "resource/texture/sky.png",800,300 },
	{ "resource/texture/sky_re.png",800,300 },
	{ "resource/texture/sky2.png",800,600 },
	{ "resource/texture/title_car_B.png",402,125 },
	{ "resource/texture/title_car_cy.png",402,125 },
	{ "resource/texture/title_car_R.png",402,125 },
	{ "resource/texture/title_player.png",282,178 },
	{ "resource/texture/goal.png",800,600 },
	{ "resource/texture/died.png",800,600 },
	{ "resource/texture/pause.png",800,600 },
	{ "resource/texture/pause_title.png",200,100 },
	{ "resource/texture/pause_resume.png",200,100 },
	{ "resource/texture/pause_end.png",800,200 }, 
	{ "resource/texture/play.png",800,200 },
	{ "resource/texture/help.png",800,600 },
	{ "resource/texture/explain_1.png",800,600 },
	{ "resource/texture/explain_2.png",800,600 },
	{ "resource/texture/effect000.jpg",80,80 },
	{ "resource/texture/press_enter.png",400,300 },
	{ "resource/texture/your_score.png",400,300 },
	{ "resource/texture/dokuro.png",300,300 },
	{ "resource/texture/dog.png",225,225 },
	{ "resource/texture/ranking.png",400,300 },
	{ "resource/texture/title_ranking.png",800,200 },
	{ "resource/texture/start_ready.png",800,600 },
	{ "resource/texture/start_go.png",800,600 },
};




//=================================================================
//		プロトタイプ宣言
//=================================================================
bool InitPolygon(void);			//ポリゴンの初期化
void UninitPolygon(void);		//ポリゴンの終了処理
void UpdatePolygon(void);		//ポリゴンの更新処理
void DrawPolygon(int texNum, D3DCOLOR color, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, bool bAffine = false);			//ポリゴンの描画処理
TEXPATTERN PatternPolygon(int Count, int Frame, int texWNum, int texHNum, int texW, int texH);
void SetPolygonRotation(float cx, float cy, float angle);
void SetPolygonScale(float cx, float cy, float sx, float sy);

#endif //_POLYGON_H_
