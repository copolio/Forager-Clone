#pragma once
#include"targetingBox.h"
#include "construction_tool_tip.h"
class earth;
enum INDUSTRYKIND
{
	INDUSTRY_MISSING,
	INDUSTRY_STEELWORK,
	INDUSTRY_ANVIL,
	INDUSTRY_SEWINGMACHINE

};
struct IndustryRc
{
	RECT rc;
	INDUSTRYKIND kind;
	string name;
};
class industry
{
private:
	construction_tool_tip* tooltip;
	targetingBox *_targetBox;
	vector<IndustryRc*> indu_rc;
	bool _target;
	string Selection_building;
	
	void mouse_targetBox();
public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
public:
	bool getTarget() { return _target; };
	void setTarget(bool target) { _target = target; };
	void RemoveTarget();
private:
	bool is_building_check;
	string building;
	earth* _map;
public:
	void setInMapLink(earth* map) { _map = map; };
	void renderBuildableTile(HDC hdc);
	bool industryItemCheck();
	void addBuilding();
	void tooltiprender(HDC hdc);
};

