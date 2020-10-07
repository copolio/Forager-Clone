#pragma once
#include "unit.h"

enum SKULLSTATE
{
	STAY,
	ATTACK
};

class enemy :public unit
{
private:
	


private : 
	
	SKULLSTATE _state;
	int _index;
	int _count;
	bool isLeft;



public:
	


	virtual void setEnemy();
	virtual void render(HDC hdc) override;
	virtual void update() override;
	virtual void dead() override;
	void skullAnimation();

};

