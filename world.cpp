#include <GL/freeglut.h>
#include <vector>
#include <algorithm>
#include "world.h"
#include "block.h"
#include "player.h"
#include "renderer.h"

namespace {
	std::vector<Object*> objects;
}

void World::init(void) {
	addObject(new Player());
	for (int x = -5; x <= 5; x++)
		for (int z = -5; z <= 5; z++)
			addObject(new Block(x, -1, z, "grass"));
	for (int x = -4; x <= -2; x++)
		for (int z = -4; z <= -2; z++)
			addObject(new Block(x, 0, z, "leaves"));
	addObject(new Block(1, 0, 1, "cobblestone"));
	addObject(new Block(3, 1, 3, "cobblestone"));
	addObject(new Block(5, 1.5, 5, "cobblestone"));
}

void World::tick(void) {
	for (Object* object : objects)
		object->tick();
}

void World::render(void) {
	for (const Object* object : objects) {
		Renderer::reset();
		object->render();
	}
}

void World::addObject(Object* object) {
	objects.push_back(object);
}

void World::removeEntity(Object* object) {
	std::remove(objects.begin(), objects.end(), object);
}

bool World::collidesWithAny(const float x, const float y, const float z) {
	for (const Object* object : objects)
		if (object->collidesWith(x, y, z))
			return true;
	return false;
}

bool World::collidesWithAny(const Object& object) {
	for (const Object* other : objects)
		if (other != &object && other->collidesWith(object))
			return true;
	return false;
}
