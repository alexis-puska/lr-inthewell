#include "Item.h"

Item::Item(SDL_Surface * items, int id, std::string name, int rarity, int value, int unlock): IdElement(id){
	this->name = name;
	this->value = value;
	this->rarity = rarity;
	this->unlock = unlock;
	Uint32 rmask, gmask, bmask, amask;
	amask = 0xff000000;
	rmask = 0x00ff0000;
	gmask = 0x0000ff00;
	bmask = 0x000000ff;
	sprite = SDL_CreateRGBSurface(0, sizeX, sizeY, 32, rmask, gmask, bmask, amask);
}

Item::~Item() {
	SDL_FreeSurface(sprite);
	delete sprite;
}

std::string Item::getName() {
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

void Item::printName() {
	fprintf(stderr, "%i - %s\n", id, name.c_str());
}

void Item::printJson() {
	fprintf(stderr, "{\"id\":%i,\"name\":[{\"fr\":\"%s\"},{\"en\":\"%s\"},{\"es\":\"%s\"}],", id, name.c_str(), name.c_str(), name.c_str());
	fprintf(stderr, "\"rarity\":%i,\"value\":%i,\"unlock\":%i}\n,", rarity, value, unlock);

}