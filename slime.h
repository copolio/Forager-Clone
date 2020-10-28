#pragma once
#include "enemy.h"
#define MOVEMAX 56*3
#define JUMPMAX 56*2

enum SLIMESTATE
{


};

struct tagFRect
{
	float left;
	float right;
	float top;
	float bottom;
	

};
class slime : public enemy
{
private:
	POINT originPos;			//슬라임이 점프하기 전의 기존 위치.
	POINT currentPos;			//점프하면서 이동중인 현재 위치
	POINT destPos;				//목표, 착지 위치
	POINT midPos;				//중간 위치 

	tagFRect fRectMakeCenter(float x, float y, float width, float height)
	{
		tagFRect rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
		return rc;
	}
	
	tagFRect _fRc;
		 
	float currentJumpSpeed;
	int jumpWaitTime;			//점프 대기(delay)
	int jumpTime;				//점프 타임
	float lerpRatio;
	bool _isJump;
	bool _canJump;

	int slimeFireCount;


public:
	HRESULT init();
	void update();
	void render(HDC hdc) override;

private:
	void slimeAnimation();
	void slimeJump();

	void jumpUp();
	void jumpDown();
	void jumpStop();
	void targetDest();

	void slimeFire();

	float shootToTarget();



};

