#include "stdafx.h"
#include "ForagerPlayer.h"
#include "quick_slot.h"

HRESULT ForagerPlayer::init()
{
	tileIndex = 0;
	_dir = 0;

	// 위치 초기화
	objKey = "Player";
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 30, 41);
	_playerTilePos = FindPlayerTilePos();

	// Object 정보 초기화
	tag = TAG::PLAYER;
	layer = LAYER::OBJECT;
	_handleItem = DATABASE->GetItem("pickaxeDrop");

	// 스탯 초기화
	maxHp = 1;
	currentHp = 1;
	exp = 0;
	Atk = 0;
	_bowPowerGauge = 0.1f;

	//플레이어 상태 불값 초기화 
	_isLeft = false;
	_isUp = false;
	_isMoveHorizon = false;
	_isMoveVertical = false;
	_isMoveRotate = false;
	_isRun = false;
	_isHammering = false;
	_isBowPulling = false;
	_isGotDamage = false;
	
	_balloonRatio = 0.2f;			// 에너지 비율이 몇일때 말풍선이 나올지
	_cntBalloonMax = 1200;			// 말풍선 출력 카운트
	_cntBalloon = 0;				// 말풍선 카운트

	_cntBowDelay = 0;			// 현재 화살 연사 딜레이 수치
	_bowDelay = 20;				// 약 0.2초
	_canBowFire = true;
	_spinAngle = 0.0f;
	_state = STATE::IDLE;
	_priorState = _state;
	_angle = 0.0f;
	// 무기 위치 초기화
	_rcHammer = RectMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 - 28, 56, 56);

	//기본 플레이어 이미지
	IMAGEMANAGER->addFrameImage("playerStop", "Images/이미지/플레이어/player_idle_frame.bmp", 120,112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRUN", "Images/이미지/플레이어/player_run_frame.bmp", 160, 112, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->findImage("playerRUN")->initForRotateImage(true);
	IMAGEMANAGER->addFrameImage("playerWork", "Images/이미지/플레이어/player_hammering_frame.bmp", 130, 100, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att1", "Images/이미지/아이템/곡괭이질1.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att2", "Images/이미지/아이템/곡괭이질2.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att3", "Images/이미지/아이템/곡괭이질3.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("pickaxe_att4", "Images/이미지/아이템/곡괭이질4.bmp", 255, 140, 3, 2, true, RGB(255, 0, 255));

	IMAGEMANAGER->addFrameImage("sword_att1", "Images/이미지/아이템/sword_att1.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att2", "Images/이미지/아이템/sword_att2.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att3", "Images/이미지/아이템/sword_att3.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword_att4", "Images/이미지/아이템/sword_att4.bmp", 342, 176, 3, 2, true, RGB(255, 0, 255));
	//곡괭이 이미지
	IMAGEMANAGER->addFrameImage("Hammer1", "Images/이미지/아이템/곡괭이1.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Hammer2", "Images/이미지/아이템/곡괭이2.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Hammer3", "Images/이미지/아이템/곡괭이3.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Hammer4", "Images/이미지/아이템/곡괭이4.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword1", "Images/이미지/아이템/sword1.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword2", "Images/이미지/아이템/sword2.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword3", "Images/이미지/아이템/sword3.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("sword4", "Images/이미지/아이템/sword4.bmp", 56, 112, 1, 2, true, RGB(255, 0, 255));

	// 이미지 파싱
	_foragerIdle = IMAGEMANAGER->findImage("playerStop");
	_foragerRun = IMAGEMANAGER->findImage("playerRUN");
	_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att1");
	_playerHammering = IMAGEMANAGER->findImage("playerWork");

	_handleWeapon = IMAGEMANAGER->findImage("Hammer1");
	_bow = IMAGEMANAGER->findImage("bowDrop1");

	//프레임이미지 애니메이션 관련 변수 초기화 
	_count = 0;
	_index = 0;
	_hitDelayCount = 1;

	//회전관련 변수 초기화 
	_Acount = 0;
	_spinCount = 0;
	_spinSpeed = 0;


	//플레이어 상태 불값 초기화 
	_isLeft = false;
	_isUp = false;
	_isMoveHorizon = false;
	_isMoveVertical = false;
	_isMoveRotate = false;
	_isRun = false;
	_isHammering = false;

	maxHp = 1;
	currentHp = 1;
	STATMANAGER->init();

	// 걷기 애니메이션 초기화
	_footWalkCount = 0;
	_footWalkEffectInterval = 12;

	// 기타
	inven_open = false;

	_startBalloon = false;		// 시작 말풍선
	_cntDelayStartBalloon = 0;
	_delayStartBalloon = 240;
	_powerOverwhelmingTime = 1000;

	STATMANAGER->SetLinkPlayer(this);

	return S_OK;
}

void ForagerPlayer::release()
{
}

void ForagerPlayer::update()
{
	BlinkProcess();		// 무적 깜빡이 딜레이 계산
	animation();		// 애니메이션 활성화
	if (_handleItem.weaponType == WeaponType::BOW && !inven_open) bowAnimation();
	_rcHammer = RectMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 - 28, 56, 56); // 위치 파싱


	CalcBowDelay();		// 화살 연사 체크
	weaponCheck();		// 현재 무기 체크
	hungryBalloon();	// 배고픔 수치
	CAMERA->targetFollow(rc.left, rc.top); // 카메라 추적
	STATMANAGER->update();				   // 스테이터스 업데이트
	STATMANAGER->setinvenopen(inven_open); // 인벤토리 체크

	// 플레이어 움직임 & 충돌 처리
	if (!inven_open) {
		PlayerControll();
		playerMove();
		playerLookingDirection();
		CheckPlayerTile();
		CheckCollision();
	}

	// 상태 변화 체크
	if (_priorState != _state) {
		_count = 0;
		_index = 0;
		_hitDelayCount = 0;
	}
	_priorState = _state;


	if (INPUT->GetKeyDown(VK_F5)) {
		ITEMMANAGER->getvInventory_info()[0]->count += 100;
		ITEMMANAGER->getvInventory_info()[0]->_item = DATABASE->GetItem("rockDrop");

		 ITEMMANAGER->getvInventory_info()[1]->count += 100;
		 ITEMMANAGER->getvInventory_info()[1]->_item = DATABASE->GetItem("treeDrop");

		 ITEMMANAGER->getvInventory_info()[2]->count += 100;
		 ITEMMANAGER->getvInventory_info()[2]->_item = DATABASE->GetItem("berryDrop");

		 ITEMMANAGER->getvInventory_info()[3]->count += 100;
		 ITEMMANAGER->getvInventory_info()[3]->_item = DATABASE->GetItem("goldOreDrop");

		 ITEMMANAGER->getvInventory_info()[4]->count += 100;
		 ITEMMANAGER->getvInventory_info()[4]->_item = DATABASE->GetItem("coalDrop");

		 ITEMMANAGER->getvInventory_info()[5]->count += 100;
		 ITEMMANAGER->getvInventory_info()[5]->_item = DATABASE->GetItem("ironOreDrop");

		 ITEMMANAGER->getvInventory_info()[6]->count += 100;
		 ITEMMANAGER->getvInventory_info()[6]->_item = DATABASE->GetItem("ironBarDrop");

		 ITEMMANAGER->getvInventory_info()[7]->count += 100;
		 ITEMMANAGER->getvInventory_info()[7]->_item = DATABASE->GetItem("goldBarDrop");

		 ITEMMANAGER->getvInventory_info()[8]->count += 100;
		 ITEMMANAGER->getvInventory_info()[8]->_item = DATABASE->GetItem("high_class_SteelDrop");

		 ITEMMANAGER->getvInventory_info()[9]->count += 100;
		 ITEMMANAGER->getvInventory_info()[9]->_item = DATABASE->GetItem("SteelhDrop");

		 ITEMMANAGER->getvInventory_info()[10]->count += 100;
		 ITEMMANAGER->getvInventory_info()[10]->_item = DATABASE->GetItem("roast_fishDrop");

		 ITEMMANAGER->getvInventory_info()[11]->count += 100;
		 ITEMMANAGER->getvInventory_info()[11]->_item = DATABASE->GetItem("fishDrop");

		 ITEMMANAGER->getvInventory_info()[12]->count += 100;
		 ITEMMANAGER->getvInventory_info()[12]->_item = DATABASE->GetItem("threadDrop");

		ITEMMANAGER->setMoney(ITEMMANAGER->getMoney() + 100);
		_quick->quick_slot_update();

	}


}

void ForagerPlayer::render(HDC hdc)
{
	if (_isGotDamage) {
		if (_count % 5 == 0) 
			renderPlayer(hdc);
	}
	else 
		renderPlayer(hdc);
}


void ForagerPlayer::renderPlayer(HDC hdc)
{
	int relX = CAMERA->GetRelativeX(rc.left);
	int relY = CAMERA->GetRelativeY(rc.top);
	int relWeaponX = CAMERA->GetRelativeX(_rcHammer.left);
	int relWeaponY = CAMERA->GetRelativeY(_rcHammer.top);
	float zoomRate = CAMERA->GetZoom();

	switch (_state)
	{
		case IDLE:
			_foragerIdle->frameRender(hdc, relX, relY, zoomRate);
			break;

		case RUN:
			_foragerRun->frameRender(hdc, relX, relY, zoomRate);
			break;

		case ROTATE:
			_foragerRun->rotateFrameRender(hdc, relX + 20, relY + 20, _foragerRun->getFrameX(), _foragerRun->getFrameY(), _spinAngle * PI / 180.0f);
			if (_handleItem.weaponType == WeaponType::PICKAXE)
				_handleWeapon->rotateFrameRender(hdc, relWeaponX, relWeaponY + 20, 0, _dir, _spinAngle * PI / 180.0f);
			break;

		case HAMMERING:
			_playerHammering->frameRender(hdc, relX, relY, zoomRate);
			if (_handleItem.weaponType == PICKAXE  ) {
				_foragerAttacking->frameRender(hdc, CAMERA->GetRelativeX(rc.left - 16), CAMERA->GetRelativeY(rc.top - 20), zoomRate);
			}
			else if (_handleItem.weaponType == SWORD) {
				_foragerAttacking->frameRender(hdc, CAMERA->GetRelativeX(rc.left-30), CAMERA->GetRelativeY(rc.top - 17), zoomRate);
			}
			break;
	}

	if (_state != ROTATE && _state != HAMMERING)
	{
		if (_handleItem.weaponType == PICKAXE || _handleItem.weaponType == SWORD) {
			if(_isLeft)
				_handleWeapon->frameRender(hdc, relWeaponX, relWeaponY, 0, _dir, zoomRate);
			else
				_handleWeapon->frameRender(hdc, relWeaponX - 45, relWeaponY, 0, _dir, zoomRate);
		}

		// 보우
		else if (_handleItem.weaponType == BOW)
			_bow->rotateRender(hdc, relWeaponX * zoomRate, (relWeaponY + 35) * zoomRate, _angle * PI / 180.0f);
		
		else if (_handleItem.itemType == ItemType::CONSUMABLE) {

			if (_handleItem.itemKey == "milkDrop") {
				if (_isLeft) {
					IMAGEMANAGER->render("carryMilk", hdc, relWeaponX - 30, relWeaponY + 30, zoomRate);
				}
				else {
					IMAGEMANAGER->render("carryMilk", hdc, relWeaponX + 10, relWeaponY + 30, zoomRate);
				}

			}if (_handleItem.itemKey == "berryDrop") {
				if (_isLeft) {
					IMAGEMANAGER->render("carryBerry", hdc, relWeaponX - 30, relWeaponY + 30, zoomRate);
				}
				else {
					IMAGEMANAGER->render("carryBerry", hdc, relWeaponX + 10, relWeaponY + 30, zoomRate);
				}
			}
		}
	}
}



void ForagerPlayer::animation()
{

	switch (_state)
	{
	case IDLE:
		_foragerIdle->setFrameY((_isLeft) ? 1 : 0);
		_foragerIdle->setFrameX(_index);
		if (_count++ % 10 == 0)
		{
			if (_index++ > 2)
				_index = 0;
		}
		break;
	case RUN:
		_foragerRun->setFrameY((_isLeft) ? 1 : 0);
		_foragerRun->setFrameX(_index);
		if (_count++ % 10 == 0)
		{
			if (_index++ > 3)
				_index = 0;
		}
		break;

	case ROTATE:
		if (_isLeft)
			_spinAngle += 10.0f;
		else
			_spinAngle -= 10.0f;

		if (abs(_spinAngle) >= 360.0f) {
			_spinAngle = .0f;
			_index = 0;
			_state = STATE::IDLE;
			_isMoveRotate = false;
		}
		break;
	case HAMMERING:
		if (_handleItem.weaponType == WeaponType::PICKAXE) {
			if (STATMANAGER->GetHammerUpgradeCount() == 1)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att1");
			else if (STATMANAGER->GetHammerUpgradeCount() == 2)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att2");
			else if (STATMANAGER->GetHammerUpgradeCount() == 3)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att3"); 
			else if (STATMANAGER->GetHammerUpgradeCount() == 4)
				_foragerAttacking = IMAGEMANAGER->findImage("pickaxe_att4");

		}
		else if (_handleItem.weaponType == WeaponType::SWORD) {
			if (STATMANAGER->GetSwordUpgradeCount() == 1)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att1");
			else if (STATMANAGER->GetSwordUpgradeCount() == 2)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att2");
			else if (STATMANAGER->GetSwordUpgradeCount() == 3)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att3");
			else if (STATMANAGER->GetSwordUpgradeCount() == 4)
				_foragerAttacking = IMAGEMANAGER->findImage("sword_att4");

		}

		_foragerAttacking->setFrameY((_isLeft) ? 1 : 0);
		_foragerAttacking->setFrameX(_index);
		_playerHammering->setFrameY((_isLeft) ? 1 : 0);
		_playerHammering->setFrameX(_index);
		if (_hitDelayCount++ % 10 == 0)
		{
			if (_index++ > 3)
			{
				_index = 0;
				_hitDelayCount = 1;
			}
		}
		break;
	}
}
	

void ForagerPlayer::bowAnimation()
{
	// 마우스와 플레이어 사이의 각도
	POINT t_mousePos = _ptMouse;
	POINT t_myPos = { CAMERA->GetRelativeX(GetCenterX() + 4), CAMERA->GetRelativeY(GetCenterY() + 4)};
	int x = t_mousePos.x - t_myPos.x;
	int y = t_mousePos.y - t_myPos.y;
	_angle = atan2f(-y, x);
	_angle = (_angle / PI * 180.f);

	// 각도가 음수일 경우 양수로 치환
	if (_angle < 0)
		_angle = 180.0f + (180.0f - (_angle * -1));
	
}


void ForagerPlayer::PlayerControll()
{
	// 강화 테스트
	if(INPUT->GetKeyDown('U')) {
		
		switch (_handleItem.weaponType)
		{
		case WeaponType::PICKAXE:
			STATMANAGER->SetHammerUpgradeCount(STATMANAGER->GetHammerUpgradeCount() + 1);
			break;
		case WeaponType::SWORD:
			STATMANAGER->SetSwordUpgradeCount(STATMANAGER->GetSwordUpgradeCount() + 1);
			break;
		case WeaponType::BOW:
			STATMANAGER->SetBowUpgradeCount(STATMANAGER->GetBowUpgradeCount() + 1);
			break;
		}
	}



	if (_state != ROTATE) {
		if (!INPUT->GetKey(VK_LEFT) || !INPUT->GetKey(VK_RIGHT))
		{
			_state = IDLE;
			_isMoveHorizon = false;
			_isMoveVertical = false;
		}
		//뛰어다니는 상태 (좌우 움직임)
		if (INPUT->GetKey('A') || INPUT->GetKey('D'))
		{
			if (!SOUNDMANAGER->isPlaySound("플레이어걸음2") && !SOUNDMANAGER->isPlaySound("플레이어걸음1")) {
				switch (RANDOM->range(2)) {
				case 0:
					SOUNDMANAGER->play("플레이어걸음1");

					break;
				case 1:
					SOUNDMANAGER->play("플레이어걸음2");

					break;
				}
			}
			_isMoveHorizon = true;
			_state = RUN;
			_isLeft = (INPUT->GetKey('A')) ? true : false;	//방향설정
		}
		//뛰어다니는 상태 (상하 움직임)
		if (INPUT->GetKey('W') || INPUT->GetKey('S'))
		{
			if (!SOUNDMANAGER->isPlaySound("플레이어걸음2") && !SOUNDMANAGER->isPlaySound("플레이어걸음1")) {
				switch (RANDOM->range(2)) {
				case 0:
					SOUNDMANAGER->play("플레이어걸음1");
					break;
				case 1:
					SOUNDMANAGER->play("플레이어걸음2");
					break;
				}
			}
			_isMoveVertical = true;
			_state = RUN;
			_isUp = (INPUT->GetKey('W')) ? true : false;	//방향 설정
		}

		// 움직일 떄만 굴러갈 수 있게
		if (_state != IDLE)
		{
			//굴러다니는 상태 
			if (INPUT->GetKeyDown(VK_SPACE))
			{
				_state = ROTATE;
				_isMoveRotate = false;
				STATMANAGER->setRight(5);
			}
		}

		// 공격 좌클릭
		if (INPUT->GetKey(VK_LBUTTON))
		{
			if (_handleItem.weaponType == WeaponType::PICKAXE || _handleItem.weaponType == WeaponType::SWORD) {
				MeleeWeaponClick();
			}
			else if (_handleItem.weaponType == WeaponType::BOW)
			{
				if (_canBowFire)
				{
					BowClick();
				}
			}
		}

		if (INPUT->GetKeyDown(VK_LBUTTON)) {
			if (_handleItem.itemType == ItemType::CONSUMABLE) {
				if (ITEMMANAGER->Item_count_Minus(_handleItem.itemKey, 1)) {
					_quick->Item_Minus(_handleItem.itemKey, 1);
					STATMANAGER->setRight(-_handleItem.option);
					if (_handleItem.option2 > 0)
						STATMANAGER->RecoverHp(_handleItem.option2);
					SOUNDMANAGER->play("피찰때소리", false);
				}
				else {
					_quick->changeQuickSlot(0);
					_quick->settargetNum(0);
				}

			}
		}
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			if (_handleItem.weaponType == WeaponType::PICKAXE)
			{
				_hitDelayCount = 1;
				_index = (_isLeft) ? 3 : 0;
				_foragerAttacking->setFrameX(_index);
				_playerHammering->setFrameX(_index);
			}
			else if (_handleItem.weaponType == WeaponType::BOW) {
				ArrowFire();
			}
		}
	}
}

