#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## 초기화 ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	
	/*앞으로 메인게임은 각각의 씬들만 관리를 한다*/
	/*이곳에서 각각의 씬들을 추가하고 현재씬을 설정한다*/

	/*씬추가*/
	SCENEMANAGER->addScene("로딩 화면", new loadingScene);
	SCENEMANAGER->addScene("시작 화면", new startScene);
	SCENEMANAGER->addScene("게임 화면", new gameScene);

	/*사운드 추가*/
	/*배경음악*/
	SOUNDMANAGER->addSound("배경음악", "Sound/BGM/FORAGER - FULL OST - COMPLETE SOUNDTRACK.mp3", true, true);
	
	/*효과음*/
	SOUNDMANAGER->addSound("커서음1", "Sound/\SoundEffect/sound_sfx_slotMouseOn1.mp3");
	SOUNDMANAGER->addSound("커서음2", "Sound/\SoundEffect/sound_sfx_slotMouseOn2.mp3");
	SOUNDMANAGER->addSound("건물커서", "Sound/\SoundEffect/sound_sfx_buildTabChoice.mp3");
	SOUNDMANAGER->addSound("건물상호작용", "Sound/\SoundEffect/sound_sfx_inventoryShow2.mp3");
	SOUNDMANAGER->addSound("클릭", "Sound/\SoundEffect/sound_sfx_ok1.mp3");

	/*현재씬*/
	//SCENEMANAGER->loadScene("로딩 화면");
	SCENEMANAGER->loadScene("시작 화면");

	RECT rc;
	POINT p1, p2;

	return S_OK;
}

//=============================================================
//	## 해제 ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
}

//=============================================================
//	## 업데이트 ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	
	//씬매니져 업데이트
	SCENEMANAGER->update();

	//사운드매니져 업데이트 (이게 없으면 사운드매니져 제대로 동작하지 않는다!!!)
	SOUNDMANAGER->update();
}

//=============================================================
//	## 렌더 ## render()
//=============================================================
void mainGame::render()
{
	//흰색 빈 비트맵 (이것은 렌더에 그냥 두기)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================
	
	//글자색 배경 없애기
	SetBkMode(getMemDC(), TRANSPARENT);

	//씬매니져 렌더
	SCENEMANAGER->render();

	//타임매니져 렌더
	TIME->render(getMemDC());
	
//=============================================================
	//백버퍼의 내용을 화면DC에 그린다 (이것도 렌더에 그냥 두기)
	this->getBackBuffer()->render(getHDC(), 0, 0);
}

