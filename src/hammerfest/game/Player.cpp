#include "Player.h"

Player::Player(int x, int y, int type) :
		Position(x, y),Drawable() {
	this->type = type;
}

Player::~Player() {
}

void Player::doSomething(SDL_Surface * dest){
	copySurfaceToBackRenderer(Sprite::Instance().getAnimation("igor_right_walk", 0), dest, 50, 30);
}