void ForagerPlayer::MeleeWeaponClick()
{
	if (_hitDelayCount == 18)
	{
		SOUNDMANAGER->play("근접무기");
	}
	unit* targetUnit = _cursor->GetTargetUnit();
	if (targetUnit != nullptr)
	{
		if (targetUnit->tag == TAG::OBJECT || targetUnit->tag == TAG::ENEMY || targetUnit->tag == TAG::NPC || targetUnit->tag == TAG::BUILDING)
		{
			// 타격 시점에
			if (_hitDelayCount == 18)
			{
				//SOUNDMANAGER->play("근접무기");
				// 타겟과의 거리와 가까우면
				int tarWidth = targetUnit->rc.left + (targetUnit->rc.right - targetUnit->rc.left) / 2;
				if (abs(targetUnit->GetCenterX() - GetCenterX()) <= MAXTOUCHDISTANCE + tarWidth && abs(targetUnit->GetCenterY() - PLAYER_OFFSET_Y) <= MAXTOUCHDISTANCE + tarWidth)
				{
					// 타겟 공격
					if (_handleItem.itemType == ItemType::EQUIPMENT) {
						targetUnit->hurt(Atk);
						if (_handleItem.weaponType == WeaponType::PICKAXE) {
							if (STATMANAGER->GetHammerUpgradeCount() == 4) 
								EFFECTMANAGER->ShowEffectFrame("pickEff4", { targetUnit->GetCenterX(), targetUnit->GetCenterY() }, 7, true);
						}
						else if (_handleItem.weaponType == WeaponType::SWORD) {
							if (STATMANAGER->GetSwordUpgradeCount() == 4)
								EFFECTMANAGER->ShowEffectFrame("swordEff4", { targetUnit->GetCenterX(), targetUnit->GetCenterY() }, 1, true);
						}
					}
						
					
					// 유닛이 파괴되면
					if (targetUnit->isDead() )
					{
						if (targetUnit->objKey == "skull")
							SOUNDMANAGER->play("해골사망소리");
						else if (targetUnit->objKey =="cow")
							SOUNDMANAGER->play("황소사망소리");
					
						//스태니마 감소
							STATMANAGER->setRight(5);

							//그 유닛의 경험치 획득.
							int t_exp = targetUnit->exp;
							if (t_exp > 0) {
								t_exp = RANDOM->range(t_exp - 2, t_exp + 3);
								POINT pt = { targetUnit->rc.left, targetUnit->rc.top };
								string str = std::to_string(t_exp);
								str.insert(0, "EXP ");
								TEXTMANAGER->ShowFloatingText(str, pt, RGB(100, 255, 100), RGB(0, 0, 0));
								STATMANAGER->IncreaseExp(t_exp);
							}
						// 타격 줌인 연출
						CAMERA->forceZoomIn(0.04f, 0.008f);
					}
					else {
						CAMERA->forceZoomIn(0.008f, 0.002f);
					}
				}
			}
		}
	}
	_state = HAMMERING;
}

