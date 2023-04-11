#pragma once

#ifndef WORLDH
#define WORLDH

class Object;

namespace World {
	void init(void);
	void tick(void);
	void render(void);
	void addObject(Object*);
	void removeEntity(Object*);
	bool collidesWithAny(const float, const float, const float);
	bool collidesWithAny(const Object&);
}

#endif WORLDH
