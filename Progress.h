//===================================================================================================
//		�i�s�x�w�b�_�[
//																	
//===================================================================================================
#ifndef _PROGRESS_H_
#define _PROGRESS_H_


#define PROGRESS	(70000)		//�Q�[���N���A���邽�߂ɐi�܂Ȃ��Ƃ����Ȃ����� 50000
//#ifdef _DEBUG
//#define PROGRESS	(7000)
//#endif // DEBUG

#define TIME_SCORE	(25)		//Time Score
#define LIFE_SCORE	(50)		//Life Score
#define DEAD_POINT	(46)

void InitProgress(void);
void UninitProgress(void);
void UpdateProgress(void);
void DrawProgress(void);

#endif