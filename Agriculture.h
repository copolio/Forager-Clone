#pragma once
#include "targetingBox.h"
class earth;
enum AGRICULTUREKIND
{
	AGRICULTUREKIND_MISSING,
	AGRICULTUREKIND_BRIDGE,
	AGRICULTUREKIND_FISHTRAP
};
struct  AGRICULTURERc
{
	RECT rc;
	AGRICULTUREKIND kind;
	string name;
};
class Agriculture
{
private:
	targetingBox *_targetBox;
	vector<AGRICULTURERc*> agriRc;
	bool _target;
	void mouse_targetBox();

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void RemoveTarget();
public:
	bool getTarget() { return _target; };
	void setTarget(bool target) { _target = target; };
private:
	bool is_building_check;
	string building;
	image* greentile;
	image* redtile;
	earth* _map;
public:
	void setAgMapLink(earth* map) { _map = map; };
	void renderBuildableTile(HDC hdc);
	bool agricultureItemCheck();
	void addBuilding();
};

