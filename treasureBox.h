#pragma once
#include "unit.h"
class treasureBox : public unit
{
private:
	RECT* _rcPlayer;
	bool _isNear;


	void CheckNearPlayer();
	void CheckKey();
	void GiveReward();


public:
	void setTreasureBox(string p_imgKey, string p_itemRewardKey, POINT p_ptPos, RECT* p_rcPlayer);
	void update() override;
	void render(HDC hdc) override;

};

