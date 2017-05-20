#pragma once

#include "common_types.h"

#include <cstdlib>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/GLU.h>

namespace Trinity {

	class GL_Bitmap
	{
	public:
		GL_Bitmap(const char *fileName);
		virtual ~GL_Bitmap();

		// 设定纹理资源路径
		BOOL setPicturePath(const char* fileName);
		
		// 取得纹理
		GLuint getTexture();

	private:
		// 生成纹理
		void generateTexture();

		unsigned long m_width;
		unsigned long m_height;
		char *m_data;
		GLuint m_texture;
	};

}