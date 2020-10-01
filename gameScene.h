#pragma once
#include "gameNode.h"
class gameScene :public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

