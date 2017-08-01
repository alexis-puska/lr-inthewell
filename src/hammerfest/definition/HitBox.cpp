#include "HitBox.h"

HitBox::HitBox() {
}

void HitBox::initHitBox(int x, int y, int hitBoxWidth, int hitBoxHeight) {
	this->hitBoxWidth = hitBoxWidth;
	this->hitBoxHeight = hitBoxHeight;
	updateHitBox(x, y);
}

HitBox::~HitBox() {

}

SDL_Rect HitBox::getRect() {
	return rect;
}

void HitBox::updateHitBox(int x, int y) {
	rect.x = x;
	rect.y = y;
	rect.w = hitBoxWidth;
	rect.h = hitBoxHeight;
}

bool HitBox::hit(SDL_Rect other) {
	return SDL_HasIntersection(&rect, &other);
}

bool HitBox::hitByLeftSide(SDL_Rect other) {
	int x1 = other.x + other.w;
	int y1 = other.y;
	int x2 = other.x + other.w;
	int y2 = other.y + other.h;
	return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2);
}

bool HitBox::hitByRightSide(SDL_Rect other) {
	int x1 = other.x;
	int y1 = other.y;
	int x2 = other.x;
	int y2 = other.y + other.h;
	return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2);
}

bool HitBox::hitByBottonSide(SDL_Rect other) {
	int x1 = other.x;
	int y1 = other.y;
	int x2 = other.x + other.w;
	int y2 = other.y;
	return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2);
}

bool HitBox::hitByTopSide(SDL_Rect other) {
	int x1 = other.x;
	int y1 = other.y + other.h;
	int x2 = other.x + other.w;
	int y2 = other.y + other.h;
	return SDL_IntersectRectAndLine(&rect, &x1, &y1, &x2, &y2);
}

int HitBox::getIntersect(SDL_Rect other, bool horizontal) {
	SDL_Rect result;
	SDL_IntersectRect(&rect, &other, &result);
	if (horizontal) {
		return result.h;
	} else {
		return result.w;
	}
}
