#pragma once
#include "gameNode.h"
#include "ForagerPlayer.h"
#include "inGameMenu.h"
#include "earth.h"
class gameScene :public gameNode
{
private:
	ForagerPlayer* _player;
	inGameMenu* _Meun;
	earth* _map;

private:
	bool inven_open;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

