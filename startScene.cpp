#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	IMAGEMANAGER->addImage("img_Logo", "Images/이미지/img_Logo.bmp.bmp", 400, 300, true, RGB(255, 0, 255));
	//렉트 위치 초기화
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 400, 300);

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (INPUT->GetKeyDown(VK_LBUTTON))
	{
		if (PtInRect(&_rc, _ptMouse))
		{
			SCENEMANAGER->loadScene("게임화면");
		}
	}

}

void startScene::render()
{
	IMAGEMANAGER->findImage("img_Logo")->render(getMemDC(), WINSIZEX / 2, WINSIZEY / 2 - 200);
}
