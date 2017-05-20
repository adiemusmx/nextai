#pragma once

#include "gl_object.h"
#include "gl_bitmap.h"

namespace Trinity {
class GL_Picture : public GL_Object {
  public:
    GL_Picture(GL_Object *parent);
    virtual ~GL_Picture();

    // 描画函数
    virtual void Draw();

    // 设定图片路径，最大D_FILE_PATH_MAX_LENGTH
    void setPicturePath(const char *path);

  private:
    // 禁止拷贝
    CLASS_disableCopy(GL_Picture);

	GL_Bitmap* m_bmp;
};
}