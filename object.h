#pragma once

#ifndef OBJECTH
#define OBJECTH

struct BoundingBox {
	float minX, minY, minZ, maxX, maxY, maxZ;
};

class Object {
protected:
	float locX = 0.0;
	float locY = 0.0;
	float locZ = 0.0;
	BoundingBox collider = { 0.0F,0.0F,0.0F,0.0F,0.0F,0.0F };
public:
	float getX(void) const;
	float getY(void) const;
	float getZ(void) const;

	bool collidesWith(const float, const float, const  float) const;
	bool collidesWith(const Object&) const;

	virtual void tick(void);
	virtual void render(void) const;
};

#endif OBJECTH