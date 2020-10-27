#include "stdafx.h"
#include "TextureManager.h"

void TextureManager::render(HDC hdc)
{

	Sorting();

	for (auto iter = _lRenderObject.begin(); iter != _lRenderObject.end(); ++iter) {

		if (iter->isFrameImage) {
			IMAGEMANAGER->frameRender(iter->imgKey, hdc, (*iter->rc).left, (*iter->rc).top, *iter->frameX, *iter->frameY, CAMERA->GetZoom());
		}
		else if (iter->isAlaphImage) {
			IMAGEMANAGER->alphaRender(iter->imgKey, hdc, (*iter->rc).left, (*iter->rc).top, *iter->alpha, CAMERA->GetZoom());
		}
		else {
			IMAGEMANAGER->render(iter->imgKey, hdc, (*iter->rc).left, (*iter->rc).top, CAMERA->GetZoom());
		}
	}

}

void TextureManager::release()
{
	_lRenderObject.clear();
}

// yÃà Á¤·Ä
void TextureManager::Sorting()
{
	sort(_lRenderObject.begin(), _lRenderObject.end(), Compare);
}

bool TextureManager::Compare(tagRender * a, tagRender * b)
{
	return (*a).rc->bottom < (*b).rc->bottom;
}



void TextureManager::AddRender(string p_imgKey, RECT *rc, LAYER p_layer, int* p_frameX, int* p_frameY, BYTE* p_alpha, bool isFrameImage)
{

	tagRender t_render;
	t_render.imgKey = p_imgKey;
	t_render.layer = p_layer;
	t_render.rc = rc;
	if (p_frameX != nullptr)
	{
		t_render.frameX = p_frameX;
		t_render.frameY = p_frameY;
	}

	t_render.isFrameImage = isFrameImage;

	if (p_alpha != nullptr) {
		t_render.isAlaphImage = true;
		t_render.alpha = p_alpha;
	}

	_lRenderObject.push_back(t_render);
}

void TextureManager::CheckRemoveRenderObject()
{
	for (auto iter = _lRenderObject.begin(); iter != _lRenderObject.end();) {
		if ((*iter).rc == nullptr) {
			iter = _lRenderObject.erase(iter);
		}
		else
			++iter;
	}

}
