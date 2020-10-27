#pragma once
#include "singletonBase.h"
#include "item.h"

#define UPGRADE_MAX 3

class ItemDatabase : public singletonBase<ItemDatabase>
{

private:
	map<string, tagItem> _itemDictionary;

	int _hammerUpgradeCount;
	int _swordUpgradeCount;
	int _bowUpgradeCount;
	int _staffUpgradeCount;

	float _enhancingRatio[UPGRADE_MAX];	// 강화 데미지 증폭 비율



public:
	void init();



public:
	tagItem GetItem(string p_key) { return _itemDictionary[p_key]; };
	float GetEnhanceRatio(int p_num) { return _enhancingRatio[p_num]; };

public:
	int GetHammerUpgradeCount() { return _hammerUpgradeCount; };
	int GetSwordUpgradeCount() { return _swordUpgradeCount; };
	int GetBowUpgradeCount() { return _bowUpgradeCount; };
	int GetStaffUpgradeCount() { return _staffUpgradeCount; };

	void SetHammerUpgradeCount(int p_num) { _hammerUpgradeCount = p_num; };
	void SetSwordUpgradeCount(int p_num) { _swordUpgradeCount = p_num; };
	void SetBowUpgradeCount(int p_num) { _bowUpgradeCount = p_num; };
	void SetStaffUpgradeCount(int p_num) { _staffUpgradeCount = p_num; };


};

