#include "stdafx.h"
#include "productionManager.h"



void productionManager::init()
{
	count = 0;
}

void productionManager::relese()
{
}

void productionManager::update()
{

	count_increase();
	//cout << Myrc.left << endl;;
}

void productionManager::render(HDC hdc)
{
	for (int i = 0; i < _production.size(); i++) {
		if (_production[i]->countStart) {
			POINT pos;
			pos.x = CAMERA->GetRelativeX((_production[i]->rc.left + _production[i]->rc.right) / 2);
			pos.y = CAMERA->GetRelativeY((_production[i]->rc.top + _production[i]->rc.bottom) / 2);
			IMAGEMANAGER->alphaRender(_production[i]->image_name, hdc,pos.x-15, pos.y, _production[i]->alpha);
			pos.x += 15;
			pos.y += 15;
			TEXTMANAGER->ShowText(hdc, false, to_string(_production[i]->count), pos, 20);
		}
	}
}

void productionManager::count_increase()
{
	count++;
	if (count > 5) {
		count = 0;
		for (int i = 0; i < _production.size(); i++) {
			if (_production[i]->countStart) {
				if (_production[i]->count > 0) {
					_production[i]->alpha++;
					if (_production[i]->alpha > 255) {
						_production[i]->alpha = 0;
						_production[i]->count--;
						POINT pos;
						pos.x =	(_production[i]->rc.left + _production[i]->rc.right) / 2;
						pos.y = (_production[i]->rc.top + _production[i]->rc.bottom) / 2+80;
						UNITMANAGER->AddProduction(_production[i]->image_name, pos);
					}
				}
				else {
					_production[i]->countStart = false;
					
					_production[i]->image_name = "";
					
				}
			}

		}
	}
	
	
}

//카운트값 증가

void productionManager::settion(RECT rc)
{
	if (isCilck(rc) == -1)
	{
		tagProduction* _pro = new tagProduction;
		_pro->rc = rc;
		_pro->count = 0;
		_pro->alpha = 0;
		_pro->image_name = "";
		_pro->countStart = false;
		_production.push_back(_pro);
	}
}//처음 e를 눌렀을때 그위치 저장.


int productionManager::isCilck(RECT rc)
{
	for (int i = 0; i < _production.size(); i++) {
		if (_production[i]->rc.left == rc.left && _production[i]->rc.top == rc.top && _production[i]->rc.bottom == rc.bottom&&_production[i]->rc.right == rc.right) {
			return i;
		}
	}
	return -1;
}//같은 건물인지 검사
void productionManager::isCount(string name)
{
	int cilck = isCilck(this->Myrc);
	if (cilck != -1) {
		if (_production[cilck]->image_name == "") {
			_production[cilck]->image_name = name;
			_production[cilck]->count++;
			_production[cilck]->countStart = true;
		}else if (_production[cilck]->image_name == name) {
			_production[cilck]->count++;
		}
	}
}

bool productionManager::is_Item_Cilck(string name)
{
	int cilck = isCilck(this->Myrc);
	if (cilck != -1) {
		if (_production[cilck]->image_name == "" || _production[cilck]->image_name == name) {
			return true;
		}
	}
	return false;
}

void productionManager::removeBuildingRc(RECT rc)
{
	for (int i = 0; i < _production.size(); i++) {
		if (_production[i]->rc.left == rc.left && _production[i]->rc.top == rc.top && _production[i]->rc.bottom == rc.bottom&&_production[i]->rc.right == rc.right) {
			_production.erase(_production.begin() + i);
			break;
		}
	}
}

