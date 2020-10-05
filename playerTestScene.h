#pragma once
#include "gameNode.h"
#include "ForagerStatManager.h"

class playerTestScene : public gameNode
{

private:
	ForagerPlayer* _player;
	ForagerStatManager* _statManager;


public:

	HRESULT init();
	void release();
	void update();
	void render();
};

