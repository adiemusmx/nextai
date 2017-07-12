#pragma once

#include "common_types.h"

#include <cstdlib>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/glu.h>

namespace Trinity {

class GL_Bitmap
{
public:
	GL_Bitmap(const char *fileName);
	virtual ~GL_Bitmap();

	// 设定文件路径
	BOOL setPath(const char* fileName);

	// 设定描画区域
	virtual void setArea(const RECT& area);
	virtual const RECT& getArea();

	// 描画函数
	void draw();

private:
	// 取得已经加载的图片纹理
	GLuint getTexture();

private:
	// 生成图片纹理
	void generateTexture();

	// 图片宽度和高度
	unsigned long m_width;
	unsigned long m_height;

	// 图片数据
	char *m_data;

	// 描画位置
	RECT m_area;

	// 纹理ID
	GLuint m_texture;
};

}