void ForagerPlayer::CalcBowDelay()
{
	if (!_canBowFire) {
		if (_cntBowDelay++ >= _bowDelay) {
			_cntBowDelay = 0;
			_canBowFire = true;
		}
	}
}

void ForagerPlayer::BowClick()
{
	if (!_isBowPulling) {
		_isBowPulling = true;
		CAMERA->forceZoomIn(-0.15f, -0.002f, false);
	}
	else {
		if (_bowPowerGauge >= 1.0f)
			_bowPowerGauge = 1.0f;
		else
			_bowPowerGauge += 0.01f;
	}
}

void ForagerPlayer::ArrowFire()
{


	if (_isBowPulling) {

		_canBowFire = false;
		_isBowPulling = false;
		CAMERA->forceZoomIn(0.0f, 0.02f, false);

		if (ITEMMANAGER->Item_count_Minus("arrowDrop", 1)) {
			SOUNDMANAGER->play("원거리무기");
			int arrowDamage = Atk * _bowPowerGauge;
			EFFECTMANAGER->ShowEffectFrame("DigSmoke", { GetCenterX(), GetCenterY() }, 2, 10, true);

			int t_bowUpgrade = STATMANAGER->GetBowUpgradeCount();
			if (t_bowUpgrade == 1)
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle, 7.0f, 20, false, false);
			else if (t_bowUpgrade == 2) {
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 15.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 15.0f, 7.0f, 20, false, false);
			}
			else if (t_bowUpgrade == 3) {
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 15.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 15.0f, 7.0f, 20, false, false);
			}
			else if (t_bowUpgrade == 4) {
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 15.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle - 5.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 5.0f, 7.0f, 20, false, false);
				UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle + 15.0f, 7.0f, 20, false, false);
			}
		}
		else {
			vector<string> t_vStr;
			string str;
			int t_random = RANDOM->range(0, 2);
			if (t_random == 0)
				str = "화살이 부족해!";
			else if (t_random == 1)
				str = "가방에 화살이 없어!";

			t_vStr.push_back(str);
			DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
		}
		_bowPowerGauge = .1f;
	}
}

