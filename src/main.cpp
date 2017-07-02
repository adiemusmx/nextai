#include "render_system.h"

int main(int argc, char *argv[])
{
	Trinity::GLRenderer* rs = Trinity::GLRenderer::getInstance();

	rs->init(&argc, argv);

	// 主循环
	rs->mainLoop();

	return 0;
}