#pragma once

#include "common_define.h"
#include "gl_bitmap.h"
#include "widget_object.h"

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
	DISABLE_CLASS_COPY(WidgetPicture);

private:
	GL_Bitmap* m_bmp;
};
}