void ForagerPlayer::playerMove()
{
	//플레이어 좌우 움직임 처리 
	if (_isMoveHorizon)
	{
		bool _cantMove = false;
		int applySpeed = (_isLeft) ? -3 : 3;

		_cantMove = (_isLeft) ? CanCheckMove(-1) : CanCheckMove(1);

		if (!_cantMove) {

			OffsetRect(&rc, applySpeed, 0);
			//플레이어가 움직이다가, 스페이스바 누르면 회전하면서 가속
			if (_state == STATE::ROTATE) {
				_spinSpeed = applySpeed * 1.5f;
				OffsetRect(&rc, _spinSpeed, 0);
			}
		}
	}

	//플레이어 상하 움직임 처리 
	if (_isMoveVertical)
	{
		bool _cantMove = false;
		int applySpeed = (_isUp) ? -3 : 3;

		_cantMove = (_isUp) ? CanCheckMove(-MAPTILEX) : CanCheckMove(MAPTILEX);

		if (!_cantMove) {

			OffsetRect(&rc, 0, applySpeed);

			//플레이어가 움직이다가, 스페이스바 누르면 회전하면서 가속
			if (_state == STATE::ROTATE)
			{
				_spinSpeed = applySpeed * 1.5f;
				OffsetRect(&rc, 0, _spinSpeed);
			}
		}
	}

	if (_state == ROTATE || _state == RUN) {
		// 발걸음 이펙트
		if (_footWalkCount++ >= _footWalkEffectInterval) {
			_footWalkCount = 0;
			POINT ptCenter = { rc.left + (rc.right - rc.left) / 2 + RANDOM->range(-10, 0),
							 rc.bottom - RANDOM->range(-1, -6) };
			float randomScale = RANDOM->range(0.5f, 0.7f);
			EFFECTMANAGER->ShowEffectAlphaSize("Walk1", ptCenter, 0.25f, randomScale, 50, 200, true);
		}
	}
}


