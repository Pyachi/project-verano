#include <GL/freeglut.h>
#include "window.h"

namespace {
	int width = 800;
	int height = 800;

	void reshapeHandler(int width, int height) {
		Window::setWidth(width);
		Window::setHeight(height);
		glViewport(0, 0, width, height);
	}
}

void Window::init(void) {
	glutReshapeFunc(reshapeHandler);
}

int Window::getWidth(void) {
	return width;
}

int Window::getHeight(void) {
	return height;
}

void Window::setWidth(int val) {
	width = val;
}

void Window::setHeight(int val) {
	height = val;
}