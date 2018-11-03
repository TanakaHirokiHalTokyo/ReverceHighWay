//==============================================================================================================
//
//		PLAYERヘッダー
//
//==============================================================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_WIDTH		(64)		//PLAYER幅
#define PLAYER_HEIGHT		(64)		//PLAYER高さ
#define PLAYER_SPEED		(10.0f)		//PLAYERスピード
#define PLAYER_INVINCIBLE	(150)		//2.5秒間無敵
#define HEART_WIDTH			(32)		//体力　幅
#define HEART_HEIGHT		(32)		//体力　高さ
#define HEART_NUM			(5)			//体力	数
#define MISSILE_WIDTH		(32)		//ミサイル　幅
#define MISSILE_HEIGHT		(32)		//ミサイル　高さ
#define MISSILE_SPEED		(5.0f)		//ミサイル　スピード
#define GAUGE_WIDTH			(30)		//ゲージ	幅
#define GAUGE_HEIGHT		(100)		//ゲージ	高さ
#define PLAYER_SPEEDUP		(0.05f)		//スピード上昇値
#define PLAYER_SPEEDDOWN	(-0.15f)	//スピード減速値
#define PLAYER_COOLSHOT		(60 * 5)	//ミサイルクールタイム   5秒間

enum
{
	VEC_LEFT = 1,		//移動方向　左
	VEC_RIGHT,			//移動方向　右
};


typedef struct
{
	D3DXVECTOR2 g_vPos;
	float AnimSpeed;
	bool NowMove;				//左右に移動中かどうか	移動していたら　左右には移動できない
	int MoveVec;				//1:Left 2:Right 方向に移動
	float SideSpeed;			//カウントに使う変数　２００カウントしたらとめる
	bool Alive;
	int CoolTime;				//復活までのクールタイム
	int Life;					//体力
	int InvicibleTime;			//無敵時間
	bool Invicible;				//無敵かどうか
	bool NowShot;				//対向車に当たってからクールタイムカウント後、false
	int CoolShot;				//クールタイム計測
	bool bCoolShot;				//クールタイムが終わったか
	D3DXVECTOR2 M_pos;			//ミサイル位置
	int DeadNum;
}PLAYER;

static PLAYER player;

void InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
float ReturnSpeed(void);
bool AlivePlayer(void);
void DestroyPlayer(void);
D3DXVECTOR2 GetPosPlayer(void);
bool ReturnInvicible(void);
void DrawLife(void);
void DrawMissile(void);
int ReturnPlayerLife(void);
D3DXVECTOR2 GetPosMissile(void);
void DestroyMissile(void);
bool NowShot(void);
void bCoolShot(void);
void LifeHeal(void);
int ReturnDeadNum(void);

#endif