#include "Door.h"

Door::Door(int id, int x, int y, int type, bool locked, int toLevel, int requieredKey, Lock * lock) :
		Position(x, y),Drawable(), HitBox(), IdElement(id) {
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
	if (type == 0) { //starter
		tmp = Sprite::Instance().getAnimation("doors", 0);
		copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
	} else if (type == 1) { //stickers
		tmp = Sprite::Instance().getAnimation("doors", 1);
		copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
	} else if (type == 2) { //flower
		tmp = Sprite::Instance().getAnimation("doors", 2);
		copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
	} else if (type == 3) { //classic
		if (locked) {
			tmp = Sprite::Instance().getAnimation("doors", 3);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		} else {
			tmp = Sprite::Instance().getAnimation("doors", 4);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		}
	} else if (type == 4) { //vin
		if (locked) {
			tmp = Sprite::Instance().getAnimation("doors", 5);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		} else {
			tmp = Sprite::Instance().getAnimation("doors", 6);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		}

	} else if (type == 5) { //level0
		if (!locked) {
			tmp = Sprite::Instance().getAnimation("doors", 7);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		}

	} else if (type == 6) { //hell
		if (locked) {
			tmp = Sprite::Instance().getAnimation("doors", 9);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		} else {
			tmp = Sprite::Instance().getAnimation("doors", 8);
			copySurfaceToBackRenderer(tmp, dest, x - (tmp->w / 2), y - tmp->h);
		}

	}
}
