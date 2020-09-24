#include "stdafx.h"
#include "farming.h"

HRESULT farming::init()
{
	berryDrop = IMAGEMANAGER->addImage("berry", "berry.bmp", 56, 56, true, RGB(255, 0, 255));


	return S_OK;
}

void farming::release()
{
}

void farming::update()
{
	
}

void farming::render()
{
	//for (int i = 0; i < _tiles.size(); i++)
	//{
	//	if (_tiles[i].objHp < 0 && _tiles[i].object == IMAGEMANAGER->findImage("tree"))
	//	{
	//		IMAGEMANAGER->findImage("berry")->render(getMemDC(), _tiles[i].rc.left, _tiles[i].rc.top);
	//
	//	}
	//}
}
