#pragma once
#include "basicmap.h"
class farming 
{
private:
	image* treeDrop;
	image* rockDrop;
	image* berryDrop;
private:
	//basicmap* _map;
public:
	


	HRESULT init();
	void release();
	void update();
	void render();

	
	

	//void setBMLink(vector<tile> _vtiles) { _tiles = _vtiles; };
};

