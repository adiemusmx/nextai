#pragma once

#include <cstdlib>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/GLU.h>

namespace Trinity {

	class GL_Bitmap
	{
	public:
		GL_Bitmap(const char *FileName);

		// 设定纹理资源路径
		bool setPicture(const char *filename);
		
		// 取得纹理
		GLuint getTexture();

	private:
		// 生成纹理
		void generateTexture();

		unsigned long sizeX;
		unsigned long sizeY;
		char *Data;
		GLuint texture;
	};

}