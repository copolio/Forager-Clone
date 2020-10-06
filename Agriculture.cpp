#include "stdafx.h"
#include "Agriculture.h"



HRESULT Agriculture::init()
{
	_target = false;
	_targetBox = new targetingBox;
	_targetBox->init();

	AGRICULTURERc *push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_BRIDGE;
	push->name = "bridge";
	push->rc = RectMake(WINSIZEX - 267, 235, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_FISHTRAP;
	push->name = "fishtrap";
	push->rc = RectMake(WINSIZEX - 267, 295, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 355, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 415, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 475, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 535, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 595, 220, 50);
	agriRc.push_back(push);

	push = new AGRICULTURERc;
	push->kind = AGRICULTUREKIND_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 655, 220, 50);
	agriRc.push_back(push);

	return S_OK;
}

void Agriculture::release()
{
}

void Agriculture::update()
{
	if (_target) {
		_targetBox->update();
	}
	mouse_targetBox();
}

void Agriculture::render(HDC hdc)
{
	for (int i = 0; i < agriRc.size(); i++) {
		switch (agriRc[i]->kind)
		{
		case AGRICULTUREKIND_MISSING:
			IMAGEMANAGER->render("img_Agriculture_missing_icon", hdc, agriRc[i]->rc.left, agriRc[i]->rc.top);
			break;
		case AGRICULTUREKIND_BRIDGE:
			cout << "a" << endl;
			IMAGEMANAGER->render("img_bridge_icon", hdc, agriRc[i]->rc.left, agriRc[i]->rc.top);
			break;
		case AGRICULTUREKIND_FISHTRAP:
			IMAGEMANAGER->render("img_fish_trap_icon", hdc, agriRc[i]->rc.left, agriRc[i]->rc.top);
			break;
		}

	}
	_targetBox->render(hdc);
}


void Agriculture::mouse_targetBox()
{
	for (int i = 0; i < agriRc.size(); i++) {
		if (PtInRect(&agriRc[i]->rc, _ptMouse)) {
			_targetBox->SetTarget(agriRc[i]->rc, 2, i, 4, false);
			_target = true;
			break;
		}
		
	}
}

void Agriculture::RemoveTarget()
{
	_targetBox->RemoveTarget();
}
