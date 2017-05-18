#include <windef.h>
#include <WinUser.h>
#include <wingdi.h>
#include "Picture.h"
#include <string.h>
#include <stdio.h>
#include "Log.h"
#include "glut.h"

Picture::Picture()
{
	memset(m_picturePath, 0x00, sizeof(m_picturePath));
}

Picture::~Picture()
{
}

void Picture::Draw()
{
	FILE* fp = fopen("res/background.bmp", "r+");

	if (NULL == fp)
	{
		return;
	}

	// 读取文件的头信息
	BITMAPFILEHEADER fileHeader = {0};
	fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	BITMAPINFOHEADER fileInfoHeader = {0};
	fread(&fileInfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);

	GLuint texid = 1000;

	HBITMAP hBMP = 0;					// Handle Of The Bitmap
	BITMAP BMP;						// Bitmap Structure
	glGenTextures(1, &texid);		// Create The Texture
	hBMP = (HBITMAP)LoadImage(GetModuleHandle(NULL), L"res/background.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	if (!hBMP)        // Does The Bitmap Exist?
		return;       // If Not Return False

	GetObject(hBMP, sizeof(BMP), &BMP);     // Get The Object
											// hBMP:    Handle To Graphics Object
											// sizeof(BMP): Size Of Buffer For Object Information
											// &BMP:    Buffer For Object Information
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);    // Pixel Storage Mode (Word Alignment / 4 Bytes)
											  // Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texid);     // Bind To The Texture ID
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Linear Min Filter
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Linear Mag Filter
	glTexImage2D(GL_TEXTURE_2D, 0, 3, BMP.bmWidth, BMP.bmHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, BMP.bmBits);
	DeleteObject(hBMP);       // Delete The Object

	return;       // Loading Was Successful
}

void Picture::setPicturePath(const char* path)
{
	if (NULL != path)
	{
		errno_t errId = strcpy_s(m_picturePath, sizeof(m_picturePath), path);
		LOG_LEVEL_PRINT(E_LOG_LEVEL_OBJECT_IMP, "Something wrong while copying string. [%d]", errId);
	}
}