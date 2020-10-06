#pragma once
#include "targetingBox.h"
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


};

