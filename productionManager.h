#pragma once
#include "singletonBase.h"
#include "item.h"
struct tagProduction
{
	RECT rc;
	string image_name;
	int count;
	int alpha;
	bool countStart;
	

};
struct tagSmoke
{
	RECT rc;
	POINT pos;
	image* img;
	int image_count;
	int image_index;
};
class productionManager :public singletonBase<productionManager>
{

private:
	vector<tagProduction*>  _production;
	int count;
	int img_alpha[50] = {0};


	int img_count;
	int img_index;
	RECT Myrc;
private:
	void count_increase();
	int isCilck(RECT rc);


public:
	void settion(RECT rc);
	void init();
	void relese();
	void update();
	void render(HDC hdc);
	
	
	vector<tagProduction*> getProduction() {
		return _production;
	};

public:

	void getRc(RECT _rc) {
		Myrc = _rc;
	}
	void isCount( string name);
	bool is_Item_Cilck(string name);

	void removeBuildingRc(RECT rc);
};

