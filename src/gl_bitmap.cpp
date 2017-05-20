#include "gl_bitmap.h"
#include "log.h"

namespace Trinity {

	GL_Bitmap::GL_Bitmap(const char* fileName) {
		m_texture = 0;
		setPicturePath(fileName);
	}

	GL_Bitmap::~GL_Bitmap() {
		if (glIsTexture(m_texture))
		{
			glDeleteTextures(1, &m_texture);
		}
	}

	BOOL GL_Bitmap::setPicturePath(const char* fileName) 
	{
		FILE *fp;
		unsigned long size;					// 主要大小
		unsigned long i;					// 计数
		unsigned short int planes;			//面数
		unsigned short int bpp;				// 像素数
		char temp;							// 颜色相关

		fopen_s(&fp, fileName, "rb");
		if (fp == NULL) {
			TRI_ERROR_LOG("Image[%s] do NOT exist.", fileName);
			return FALSE;
		}
		//移动至图像的横向
		fseek(fp, 18, SEEK_CUR);

		//读取横向
		if ((i = fread(&m_width, 4, 1, fp)) != 1) {
			TRI_ERROR_LOG("Image[%s] read width failed.", fileName);
			return FALSE;
		}
		//读取纵向
		if ((i = fread(&m_height, 4, 1, fp)) != 1) {
			TRI_ERROR_LOG("Image[%s] read height failed.", fileName);
			return FALSE;
		}
		//计算图像的尺寸
		size = m_width * m_height * 3;
		if ((fread(&planes, 2, 1, fp)) != 1) {   //bmp填1
			TRI_ERROR_LOG("Image[%s] read planes' flag failed.", fileName);
			return FALSE;
		}
		if (planes != 1) {
			TRI_ERROR_LOG("Image[%s] is not bmp file.", fileName);
			return FALSE;
		}
		//读取像素值
		if ((i = fread(&bpp, 2, 1, fp)) != 1) {
			TRI_ERROR_LOG("Can NOT read Image[%s] bpp.", fileName);
			return FALSE;
		}
		if (bpp != 24) {//如果不是24bpp的话失败
			TRI_ERROR_LOG("Image[%s] is not 24bpp.", fileName);
			return FALSE;
		}
		//跳过24bit，监测RGB数据
		fseek(fp, 24, SEEK_CUR);    //读取数据
		m_data = (char *)malloc(size);
		if (m_data == NULL) {
			TRI_ERROR_LOG("Image[%s]'s malloc failed.", fileName);
			return FALSE;
		}
		if ((i = fread(m_data, size, 1, fp)) != 1) {
			TRI_ERROR_LOG("Can NOT read image[%s] data.", fileName);
			return FALSE;
		}
		for (i = 0; i < size; i += 3) { //bgr -> rgb
			temp = m_data[i];
			m_data[i] = m_data[i + 2];
			m_data[i + 2] = temp;
		}

		generateTexture();

		return TRUE;
	}

	void GL_Bitmap::generateTexture()
	{
		if (glIsTexture(m_texture))
			glDeleteTextures(1, &m_texture);

		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &m_texture);
		glBindTexture(GL_TEXTURE_2D, m_texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint GL_Bitmap::getTexture()
	{
		return m_texture;
	}
}