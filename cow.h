#pragma once
#include "enemy.h"
class cow : public enemy
{
private:
	int cowMoveCount;
	int cowIdleCount;
	int cowAttackRange;
private:

public:
	HRESULT init();
	void update() override;
	void render(HDC hdc) override;
	void cowMove();
	void canAttackCheck();
	void cowAnimation();
	void cowLookDirection();
};

