#include "stdafx.h"
#include "render_system/render_system_image.h"
#include "FreeImage/FreeImage.h"

namespace NextAI
{
	bool generateTexture(FIBITMAP *fibmp, PICTURE_TEXTURE_ID& texture)
	{
		int pitch = FreeImage_GetPitch(fibmp);
		unsigned char *bits = FreeImage_GetBits(fibmp);
		unsigned char *buf = NULL;
		GLuint rgb_mode;
		int width = FreeImage_GetWidth(fibmp);
		int height = FreeImage_GetHeight(fibmp);
		
		switch (FreeImage_GetBPP(fibmp))
		{
		case 8:
		{
			RGBQUAD *palette = NULL;
			
			if (!(palette = FreeImage_GetPalette(fibmp)))
			{
				texture = INVALID_TEXTURE_ID;
				return false;
			}
			
			if (!(buf = (unsigned char *)malloc(width * height * 3)))
			{
				texture = INVALID_TEXTURE_ID;
				return false;
			}
			
			rgb_mode = GL_RGB;
			
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					int k = bits[i * pitch + j];
					buf[(i * width + j) * 3 + 0] = palette[k].rgbRed;
					buf[(i * width + j) * 3 + 1] = palette[k].rgbGreen;
					buf[(i * width + j) * 3 + 2] = palette[k].rgbBlue;
				}
			}
		}
		break;
		
		case 24:
			if (!(buf = (unsigned char *)malloc(width * height * 3)))
			{
				texture = INVALID_TEXTURE_ID;
				return false;
			}
			