//플레이어가 보는 시선이 마우스 위치에 따라 변경 
void ForagerPlayer::playerLookingDirection()
{
	int forgaerCenter = (rc.left + rc.right) / 2;

	if (_state != STATE::ROTATE) {
		if (forgaerCenter < CAMERA->GetMouseRelativePos(_ptMouse).x) {
			_dir = 1;
			_isLeft = false;
		}
			
		else {
			_dir = 0;
			_isLeft = true;
		}
			
	}
}

void ForagerPlayer::weaponCheck()
{

	string t_imgKey = _quick->GetQuickSlotNumber()->_item.itemKey;

	_handleItem = DATABASE->GetItem(t_imgKey);
	Atk = _handleItem.option;

	if(_handleItem.weaponType == WeaponType::PICKAXE)
		_handleWeapon = IMAGEMANAGER->findImage("Hammer" + (to_string(STATMANAGER->GetHammerUpgradeCount())));
	else if (_handleItem.weaponType == WeaponType::SWORD)
		_handleWeapon = IMAGEMANAGER->findImage("sword" + (to_string(STATMANAGER->GetSwordUpgradeCount())));

	_bow = IMAGEMANAGER->findImage("bowDrop" + (to_string(STATMANAGER->GetBowUpgradeCount())));

}

void ForagerPlayer::hungryBalloon()
{
	if (!inven_open) {
		if (STATMANAGER->GetSpRatio() <= _balloonRatio) {
			if (_cntBalloon-- <= 0) {
				_cntBalloon = _cntBalloonMax;
				vector<string> t_vStr;
				string str;
				int t_random = RANDOM->range(0, 2);
				if (t_random == 0)
					str = "배가 고파지기 시작했어.";
				else if (t_random == 1)
					str = "뭐라도 먹어야만 해.";
				t_vStr.push_back(str);
				DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
			}
		}
		else {
			_cntBalloon = 0;
		}
		if (!_startBalloon) {

			if (_cntDelayStartBalloon++ >= _delayStartBalloon) {
				_startBalloon = true;
				vector<string> t_vStr;
				t_vStr.push_back("이 세계의 끝은 어디까지일까??");
				t_vStr.push_back("우선 용광로부터 지어보자고!");
				DIALOGUE->ShowDialogue(t_vStr, &rc, 10);
			}
		}
	}



}

