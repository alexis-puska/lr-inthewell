#include "Door.h"

Door::Door(int x, int y, int type, bool locked, int toLevel, int requieredKey, Lock * lock) :
		Position(x, y),Drawable() {
	this->type = type;
	this->locked = true;
	this->toLevel = toLevel;
	this->requieredKey = requieredKey;
	this->lock = lock;
}

Door::~Door() {
	this->lock = NULL;
}

bool Door::isLocked() {
	return locked;
}

void Door::unlock() {
	this->locked = false;
}

void Door::checkToUnlock(/*PlayerPosition TODO*/) {
	if (requieredKey != -1 && ItemFileSystem::Instance().getQuantity(requieredKey) >= 1) {
		locked = false;
	} else if (lock != NULL && lock->isLocked()) {
		locked = false;
	}
}

int Door::getDestination() {
	return toLevel;
}

void Door::drawHimself(SDL_Surface * dest) {
	if (type == 0) {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("doors", 0), dest, (x * gridSize), (y * gridSize));
	} else if (type == 1) {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("doors", 1), dest, (x * gridSize), (y * gridSize));
	} else if (type == 2) {
		copySurfaceToBackRenderer(Sprite::Instance().getAnimation("doors", 2), dest, (x * gridSize), (y * gridSize));
	} else if (type == 3) {
		if (locked) {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("doors", 3), dest, (x * gridSize), (y * gridSize));
		} else {
			copySurfaceToBackRenderer(Sprite::Instance().getAnimation("doors", 4), dest, (x * gridSize), (y * gridSize));
		}
	}
}
