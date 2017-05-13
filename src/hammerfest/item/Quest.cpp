#include "Quest.h"

Quest::Quest() {

}

Quest::~Quest() {
	giveFamilly.clear();
	requireItemId.clear();
}

Quest::Quest(char * titre, char * description, int giveOption, int giveMode, int removeFamilly, int famillyId) {
	strcpy(this->titre, titre);
	strcpy(this->description, description);
	this->giveOption = giveOption;
	this->giveOption = giveMode;
	this->giveOption = removeFamilly;
	giveFamilly.push_back(famillyId);
}
Quest::Quest(char * titre, char * description, int giveOption, int giveMode, int removeFamilly) {
	strcpy(this->titre, titre);
	strcpy(this->description, description);
	this->giveOption = giveOption;
	this->giveOption = giveMode;
	this->giveOption = removeFamilly;
}

char * Quest::getDescription() {
	return description;
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