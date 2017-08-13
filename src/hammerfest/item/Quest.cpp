#include "Quest.h"

Quest::~Quest() {
	giveFamilly.clear();
	requireItemId.clear();
}

Quest::Quest(int id, bool bombe, bool bombeUp, bool life, bool light, int disguise, int key, int giveOption, int giveMode, int removeFamilly, int famillyId, std::string titre, std::string) :
		IdElement(id) {
	this->bombe = bombe;
	this->bombeUp = bombeUp;
	this->disguise = disguise;
	this->key = key;
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
	this->bombe = bombe;
	this->bombeUp = bombeUp;
	this->disguise = disguise;
	this->key = key;
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
    std::cout<<id<<" - "<<titre<<" - "<<description<<"\n";
}

bool Quest::giveLife() {
	return life;
}

bool Quest::turnLightOn() {
	return light;
}

void Quest::printJson() {
    std::cout<<"{\"id\":"<<id<<",";
	std::cout<<"\"light\":"<<(light ? "true" : "false")<<",";
	std::cout<<"\"life\":"<<(life ? "true" : "false")<<",";
	std::cout<<"\"titre\":[";
	std::cout<<"{\"fr\":\""<<titre<<"\"},";
	std::cout<<"{\"en\":\""<<titre<<"\"},";
	std::cout<<"{\"es\":\""<<titre<<"\"}";
	std::cout<<"],";
	std::cout<<"\"description\":[";
	std::cout<<"{\"fr\":\""<<description<<"\"},";
	std::cout<<"{\"en\":\""<<description<<"\"},";
	std::cout<<"{\"es\":\""<<description<<"\"}";
	std::cout<<"],";
	std::cout<<"\"option\":"<<giveOption<<",";
	std::cout<<"\"mode\":"<<giveMode<<",";
	std::cout<<"\"remove\":"<<removeFamilly<<",";
	std::cout<<"\"bombe\":"<<(bombe ? "true" : "false")<<",";
	std::cout<<"\"bombeUp\":"<<(bombeUp ? "true" : "false")<<",";
	std::cout<<"\"disguise\":"<<disguise<<",";
	std::cout<<"\"key\":"<<key<<",";
	std::cout<<"\"family\":[";
	for (unsigned int i = 0; i < giveFamilly.size(); i++) {
		if (i < giveFamilly.size() - 1) {
			std::cout<<giveFamilly[i]<<",";
		} else {
			std::cout<<giveFamilly[i];
		}
	}
	std::cout<<"],";
	std::cout<<"\"require\":[";
	std::map<int, int>::iterator last;
	last = requireItemId.end();
	--last;
	for (std::map<int, int>::iterator it = requireItemId.begin(); it != requireItemId.end(); ++it) {
		if (it != last) {
            std::cout<<"{\"id\":"<<it->first<<",\"val\":"<<it->second<<"},";
		} else {
			std::cout<<"{\"id\":"<<it->first<<",\"val\":"<<it->second<<"}";
		}
	}
	std::cout<<"]";
	std::cout<<"},\n";
}
