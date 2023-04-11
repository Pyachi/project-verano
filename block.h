#pragma once

#ifndef BLOCKH
#define BLOCKH

#include <string>
#include "object.h"

class Block : public Object {
protected:
	std::string topTexture;
	std::string sideTexture;
	std::string bottomTexture;
public:
	Block(const float, const float, const float, const std::string&);
	Block(const float, const  float, const float, const std::string&, const std::string&, const std::string&);
	~Block(void);

	virtual void render(void) const override;
};

#endif BLOCKH