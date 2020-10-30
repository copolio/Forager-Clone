#pragma once
#include "enemy.h"
//#define MOVEMAX 56*3
//#define JUMPMAX 56*2

#define MOVERANGE 2
#define MOVESPEED 1

struct tagBRect
{
	float left;
	float right;
	float top;
	float bottom;

};
class slimeBoss :public enemy
{
private :
	POINT originPos;			//슬라임이 점프하기 전의 기존 위치.
	POINT currentPos;			//점프하면서 이동중인 현재 위치
	POINT destPos;				//목표, 착지 위치
	POINT midPos;				//중간 위치 

	tagBRect fRectMakeCenter(float x, float y, float width, float height)
	{
		tagBRect rc = { x - width / 2, y - height / 2, x + width / 2, y + height / 2 };
		return rc;
	}
	tagBRect _fRc;

	float currentJumpSpeed;
	int jumpWaitTime;			//점프 대기(delay)
	int jumpTime;				//점프 타임
	int shootDelayTime;
	float lerpRatio;
	bool _isJump;
	bool _canJump;

	bool _slimeGotDamage;

	int slimeFireCount;
	//====================================================
	bool _canFollow;
	bool isattacking;
	int searchCount;
	int slimeShootCount;


private:

public:

	HRESULT init();
	void update();
	void render(HDC hdc) override;


	void slimeBossAnimation();
	void targetDest();
	void slimeFire();



	//====================================================
	void slimeMove();
};

