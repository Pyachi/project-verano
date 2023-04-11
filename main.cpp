#include <GL/freeglut.h>
#include "player.h"
#include "window.h"
#include "renderer.h"
#include "world.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(800, 25);
	glutCreateWindow("Project Verano");
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);
	glutSetOption(GLUT_MULTISAMPLE, 8);
	glutIgnoreKeyRepeat(true);
	World::init();
	Window::init();
	Renderer::init();
	glutMainLoop();
	return 0;
}