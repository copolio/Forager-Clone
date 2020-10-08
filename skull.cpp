#include "stdafx.h"
#include "skull.h"

void skull::render(HDC hdc)
{
	IMAGEMANAGER->frameRender(objKey, hdc, CAMERA->GetRelativeX(rc.left), 
		CAMERA->GetRelativeY(rc.top),objFrameX,objFrameY, CAMERA->GetZoom());
}
