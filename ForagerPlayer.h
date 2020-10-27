#pragma once
#include "ForagerStatManager.h"
#include "unit.h"
#include "earth.h"
#include "cursor.h"
#include "inventory.h"

#define PI 3.1415926f
#define PLAYER_OFFSET_Y rc.bottom + 12

class inventory;
class earth;
class cursor;

enum STATE
{
	IDLE,
	RUN,
	ROTATE,
	HAMMERING,
	DAMAGE
};


class quick_slot;
class ForagerPlayer : public unit
{
private:

	// 기본
	STATE _state;				// 캐릭터 상태
	STATE _priorState;			// 이전 캐릭터 상태

	float _speed;				// 플레이어 스피드 
	float _currentSpeed;		// 플레이어 현재 스피드 
	int Atk;					// 공격력
	int _playerTilePos;			// 플레이어 타일 좌표
	float _angle;				// 마우스와 플레이어 사이의 각도
	float _bowPowerGauge;		// 파워 게이지
	tagItem _handleItem;		// 손에 들고 있는 아이템
	quick_slot* _quick;			// 무기를 먹었을 때 퀵슬롯 추가

	//망치 영역
	RECT _rcHammer;

	//플레이어 상태변수
	bool _isLeft;		//왼쪽이냐?
	bool _isUp;			//위쪽이냐?
	bool _isMoveHorizon;//좌우로 움직이는가?
	bool _isMoveVertical;//상하로 움직이는가?
	bool _isMoveRotate;	//회전하면서 움직이는가?
	bool _isRun;		//뛰고 있는가?
	bool _isHammering;	//곡괭이질인가?
	bool _isBowPulling;	//활시위를 당기고 있는가?
	bool _isGotDamage;  //데미지 받았는가?

	// 이미지
	image* _foragerIdle;
	image* _foragerRun;
	image* _foragerRotate;
	image* _foragerHammering;		
	image* _playerHammering;
	image* _playerGotHurt;
	image* _hammer;
	image* _hammerLeft;
	image* _bow;
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];
	
	// 애니메이션 스피드
	int _hitDelayCount;
	int _count;
	int _index;

	//플레이어 발걸음 연출
	int _footWalkCount;
	int _footWalkEffectInterval;

	//플레이어 회전 관련 변수 카운트 
	int _Acount;
	int _spinCount;
	float _spinSpeed;

	// 기타
	bool inven_open;		// 인벤 열면 이동 불가능
	float _balloonRatio;	// 에너지 비율이 몇일때 말풍선이 나올지
	int _cntBalloon;		// 배고플 때 나오는 말풍선 카운트
	int _cntBalloonMax;		// 말풍선 출력 카운트

	bool _startBalloon;		// 시작 말풍선
	int _cntDelayStartBalloon;
	int _delayStartBalloon;

	int _powerOverwhelmingTime;

	// 참조
	earth* _map;
	cursor* _cursor;
	inventory* _theInven;
	unit* _unit;

public: 
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc) override;


private:

	void PlayerControll();

	void MeleeWeaponClick();
	void BowClick();
	void ArrowFire();
	void bowAnimation();
	void animation();
	void playerMove();
	void playerLookingDirection();
	void weaponCheck();
	void hungryBalloon();

public:
	float getPlayerMaxHp() { return maxHp; }
	float getPlayerCurrentHp(){ return currentHp; }
	void setCurrentPlayerHp(float _hp) { currentHp -= _hp; }
	void setInvenOpen(bool isOpen) { inven_open = isOpen; };
	void setPMLink(earth* map) { _map = map; };
	void setCursorLink(cursor* cursor) { _cursor = cursor; };
	void setInvenLink(inventory* inven) { _theInven = inven; };
	void setBalloon(bool p_flag) { _startBalloon = p_flag; };


	void getquick_slotInfo(quick_slot* _q) {
		_quick = _q;
	}

	int FindPlayerTilePos();
	bool CanCheckMove(int index);
	void CheckPlayerTile();
	void CheckCollision();
	

public:
	int GetPlayerTilePos() { return _playerTilePos; };
	bool IsBow() { return  _handleItem.weaponType == WeaponType::BOW; };
	POINT GetBowXY();
	void hurt(int damage) override;
	void SetIsMoveRotate() { _isMoveRotate = false; };
	void Init_PowerOverwhelmingTime() {
		_powerOverwhelmingTime = 0;
	}
private:
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);
};

