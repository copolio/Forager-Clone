#pragma once
#include "inventory.h"
#include "gameNode.h"
#include "inventory_images.h"
class inventory_test_scenes :public gameNode
{
private:
	inventory* _IGM;
	inventory_images* inven_img;

public:
	HRESULT init();
	void release();
	void update();
	void render();

};

