#pragma once

#ifndef TEXTUREH
#define TEXTUREH

#include <string>

namespace Texture {
	void registerTexture(const std::string&, const std::string&);
	void loadTexture(const std::string&);
	void unloadTexture();
}

#endif TEXTUREH