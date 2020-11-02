#include "stdafx.h"
#include "treasureBox.h"

void treasureBox::setTreasureBox(string p_imgKey, string p_itemRewardKey, POINT p_ptPos, RECT* p_rcPlayer)
{
	tileIndex = 0;
	objKey = p_imgKey;
	dropItem.itemKey = p_itemRewardKey;
	_rcPlayer = p_rcPlayer;

	// Object 정보 셋팅
	tag = TAG::NPC;
	layer = LAYER::OBJECT;
	x = p_ptPos.x;
	y = p_ptPos.y;
	rc = RectMakeCenter(x, y, 140, 132);

	// 스테이터스 셋팅
	_isNear = false;


	maxHp = 1000000;
	currentHp = maxHp;
}

void treasureBox::update()
{
	CheckNearPlayer();
	CheckKey();
}

void treasureBox::CheckNearPlayer()
{

	POINT t_ptRelMouse = _ptMouse;
	POINT t_ptPlayerPos = { CAMERA->GetRelativeX(_rcPlayer->left + (_rcPlayer->right - _rcPlayer->left) / 2),
							CAMERA->GetRelativeY(_rcPlayer->top + (_rcPlayer->bottom - _rcPlayer->top) / 2) };
	
	if (abs(t_ptPlayerPos.x - CAMERA->GetRelativeX(GetCenterX())) <= MAXTOUCHDISTANCE && abs(t_ptPlayerPos.y - CAMERA->GetRelativeY(GetCenterY())) <= MAXTOUCHDISTANCE)
	{
		if (abs(t_ptPlayerPos.x - t_ptRelMouse.x) <= MAXTOUCHDISTANCE && abs(t_ptPlayerPos.y - t_ptRelMouse.y) <= MAXTOUCHDISTANCE)
		{
			_isNear = true;
			return;
		}
	}
	_isNear = false;
}

void treasureBox::CheckKey()
{
	if (_isNear) {
		if (INPUT->GetKeyDown('E')) {
				GiveReward();
		}
	}
}

void treasureBox::GiveReward()
{

	TEXTMANAGER->ShowNotifyText("아주 좋은 보상을 획득했다!", { WINSIZEX / 2, WINSIZEY / 2 - 190 }, 50, RGB(255, 255, 255), RGB(0, 0, 0), 3);
	EFFECTMANAGER->ShowEffectFrame("treasure", { GetCenterX(), GetCenterY() }, 5, 2.0f, true);
	
	int t_interval = 25;
	for (int i = 0; i < 10; i++) {
		if(i % 2 == 0)
			UNITMANAGER->AddUnits("img_game_money_icon", { GetCenterX() + i * t_interval, GetCenterY() });
		else
			UNITMANAGER->AddUnits("img_game_money_icon", { GetCenterX() - i * t_interval, GetCenterY() });
	}

	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0)
			UNITMANAGER->AddUnits("img_game_money_icon", { GetCenterX(), GetCenterY() - i * t_interval });
		else
			UNITMANAGER->AddUnits("img_game_money_icon", { GetCenterX(), GetCenterY() + i * t_interval });
	}

	for (int i = 0; i < 10; i++) {
		if (i % 2 == 0)
			UNITMANAGER->AddUnits("img_game_money_icon", { GetCenterX() + i * t_interval, GetCenterY() - i * t_interval });
		else
			UNITMANAGER->AddUnits("img_game_money_icon", { GetCenterX() - i * t_interval, GetCenterY() + i * t_interval });
	}
	
	currentHp = 0;

}

void treasureBox::render(HDC hdc)
{

	int relX = CAMERA->GetRelativeX(rc.left);
	int relY = CAMERA->GetRelativeY(rc.top);

	IMAGEMANAGER->render(objKey, hdc, relX, relY, CAMERA->GetZoom());
	if (_isNear) {
		
		IMAGEMANAGER->render("E", hdc, relX + 40, relY - 20, CAMERA->GetZoom());
	}
}
