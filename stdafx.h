// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//
#pragma once

#include <SDKDDKVer.h>

//디버깅용 (주석치면 콘솔창이 사라진다)
//#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <Windows.h>
// C 런타임 헤더 파일입니다.
#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
// C++ 런타임 헤더 파일입니다.
#include <iostream>
using namespace std;

// 자주사용하는 STL
#include <string>
#include <vector>
#include <map>

//=============================================================
//	## 내가 만든 헤더파일을 이곳에 추가한다 ##
//=============================================================
#include "commonMacroFunction.h"
#include "input.h"
#include "random.h"
#include "imageManager.h"
#include "util.h"
using namespace MY_UTIL;
#include "sceneManager.h"
#include "iniData.h"
#include "soundManager.h"
#include "TextManager.h"
#include "EffectManager.h"
#include "cameraManager.h"
#include "timeManager.h"
#include "targetingBox.h"
#include "UnitManager.h"
#include "item_Manager.h"
#include "productionManager.h"
#include "DialogueManager.h"
#include "ForagerStatManager.h"
#include "SpawnManager.h"
#include "Astar.h"
#include "saveManager.h"
#include "ItemDatabase.h"

//=============================================================
//	## 싱글톤을 추가한다 ##
//=============================================================
#define INPUT input::getSingleton() //세미콜론 찍으면 작동안함
#define RANDOM random::getSingleton()
#define IMAGEMANAGER imageManager::getSingleton()
#define PLAYERDATA playerData::getSingleton()
#define SCENEMANAGER sceneManager::getSingleton()
#define INIDATA iniData::getSingleton()
#define SOUNDMANAGER soundManager::getSingleton()
#define TEXTMANAGER TextManager::getSingleton()
#define EFFECTMANAGER EffectManager::getSingleton()
#define CAMERA cameraManager::getSingleton()
#define TIME timeManager::getSingleton()
#define UNITMANAGER UnitManager::getSingleton()
#define ITEMMANAGER item_Manager::getSingleton()
#define PRODUCTIONMANAGER productionManager::getSingleton()
#define DIALOGUE DialogueManager::getSingleton()
#define SAVEMANAGER	saveManager::getSingleton()
#define STATMANAGER ForagerStatManager::getSingleton()
#define SPAWNMANAGER SpawnManager::getSingleton()
#define ASTAR Astar::getSingleton()
#define DATABASE ItemDatabase::getSingleton()

//=============================================================
//	## 디파인문 ## (윈도우창 초기화)
//=============================================================
#define WINNAME (LPTSTR)(TEXT("Forager by KGA22 - 김기정, 김으뜸, 전영은, 한유인"))
#define WINSTARTX	0
#define WINSTARTY	0
#define WINSIZEX		1280
#define WINSIZEY		720
#define WINSTYLE		WS_CAPTION | WS_SYSMENU

//=============================================================
//	## 매크로함수 ## (클래스에서 동적할당된 부분 해제)
//=============================================================
#define SAFE_DELETE(p)		{if(p) {delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = NULL;}}

//=============================================================
//	## 전역변수 ##
//=============================================================
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;