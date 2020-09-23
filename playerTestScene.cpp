#include "stdafx.h"
#include "playerTestScene.h"

HRESULT playerTestScene::init()
{
	_player = new ForagerPlayer;
	_statManager = new ForagerStatManager;

	_player->init();
	_statManager->init();


	return S_OK;
}

void playerTestScene::release()
{

	//_player->release();
	//_statManager->release();
}

void playerTestScene::update()
{
	_player->update();
	_statManager->update();
}

void playerTestScene::render()
{
	_player->render();
	_statManager->render();
}
