#include <GL/freeglut.h>
#include "block.h"
#include "world.h"
#include "renderer.h"
#include "texture.h"

Block::Block(const float x, const float y, const float z, const std::string& texture) {
	topTexture = sideTexture = bottomTexture = texture;
	locX = x;
	locY = y;
	locZ = z;
	collider = { 0.0F,0.0F,0.0F,1.0F,1.0F,1.0F };
}

Block::Block(const float x, const float y, const float z, const std::string& top, const std::string& side, const std::string& bottom) {
	topTexture = top;
	sideTexture = side;
	bottomTexture = bottom;
	locX = x;
	locY = y;
	locZ = z;
	collider = { 0.0F,0.0F,0.0F,1.0F,1.0F,1.0F };
}

Block::~Block(void) {
	World::removeEntity(this);
}

void Block::render(void) const {
	glTranslatef(locX + 0.5F, locY + 0.5F, locZ + 0.5F);
	//Top
	Texture::loadTexture(topTexture);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, -0.5);
	glEnd();
	//Bottom
	Texture::loadTexture(bottomTexture);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, -0.5, -0.5);
	glEnd();
	//Front
	Texture::loadTexture(sideTexture);
	glBegin(GL_QUADS);
	glTexCoord2i(0, 0); glVertex3f(0.5, 0.5, 0.5);
	glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, -0.5);
	//Back
	glTexCoord2i(0, 0); glVertex3f(-0.5, 0.5, -0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, 0.5);
	//Left
	glTexCoord2i(0, 0); glVertex3f(-0.5, 0.5, 0.5);
	glTexCoord2i(0, 1); glVertex3f(-0.5, -0.5, 0.5);
	glTexCoord2i(1, 1); glVertex3f(0.5, -0.5, 0.5);
	glTexCoord2i(1, 0); glVertex3f(0.5, 0.5, 0.5);
	//Right
	glTexCoord2i(0, 0); glVertex3f(0.5, 0.5, -0.5);
	glTexCoord2i(0, 1); glVertex3f(0.5, -0.5, -0.5);
	glTexCoord2i(1, 1); glVertex3f(-0.5, -0.5, -0.5);
	glTexCoord2i(1, 0); glVertex3f(-0.5, 0.5, -0.5);
	glEnd();
}