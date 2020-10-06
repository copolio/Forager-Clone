#include "stdafx.h"
#include "unit.h"

void unit::hurt(int damage)
{
	currentHp -= damage;
	if (currentHp <= 0)
		dead();
}

bool unit::isDead()
{
	if (currentHp <= 0) 
		return true; 
	else 
		return false;
}
