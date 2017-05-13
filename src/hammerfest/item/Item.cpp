#include "Item.h"

Item::Item() {

}

Item::~Item() {
	SDL_FreeSurface(sprite);
	delete sprite;
}

Item::Item(SDL_Surface * items, int id, char * name, int value, int rarity, int unlock){
	this->id = id;
	strcpy(this->name, name);
	this->value = value;
	this->rarity = rarity;
	this->unlock = unlock;
	Uint32 rmask, gmask, bmask, amask;
	amask = 0xff000000;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	sprite = SDL_CreateRGBSurface(0, sizeX, sizeY, 32, rmask, gmask, bmask, amask);
	//TODO crop image
}

int Item::getId() {
	return id;
}

char* Item::getName() {
	return name;
}

int Item::getRarity() {
	return rarity;
}

int Item::getUnlock() {
	return unlock;
}

int Item::getValue() {
	return value;
}

SDL_Surface * Item::getSprite(){
	return sprite;
}