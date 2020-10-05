#pragma once
#include "ForagerStatManager.h"
#include "unit.h"

#define PI 3.1415926f

enum STATE
{
	IDLE,
	RUN,
	ROTATE,
	HAMMERING

};
class ForagerStatManager;

class ForagerPlayer :public unit
{
private:
	//basicmap* _map;
private:
	image* _foragerIdle;
	image* _foragerRun;
	image* _foragerRotate;
	image* _foragerHammering;		//곡괭이가 괭이질 하는 이미지
	image* _playerHammering;
	image* _hammer;
	image* _hammerLeft;
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
	STATE _state;		//캐릭터 상태
	float _speed;		//플레이어 스피드 
	float _currentSpeed;//플레이어 현재 스피드 
	

	//플레이어 발걸음 연출
	int _footWalkCount;
	int _footWalkEffectInterval;

	//플레이어 영역
	RECT _rcForager;

	//망치 영역
	RECT _rcHammer;

	//플레이어 체력 칸 이미지
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];

	ForagerStatManager* _foragerHp;


	bool inven_open;
public: 
	HRESULT init();
	void release();
	void update() override;
	void render(HDC hdc) override;

	//플레이어 애니메이션
	void animation();
	void PlayerControll();
	void playerMove();
	void playerLookingDirection();
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);

	float getPlayerMaxHp() { return hp; }
	float getPlayerCurrentHp(){ return currentHp; }
	void setCurrentPlayerHp(float _hp) { currentHp -= _hp; }
	RECT getPlayerRect() { return _rcForager; };

	
	void setPlayerRect(RECT pos) { _rcForager = pos; };
	void setInvenOpen(bool isOpen) { inven_open = isOpen; };
//	void setPMLink(basicmap* map) { _map = map; };
};

