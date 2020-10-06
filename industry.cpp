#include "stdafx.h"
#include "industry.h"


HRESULT industry::init()
{
	_target = false;
	_targetBox = new targetingBox;
	_targetBox->init();
	IndustryRc *push = new IndustryRc;

	push->kind = INDUSTRY_STEELWORK;
	push->rc = RectMake(WINSIZEX - 267, 115, 220, 50);
	push->name = "steelwork";
	indu_rc.push_back(push);
	
	push = new IndustryRc;
	push->kind = INDUSTRY_ANVIL;
	push->name = "anvil";
	push->rc = RectMake(WINSIZEX - 267, 175, 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_SEWINGMACHINE;
	push->name = "sewingmachine";
	push->rc = RectMake(WINSIZEX - 267, 235 , 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 295, 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 355, 220, 50);
	indu_rc.push_back(push);


	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 415, 220, 50);
	indu_rc.push_back(push);

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 475, 220, 50);
	indu_rc.push_back(push); 

	push = new IndustryRc;
	push->kind = INDUSTRY_MISSING;
	push->name = "missing";
	push->rc = RectMake(WINSIZEX - 267, 535, 220, 50);
	indu_rc.push_back(push);
	return S_OK;


}

void industry::release()
{
}

void industry::update()
{
	if (_target) {
		_targetBox->update();
	}
	mouse_targetBox();
	
}

void industry::render(HDC hdc)
{
	for (int i = 0; i < indu_rc.size(); i++) {
		switch (indu_rc[i]->kind)
		{
		case INDUSTRY_MISSING:
			IMAGEMANAGER->render("img_missing_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		case INDUSTRY_STEELWORK:
			IMAGEMANAGER->render("img_steelwork_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		case INDUSTRY_ANVIL:
			IMAGEMANAGER->render("img_anvil_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		case INDUSTRY_SEWINGMACHINE:
			IMAGEMANAGER->render("img_sewingmachine_icon", hdc, indu_rc[i]->rc.left, indu_rc[i]->rc.top);
			break;
		}

	}
	_targetBox->render(hdc);
}


void industry::mouse_targetBox()
{
	for (int i = 0; i < indu_rc.size(); i++) {
		if (PtInRect(&indu_rc[i]->rc, _ptMouse)) {
			_targetBox->SetTarget(indu_rc[i]->rc, 2, i, 4, false);
			_target = true;
			break;
		}

	}
}

void industry::RemoveTarget()
{
	_targetBox->RemoveTarget();
}

bool industry::industryItemCheck()
{
	for (int i = 0; i < indu_rc.size(); i++) {
		if (PtInRect(&indu_rc[i]->rc, _ptMouse) && indu_rc[i]->kind != INDUSTRY_MISSING&& INPUT->GetKeyDown(VK_LBUTTON)) {
		
			if (indu_rc[i]->kind == INDUSTRY_STEELWORK) {
				return ITEMMANAGER->Item_industry_check("steelwork");
			}
			else if (indu_rc[i]->kind == INDUSTRY_ANVIL) {
				return ITEMMANAGER->Item_industry_check("anvil");
			}
			else if (indu_rc[i]->kind == INDUSTRY_SEWINGMACHINE) {
				return ITEMMANAGER->Item_industry_check("sewingmachine");
			}
			
		}
	}
	return false;
}
