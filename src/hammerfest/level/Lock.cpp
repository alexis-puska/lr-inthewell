#include "Lock.h"

Lock::Lock(int x, int y, int requieredKeyId) :
		Drawable(), Position(x, y), HitBox() {
	this->locked = true;
	this->requieredKey = requieredKeyId;
	this->height = 35;
	this->width = 37;
	initHitBox(x, y, width - lockHitboxBorder, height - lockHitboxBorder);
}

Lock::~Lock() {

}

bool Lock::isLocked() {
	return locked;
}

void Lock::checkToUnlock(/*PlayerPosition TODO*/) {
	if (ItemFileSystem::Instance().getQuantity(requieredKey) >= 1) {
		locked = false;
	}
}

void Lock::drawHimself(SDL_Surface * dest) {
	if (locked) {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("serrure", 1), dest, (x * gridSize) - floor(width / 2), (y * gridSize) - height);
	} else {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("serrure", 0), dest, (x * gridSize) - floor(width / 2), (y * gridSize) - height);
	}
}
