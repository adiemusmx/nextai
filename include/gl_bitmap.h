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

		// �趨������Դ·��
		bool setPicture(const char *filename);
		
		// ȡ������
		GLuint getTexture();

	private:
		// ��������
		void generateTexture();

		unsigned long sizeX;
		unsigned long sizeY;
		char *Data;
		GLuint texture;
	};

}