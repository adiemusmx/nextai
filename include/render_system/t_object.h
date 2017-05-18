#pragma once

#include "common/types.h"

#define INVALID_ID (-1)
#define CHLIDREN_NUM (50)

namespace Trinity {

class TObject {
  public:
    TObject(TObject *parent, Rect area);
    virtual ~TObject();

    // ID
    const OBJECT_ID getId();
    void setId(OBJECT_ID id);
    TObject *getObjectById(OBJECT_ID id);

    // 描画
    virtual void draw();
    virtual void drawImpl();

    // 点击函数，返回值用于判断是否需要其他部品继续处理该压下
    virtual bool hit(const Point point, const E_HIT_TYPE hitType);
    virtual bool hitImpl(const Point point, const E_HIT_TYPE hitType);

    // 控件位置
    virtual void setArea(const Rect area);
    virtual const Rect getArea();

  private:
    D_DISABLE_COPY(TObject);

    // 追加子控件
    void addChild(TObject *id);

    // 删除子控件
    bool removeChild(OBJECT_ID id);
    void removeALLChild();

  private:
    // ID
    OBJECT_ID m_id;

    // 父控件
    TObject *m_parent;

    // 子控件
    TObject *m_children[CHLIDREN_NUM];

    // 控件的区域
    Rect m_area;

    // 是否处理hit消息
    bool m_isHitEnable;

    // 是否能够进行描画
    bool m_enable;

    // 是否传递hit消息
    bool m_isHitTrans;
};
}