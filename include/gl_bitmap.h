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

	// �趨�ļ�·��
	BOOL setPath(const char* fileName);

	// �趨�軭����
	virtual void setArea(const RECT& area);
	virtual const RECT& getArea();

	// �軭����
	void draw();

private:
	// ȡ���Ѿ����ص�ͼƬ����
	GLuint getTexture();

private:
	// ����ͼƬ����
	void generateTexture();

	// ͼƬ��Ⱥ͸߶�
	unsigned long m_width;
	unsigned long m_height;

	// ͼƬ����
	char *m_data;

	// �軭λ��
	RECT m_area;

	// ����ID
	GLuint m_texture;
};

}
