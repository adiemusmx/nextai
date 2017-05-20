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
		unsigned long size;					// ��Ҫ��С
		unsigned long i;					// ����
		unsigned short int planes;			//����
		unsigned short int bpp;				// ������
		char temp;							// ��ɫ���

		fopen_s(&fp, fileName, "rb");
		if (fp == NULL) {
			TRI_ERROR_LOG("Image[%s] do NOT exist.", fileName);
			return FALSE;
		}
		//�ƶ���ͼ��ĺ���
		fseek(fp, 18, SEEK_CUR);

		//��ȡ����
		if ((i = fread(&m_width, 4, 1, fp)) != 1) {
			TRI_ERROR_LOG("Image[%s] read width failed.", fileName);
			return FALSE;
		}
		//��ȡ����
		if ((i = fread(&m_height, 4, 1, fp)) != 1) {
			TRI_ERROR_LOG("Image[%s] read height failed.", fileName);
			return FALSE;
		}
		//����ͼ��ĳߴ�
		size = m_width * m_height * 3;
		if ((fread(&planes, 2, 1, fp)) != 1) {   //bmp��1
			TRI_ERROR_LOG("Image[%s] read planes' flag failed.", fileName);
			return FALSE;
		}
		if (planes != 1) {
			TRI_ERROR_LOG("Image[%s] is not bmp file.", fileName);
			return FALSE;
		}
		//��ȡ����ֵ
		if ((i = fread(&bpp, 2, 1, fp)) != 1) {
			TRI_ERROR_LOG("Can NOT read Image[%s] bpp.", fileName);
			return FALSE;
		}
		if (bpp != 24) {//�������24bpp�Ļ�ʧ��
			TRI_ERROR_LOG("Image[%s] is not 24bpp.", fileName);
			return FALSE;
		}
		//����24bit�����RGB����
		fseek(fp, 24, SEEK_CUR);    //��ȡ����
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