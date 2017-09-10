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
	GL_Bitmap(const char* fileName);
	virtual ~GL_Bitmap();

	// Set the path of the bitmap file.
	BOOL setPath(const char* fileName);

	// Set control's area
	virtual void setArea(const RECT& area);
	virtual const RECT& getArea();

	// Draw function
	void draw();

private:
	GLuint getTexture();

private:
	void generateTexture();

	unsigned long m_width;
	unsigned long m_height;

	char* m_data;
	RECT m_area;

	GLuint m_texture;
};

}
