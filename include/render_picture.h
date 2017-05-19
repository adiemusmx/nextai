#pragma once

#include "render_system/objects/object.h"

namespace Trinity {
class Picture {
  public:
    Picture();
    virtual ~Picture();

    // 描画函数
    virtual void Draw();

    // 设定图片路径
    void setPicturePath(const char *path);

  private:
    // 禁止拷贝
    D_DISABLE_COPY(Picture);

    char m_picturePath[MAX_FILE_NAME_LENGTH];
};
}