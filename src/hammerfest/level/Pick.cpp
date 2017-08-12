#include "Pick.h"

Pick::Pick(int id, int x, int y, bool visible, int direction) :
		Drawable(), Position(x, y), IdElement(id), HitBox() {
	this->visible = visible;
	this->direction = direction;
}

Pick::~Pick() {
}

void Pick::drawHimself(SDL_Surface * dest) {
	if (visible) {
		SDL_Surface * temp = NULL;
		switch (direction) {
			case pickToTop:
                //std::cout << "draw pick tot\n";
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("pick", 1), dest, (x * gridSize) + leftPadding, (y * gridSize));
				break;
			case pickToLeft:
                //std::cout << "draw pick tol\n";
				temp = rotozoomSurface(Sprite::Instance().getAnimation("pick", 1), 90, 1, 0);
				copySurfaceToBackRenderer(temp, dest, (x * gridSize) + leftPadding, (y * gridSize));
				break;
			case pickToBottom:
                //std::cout << "draw pick tob\n";
				temp = rotozoomSurface(Sprite::Instance().getAnimation("pick", 1), 180, 1, 0);
				copySurfaceToBackRenderer(temp, dest, (x * gridSize) + leftPadding, (y * gridSize));
				break;
			case pickToRight:
                //std::cout << "draw pick tor\n";
				temp = rotozoomSurface(Sprite::Instance().getAnimation("pick", 1), 270, 1, 0);
				copySurfaceToBackRenderer(temp, dest, (x * gridSize) + leftPadding, (y * gridSize));
				break;
		}
		if (temp != NULL) {
			SDL_FreeSurface(temp);
		}
		//std::cout << "fin draw pick\n";
	}
}
