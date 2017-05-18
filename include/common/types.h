#pragma once

namespace Trinity {

// 坐标
class POINT {
  public:
    // 基本数据
    INT32 m_x;
    INT32 m_y;

    // 重载操作符
    BOOL operator==(const POINT &POINT);
    POINT &operator=(const POINT &POINT);

    // 构造函数
    POINT() {}
    POINT(INT32 x, INT32 y);
    POINT(const POINT &POINT);
};

// 矩形
class RECT {
  public:
    // 基本数据
    POINT m_leftTop;
    POINT m_rightBottom;

    // 重载操作符
    BOOL operator==(const RECT &RECT);
    RECT &operator=(const RECT &RECT);

    // POINT是否在RECT里面
    BOOL testPoint(const POINT POINT);

    // 构造函数
    RECT() {}
    RECT(POINT leftTop, POINT rightBottom);
    RECT(INT32 left, INT32 top, INT32 width, INT32 height);
    RECT(const RECT &RECT);
};
}