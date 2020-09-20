#include "stdafx.h"
#include "startScene.h"


HRESULT startScene::init()
{
	//렉트 위치 초기화
	_rc = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 200, 200, 100);

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
	Rectangle(getMemDC(), _rc);
	TextOut(getMemDC(), _rc.left + 80, _rc.top + 50, "START", strlen("START"));
}
