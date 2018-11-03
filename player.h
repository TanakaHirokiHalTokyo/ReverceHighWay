//==============================================================================================================
//
//		PLAYER�w�b�_�[
//
//==============================================================================================================

#ifndef _PLAYER_H_
#define _PLAYER_H_

#define PLAYER_WIDTH		(64)		//PLAYER��
#define PLAYER_HEIGHT		(64)		//PLAYER����
#define PLAYER_SPEED		(10.0f)		//PLAYER�X�s�[�h
#define PLAYER_INVINCIBLE	(150)		//2.5�b�Ԗ��G
#define HEART_WIDTH			(32)		//�̗́@��
#define HEART_HEIGHT		(32)		//�̗́@����
#define HEART_NUM			(5)			//�̗�	��
#define MISSILE_WIDTH		(32)		//�~�T�C���@��
#define MISSILE_HEIGHT		(32)		//�~�T�C���@����
#define MISSILE_SPEED		(5.0f)		//�~�T�C���@�X�s�[�h
#define GAUGE_WIDTH			(30)		//�Q�[�W	��
#define GAUGE_HEIGHT		(100)		//�Q�[�W	����
#define PLAYER_SPEEDUP		(0.05f)		//�X�s�[�h�㏸�l
#define PLAYER_SPEEDDOWN	(-0.15f)	//�X�s�[�h�����l
#define PLAYER_COOLSHOT		(60 * 5)	//�~�T�C���N�[���^�C��   5�b��

enum
{
	VEC_LEFT = 1,		//�ړ������@��
	VEC_RIGHT,			//�ړ������@�E
};


typedef struct
{
	D3DXVECTOR2 g_vPos;
	float AnimSpeed;
	bool NowMove;				//���E�Ɉړ������ǂ���	�ړ����Ă�����@���E�ɂ͈ړ��ł��Ȃ�
	int MoveVec;				//1:Left 2:Right �����Ɉړ�
	float SideSpeed;			//�J�E���g�Ɏg���ϐ��@�Q�O�O�J�E���g������Ƃ߂�
	bool Alive;
	int CoolTime;				//�����܂ł̃N�[���^�C��
	int Life;					//�̗�
	int InvicibleTime;			//���G����
	bool Invicible;				//���G���ǂ���
	bool NowShot;				//�Ό��Ԃɓ������Ă���N�[���^�C���J�E���g��Afalse
	int CoolShot;				//�N�[���^�C���v��
	bool bCoolShot;				//�N�[���^�C�����I�������
	D3DXVECTOR2 M_pos;			//�~�T�C���ʒu
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