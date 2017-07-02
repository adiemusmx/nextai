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

		// Set the picture's path.
		BOOL setPicturePath(const char* fileName);
		
		// Get texture of bitmap.
		GLuint getTexture();

	private:
		// Generate texture
		void generateTexture();

		unsigned long m_width;
		unsigned long m_height;
		char *m_data;
		GLuint m_texture;
	};

}