void ForagerPlayer::BlinkProcess()
{
	if (_isGotDamage) {
		if (_powerOverwhelmingTime++ >= 120) {
			_isGotDamage = false;
			_powerOverwhelmingTime = 1000;
		}
	}
	else {
		_powerOverwhelmingTime = 1000;
	}
}

POINT ForagerPlayer::GetBowXY()
{
	int distance = 1150 - ((CAMERA->GetZoom() * 1000));
	float x = CAMERA->GetRelativeX(GetCenterX() + (cosf(_angle * PI / 180.0f) * distance)) * CAMERA->GetZoom();
	float y = CAMERA->GetRelativeY(GetCenterY() - (sinf(_angle * PI / 180.0f) * distance)) * CAMERA->GetZoom();

	POINT t_ClampPos = { x, y };

	return t_ClampPos;
}

void ForagerPlayer::RotateImage(image* img)
{
	if (_spinCount++ >= 12)
		_spinCount = 1;

	Rotate(img, img->getFrameWidth(), img->getFrameHeight(), _spinCount, _isLeft);
}

void ForagerPlayer::Rotate(image* img, int sizeX, int sizeY, int frameX, bool left)
{
	int x, y;
	int orig_x, orig_y;
	int pixel;

	double radian = 0;

	if (left)
		radian = (frameX * 30 * PI / 180.0);
	else
		radian = (frameX * -30 * PI / 180.0);

	double cc = cos(radian), ss = sin(-radian);
	double xcenter = (double)sizeX / 2.0, ycenter = (double)sizeY / 2.0; // (2)
	for (y = 0; y < sizeY; y++)
	{
		for (x = 0; x < sizeX; x++)
		{
			orig_x = (int)(xcenter + ((double)y - ycenter)*ss + ((double)x - xcenter)*cc);
			orig_y = (int)(ycenter + ((double)y - ycenter)*cc - ((double)x - xcenter)*ss);
			pixel = 0; // (3)

			if ((orig_y >= 0 && orig_y < sizeY) && (orig_x >= 0 && orig_x < sizeX)) // (4)
				SetPixel(img->getMemDC(), frameX * sizeX + x, y, GetPixel(img->getMemDC(), orig_x, orig_y));

		}
	}
}


