#include <GL/freeglut.h>
#include <map>
#include "stb_image.h"
#include "texture.h"

namespace {
	std::map<const std::string, unsigned int> textureRegistry;
}

void Texture::registerTexture(const std::string& file, const std::string& name) {
	glEnable(GL_TEXTURE_2D);
	unsigned int tex;
	int width=0, height=0, channels=0;
	unsigned char *data = stbi_load(file.c_str(), &width, &height, &channels, 0);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glBindTexture(GL_TEXTURE_2D, 0);
	textureRegistry[name] = tex;
	glDisable(GL_TEXTURE_2D);
}

void Texture::loadTexture(const std::string& name) {
	unloadTexture();
	glEnable(GL_TEXTURE_2D);
	try {
		glBindTexture(GL_TEXTURE_2D, textureRegistry.at(name));
	}
	catch (const std::out_of_range& e) {
		glBindTexture(GL_TEXTURE_2D, textureRegistry["null"]);
	}
}

void Texture::unloadTexture() {
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);
}