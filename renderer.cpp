#include <GL/freeglut.h>
#include <filesystem>
#include "renderer.h"
#include "player.h"
#include "world.h"
#include "texture.h"

namespace {
	void display_func() {
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		World::render();
		glutSwapBuffers();
	}

	void renderTimer(int value) {
		glutPostRedisplay();
		glutTimerFunc(7, renderTimer, 0);
	}

	void physicsTimer(int value) {
		World::tick();
		glutTimerFunc(20, physicsTimer, 0);
	}
}

void Renderer::init(void) {
	glutDisplayFunc(display_func);
	glutTimerFunc(20, physicsTimer, 0);
	glutTimerFunc(7, renderTimer, 0);
	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("resources/")) {
		std::string path = entry.path().generic_string();
		std::string name = path;
		Texture::registerTexture(path, name.replace(0, 10, "").replace(name.end() - 4, name.end(), ""));
	}
}

void Renderer::reset(void) {
	glColor3f(1.0,1.0,1.0);
	glColorMaterial(GL_FRONT, GL_AMBIENT | GL_DIFFUSE | GL_SPECULAR);
	Texture::unloadTexture();
	glLoadIdentity();
}