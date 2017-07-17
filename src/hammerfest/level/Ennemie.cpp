#include "Ennemie.h"

Ennemie::Ennemie(int id, int x, int y, int type) :
		Position(x, y), Drawable(), HitBox(), IdElement(id) {
	this->type = type;
}

Ennemie::~Ennemie() {

}

void Ennemie::drawHimself(SDL_Surface * dest) {

}

void Ennemie::doSomething() {
	switch (type) {
		case cerise:
			break;
		case orange:
			break;
		case pomme:
			break;
		case banane:
			break;
		case citron:
			break;
		case bombinos:
			break;
		case poire:
			break;
		case abricot:
			break;
		case litchi:
			break;
		case fraise:
			break;
		case kiwi:
			break;
		case pasteque:
			break;
		case ananas:
			break;
		case blob:
			break;
		case framboise:
			break;
		case nainbricot:
			break;
	}
}
