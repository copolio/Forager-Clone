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
	HAMMERING

};
class ForagerStatManager;

class ForagerPlayer : public unit
{
private:

	// 이미지
	image* _foragerIdle;
	image* _foragerRun;
	image* _foragerRotate;
	image* _foragerHammering;		
	image* _playerHammering;
	image* _hammer;
	image* _hammerLeft;

	// 프레임 스피드
	int _hitDelayCount;
	int _count;
	int _index;

	

	//플레이어 회전 관련 변수 카운트 
	int _Acount;
	int _spinCount;
	float _spinSpeed;

	//플레이어 상태변수
	bool _isLeft;		//왼쪽이냐?
	bool _isUp;			//위쪽이냐?
	bool _isMoveHorizon;//좌우로 움직이는가?
	bool _isMoveVertical;//상하로 움직이는가?
	bool _isMoveRotate;	//회전하면서 움직이는가?
	bool _isRun;		//뛰고 있는가?
	bool _isHammering;	//곡괭이질인가?

	bool inven_open;	// 인벤 열면 이동 불가능

	STATE _state;		//캐릭터 상태
	float _speed;		//플레이어 스피드 
	float _currentSpeed;//플레이어 현재 스피드 
	
	int _skullTilePos;		// 플레이어 타일 좌표

	//플레이어 발걸음 연출
	int _footWalkCount;
	int _footWalkEffectInterval;


	//망치 영역
	RECT _rcHammer;

	//플레이어 체력 칸 이미지
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];

	// 참조
	ForagerStatManager* _foragerHp;
	earth* _map;
	cursor* _cursor;
	inventory* _theInven;
	//enemy* _enemy;
	unit* _unit;

	int Atk;

public: 
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc) override;

	//플레이어 애니메이션
	void animation();
	void PlayerControll();
	void playerMove();
	void playerLookingDirection();
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);

	float getPlayerMaxHp() { return maxHp; }
	float getPlayerCurrentHp(){ return currentHp; }
	void setCurrentPlayerHp(float _hp) { currentHp -= _hp; }

	void setInvenOpen(bool isOpen) { inven_open = isOpen; };
	void setPMLink(earth* map) { _map = map; };
	void setCursorLink(cursor* cursor) { _cursor = cursor; };
	void setInvenLink(inventory* inven) { _theInven = inven; };


	int FindPlayerTilePos();
	bool CanCheckMove(int index);
	void CheckPlayerTile();
	void CheckCollision();

public:
	int GetPlayerTilePos() { return _skullTilePos; };
};

