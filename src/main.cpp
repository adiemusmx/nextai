#if 1
#include "render_system.h"

void main(int argc, char *argv[])
{
	Trinity::RenderSystem* rs = Trinity::RenderSystem::getInstance();

	rs->init(&argc, argv);

	// 主循环
	rs->mainLoop();
}

#else
#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#define WIDTH 320
#define HEIGHT 240
class BMP
{
public:
	unsigned long sizeX;  //横
	unsigned long sizeY; //竖
	char *Data;  //放置图像数据
	bool Load(char *filename);
	GLuint texture;
	void TexSet();
	BMP(char *FileName);
};
BMP::BMP(char *FileName) {
	Load(FileName);
	TexSet();
}
bool BMP::Load(char *FileName) {
	FILE *File;
	unsigned long size;// 主要大小
	unsigned long i;// 计数
	unsigned short int planes;        //面数
	unsigned short int bpp;            // 像素数
	char temp;                         // 颜色相关
									   //打开图片
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
	return true;
}
void BMP::TexSet()
{
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
	glBindTexture(GL_TEXTURE_2D, 0);
}
BMP *bmp;
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);
	glEnable(GL_TEXTURE_2D);//图像有效化
	glBindTexture(GL_TEXTURE_2D, bmp->texture);
	glEnable(GL_ALPHA_TEST);//试描画开始
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, 0.0f); glVertex2d(10, 230);//左下
	glTexCoord2f(0.0f, 1.0f); glVertex2d(10, 10);//左上
	glTexCoord2f(1.0f, 1.0f); glVertex2d(310, 10);//右上
	glTexCoord2f(1.0f, 0.0f); glVertex2d(310, 230);//右下
	glEnd();
	glDisable(GL_ALPHA_TEST);//试描画结束
	glDisable(GL_TEXTURE_2D);//图像无效
	glutSwapBuffers();
}
void idle(void)
{
	glutPostRedisplay();
}
void Init() {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glOrtho(0, WIDTH, HEIGHT, 0, -1, 1);
	bmp = new BMP("res/background.bmp");
}
int main(int argc, char *argv[])
{
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutCreateWindow("读取BMP图像并显示");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	Init();
	glutMainLoop();
	return 0;
}
#endif