// 플레이어 타일 좌표 탐색
int ForagerPlayer::FindPlayerTilePos()
{
	vector<tile> _vTiles = _map->GetTiles();
	POINT _ptPlayerPos = { GetCenterX(), PLAYER_OFFSET_Y };

	for (int i = 0; i < MAPTILEY; i++) {
		for (int j = 0; j < MAPTILEX; j++) {
			if (PtInRect(&_vTiles[i*MAPTILEY + j].rc, _ptPlayerPos)) {
				return (i*MAPTILEY + j);
			}
		}
	}
}

// 플레이어 움직임 가능 체크
bool ForagerPlayer::CanCheckMove(int index)
{
	if (_map->GetTileY(_playerTilePos) == 0 && index < 0) return true;
	if (_map->GetTileY(_playerTilePos) == 83 && index > 0) return true;
	if (_map->GetTileX(_playerTilePos) == 0 && index < 0) return true;
	if (_map->GetTileX(_playerTilePos) == 83 && index > 0) return true;

	tile _tile = _map->GetTile(_playerTilePos + index);

	// 지나갈 수 있는 타일이면 움직임 가능
	if (_tile.canPass)
		return false;

	// 이동 불가 타일에 가까이 접근하는 움직임까진 허용
	RECT t_bound = RectMakeCenter(GetCenterX(), PLAYER_OFFSET_Y, 20, 20);
	RECT t_temp;
	if (!IntersectRect(&t_temp, &t_bound, &_tile.rc)) {
		return false;
	}

	// 이동 불가
	return true;
}

