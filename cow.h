#pragma once
#include "enemy.h"

#define MOVERANGE 2
#define MOVESPEED 1
enum COWSTATE
{
	IDLE3,
	WALK,
	DASH,

};
class cow : public enemy
{
private:
	int cowHitCount;
	int cowHitWaitCount;
	int searchCount;
	int cowDashRange;
	int _cowTilePos;
	int Atk;

	bool tryAttack;
	bool isattacking;


private:
	COWSTATE _state2;
public:
	HRESULT init();
	void update();
	void render(HDC hdc) override;

	void cowAnimation();
	void cowMove();
	void cowAttackAttempt();
	void cowDash();
	void cowLookDirection();
	
	void checkCowTile();

	int FindCowTilePos();



	
};

