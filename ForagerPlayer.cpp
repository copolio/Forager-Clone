#include "stdafx.h"
#include "ForagerPlayer.h"
#include "quick_slot.h"

HRESULT ForagerPlayer::init()
{
	tileIndex = 0;

	// 위치 초기화
	objKey = "Player";
	x = WINSIZEX / 2;
	y = WINSIZEY / 2;
	rc = RectMakeCenter(x, y, 30, 41);
	_playerTilePos = FindPlayerTilePos();

	// Object 정보 초기화
	tag = TAG::PLAYER;
	layer = LAYER::OBJECT;
	_equipWeapon = EQUIPWEAPON::PICKAXE;

	// 스탯 초기화
	maxHp = 1;
	currentHp = 1;
	exp = 0;
	Atk = 15;
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

	
	
	_state = STATE::IDLE;
	_priorState = _state;
	_angle = 0.0f;
	// 무기 위치 초기화
	_rcHammer = RectMake((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2 - 28, 56, 56);

	//기본 플레이어 이미지
	IMAGEMANAGER->addFrameImage("playerStop", "Images/이미지/플레이어/player_idle_frame.bmp", 120,112, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRUN", "Images/이미지/플레이어/player_run_frame.bmp", 160, 112, 4, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRotate", "Images/이미지/플레이어/player_rotate_frame.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRotateLeft", "Images/이미지/플레이어/player_rotate_frame_left.bmp", 672, 56, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerWork", "Images/이미지/플레이어/player_hammering_frame.bmp", 130, 100, 3, 2, true, RGB(255, 0, 255));

	//플레이어 맞을 때 
	IMAGEMANAGER->addFrameImage("playerHurt", "Images/이미지/플레이어/playerGotDamage.bmp", 480, 112, 12, 2, true, RGB(255, 0, 255));
	
	//곡괭이 이미지
	IMAGEMANAGER->addImage("Hammer", "Images/이미지/아이템/곡괭이.bmp", 56, 56, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("HammerLeft", "Images/이미지/아이템/곡괭이왼쪽.bmp", 56, 56, true, RGB(255, 0, 255));
	// 곡괭이질 이미지 3x1
	IMAGEMANAGER->addFrameImage("playerHammering", "Images/이미지/아이템/곡괭이질하기3.bmp",255,140, 3, 2, true, RGB(255, 0, 255));
	//곡괭이 회전 이미지 12x1
	IMAGEMANAGER->addFrameImage("HammerImg", "Images/이미지/아이템/곡괭이right.bmp", 672, 56, 12, 1,true,RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("HammerImgLeft", "Images/이미지/아이템/곡괭이left.bmp", 672, 56, 12, 1,true,RGB(255, 0, 255));

	// 활 프레임 이미지
	IMAGEMANAGER->addFrameImage("Bow", "Images/이미지/아이템/img_equip_bow.bmp", 250, 250, 4, 4, true, RGB(255, 0, 255));

	// 이미지 파싱
	_foragerIdle = IMAGEMANAGER->findImage("playerStop");
	_foragerRun = IMAGEMANAGER->findImage("playerRUN");
	_foragerRotate = IMAGEMANAGER->findImage("playerRotate");
	_foragerHammering = IMAGEMANAGER->findImage("playerHammering");
	_playerHammering = IMAGEMANAGER->findImage("playerWork");
	_playerGotHurt = IMAGEMANAGER->findImage("playerHurt");

	_hammer = IMAGEMANAGER->findImage("Hammer");
	_hammerLeft = IMAGEMANAGER->findImage("Hammer");
	_bow = IMAGEMANAGER->findImage("Bow");

	//플레이어 회전 이미지 찍어내기
	for(int i = 1 ; i < 12; i++)
	{
		image *left = IMAGEMANAGER->findImage("playerRotateLeft");
		image *right = IMAGEMANAGER->findImage("playerRotate");

		Rotate(left, left->getFrameWidth(), left->getFrameHeight(), i, true);
		Rotate(right, right->getFrameWidth(), right->getFrameHeight(), i, false);
	}

	//곡괭이 회전 이미지 찍어내기
	for (int i = 1; i < 12; i++)
	{
		image *hammerLeft = IMAGEMANAGER->findImage("HammerImgLeft");
		image *hammerRight = IMAGEMANAGER->findImage("HammerImg");
	
		Rotate(hammerLeft, hammerLeft->getFrameWidth(), hammerLeft->getFrameHeight(), i, true);
		Rotate(hammerRight, hammerRight->getFrameWidth(), hammerRight->getFrameHeight(), i, false);
	}

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
	_powerOverwhelmingTime = 100;

	return S_OK;
}

void ForagerPlayer::release()
{
}

void ForagerPlayer::update()
{


	weaponCheck();

	animation();
	if (_equipWeapon == BOW && !inven_open) bowAnimation();

	if (!inven_open) {
		PlayerControll();
		playerMove();
		playerLookingDirection();
		CheckPlayerTile();
		CheckCollision();
	}
	
	_rcHammer = RectMake((rc.left + rc.right) / 2 , (rc.top + rc.bottom) / 2 - 28, 56, 56);
	CAMERA->targetFollow(rc.left, rc.top);
	STATMANAGER->update();
	STATMANAGER->setinvenopen(inven_open);

	if (_isGotDamage) {
		_powerOverwhelmingTime++;
	}

	hungryBalloon();
	
	if (_priorState != _state) {
		_count = 0;
		_index = 0;
		_hitDelayCount = 0;
	}
	_priorState = _state;
}

void ForagerPlayer::render(HDC hdc)
{
	int relX = CAMERA->GetRelativeX(rc.left);
	int relY = CAMERA->GetRelativeY(rc.top);
	int relWeaponX = CAMERA->GetRelativeX(_rcHammer.left);
	int relWeaponY = CAMERA->GetRelativeY(_rcHammer.top);

	switch (_state)
	{
	case IDLE:
		if (!_isGotDamage)
			IMAGEMANAGER->frameRender("playerStop", hdc, relX, relY, CAMERA->GetZoom());
		else
			IMAGEMANAGER->frameRender("playerHurt", hdc, relX, relY, CAMERA->GetZoom());
		break;
	case RUN:
		if (!_isGotDamage)
			IMAGEMANAGER->frameRender("playerRUN", hdc, relX, relY, CAMERA->GetZoom());
		else
			IMAGEMANAGER->frameRender("playerHurt", hdc, relX, relY, CAMERA->GetZoom());
		break;

	case ROTATE:
		if (_isLeft)
		{
			IMAGEMANAGER->frameRender("playerRotateLeft", hdc, relX, relY, CAMERA->GetZoom());
			if (_equipWeapon == PICKAXE)
				IMAGEMANAGER->frameRender("HammerImgLeft", hdc, relX, relY, CAMERA->GetZoom());
		}
		else
		{
			IMAGEMANAGER->frameRender("playerRotate", hdc, relX, relY, CAMERA->GetZoom());
			if (_equipWeapon == PICKAXE)
				IMAGEMANAGER->frameRender("HammerImg", hdc, relX, relY, CAMERA->GetZoom());
		}
		break;


	case HAMMERING:
		IMAGEMANAGER->frameRender("playerWork", hdc, relX, relY, CAMERA->GetZoom());
		if (_equipWeapon == PICKAXE) {
			_foragerHammering->frameRender(hdc, CAMERA->GetRelativeX(rc.left - 16), CAMERA->GetRelativeY(rc.top - 20), CAMERA->GetZoom());
		}
		if (_equipWeapon == SWORD) {
			_foragerHammering->frameRender(hdc, CAMERA->GetRelativeX(rc.left - 30), CAMERA->GetRelativeY(rc.top - 15), CAMERA->GetZoom());
		}
		break;
	}
	if (_state != ROTATE && _state != HAMMERING)
	{
		// 곡괭이 일반 상태
		if (_equipWeapon == PICKAXE) {
			if (_isLeft)
				IMAGEMANAGER->render("Hammer", hdc, relWeaponX, relWeaponY, CAMERA->GetZoom());
			else
				IMAGEMANAGER->render("HammerLeft", hdc, CAMERA->GetRelativeX(_rcHammer.left - 40), relWeaponY, CAMERA->GetZoom());
		}
		// 보우 일반 상태
		else if (_equipWeapon == BOW)
		{
			if (_isLeft)
				_bow->frameRender(hdc, relWeaponX - 35, relWeaponY + 15, _bow->getFrameX(), _bow->getFrameY(), CAMERA->GetZoom());
			else
				_bow->frameRender(hdc, relWeaponX - 15, relWeaponY + 15, _bow->getFrameX(), _bow->getFrameY(), CAMERA->GetZoom());
		}
		else if (_equipWeapon == SWORD) {
			if (_isLeft)
				IMAGEMANAGER->render("sword", hdc, relWeaponX, relWeaponY, CAMERA->GetZoom());
			else
				IMAGEMANAGER->render("sword_right", hdc, CAMERA->GetRelativeX(_rcHammer.left - 40), relWeaponY, CAMERA->GetZoom());
		}
		else if (_equipWeapon == FOOD) {
		
			if (_quick->GetQuickSlotNumber()->img_name == "milkDrop") {
				if (_isLeft) {
					IMAGEMANAGER->render("carry_milk", hdc, relWeaponX -30, relWeaponY + 30, CAMERA->GetZoom());
				}
				else {
					IMAGEMANAGER->render("carry_milk", hdc, relWeaponX +10, relWeaponY + 30, CAMERA->GetZoom());
				}
				
			}if (_quick->GetQuickSlotNumber()->img_name == "berryDrop") {
				if (_isLeft) {
					IMAGEMANAGER->render("carry_berry", hdc, relWeaponX - 30, relWeaponY + 30, CAMERA->GetZoom());
				}
				else {
					IMAGEMANAGER->render("carry_berry", hdc, relWeaponX + 10, relWeaponY + 30, CAMERA->GetZoom());
				}

			}

		}
	}
	STATMANAGER->render(hdc);
}


void ForagerPlayer::animation()
{
	if (!_isGotDamage)
	{
		switch (_state)
		{
		case IDLE:
			_foragerIdle->setFrameY((_isLeft) ? 1 : 0);
			_foragerIdle->setFrameX(_index);
			if (_count++ % 10 == 0)
			{
				if (_index++ > 3)
					_index = 0;
			}
			break;
		case RUN:
			_foragerRun->setFrameY( (_isLeft) ? 1 : 0);
			_foragerRun->setFrameX(_index);
			if (_count++ % 5 == 0)
			{
				if (_index++ > 4)
					_index = 0;
			}
			break;

		case ROTATE:
			if (_isLeft)
			{
				if (_count++ % 3 == 0)
				{
					if (_index++ > 11)
					{
						_index = 0;
						_state = STATE::IDLE;
						_isMoveRotate = false;
					}
					IMAGEMANAGER->findImage("playerRotateLeft")->setFrameX(_index);
					IMAGEMANAGER->findImage("HammerImgLeft")->setFrameX(_index);
				}
			}
			else
			{
				_foragerRotate->setFrameY(0);
				_foragerRotate->setFrameX(_index);
				if (_count++ % 3 == 0)
				{
					if (_index++ > 11)
					{
						_index = 0;
						_state = STATE::IDLE;
						_isMoveRotate = false;
					}
					IMAGEMANAGER->findImage("HammerImg")->setFrameX(_index);
				}
			}
			break;
		case HAMMERING:
			if (_equipWeapon == EQUIPWEAPON::PICKAXE) {
				_foragerHammering = IMAGEMANAGER->findImage("playerHammering");
			}
			else {
				_foragerHammering = IMAGEMANAGER->findImage("sword_att");
			}
			
			_foragerHammering->setFrameY((_isLeft) ? 1 : 0);
			_foragerHammering->setFrameX(_index);
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
	else
	{
		if (_state != HAMMERING)
		{
			if (_count++ > 5)
			{
				_count = 0;

				if (_index > 12)
				{
					_index = 0;
					_isGotDamage = false;
					_powerOverwhelmingTime = 100;
				}
				_index++;
				_playerGotHurt->setFrameX(_index);
				if (_isLeft)
					_playerGotHurt->setFrameY(1);
				else
					_playerGotHurt->setFrameY(0);
			}
		}
		switch (_state)
		{
		case HAMMERING:
			if (_equipWeapon == EQUIPWEAPON::PICKAXE) {
				_foragerHammering = IMAGEMANAGER->findImage("playerHammering");
			}
			else {
				_foragerHammering = IMAGEMANAGER->findImage("sword_att");
			}
			
			_foragerHammering->setFrameY((_isLeft) ? 1 : 0);
			_foragerHammering->setFrameX(_index);
			_playerHammering->setFrameY((_isLeft) ? 1 : 0);
			_playerHammering->setFrameX(_index);
			if (_hitDelayCount++ % 10 == 0)
			{
				if (_index++ > 3)
				{
					_hitDelayCount = 1;
					_index = 0;
				}
			}
			break;
		}
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
	
	int t_angle = _angle;
	// 이미지 프레임 오프셋 보정(45도부터 0도로 계산해서 프레임 이미지의 각도와 일치시킴)
	t_angle += 45.0f;
	if (t_angle > 360.0f) {
		t_angle = t_angle - 360.0f;
	}

	// 22.5도 단위로 이미지 프레임값 바꾸기.
	float minAngle = -11.25f;
	float maxAngle = 11.25f;
	float addAngle = 22.5f;
	int count = 0;
	for (int y = 0; y < 4; y++) {
		for (int x = 0; x < 4; x++) {
			if (minAngle + (count * addAngle) <= t_angle && t_angle <= maxAngle + (count * addAngle)) {
				_bow->setFrameX(x);
				_bow->setFrameY(y);
				return;
			}
			count++;
		}
	}
}


void ForagerPlayer::PlayerControll()
{
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
		if (_state != IDLE || _isGotDamage == false)
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
			if (_isGotDamage)
			{
				_isGotDamage = false;
				_index = 0;
				_count = 0;
			}
			if (_equipWeapon == EQUIPWEAPON::PICKAXE || _equipWeapon == EQUIPWEAPON::SWORD) {
				MeleeWeaponClick();
			}
			else if (_equipWeapon == EQUIPWEAPON::BOW) {
				BowClick();
			}
		}

		if (INPUT->GetKeyDown(VK_LBUTTON)) {
			if (_equipWeapon == EQUIPWEAPON::FOOD) {
				if (ITEMMANAGER->Item_count_Minus(_quick->GetQuickSlotNumber()->img_name, 1)) {
					_quick->Item_Minus(_quick->GetQuickSlotNumber()->img_name, 1);
					STATMANAGER->setRight(-5);
					SOUNDMANAGER->play("피찰때소리", false);
				}
				else {
					_quick->target(0);
					_quick->settargetNum(0);
				}

			}
		}
		if (INPUT->GetKeyUp(VK_LBUTTON))
		{
			if (_equipWeapon == EQUIPWEAPON::PICKAXE)
			{
				_hitDelayCount = 1;
				_index = (_isLeft) ? 3 : 0;
				_foragerHammering->setFrameX(_index);
				_playerHammering->setFrameX(_index);
			}
			else if (_equipWeapon == EQUIPWEAPON::BOW) {
				ArrowFire();
			}
		}
	}
	else {

		_isGotDamage = false;
		_powerOverwhelmingTime = 100;
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
				if (abs(targetUnit->GetCenterX() - GetCenterX()) <= 100 && abs(targetUnit->GetCenterY() - PLAYER_OFFSET_Y) <= 100)
				{
					// 타겟 공격
					if (_equipWeapon == EQUIPWEAPON::PICKAXE) {
						Atk = 15;
					}
					else if(_equipWeapon == EQUIPWEAPON::SWORD) {
						Atk = 25;
					}
					targetUnit->hurt(Atk);

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
	SOUNDMANAGER->play("원거리무기");
	if (_isBowPulling) {
		_isBowPulling = false;
		CAMERA->forceZoomIn(0.0f, 0.02f, false);
		int arrowDamage = (Atk * 2) * _bowPowerGauge;
		EFFECTMANAGER->ShowEffectFrame("DigSmoke", { GetCenterX(), GetCenterY() }, 2, 10, true);
		UNITMANAGER->GetProjectileMG()->CreateProjectile("BowArrow", GetCenterX(), GetCenterY(), arrowDamage, _angle, 7.0f,20, false, false);
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
			float randomScale = RANDOM->range(0.01f, 0.03f);
			EFFECTMANAGER->ShowEffectAlphaSize("Walk1", ptCenter, 0, randomScale, 50, 150, true);
		}
	}
}


//플레이어가 보는 시선이 마우스 위치에 따라 변경 
void ForagerPlayer::playerLookingDirection()
{
	int forgaerCenter = (rc.left + rc.right) / 2;

	if (_state != STATE::ROTATE) {
		if (forgaerCenter < CAMERA->GetMouseRelativePos(_ptMouse).x)
			_isLeft = false;
		else
			_isLeft = true;
	}
}

void ForagerPlayer::weaponCheck()
{
	if (_quick->GetQuickSlotNumber()->img_name == "slot_Bow") {
		_equipWeapon = EQUIPWEAPON::BOW;
	}
	else if (_quick->GetQuickSlotNumber()->img_name == "pick") {
		_equipWeapon = EQUIPWEAPON::PICKAXE;
	}
	else if (_quick->GetQuickSlotNumber()->img_name == "sword") {
		_equipWeapon = EQUIPWEAPON::SWORD;
	}
	else if (_quick->GetQuickSlotNumber()->img_name == "berryDrop") {
		_equipWeapon = EQUIPWEAPON::FOOD;
	}
	else if (_quick->GetQuickSlotNumber()->img_name == "milkDrop") {
		_equipWeapon = EQUIPWEAPON::FOOD;
	}

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
				DIALOGUE->ShowDialogue(t_vStr, &rc, 0);
			}
		}
		else {
			_cntBalloon = 0;
		}
		if (!_startBalloon) {

			if (_cntDelayStartBalloon++ >= _delayStartBalloon) {
				_startBalloon = true;
				vector<string> t_vStr;
				t_vStr.push_back("우선 용광로부터 지어보자고!");
				DIALOGUE->ShowDialogue(t_vStr, &rc, 0);
			}
		}
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
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + 1), ptPlayerPos))
		_playerTilePos += 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - 1), ptPlayerPos))
		_playerTilePos -= 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX), ptPlayerPos))
		_playerTilePos += MAPTILEX;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX), ptPlayerPos))
		_playerTilePos -= MAPTILEX;

	// 플레이어 좌표 기준 대각선 타일 충돌 체크
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos - MAPTILEX - 1), ptPlayerPos))
		_playerTilePos -= MAPTILEX - 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX + 1), ptPlayerPos))
		_playerTilePos += MAPTILEX + 1;
	else if (PtInRect(&_map->GetTileRc(_playerTilePos + MAPTILEX - 1), ptPlayerPos))
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
				if (t_vUnit[i]->dropItem.itemKey == "sword" || t_vUnit[i]->dropItem.itemKey == "slot_Bow") {
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


void ForagerPlayer::hurt(int damage)
{
	if (_powerOverwhelmingTime >= 10) {
		_powerOverwhelmingTime = 0;
		STATMANAGER->setRight(damage);
		SOUNDMANAGER->play("나무타격");
		_isGotDamage = true;
		_index = 1;
		_count = 0;
	}
	
}


