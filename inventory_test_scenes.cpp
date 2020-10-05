#include "stdafx.h"
#include "inventory_test_scenes.h"

HRESULT inventory_test_scenes::init()
{
	inven_img = new inventory_images;
	_IGM = new inventory;
	
	inven_img->init();
	_IGM->init();

	return S_OK;
}

void inventory_test_scenes::release()
{
	_IGM->release();
}

void inventory_test_scenes::update()
{
	_IGM->update();
}

void inventory_test_scenes::render()
{
	
	_IGM->render(getMemDC());
}
