#include "Ennemie.h"

Ennemie::Ennemie(int id, int x, int y, int type) :
		Position((x * 20) + 10, (y * 20) + 20), Drawable(), HitBox(), IdElement(id) {
	this->type = type;
	this->id = id;
}

Ennemie::~Ennemie() {

}

void Ennemie::doSomething(SDL_Surface * dest) {
	SDL_Surface * t = NULL;
	switch (type) {
		case cerise:
			t = Sprite::Instance().getAnimation("cerise_walk", 0);
			break;
		case orange:
			t = Sprite::Instance().getAnimation("orange_walk", 0);
			break;
		case pomme:
			t = Sprite::Instance().getAnimation("pomme_walk", 0);
			break;
		case banane:
			t = Sprite::Instance().getAnimation("banane_walk", 0);
			break;
		case citron:
			t = Sprite::Instance().getAnimation("citron_walk", 0);
			break;
		case bombinos:
			t = Sprite::Instance().getAnimation("bombinos_walk", 0);
			break;
		case poire:
			t = Sprite::Instance().getAnimation("poire_walk", 0);
			break;
		case abricot:
			t = Sprite::Instance().getAnimation("abricot_walk", 0);
			break;
		case litchi:
			t = Sprite::Instance().getAnimation("litchi_walk", 0);
			break;
		case fraise:
			t = Sprite::Instance().getAnimation("fraise_walk", 0);
			break;
		case kiwi:
			t = Sprite::Instance().getAnimation("kiwi_walk", 0);
			break;
		case pasteque:
			t = Sprite::Instance().getAnimation("pasteque_walk", 0);
			break;
		case ananas:
			t = Sprite::Instance().getAnimation("annanas_walk", 0);
			break;
		case blob:
			t = Sprite::Instance().getAnimation("blob_walk", 0);
			break;
		case framboise:
			t = Sprite::Instance().getAnimation("framboise_walk", 0);
			break;
		case nainbricot:
			t = Sprite::Instance().getAnimation("abricot_walk", 0);
			break;
	}
	copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h));
}
