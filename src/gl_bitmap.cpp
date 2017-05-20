#include "gl_bitmap.h"

namespace Trinity {

	GL_Bitmap::GL_Bitmap(const char *FileName) {
		setPicture(FileName);
	}

	bool GL_Bitmap::setPicture(const char *FileName) {
		FILE *File;
		unsigned long size;// 主要大小
		unsigned long i;// 计数
		unsigned short int planes;        //面数
		unsigned short int bpp;            // 像素数
		char temp;                         // 颜色相关
		
		fopen_s(&File, FileName, "rb");
		if (File == NULL) {
			printf("图片不存在");
			return false;
		}
		//移动至图像的横向
		fseek(File, 18, SEEK_CUR);
		//读取横向
		if ((i = fread(&sizeX, 4, 1, File)) != 1) {
			printf("读取失败");
			return false;
		}
		//读取纵向
		if ((i = fread(&sizeY, 4, 1, File)) != 1) {
			printf("读取失败");
			return false;
		}
		//计算图像的尺寸
		size = sizeX * sizeY * 3;
		if ((fread(&planes, 2, 1, File)) != 1) {   //bmp填1
			printf("读取失败");
			return false;
		}
		if (planes != 1) {
			printf("不是bmp图像");
			return false;
		}
		//读取像素值
		if ((i = fread(&bpp, 2, 1, File)) != 1) {
			printf("读取像素值失败");
			return false;
		}
		if (bpp != 24) {//如果不是24bpp的话失败
			printf("不是24bit图像");
			return false;
		}
		//跳过24bit，监测RGB数据
		fseek(File, 24, SEEK_CUR);    //读取数据
		Data = (char *)malloc(size);
		if (Data == NULL) {
			printf("内存量不能锁定");
			return false;
		}
		if ((i = fread(Data, size, 1, File)) != 1) {
			printf("不能读取数据");
			return false;
		}
		for (i = 0; i < size; i += 3) { //bgr -> rgb
			temp = Data[i];
			Data[i] = Data[i + 2];
			Data[i + 2] = temp;
		}

		generateTexture();

		return true;
	}

	void GL_Bitmap::generateTexture()
	{
		glEnable(GL_TEXTURE_2D);
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	GLuint GL_Bitmap::getTexture()
	{
		return texture;
	}
}