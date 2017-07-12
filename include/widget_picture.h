#pragma once

#include "gl_bitmap.h"

namespace Trinity {

class WidgetPicture : public WidgetObject
{
public:
	WidgetPicture(ObjectId id);
	virtual ~WidgetPicture();

	// 设定/取得区域
	virtual void setArea(const RECT& area);

	// 重载描画函数
	virtual void drawImpl();

private:
	D_CLASS_DISABLE_COPY(WidgetPicture);

private:
	GL_Bitmap* m_bmp;
};
}