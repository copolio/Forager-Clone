#pragma once
#include "gameNode.h"
#include "ForagerStatManager.h"

#define PI 3.1415926f

enum STATE
{
	IDLE,
	RUN,
	ROTATE,
	HAMMERING

};

class basicmap;
class ForagerStatManager;

class ForagerPlayer :public gameNode
{
private:
	basicmap* _map;
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
	bool _isMoveVertical;//좌우로 움직이는가?
	bool _isMoveRotate;	//회전하면서 움직이는가?
	bool _isRun;		//뛰고 있는가?
	bool _isGround;		//땅에 붙어있는가?
	bool _isLookDown;	//아래를 보고있는가?
	bool _isLookLeft;	//왼쪽을 보고있는가?
	bool _isLookRight;	//오른쪽을 보고있는가?
	bool _isJumpDown;	//하단 점프인가?
	bool _isJump;		//상단 점프인가?
	bool _isHammering;	//곡괭이질인가?
	bool _upDownCheck;
	STATE _state;		//캐릭터 상태
	float _x, _y;		//플레이어 x,y좌표
	float _speed;		//플레이어 스피드 
	float _currentSpeed;//플레이어 현재 스피드 

	//플레이어 스탯
	float _playerMaxHp;	//플레이어 최대체력
	float _currentHp;		//플레이어 현재체력 
	


	//플레이어 영역
	RECT _rcForager;

	//망치 영역
	RECT _rcHammer;

	//플레이어 체력 칸 이미지
	image* _foragerHpBarFront[3];
	image* _foragerHpBarBack[3];

	ForagerStatManager* _foragerHp;



public: 
	HRESULT init();
	void release();
	void update();
	void render();

	//플레이어 애니메이션
	void animation();
	void PlayerControll();
	void playerMove();
	void playerLookingDirection();
	void RotateImage(image* img);
	void Rotate(image* img, int sizeX, int sizeY, int frameX, bool left = false);

	float getPlayerMaxHp() { return _playerMaxHp; }
	float getPlayerCurrentHp(){ return _currentHp; }
	void setCurrentPlayerHp(float _hp) { _currentHp -= _hp; }
	RECT getPlayerRect() { return _rcForager; };


	void setPlayerRect(RECT pos) { _rcForager = pos; };

	void setPMLink(basicmap* map) { _map = map; };
};

