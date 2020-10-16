#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	SCENEMANAGER->deleteScene("게임 화면");
	SCENEMANAGER->addScene("게임 화면", new gameScene);

	//세이브 버튼 칸 렉트
	saveRc = RectMake(100, 100, 100, 100);

	// 마우스 숨기기
	ShowCursor(false);

	// 이미지 등록 (추후 로딩 구현시 옮겨질 것들)
	IMAGEMANAGER->addImage("Logo", "Images/이미지/img_Logo.bmp", 300, 180, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BtnCredit", "Images/이미지/GUI/img_UI_BtnCredit.bmp", 213, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BtnExit", "Images/이미지/GUI/img_UI_BtnExit.bmp", 213, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BtnSetting", "Images/이미지/GUI/img_UI_BtnSetting.bmp", 213, 104, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GameSlot", "Images/이미지/GUI/img_UI_GameSlotBoundary.bmp", 227, 227, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("GameSlotInner", "Images/이미지/GUI/img_UI_GameSlotInner.bmp", 227, 227, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleBG", "Images/이미지/img_Background.bmp", 1960, 1280, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("TitleCursor", "Images/이미지/GUI/커서.bmp", 15, 15, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("BowCursor", "Images/이미지/GUI/img_UI_bowCursor.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Balloon", "Images/이미지/GUI/img_UI_DialogueBalloon.bmp", 214, 67, true, RGB(255, 0, 255));

	// 커서 반응형 이미지 설정
	for (int i = 0; i < BUTTON_MAX / 2; i++) {
		RECT slotRC = RectMakeCenter(WINSIZEX / 2 - 400 + i * 400, 360, 227, 227);
		RECT btnRC = RectMakeCenter(WINSIZEX / 2 - 300 + i * 300, WINSIZEY - 120, 213, 104);

		_button[i + BUTTON_MAX / 2].init(slotRC, 18, 4, "GameSlot", "GameSlotInner", 100);
		if (i == 0) _button[i].init(btnRC, 12, 3, "BtnSetting");
		else if (i == 1) _button[i].init(btnRC, 12, 3, "BtnCredit");
		else if (i == 2) _button[i].init(btnRC, 12, 3, "BtnExit");
	}

	// 타겟팅 박스 설정
	_targetingBox = new targetingBox;
	_targetingBox->init();
	
	gameSlotCheck = 0;

	if (SOUNDMANAGER->isPlaySound("배경음악"))
	{
		SOUNDMANAGER->stop("배경음악");
	}
	SOUNDMANAGER->play("배경음악");

	gameOptionCheck = false;

	_game_setting = new gamesetting;
	_game_setting->init();

	_gameslotOne = false;
	_gameslotTwo = false;
	_gameslotThree = false;
	CheckGameFile();

	return S_OK;
}

void startScene::release()
{
	if (SCENEMANAGER->get_ischeck()){
		// 타겟팅 박스 제거
		SAFE_DELETE(_targetingBox);
	}
}

void startScene::update()
{
	// 마우스 호버 체크
	CheckCursorOnButton();
	
	// 마우스 클릭 체크
	CheckButtonClick();


	// 발걸음 이펙트 테스트용
	if (testWalkEffectCount++ >= testWalkEffectInterval) {
		testWalkEffectCount = 0;
		EFFECTMANAGER->ShowEffectAlphaSize("Walk1", _ptMouse, 0, 0.25f, 0, 150);
	}

	if (gameOptionCheck) {
		_game_setting->update();
	}
	EFFECTMANAGER->update();
}

void startScene::render()
{

	// 파란 배경 렌더
	IMAGEMANAGER->findImage("TitleBG")->render(getMemDC(), -300, -300);

	// 로고 렌더
	IMAGEMANAGER->findImage("Logo")->render(getMemDC(), WINSIZEX / 2 - 150, 0);


	// 게임슬롯 렌더
	for (int i = 0; i < BUTTON_MAX; i++) {
		_button[i].render(getMemDC());
	}

	for (int i = 3; i < BUTTON_MAX; i++) {
		int centerX = _button[i].GetRect().left + (_button[i].GetRect().right - _button[i].GetRect().left) / 2;
		int centerY = _button[i].GetRect().top + (_button[i].GetRect().bottom- _button[i].GetRect().top) / 2;
		POINT ptPos = { centerX , centerY - 15 };
		if (i == 3) {
			if (!_gameslotOne)
				TEXTMANAGER->ShowText(getMemDC(), false, "새게임", ptPos, 35, 1, RGB(255, 255, 255), true, RGB(0, 0, 0));
			else
				TEXTMANAGER->ShowText(getMemDC(), false, "이어하기", ptPos, 35, 1, RGB(255, 255, 255), true, RGB(0, 0, 0));
		}
		if (i == 4) {
			if (!_gameslotTwo)
				TEXTMANAGER->ShowText(getMemDC(), false, "새게임", ptPos, 35, 1, RGB(255, 255, 255), true, RGB(0, 0, 0));
			else
				TEXTMANAGER->ShowText(getMemDC(), false, "이어하기", ptPos, 35, 1, RGB(255, 255, 255), true, RGB(0, 0, 0));
		}
		if (i == 5) {
			if (!_gameslotThree)
				TEXTMANAGER->ShowText(getMemDC(), false, "새게임", ptPos, 35, 1, RGB(255, 255, 255), true, RGB(0, 0, 0));
			else
				TEXTMANAGER->ShowText(getMemDC(), false, "이어하기", ptPos, 35, 1, RGB(255, 255, 255), true, RGB(0, 0, 0));
		}
	}


	EFFECTMANAGER->render(getMemDC());

	// 타겟팅 박스 렌더
	_targetingBox->render(getMemDC());

	if (gameOptionCheck) {
		_game_setting->render(getMemDC());
	}

	// 커서 렌더
	IMAGEMANAGER->findImage("TitleCursor")->render(getMemDC(), _ptMouse.x, _ptMouse.y);


}

void startScene::CheckGameFile()
{
	LPCSTR slotOne = "save/tile_save1.map";
	LPCSTR slotTwo = "save/tile_save2.map";
	LPCSTR slotThree = "save/tile_save3.map";

	DWORD dwAttrib = GetFileAttributes(slotOne);
	_gameslotOne = (!(dwAttrib & FILE_ATTRIBUTE_DEVICE) &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	dwAttrib = GetFileAttributes(slotTwo);
	_gameslotTwo = (!(dwAttrib & FILE_ATTRIBUTE_DEVICE) &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
	dwAttrib = GetFileAttributes(slotThree);
	_gameslotThree = (!(dwAttrib & FILE_ATTRIBUTE_DEVICE) &&
		!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));

}
void startScene::CheckCursorOnButton()
{
	bool _cursor = false;
	for (int i = 0; i < BUTTON_MAX; i++)
	{
		_button[i].update();

		// 버튼 위에 커서
		if (PtInRect(&_button[i].GetRect(), _ptMouse)) {
			_targetingBox->SetTarget(_button[i].GetRect(), 4, i);
			_button[i].CursorIn();
			_cursor = true;
		}
		else
			_button[i].CursorOut();
	}
	if (!_cursor)
		_targetingBox->CursorOut();

	_targetingBox->update();

}




void startScene::CheckButtonClick()
{
	if (INPUT->GetKeyDown(VK_RBUTTON)) {
		EFFECTMANAGER->ShowEffectFrame("DigSmoke", _ptMouse);
	}

	// 버튼 클릭
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (!PtInRect(&_game_setting->GetRcWindow(), _ptMouse) && gameOptionCheck) {
			gameOptionCheck = false;
		}
		if (!gameOptionCheck) {
			for (int i = 0; i < BUTTON_MAX; i++)
			{
				if (PtInRect(&_button[i].GetRect(), _ptMouse))
				{
					SOUNDMANAGER->play("클릭");
					switch (i) {
					case BTN::SETTING:					// 환경설정 창
						//SCENEMANAGER->loadScene("게임 화면"); 
						gameOptionCheck = true;
						break;	
					case BTN::CREDIT:					// 크레딧 창
						//추후 추가
						break;	
					case BTN::EXIT:		exit(0); break;	// 게임 종료

					case BTN::SLOT1:

						SAVEMANAGER->My_Game_save_file_item = "save/item_save1.map";
						SAVEMANAGER->My_Game_save_file_equip = "save/equip_save1.map";
						SAVEMANAGER->My_Game_save_file_tile = "save/tile_save1.map";
						SAVEMANAGER->My_Game_save_file_unit = "save/unit_save1.map";
						SAVEMANAGER->My_Game_save_file_player = "save/player_save1";
						SCENEMANAGER->loadScene("게임 화면");
						break;	// 게임 슬롯 1

					case BTN::SLOT2:

						SAVEMANAGER->My_Game_save_file_item = "save/item_save2.map";
						SAVEMANAGER->My_Game_save_file_equip = "save/equip_save2.map";
						SAVEMANAGER->My_Game_save_file_tile = "save/tile_save2.map";
						SAVEMANAGER->My_Game_save_file_unit = "save/unit_save2.map";
						SAVEMANAGER->My_Game_save_file_player = "save/player_save2";
						SCENEMANAGER->loadScene("게임 화면");

						break;	// 게임 슬롯 2
					case BTN::SLOT3:

						SAVEMANAGER->My_Game_save_file_item = "save/item_save3.map";
						SAVEMANAGER->My_Game_save_file_equip = "save/equip_save3.map";
						SAVEMANAGER->My_Game_save_file_tile = "save/tile_save3.map";
						SAVEMANAGER->My_Game_save_file_unit = "save/unit_save3.map";
						SAVEMANAGER->My_Game_save_file_player = "save/player_save3";
						SCENEMANAGER->loadScene("게임 화면");
						break;	// 게임 슬롯 3
					}
				}
			}
		}
	}
	//우측 클릭시 삭제
	//if (INPUT->GetKeyDown(VK_RBUTTON))
	//{
	//}
}
