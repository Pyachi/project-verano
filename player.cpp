#include <GL/freeglut.h>
#include <cmath>
#include <algorithm>
#include "player.h"
#include "window.h"
#include "world.h"

namespace {
	Player* player;
	constexpr float pi = 3.1415926535897932;

	float yaw = 0.0F;
	float pitch = 0.0F;

	float yVel = 0.0F;
	constexpr float yAcc = -0.01F;
	constexpr float yMaxVel = 1.0F;
	constexpr float speed = 0.1F;
	constexpr float baseEyeHeight = 1.6F;

	int w = 0;
	int a = 0;
	int s = 0;
	int d = 0;
	int f = 0;
	int jump = 0;
	int f5Mode = 0;
}

void onMouseMove(const int x, const int y) {
	if (x == Window::getWidth() / 2 && y == Window::getHeight() / 2) return;
	double yaw = (x - Window::getWidth() / 2.0F) / 3.0F;
	double pitch = (y - Window::getHeight() / 2.0F) / 3.0F;
	player->addCameraX(yaw);
	player->addCameraY(pitch);
	glutWarpPointer(Window::getWidth() / 2, Window::getHeight() / 2);
}

void onKeyPress(const unsigned char key, const int mouseX, const int mouseY) {
	if (key == 'x' || key == 'X') exit(0);
	else if (key == 'w' || key == 'W' || key == 23) w = 1;
	else if (key == 's' || key == 'S' || key == 19) s = 1;
	else if (key == 'a' || key == 'A' || key == 1) a = 1;
	else if (key == 'd' || key == 'D' || key == 4) d = 1;
	else if (key == 'f' || key == 'F' || key == 6) f = 1;
	else if (key == ' ') jump = 1;
}

void onKeyRelease(const unsigned char key, const int mouseX, const int mouseY) {
	if (key == 'w' || key == 'W' || key == 23) w = 0;
	else if (key == 's' || key == 'S' || key == 19) s = 0;
	else if (key == 'a' || key == 'A' || key == 1) a = 0;
	else if (key == 'd' || key == 'D' || key == 4) d = 0;
	else if (key == 'f' || key == 'F' || key == 6) f = 0;
	else if (key == ' ') jump = 0;
}

void onFunctionPress(int key, int x, int y) {
	if (key == GLUT_KEY_F5) ++f5Mode %= 3;
}

Player::Player(void) {
	collider = { -0.35F,0.0F,-0.35F,0.35F,1.999F,0.35F };
	glutPassiveMotionFunc(onMouseMove);
	glutKeyboardFunc(onKeyPress);
	glutKeyboardUpFunc(onKeyRelease);
	glutSpecialFunc(onFunctionPress);
	player = this;
}

float Player::getEyeHeight(void) const {
	return baseEyeHeight - (isCrouching() ? 0.3 : 0.0);
}

bool Player::isSprinting(void) const {
	return GetKeyState(VK_CONTROL) < 0 && !isCrouching();
}

bool Player::isCrouching(void) const {
	return GetKeyState(VK_SHIFT) < 0;
}

void adjustCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0 + (player->isSprinting() ? 10.0 : 0.0) - (f ? 45.0 : 0.0), 1.0, 0.01, 2000.0);
	switch (f5Mode) {
	case 0:
		gluLookAt(
			player->getX(),
			player->getY() + player->getEyeHeight(),
			player->getZ(),
			player->getX() - sin(yaw)*cos(pitch),
			player->getY() - sin(pitch) + player->getEyeHeight(),
			player->getZ() + cos(yaw)*cos(pitch),
			0.0, 1.0, 0.0
		);
		break;
	case 1:
		gluLookAt(
			player->getX() + sin(yaw)*cos(pitch) * 3,
			player->getY() + player->getEyeHeight() + sin(pitch) * 3,
			player->getZ() - cos(yaw)*cos(pitch) * 3,
			player->getX() - sin(yaw)*cos(pitch),
			player->getY() - sin(pitch) + player->getEyeHeight(),
			player->getZ() + cos(yaw)*cos(pitch),
			0.0, 1.0, 0.0
		);
		break;
	case 2:
		gluLookAt(
			player->getX() - sin(yaw)*cos(pitch) * 3,
			player->getY() + player->getEyeHeight() - sin(pitch) * 3,
			player->getZ() + cos(yaw)*cos(pitch) * 3,
			player->getX() - sin(yaw)*cos(pitch),
			player->getY() - sin(pitch) + player->getEyeHeight(),
			player->getZ() + cos(yaw)*cos(pitch),
			0.0, 1.0, 0.0
		);
		break;
	}
	glMatrixMode(GL_MODELVIEW);
	glutPostRedisplay();
}

