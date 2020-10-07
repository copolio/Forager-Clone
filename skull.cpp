#include "stdafx.h"
#include "skull.h"

void skull::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc, CAMERA->GetRelativeX(GetCenterX()), 
		CAMERA->GetRelativeY(GetCenterY()),objFrameX,objFrameY);


}
