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
			pos.x = CAMERA->GetRelativeX((_production[i]->rc.left + _production[i]->rc.right) / 2) * CAMERA->GetZoom();
			pos.y = CAMERA->GetRelativeY((_production[i]->rc.top + _production[i]->rc.bottom) / 2) * CAMERA->GetZoom();

			
			img_alpha[i]+=3;
			if (img_alpha[i] > 255) {
				img_alpha[i] = 0;
				POINT img_pos;
				img_pos.x = (_production[i]->rc.left + _production[i]->rc.right) / 2 ;
				img_pos.y = (_production[i]->rc.top + _production[i]->rc.bottom) / 2 -180;
				EFFECTMANAGER->ShowEffectFrame("img_smoke", img_pos,15,true);
			}
			
			
			if (_production[i]->image_name == "bowDrop") {
				IMAGEMANAGER->alphaRender("bowDrop", hdc, pos.x-25, pos.y-5, _production[i]->alpha);
			}
			else {
				IMAGEMANAGER->alphaRender(_production[i]->image_name, hdc, pos.x - 15, pos.y, _production[i]->alpha);
			}
			
			pos.x += 30 * CAMERA->GetZoom();
			pos.y += 15 * CAMERA->GetZoom();
			TEXTMANAGER->ShowText(hdc, false, to_string(_production[i]->count), pos, 20);
			pos.x = CAMERA->GetRelativeX((_production[i]->rc.left + _production[i]->rc.right) / 2);
			pos.y = CAMERA->GetRelativeY((_production[i]->rc.top + _production[i]->rc.bottom) / 2);
			tagItemInfo _itme_info = DATABASE->GetItem_Make(_production[i]->image_name);
			if (_itme_info.type == MaterialsType::STEELWORK) {
				IMAGEMANAGER->alphaRender("steelwork_yellow", hdc, pos.x - 15, pos.y - 85, img_alpha[i], CAMERA->GetZoom());
			}
			
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
						tagItem _itme_info = DATABASE->GetItem(_production[i]->image_name);
						_production[i]->alpha = 0;
						_production[i]->count--;
						POINT pos;
						pos.x = (_production[i]->rc.left + _production[i]->rc.right) / 2;
						pos.y = (_production[i]->rc.top + _production[i]->rc.bottom) / 2 + 80;
						switch (_itme_info.weaponType)
						{
						case WeaponType::BOW:
							STATMANAGER->SetBowUpgradeCount(STATMANAGER->GetBowUpgradeCount() + 1);
							SOUNDMANAGER->play("레밸업");
							TEXTMANAGER->ShowNotifyText("활 강화가 완료되었습니다!", { WINSIZEX / 2, WINSIZEY / 2 - 190 }, 50, RGB(255, 255, 255), RGB(0, 0, 0), 3);
							ITEMMANAGER->vequip_push(_itme_info.itemKey);
							break;
						case WeaponType::PICKAXE:
							STATMANAGER->SetHammerUpgradeCount(STATMANAGER->GetHammerUpgradeCount() + 1);
							SOUNDMANAGER->play("레벨업");
							TEXTMANAGER->ShowNotifyText("곡괭이 강화가 완료되었습니다!", { WINSIZEX / 2, WINSIZEY / 2 - 190 }, 50, RGB(255, 255, 255), RGB(0, 0, 0), 3);
							ITEMMANAGER->vequip_push(_itme_info.itemKey);
							break;
						case WeaponType::SWORD:
							STATMANAGER->SetSwordUpgradeCount(STATMANAGER->GetSwordUpgradeCount() + 1);
							SOUNDMANAGER->play("레벨업");
							TEXTMANAGER->ShowNotifyText("칼 강화가 완료되었습니다!", { WINSIZEX / 2, WINSIZEY / 2 - 190 }, 50, RGB(255, 255, 255), RGB(0, 0, 0), 3);
							ITEMMANAGER->vequip_push(_itme_info.itemKey);
							break;
						default:
							SOUNDMANAGER->play("생산완료");
							UNITMANAGER->AddProduction(_production[i]->image_name, pos);
							break;
						}

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
}

//같은 건물인지 검사
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