void Player::setCameraX(float degrees) {
	while (degrees > 180.0) degrees -= 360.0;
	while (degrees <= -180.0) degrees += 360.0;
	yaw = degrees * pi / 180;
}

void Player::addCameraX(float degrees) {
	setCameraX(yaw * 180 / pi + degrees);
}

void Player::setCameraY(float degrees) {
	pitch = std::max(-89.9F, std::min(89.9F, degrees)) * pi / 180;
}

void Player::addCameraY(float degrees) {
	setCameraY(pitch * 180 / pi + degrees);
}

bool Player::isOnGround(void) {
	locY -= 0.01;
	bool onGround = World::collidesWithAny(*this);
	locY += 0.01;
	return onGround;
}

void Player::move(float x, float y, float z) {
	if (x != 0) for (int i = 1; i <= 10; i++) {
		locX += x / pow(2, i);
		if (World::collidesWithAny(*this) || (y == 0 && !isOnGround() && isCrouching())) 
			locX -= x / pow(2, i);
	}
	if (y != 0) for (int i = 1; i <= 10; i++) {
		locY += y / pow(2, i);
		if (World::collidesWithAny(*this))
			locY -= y / pow(2, i);
	}
	if (z != 0) for (int i = 1; i <= 10; i++) {
		locZ += z / pow(2, i);
		if (World::collidesWithAny(*this) || (y == 0 && !isOnGround() && isCrouching()))
			locZ -= z / pow(2, i);
	}
}

void Player::render(void) const {
	if (f5Mode == 0) return;
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(locX + (collider.maxX + collider.minX) / 2, locY + (collider.maxY + collider.minY) / 2, locZ + (collider.maxZ + collider.minZ) / 2);
	glScalef(collider.maxX - collider.minX, collider.maxY - collider.minY, collider.maxZ - collider.minZ);
	glutWireCube(0.995);
}

void Player::tick() {
	if (isOnGround() && jump) yVel = 0.15;
	collider.maxY = isCrouching() ? 1.499F : 1.999F;
	double diagonalMultiplier = (w + a + s + d) % 2 == 0 ? 0.71 : 1.0;
	double speedMultiplier = diagonalMultiplier * speed;
	double dx = 0.0, dy = 0.0, dz = 0.0;
	if (w) {
		dz += cos(yaw) * speedMultiplier * (isSprinting() ? 1.5 : 1.0) * (isCrouching() ? 0.5 : 1.0);
		dx -= sin(yaw) * speedMultiplier * (isSprinting() ? 1.5 : 1.0) * (isCrouching() ? 0.5 : 1.0);
	}
	if (a) {
		dz += sin(yaw) * speedMultiplier * (isCrouching() ? 0.5 : 1.0);
		dx += cos(yaw) * speedMultiplier * (isCrouching() ? 0.5 : 1.0);
	}
	if (s) {
		dz -= cos(yaw) * speedMultiplier * (isCrouching() ? 0.5 : 1.0);
		dx += sin(yaw) * speedMultiplier * (isCrouching() ? 0.5 : 1.0);
	}
	if (d) {
		dz -= sin(yaw) * speedMultiplier * (isCrouching() ? 0.5 : 1.0);
		dx -= cos(yaw) * speedMultiplier * (isCrouching() ? 0.5 : 1.0);
	}
	dy += yVel;
	if (dx != 0 || dy != 0 || dz != 0) move(dx, dy, dz);
	if (isOnGround()) yVel = 0;
	else {
		yVel += yAcc;
		if (yVel > yMaxVel) yVel = yMaxVel;
		else if (yVel < -yMaxVel) yVel = -yMaxVel;
	}
	adjustCamera();
}