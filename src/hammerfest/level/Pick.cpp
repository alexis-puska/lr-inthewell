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
		switch (direction) {
			case pickToTop:
				fprintf(stderr,"draw pick tot\n");
				copySurfaceToBackRenderer(Sprite::Instance().getAnimation("pick", 1), dest, (x * gridSize), (y * gridSize));
				break;
			case pickToLeft:
				fprintf(stderr,"draw pick tol\n");
				copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("pick", 1), 90, 1, 0), dest, (x * gridSize), (y * gridSize));
				break;
			case pickToBottom:
				fprintf(stderr,"draw pick tob\n");
				copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("pick", 1), 180, 1, 0), dest, (x * gridSize), (y * gridSize));
				break;
			case pickToRight:
				fprintf(stderr,"draw pick tor\n");
				copySurfaceToBackRenderer(rotozoomSurface(Sprite::Instance().getAnimation("pick", 1), 270, 1, 0), dest, (x * gridSize), (y * gridSize));
				break;
		}
		fprintf(stderr,"fin draw pick\n");
	}
}
