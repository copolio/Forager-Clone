#pragma once
#include"targetingBox.h"
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
	targetingBox *_targetBox;
	vector<IndustryRc*> indu_rc;
	bool _target;

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

public:
	bool industryItemCheck();
};