// 플레이어 인접 타일 충돌 체크
void ForagerPlayer::CheckPlayerTile()
{
	POINT ptPlayerPos = { GetCenterX(), PLAYER_OFFSET_Y };

	// 플레이어 좌표 기준 상하좌우 타일중에 
	// 지금 밟고 있는 타일로 좌표 변경
	if (PtInRect(&_map->GetTileRc(_playerTilePos), ptPlayerPos))
		_playerTilePos = _playerTilePos;


	// 플레이어 좌표 기준 상하좌우 타일 충돌 체크
	else if (_playerTilePos < _map->GetTiles().size() && PtInRect(&_map->GetTileRc(_playerTilePos + 1), ptPlayerPos))
		_playerTilePos += 1;
	else if (_playerTilePos >= 1 && PtInRect(&_map->GetTileRc(_playerTilePos - 1), ptPlayerPos))
		_playerTilePos -= 1;
	else if (_playerTilePos <= _map->GetTiles().size() - MAPTILEX && PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX), ptPlayerPos))
		_playerTilePos += MAPTILEX;
	else if (_playerTilePos >= MAPTILEX && PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX), ptPlayerPos))
		_playerTilePos -= MAPTILEX;

	// 플레이어 좌표 기준 대각선 타일 충돌 체크
	else if (_playerTilePos >= MAPTILEX - 1 && PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (_playerTilePos >= MAPTILEX + 1 && PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX - 1), ptPlayerPos))
		_playerTilePos -= MAPTILEX - 1;
	else if (_playerTilePos < _map->GetTiles().size() - MAPTILEX - 1 && PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (_playerTilePos < _map->GetTiles().size() - MAPTILEX + 1 && PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX - 1), ptPlayerPos))
		_playerTilePos -= MAPTILEX - 1;

	// 플레이어의 좌표가 어긋날 경우 다시 받아옴.
	else
		_playerTilePos = FindPlayerTilePos();
}



// Unit 충돌
void ForagerPlayer::CheckCollision()
{
	vector<unit*> t_vUnit = UNITMANAGER->GetUnits();

	for (int i = 0; i < t_vUnit.size(); i++) {

		// 아이템 충돌
		if (t_vUnit[i]->tag == TAG::ITEM) {
			RECT temp;
			RECT t_bound = RectMakeCenter(GetCenterX(), GetCenterY(), 30, 30);
			if (IntersectRect(&temp, &t_bound, &t_vUnit[i]->rc)) {
				SOUNDMANAGER->play("아이템충돌");
				
				t_vUnit[i]->collision();
				TEXTMANAGER->AppearItemText(t_vUnit[i]->dropItem.itemKey);
				// 인벤토리에 아이템 추가 (키값ex : treeDrop, berryDrop)
				tagItem item = DATABASE->GetItem(t_vUnit[i]->dropItem.itemKey);
				if (item.itemType == ItemType::EQUIPMENT) {
					ITEMMANAGER->vequip_push(t_vUnit[i]->dropItem.itemKey);
					_quick->quick_slot_update();
				}
				else {
					ITEMMANAGER->vItem_push(t_vUnit[i]->dropItem.itemKey);	
					_quick->quick_slot_update();
				}
				_quick->quick_slot_update();
				break;
				
			}
		}
		// 빌딩 상호작용 렉트 충돌
		else if (t_vUnit[i]->tag == TAG::BUILDING) {

		}
		// 에너미 충돌
		else if (t_vUnit[i]->tag == TAG::ENEMY) {

		}
	}
}


void ForagerPlayer::hurt(int damage, bool onlyEffect)
{
	if (onlyEffect)
		return;
	
	// 일반 피격
	if (damage > 1) {
		if (_powerOverwhelmingTime >= 120) {
			SOUNDMANAGER->play("나무타격");
			STATMANAGER->setRight(damage);
			_powerOverwhelmingTime = 0;

			_isGotDamage = true;
		}
	}
	// 브레스 연속 피격 
	else {
		if (_powerOverwhelmingTime >= 10) {

			_powerOverwhelmingTime = 0;
			STATMANAGER->setRight(damage);

			_isGotDamage = true;
		}
	}

	
}


