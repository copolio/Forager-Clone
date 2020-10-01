#pragma once
#include "gameNode.h"
#include "earth.h"
class gameScene :public gameNode
{
private:
	earth* _map;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

