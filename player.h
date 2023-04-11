#pragma once

#ifndef PLAYERH
#define PLAYERH

#include "object.h"

class Player : public Object {
public:
	Player(void);

	float getEyeHeight(void) const;
	bool isSprinting(void) const;
	bool isCrouching(void) const;
	bool isOnGround(void);

	void setCameraX(const float);
	void addCameraX(const float);
	void setCameraY(const float);
	void addCameraY(const float);
	void move(const float, const  float, const float);

	virtual void tick(void) override;
	virtual void render(void) const override;
};

#endif PLAYERH