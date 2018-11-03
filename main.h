//===================================================================================================
//		メインヘッダ
//																	2017/06/05			田中　大輝
//===================================================================================================
#ifndef _MAIN_H_
#define _MAIN_H_

#include <Windows.h>
#define DIRECTINPUT_VERSION	(0x0800)	
#include <dinput.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<time.h>
#include <stdio.h>
#include <stdlib.h>

#define SCREEN_WIDTH	(800)
#define SCREEN_HEIGHT	(600)
#define GAME_FPS		(60)
#define WINDOW_NAME		"Reverce Highway"
#define CLASS_NAME		"さんぷる"
#define WINDOW_STYLE	WS_OVERLAPPEDWINDOW


LPDIRECT3DDEVICE9 GetD3DDevice(void);
void EndLoop(void);

#include "Debug.h"
#include "input.h"
#include "sound.h"
#include "PressEnter.h"
#include "Progress.h"
#include "Polygon.h"
#include "Effect.h"
#include "number.h"
#include "background.h"
#include "player.h"
#include "ReverceCar.h"
#include "Hit.h"
#include "Explosion.h"
#include "Heal.h"
#include "danger.h"
#include "time.h"
#include "item.h"
#include "Pause.h"
#include "FinishGame.h"
#include "StartGame.h"
#include "Title.h"
#include "Explain.h"
#include "Ranking.h"
#include "Result.h"
#include "Game.h"
#include "Scene.h"




#endif // !_MAIN_H_
