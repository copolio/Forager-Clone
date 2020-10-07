#pragma once
#include "gameNode.h"
#include "ForagerPlayer.h"
#include "inGameMenu.h"
#include "earth.h"
#include "cursor.h"
class gameScene :public gameNode
{
private:
	ForagerPlayer* _player;
	inGameMenu* _Menu;
	earth* _map;
	cursor* _cursor;
	
private:
	bool inven_open;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

