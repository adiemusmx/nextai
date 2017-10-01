#include "trinity_gl_bitmap.h"
#include "trinity_util_log.h"

namespace Trinity
{
GL_Bitmap::GL_Bitmap(const char* fileName)
{
	m_texture = 0;
	m_width = 0;
	m_height = 0;
	m_data = NULL;
	setPath(fileName);
}

GL_Bitmap::~GL_Bitmap()
{
	if (glIsTexture(m_texture))
	{
		glDeleteTextures(1, &m_texture);
	}
}

BOOL GL_Bitmap::setPath(const char* fileName)
{
	FILE* fp;
	unsigned long size;
	unsigned long i;
	unsigned short int planes;
	unsigned short int bpp;
	char temp;

	fp = fopen(fileName, "rb");

	if (fp == NULL)
	{
		TRI_ERROR_LOG("Image[%s] do NOT exist.", fileName);
		return FALSE;
	}
	fseek(fp, 18, SEEK_CUR);

	if ((i = fread(&m_width, 4, 1, fp)) != 1)
	{
		TRI_ERROR_LOG("Image[%s] read width failed.", fileName);
		return FALSE;
	}

	if ((i = fread(&m_height, 4, 1, fp)) != 1)
	{
		TRI_ERROR_LOG("Image[%s] read height failed.", fileName);
		return FALSE;
	}

	TRI_INFO_LOG("m_width[%lu] m_height[%lu]", m_width, m_height)
	size = m_width * m_height * 3;
	if ((fread(&planes, 2, 1, fp)) != 1)
	{
		TRI_ERROR_LOG("Image[%s] read planes' flag failed.", fileName);
		return FALSE;
	}
	if (planes != 1)
	{
		TRI_ERROR_LOG("Image[%s] is not bmp file.", fileName);
		return FALSE;
	}

	if ((i = fread(&bpp, 2, 1, fp)) != 1)
	{
		TRI_ERROR_LOG("Can NOT read Image[%s] bpp.", fileName);
		return FALSE;
	}
	if (bpp != 24)
	{
		TRI_ERROR_LOG("Image[%s] is not 24bpp.", fileName);
		return FALSE;
	}

	fseek(fp, 24, SEEK_CUR);
	m_data = (char*)malloc(size);
	if (m_data == NULL)
	{
		TRI_ERROR_LOG("Image[%s]'s malloc failed. size[%lu]", fileName, size);
		return FALSE;
	}
	if ((i = fread(m_data, size, 1, fp)) != 1)
	{
		TRI_ERROR_LOG("Can NOT read image[%s] data.", fileName);
		return FALSE;
	}
	for (i = 0; i < size; i += 3)
	{
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

void GL_Bitmap::setArea(const Rect& area)
{
	m_area = area;
}

const Rect& GL_Bitmap::getArea()
{
	return m_area;
}

void GL_Bitmap::draw()
{
	glEnable(GL_TEXTURE_2D);//ͼ����Ч��
	glBindTexture(GL_TEXTURE_2D, getTexture());
	glEnable(GL_ALPHA_TEST);//���軭��ʼ
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f);
	glVertex2d(m_area.left, m_area.bottom);//����
	glTexCoord2f(0.0f, 1.0f);
	glVertex2d(m_area.left, m_area.top);//����
	glTexCoord2f(1.0f, 1.0f);
	glVertex2d(m_area.right, m_area.top);//����
	glTexCoord2f(1.0f, 0.0f);
	glVertex2d(m_area.right, m_area.bottom);//����
	glEnd();
	glDisable(GL_ALPHA_TEST);//���軭����
	glDisable(GL_TEXTURE_2D);//ͼ����Ч
}

}