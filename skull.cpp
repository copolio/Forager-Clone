#include "stdafx.h"
#include "skull.h"

void skull::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc, CAMERA->GetRelativeX(rc.left-13), 
		CAMERA->GetRelativeY(rc.top-10),objFrameX,objFrameY, CAMERA->GetZoom());

	

}
