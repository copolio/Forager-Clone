#pragma once
#include "gameNode.h"
#include "ForagerPlayer.h"
#include "inGameMenu.h"
#include "earth.h"
#include "cursor.h"
#include "quick_slot.h"


class gameScene :public gameNode
{
private:

	ForagerPlayer* _player;
	inGameMenu* _Menu;
	earth* _map;
	cursor* _cursor;
	quick_slot* _quick_slot;

	POINT money_pos;
private:
	bool inven_open;
public:
	HRESULT init();
	void release();
	void update();
	void render();

};

