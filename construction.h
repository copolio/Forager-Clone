#pragma once
#include "targetingBox.h"
enum CONSTRUCTIONKIND
{
	INDUSTRY,
	AGRICULTURE,
};
enum INDUSTRYKIND
{
	STEELWORK,
	SEWINGMACHINE,
};
struct Con_Info
{
	CONSTRUCTIONKIND kind;
	RECT rc;
	bool isInfo;
};
struct IndustryRc
{
	INDUSTRYKIND kind;
	RECT rc;
};
class construction
{
private:
	targetingBox *_targetBox;
	vector<Con_Info*> _industry_Rc;

	bool isCheck;
	bool isTargetBox;
public:

	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);
	void BoxMove();
	void mouse_targetBox();

	void setIsCheck(bool check) {
		isCheck = check;
	}

	void setisTargetBox(bool check) {
		isTargetBox = check;
	}
};

