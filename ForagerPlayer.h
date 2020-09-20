#pragma once
#include "gameNode.h"

#define PI 3.1415926f

enum STATE
{
	IDLE,
	RUN

};

class ForagerPlayer :public gameNode
{

private:
	image* _foragerIdle;
	image* _foragerRun;

	int _count;
	int _index;

	//플레이어 회전 관련 변수 카운트 
	int _Acount;
	int _spinCount;


	//플레이어 상태값

	bool _isLeft;		//왼쪽이냐?
	bool _isUp;			//위쪽이냐?
	bool _isMoveHorizon;//좌우로 움직이는가?
	bool _isMoveVertical;//좌우로 움직이는가?
	bool _isRun;		//뛰고 있는가?
	bool _isGround;		//땅에 붙어있는가?
	bool _isLookDown;	//아래를 보고있는가?
	bool _isLookLeft;	//왼쪽을 보고있는가?
	bool _isLookRight;	//오른쪽을 보고있는가?
	bool _isJumpDown;	//하단 점프인가?
	bool _isJump;		//상단 점프인가?
	bool _isHang;		//매달렸는가?
	STATE _state;		//캐릭터 상태
	float _x, _y;		//플레이어 x,y좌표
	float _speed;		//플레이어 스피드 
	float _currentSpeed;//플레이어 현재 스피드 
	


	//플레이어 영역

	RECT _rcForager;




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
	//void RotateImage(image* img);
	//void Rotate(image* img, int sizeX, int sizeY, int frameX);
	


};