			rgb_mode = GL_RGB;
			
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					buf[(i * width + j) * 3 + 0] = bits[i * pitch + j * 3 + 2];
					buf[(i * width + j) * 3 + 1] = bits[i * pitch + j * 3 + 1];
					buf[(i * width + j) * 3 + 2] = bits[i * pitch + j * 3 + 0];
				}
			}
			
			break;
			
		case 32:
			if (!(buf = (unsigned char *)malloc(width * height * 4)))
			{
				texture = INVALID_TEXTURE_ID;
				return false;
			}
			
			rgb_mode = GL_RGBA;
			
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					buf[(i * width + j) * 4 + 0] = bits[i * pitch + j * 4 + 2];
					buf[(i * width + j) * 4 + 1] = bits[i * pitch + j * 4 + 1];
					buf[(i * width + j) * 4 + 2] = bits[i * pitch + j * 4 + 0];
					buf[(i * width + j) * 4 + 3] = bits[i * pitch + j * 4 + 3];
				}
			}
			
			break;
			
		default:
			texture = INVALID_TEXTURE_ID;
			return false;
		}
		
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, rgb_mode, width, height, 0, rgb_mode, GL_UNSIGNED_BYTE, buf);
		free(buf);
		return true;
	}
	
	bool generateTexture(FIBITMAP *fibmp, int32 count, std::vector<PICTURE_TEXTURE_ID>& textures)
	{
		if (count <= 0)
		{
			textures.clear();
			return false;
		}
		
		int pitch = FreeImage_GetPitch(fibmp);
		unsigned char *bits = FreeImage_GetBits(fibmp);
		unsigned char *buf = NULL;
		int bpp = FreeImage_GetBPP(fibmp);
		RGBQUAD *palette = NULL;
		GLuint rgb_mode;
		int width = FreeImage_GetWidth(fibmp);
		int height = FreeImage_GetHeight(fibmp);
		
		switch (bpp)
		{
		case 8:
		{
			RGBQUAD *palette = NULL;
			
			if (!(palette = FreeImage_GetPalette(fibmp)))
			{
				return false;
			}
			
			if (!(buf = (unsigned char *)malloc(width * height * 3)))
			{
				return false;
			}
			
			rgb_mode = GL_RGB;
			
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					int k = bits[i * pitch + j];
					buf[(i * width + j) * 3 + 0] = palette[k].rgbRed;
					buf[(i * width + j) * 3 + 1] = palette[k].rgbGreen;
					buf[(i * width + j) * 3 + 2] = palette[k].rgbBlue;
				}
			}
		}
		break;
		
		case 24:
			if (!(buf = (unsigned char *)malloc(width * height * 3)))
			{
				return false;
			}
			
			rgb_mode = GL_RGB;
			
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					buf[(i * width + j) * 3 + 0] = bits[i * pitch + j * 3 + 2];
					buf[(i * width + j) * 3 + 1] = bits[i * pitch + j * 3 + 1];
					buf[(i * width + j) * 3 + 2] = bits[i * pitch + j * 3 + 0];
				}
			}
			
			break;
			
		case 32:
			if (!(buf = (unsigned char *)malloc(width * height * 4)))
			{
				return false;
			}
			
			rgb_mode = GL_RGBA;
			
			for (int i = 0; i < height; ++i)
			{
				for (int j = 0; j < width; ++j)
				{
					buf[(i * width + j) * 4 + 0] = bits[i * pitch + j * 4 + 2];
					buf[(i * width + j) * 4 + 1] = bits[i * pitch + j * 4 + 1];
					buf[(i * width + j) * 4 + 2] = bits[i * pitch + j * 4 + 0];
					buf[(i * width + j) * 4 + 3] = bits[i * pitch + j * 4 + 3];
				}
			}
			
			break;
			
		default:
			return false;
		}
		
		int unitHeight = height / count;
		
		for (int loopIdx = 0; loopIdx < count; ++loopIdx)
		{
			PICTURE_TEXTURE_ID texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			
			switch (bpp)
			{
			case 8:
				glTexImage2D(GL_TEXTURE_2D, 0, rgb_mode, width, unitHeight, 0, rgb_mode, GL_UNSIGNED_BYTE, buf + (3 * width * unitHeight * (count - loopIdx - 1)));
				break;
				
			case 24:
				glTexImage2D(GL_TEXTURE_2D, 0, rgb_mode, width, unitHeight, 0, rgb_mode, GL_UNSIGNED_BYTE, buf + (3 * width * unitHeight * (count - loopIdx - 1)));
				break;
				
			case 32:
				glTexImage2D(GL_TEXTURE_2D, 0, rgb_mode, width, unitHeight, 0, rgb_mode, GL_UNSIGNED_BYTE, buf + (4 * width * unitHeight * (count - loopIdx - 1)));
				break;
				
			default:
				break;
			}
			
			textures.push_back(texture);
		}
		
		free(buf);
		return true;
	}
	
	void Image::init()
	{
		FreeImage_Initialise();
	}
	
	void Image::cleanup()
	{
		FreeImage_DeInitialise();
	}
	
	bool Image::loadTexture(const std::wstring& filePath, PICTURE_TEXTURE_ID& texture)
	{
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *bitmap = NULL;
		GLBITMAP *glbmp = NULL;
		fif = FreeImage_GetFileTypeU(filePath.c_str(), 0);
		
		if (FIF_UNKNOWN == fif)
		{
			fif = FreeImage_GetFIFFromFilenameU(filePath.c_str());
			
			if (FIF_UNKNOWN == fif)
			{
				texture = INVALID_TEXTURE_ID;
				return false;
			}
		}
		
		if (FreeImage_FIFSupportsReading(fif))
		{
			bitmap = FreeImage_LoadU(fif, filePath.c_str(), 0);
		}
		
		if (!bitmap)
		{
			texture = INVALID_TEXTURE_ID;
			return false;
		}
		
		if (generateTexture(bitmap, texture) == false)
		{
			texture = INVALID_TEXTURE_ID;
			FreeImage_Unload(bitmap);
			return false;
		}
		else
		{
			FreeImage_Unload(bitmap);
			return true;
		}
	}
	
	bool Image::loadTextures(const std::wstring& filePath, int32 count, std::vector<PICTURE_TEXTURE_ID>& textures)
	{
		if (count == 0)
		{
			return false;
		}
		
		textures.clear();
		FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
		FIBITMAP *bitmap = NULL;
		GLBITMAP *glbmp = NULL;
		fif = FreeImage_GetFileTypeU(filePath.c_str(), 0);
		
		if (FIF_UNKNOWN == fif)
		{
			fif = FreeImage_GetFIFFromFilenameU(filePath.c_str());
			
			if (FIF_UNKNOWN == fif)
			{
				return false;
			}
		}
		
		if (FreeImage_FIFSupportsReading(fif))
		{
			bitmap = FreeImage_LoadU(fif, filePath.c_str(), 0);
		}
		
		if (!bitmap)
		{
			return false;
		}
		
		if (generateTexture(bitmap, count, textures) == false)
		{
			FreeImage_Unload(bitmap);
			return false;
		}
		else
		{
			FreeImage_Unload(bitmap);
			return true;
		}
	}
}