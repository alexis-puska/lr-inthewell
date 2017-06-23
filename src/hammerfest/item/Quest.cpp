#include "Quest.h"

Quest::~Quest() {
	giveFamilly.clear();
	requireItemId.clear();
}

Quest::Quest(int id, bool bombe, bool bombeUp, bool life, bool light, int disguise, int key, int giveOption, int giveMode, int removeFamilly, int famillyId, std::string titre, std::string) :
		IdElement(id) {
	this->titre = titre;
	this->description = description;
	this->giveOption = giveOption;
	this->giveMode = giveMode;
	this->removeFamilly = removeFamilly;
	giveFamilly.push_back(famillyId);
	this->life = life;
	this->light = light;
}
Quest::Quest(int id, bool bombe, bool bombeUp, bool life, bool light, int disguise, int key, int giveOption, int giveMode, int removeFamilly, std::string titre, std::string description) :
		IdElement(id) {
	this->titre = titre;
	this->description = description;
	this->giveOption = giveOption;
	this->giveMode = giveMode;
	this->removeFamilly = removeFamilly;
	this->life = life;
	this->light = light;
}

std::string Quest::getDescription() {
	return description;
}

std::string Quest::getTitre() {
	return titre;
}

int Quest::getGiveOption() {
	return giveOption;
}

int Quest::getGiveMode() {
	return giveMode;
}

int Quest::getRemoveFamilly() {
	return removeFamilly;
}

std::vector<int> Quest::getGiveFamilly() {
	return giveFamilly;
}

std::map<int, int> Quest::getRequireItemId() {
	return requireItemId;
}

void Quest::addRequireItemId(int itemId, int quantity) {
	requireItemId[itemId] = quantity;
}

void Quest::addGiveFamilly(int famillyId) {
	giveFamilly.push_back(famillyId);
}

void Quest::printName() {
	fprintf(stderr, "%i - %s - %s\n", id, titre.c_str(), description.c_str());
}

bool Quest::giveLife() {
	return life;
}

bool Quest::turnLightOn() {
	return light;
}
