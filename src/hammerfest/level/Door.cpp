#include "Door.h"

Door::Door(int x, int y, int type, bool locked, int toLevel, int requieredKey, Lock * lock) :
		Position(x, y),Drawable(), HitBox() {
	this->type = type;
	this->locked = true;
	this->toLevel = toLevel;
	this->requieredKey = requieredKey;
	this->lock = lock;
	this->height = 64;
	this->width = 52;
	initHitBox(x, y, width - doorHitboxBorder, height - doorHitboxBorder);
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
	SDL_Surface * tmp;
	if (type == 0) {
		tmp = Sprite::Instance().getAnimation("doors", 0);
		copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
	} else if (type == 1) {
		tmp = Sprite::Instance().getAnimation("doors", 1);
		copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
	} else if (type == 2) {
		tmp = Sprite::Instance().getAnimation("doors", 2);
		copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
	} else if (type == 3) {
		if (locked) {
			tmp = Sprite::Instance().getAnimation("doors", 3);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		} else {
			tmp = Sprite::Instance().getAnimation("doors", 4);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		}
	}
}
