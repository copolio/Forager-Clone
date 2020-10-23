#include "stdafx.h"
#include "construction.h"

HRESULT construction::init()
{
	_targetBox = new targetingBox;
	_targetBox->init();
	//_industry_Rc.push_back(RectMake(WINSIZEX - 280, 30, 226, 72));
	Con_Info* con = new Con_Info;
	con->rc = RectMake(WINSIZEX - 280, 30, 250, 80);
	con->kind = INDUSTRY;
	_industry_Rc.push_back(con);

	con = new Con_Info;
	con->rc = RectMake(WINSIZEX - 280, 150, 250, 80);
	con->kind = AGRICULTURE;
	_industry_Rc.push_back(con);

	isCheck = false;
	isTargetBox = false;
	agrocultureCheck = false;

	_industry = new industry;
	_industry->init();

	_agriculture = new Agriculture;
	_agriculture->init();

	return S_OK;
}

void construction::release()
{
	SAFE_DELETE(_industry);
	_industry = NULL;
	SAFE_DELETE(_agriculture);
	_agriculture = NULL;
};

void construction::update()
{
	_targetBox->update();
	mouse_targetBox();
	if (isCheck) {
		_industry->update();
	}
	if (agrocultureCheck) {
		_agriculture->update();
	}
	BoxMove();
	if (isTargetBox) {
		mouse_Click();
	}
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
		_industry->render(hdc);
	}
	if (agrocultureCheck) {
		_agriculture->render(hdc);
	}
	if (!_agriculture->getTarget() && !_industry->getTarget()) {
		if (isTargetBox) {
			_targetBox->render(hdc);
		}
	}

	
}

void construction::BoxMove()
{
	if (isCheck) {
		for (int i = 0; i < _industry_Rc.size(); i++) {
			if (_industry_Rc[i]->kind == INDUSTRY) continue;
			_industry_Rc[i]->rc = RectMake(WINSIZEX - 280, 150+480, 250, 80);
		}

	}
	else {
		for (int i = 0; i < _industry_Rc.size(); i++) {
			if (_industry_Rc[i]->kind == INDUSTRY) continue;
			_industry_Rc[i]->rc = RectMake(WINSIZEX - 280, 150 , 250, 80);
		}
	}
}

void construction::mouse_targetBox()
{
	
	for (int i = 0; i < _industry_Rc.size(); i++) {
		if (PtInRect(&_industry_Rc[i]->rc, _ptMouse)) {
			_targetBox->SetTarget(_industry_Rc[i]->rc, 2, i, 4, false);
			_agriculture->setTarget(false);
			_industry->setTarget(false);
			isTargetBox = true;
			_agriculture->RemoveTarget();
			_industry->RemoveTarget();
			break;
		}
	}
}

void construction::mouse_Click()
{
	for (int i = 0; i < _industry_Rc.size(); i++) {
		if (PtInRect(&_industry_Rc[i]->rc, _ptMouse) && INPUT->GetKeyDown(VK_LBUTTON))
		{
			SOUNDMANAGER->play("°Ç¼³ÅÇ¼±ÅÃ");
			if (_industry_Rc[i]->kind == INDUSTRY) {
				agrocultureCheck = false;
				if (isCheck) {
					isCheck = false;
				}
				else {
					isCheck = true;

				}
			}
			else if (_industry_Rc[i]->kind == AGRICULTURE) {
				isCheck = false;
				if (agrocultureCheck) {

					agrocultureCheck = false;
				}
				else {
					agrocultureCheck = true;
				}
			}

		}
		
	}
}

void construction::setting()
{
	isCheck = false;
	isTargetBox = false;
	agrocultureCheck = false;
}
