#include "gl_bitmap.h"

namespace Trinity {

	GL_Bitmap::GL_Bitmap(const char *FileName) {
		setPicture(FileName);
	}

	bool GL_Bitmap::setPicture(const char *FileName) {
		FILE *File;
		unsigned long size;// ��Ҫ��С
		unsigned long i;// ����
		unsigned short int planes;        //����
		unsigned short int bpp;            // ������
		char temp;                         // ��ɫ���
		
		fopen_s(&File, FileName, "rb");
		if (File == NULL) {
			printf("ͼƬ������");
			return false;
		}
		//�ƶ���ͼ��ĺ���
		fseek(File, 18, SEEK_CUR);
		//��ȡ����
		if ((i = fread(&sizeX, 4, 1, File)) != 1) {
			printf("��ȡʧ��");
			return false;
		}
		//��ȡ����
		if ((i = fread(&sizeY, 4, 1, File)) != 1) {
			printf("��ȡʧ��");
			return false;
		}
		//����ͼ��ĳߴ�
		size = sizeX * sizeY * 3;
		if ((fread(&planes, 2, 1, File)) != 1) {   //bmp��1
			printf("��ȡʧ��");
			return false;
		}
		if (planes != 1) {
			printf("����bmpͼ��");
			return false;
		}
		//��ȡ����ֵ
		if ((i = fread(&bpp, 2, 1, File)) != 1) {
			printf("��ȡ����ֵʧ��");
			return false;
		}
		if (bpp != 24) {//�������24bpp�Ļ�ʧ��
			printf("����24bitͼ��");
			return false;
		}
		//����24bit�����RGB����
		fseek(File, 24, SEEK_CUR);    //��ȡ����
		Data = (char *)malloc(size);
		if (Data == NULL) {
			printf("�ڴ�����������");
			return false;
		}
		if ((i = fread(Data, size, 1, File)) != 1) {
			printf("���ܶ�ȡ����");
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