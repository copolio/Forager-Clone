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

	/*사운드 추가*/
/*배경음악*/
	SOUNDMANAGER->addSound("배경음악", "Sound/BGM/FORAGER - FULL OST - COMPLETE SOUNDTRACK.mp3", true, true);

	/*효과음*/
	SOUNDMANAGER->addSound("커서음1", "Sound/\SoundEffect/sound_sfx_slotMouseOn1.mp3");
	SOUNDMANAGER->addSound("커서음2", "Sound/\SoundEffect/sound_sfx_slotMouseOn2.mp3");
	SOUNDMANAGER->addSound("건물커서", "Sound/\SoundEffect/sound_sfx_buildTabChoice.mp3");
	SOUNDMANAGER->addSound("건물상호작용", "Sound/\SoundEffect/sound_sfx_itemMadeWindowOpen.mp3");
	SOUNDMANAGER->addSound("클릭", "Sound/\SoundEffect/sound_sfx_ok1.mp3");
	SOUNDMANAGER->addSound("인벤토리오픈", "Sound/\SoundEffect/sound_sfx_inventoryShow1.mp3");
	SOUNDMANAGER->addSound("인벤토리닫기", "Sound/\SoundEffect/sound_sfx_inventoryHide.mp3");
	SOUNDMANAGER->addSound("건설탭클릭", "Sound/\SoundEffect/sound_sfx_buildTabSlotClick.mp3");
	SOUNDMANAGER->addSound("건설탭선택", "Sound/\SoundEffect/sound_sfx_buildTabChoice.mp3");
	SOUNDMANAGER->addSound("건설성공", "Sound/\SoundEffect/sound_sfx_buildSuccess.mp3");
	SOUNDMANAGER->addSound("건설실패", "Sound/\SoundEffect/sound_sfx_buildFail.mp3");
	SOUNDMANAGER->addSound("건설취소", "Sound/\SoundEffect/sound_sfx_buildTabSlotClick.mp3");
	SOUNDMANAGER->addSound("생산시작", "Sound/\SoundEffect/sound_sfx_itemMadeStart.mp3");
	SOUNDMANAGER->addSound("생산완료", "Sound/\SoundEffect/sound_sfx_itemMadeSuccess.mp3");
	SOUNDMANAGER->addSound("아이템탄생", "Sound/\SoundEffect/sound_sfx_createObject.mp3");
	SOUNDMANAGER->addSound("아이템충돌", "Sound/\SoundEffect/sound_sfx_itemGet1.mp3");
	SOUNDMANAGER->addSound("근접무기", "Sound/\SoundEffect/sound_sfx_weaponSwing1.mp3");
	SOUNDMANAGER->addSound("원거리무기", "Sound/\SoundEffect/sound_sfx_weaponSwing2.mp3");
	SOUNDMANAGER->addSound("과일타격", "Sound/\SoundEffect/sound_sfx_berryHit1.mp3");
	SOUNDMANAGER->addSound("과일파괴", "Sound/\SoundEffect/sound_sfx_berryDestory.mp3");
	SOUNDMANAGER->addSound("나무타격", "Sound/\SoundEffect/sound_sfx_treeHit1.mp3");
	SOUNDMANAGER->addSound("나무파괴", "Sound/\SoundEffect/sound_sfx_treeDestroy.mp3");
	SOUNDMANAGER->addSound("바위타격", "Sound/\SoundEffect/sound_sfx_rockHit1.mp3");
	SOUNDMANAGER->addSound("바위파괴", "Sound/\SoundEffect/sound_sfx_rockDestory.mp3");
	SOUNDMANAGER->addSound("플레이어걸음1", "Sound/\SoundEffect/sound_sfx_footStep1.mp3");
	SOUNDMANAGER->addSound("플레이어걸음2", "Sound/\SoundEffect/sound_sfx_footStep2.mp3");
	SOUNDMANAGER->addSound("레벨업", "Sound/\SoundEffect/sound_sfx_levelUp.mp3");
	SOUNDMANAGER->addSound("해골사망소리", "Sound/\SoundEffect/skulldeadSound.mp3");
	SOUNDMANAGER->addSound("황소사망소리", "Sound/\SoundEffect/cowDeadSound.mp3");
	SOUNDMANAGER->addSound("유령무기발사소리", "Sound/\SoundEffect/wraithShootSound.mp3");
	SOUNDMANAGER->addSound("유령무기맞는소리", "Sound/\SoundEffect/gotHitByWraith.mp3");
	SOUNDMANAGER->addSound("피찰때소리", "Sound/\SoundEffect/plusBlooding.mp3");
	SOUNDMANAGER->addSound("무맞을때소리", "Sound/\SoundEffect/muBossCry.mp3");
	SOUNDMANAGER->addSound("악마불지질때소리", "Sound/\SoundEffect/fireBrass.mp3");
	

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

