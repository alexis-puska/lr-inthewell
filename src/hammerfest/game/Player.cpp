#include "Player.h"

Player::Player(int x, int y, int type) :
		Position(x, y),Drawable() {
	this->type = type;
}

Player::~Player() {
}
