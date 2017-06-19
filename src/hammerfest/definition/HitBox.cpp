#include "HitBox.h"

HitBox::HitBox() {
	this->yMax = 0;
	this->yMin = 0;
	this->xMax = 0;
	this->xMin = 0;
	this->hitBoxWidth = 0;
	this->hitBoxHeight = 0;
}

void HitBox::initHitBox(int x, int y, int hitBoxWidth, int hitBoxHeight) {
	fprintf(stderr, "init hitbox : %i %i %i %i\n", x, y, hitBoxWidth, hitBoxHeight);
	this->hitBoxWidth = hitBoxWidth;
	this->hitBoxHeight = hitBoxHeight;
	updateHitBox(x, y);
	fprintf(stderr, "fin init hitbox : %i %i %i %i\n", xMin, xMax, yMin, yMax);
}

HitBox::~HitBox() {

}

void HitBox::updateHitBox(int x, int y) {
	xMin = x - (hitBoxWidth / 2);
	xMax = x + (hitBoxWidth / 2);
	yMin = y - hitBoxHeight;
	yMax = y;
}

bool HitBox::hit(HitBox other) {
	int oXMin = other.getXMin();
	int oXMax = other.getXMax();
	int oYMin = other.getYMin();
	int oYMax = other.getYMax();
	if (oXMin >= xMin && oXMin <= xMax) {
		if (oYMin >= yMin && oYMin <= yMax) {
			return true;
		} else if (oYMax >= yMin && oYMax <= yMax) {
			return true;
		}

	} else if (oXMax >= xMin && oXMax <= xMax) {
		if (oYMin >= yMin && oYMin <= yMax) {
			return true;
		} else if (oYMax >= yMin && oYMax <= yMax) {
			return true;
		}
	}
	return false;
}

int HitBox::getXMin() {
	return xMin;
}

int HitBox::getXMax() {
	return xMax;
}

int HitBox::getYMin() {
	return yMin;
}

int HitBox::getYMax() {
	return yMax;
}
