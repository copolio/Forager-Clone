#include "stdafx.h"
#include "construction.h"

HRESULT construction::init()
{
	_targetBox = new targetingBox;
	_targetBox->init();
	//_industry_Rc.push_back(RectMake(WINSIZEX - 280, 30, 226, 72));
	Con_Info* con = new Con_Info;
	con->rc = RectMake(WINSIZEX - 280, 30, 226, 72);
	con->kind = INDUSTRY;
	_industry_Rc.push_back(con);
	con = new Con_Info;
	con->rc = RectMake(WINSIZEX - 280, 150, 226, 72);
	con->kind = AGRICULTURE;
	_industry_Rc.push_back(con);
	isCheck = false;
	isTargetBox = false;
	return S_OK;
}

void construction::release()
{
}

void construction::update()
{
	_targetBox->update();
	mouse_targetBox();
	BoxMove();
}

void construction::render(HDC hdc)
{
	IMAGEMANAGER->render("inventory_Kinds", hdc, WINSIZEX / 2 - 240, 15);
	IMAGEMANAGER->render("Q", hdc, 320, 70);
	IMAGEMANAGER->render("E", hdc, 890, 70);
	IMAGEMANAGER->render("img_construction_icon", hdc, 597, 30);
	IMAGEMANAGER->alphaRender("construction_background", hdc, 960, 0, 180);
	IMAGEMANAGER->render("img_industry_icon", hdc, WINSIZEX - 280, 30);
	for (int i = 0; i < _industry_Rc.size(); i++) {
		switch (_industry_Rc[i]->kind)
		{
		case INDUSTRY:
			IMAGEMANAGER->render("img_industry_icon", hdc, _industry_Rc[i]->rc.left, _industry_Rc[i]->rc.top);
			break;
		case AGRICULTURE:
			IMAGEMANAGER->render("img_Agriculture_icon", hdc, _industry_Rc[i]->rc.left, _industry_Rc[i]->rc.top);
			break;
		}
	}
	if (isCheck) {
		IMAGEMANAGER->render("img_steelwork_icon", hdc, WINSIZEX - 267, 98);
	}
	if (isTargetBox) {
		_targetBox->render(hdc);
	}
	/*for (int i = 0; i < _industry_Rc.size(); i++) {
		Rectangle(hdc, _industry_Rc[i]);
	}*/
	
}

void construction::BoxMove()
{
	if (isCheck) {
		for (int i = 0; i < _industry_Rc.size(); i++) {
			if (_industry_Rc[i]->kind == INDUSTRY) continue;

			_industry_Rc[i]->rc = RectMake(WINSIZEX - 280, 150+60, 226, 72);
		}

	}
	else {
		for (int i = 0; i < _industry_Rc.size(); i++) {
			if (_industry_Rc[i]->kind == INDUSTRY) continue;

			_industry_Rc[i]->rc = RectMake(WINSIZEX - 280, 150 , 226, 72);
		}
	}
}

void construction::mouse_targetBox()
{
	
	for (int i = 0; i < _industry_Rc.size(); i++) {
		if (PtInRect(&_industry_Rc[i]->rc, _ptMouse)) {
			_targetBox->SetTarget(_industry_Rc[i]->rc, 2, i, 4, false);
			isTargetBox = true;
			if (INPUT->GetKeyDown(VK_LBUTTON)&& _industry_Rc[i]->kind == INDUSTRY) {
				if (isCheck) {
					isCheck = false;

				}
				else {
					isCheck = true;

				}
			}
			break;
		}
	}

	if (isCheck) {


	}
	
}
