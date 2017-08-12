#include "Item.h"

Item::Item(int id, std::string name, int rarity, int value, int unlock): IdElement(id){
	this->name = name;
	this->value = value;
	this->rarity = rarity;
	this->unlock = unlock;
}

Item::~Item() {
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

void Item::printName() {
	std::cout << id << " - " << name << "\n";
}

void Item::printJson() {
	fprintf(stderr, "{\"id\":%i,\"name\":[{\"fr\":\"%s\"},{\"en\":\"%s\"},{\"es\":\"%s\"}],", id, name.c_str(), name.c_str(), name.c_str());
	fprintf(stderr, "\"rarity\":%i,\"value\":%i,\"unlock\":%i}\n,", rarity, value, unlock);

}