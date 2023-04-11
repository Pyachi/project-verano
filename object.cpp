#include "GL/freeglut.h"
#include "object.h"

float Object::getX(void) const {
	return locX;
}

float Object::getY(void) const {
	return locY;
}

float Object::getZ(void) const {
	return locZ;
}

void Object::render(void) const {}

void Object::tick(void) {}

bool Object::collidesWith(const float x, const float y, const float z) const {
	return locX + collider.minX < x && x < locX + collider.maxX
		&& locY + collider.minY < y && y < locY + collider.maxY
		&& locZ + collider.minZ < z && z < locZ + collider.maxZ;
}

bool Object::collidesWith(const Object& other) const {
	return locX + collider.minX < other.locX + other.collider.maxX
		&& other.locX + other.collider.minX < locX + collider.maxX
		&& locY + collider.minY < other.locY + other.collider.maxY
		&& other.locY + other.collider.minY < locY + collider.maxY
		&& locZ + collider.minZ < other.locZ + other.collider.maxZ
		&& other.locZ + other.collider.minZ < locZ + collider.maxZ;
}
