#include "GameConfig.h"



GameConfig& GameConfig::Instance() {
    static GameConfig m_instance;
	return m_instance;
}

GameConfig::GameConfig() {
	this->gameLoaded = 0;
	this->gameMode = 0;
}

GameConfig::~GameConfig() {
}

int GameConfig::getGameLoaded() {
	return this->gameLoaded;
}

void GameConfig::incGameLoaded() {
	this->gameLoaded++;
	if (this->gameLoaded > 3) {
		this->gameLoaded = 0;
	}
}

void GameConfig::decGameLoaded() {
	this->gameLoaded--;
	if (this->gameLoaded < 0) {
		this->gameLoaded = 3;
	}
}

void GameConfig::incGameMode() {
	this->gameMode++;
	if (this->gameMode == timeAttackMode && !timeAttack) {
        std::cout <<"switch time attack\n";
		this->gameMode++;
	}
	if (this->gameMode == multicoopMode && !multi) {
		std::cout << "switch multi\n";
		this->gameMode++;
	}
	if (this->gameMode > soccerMode) {
		this->gameMode = soloMode;
	}
}

void GameConfig::decGameMode() {
	this->gameMode--;
	if (this->gameMode == multicoopMode && !isMulticoopUnlock()) {
		std::cout << "switch multi\n";
		this->gameMode--;
	}
	if (this->gameMode == timeAttackMode && !isTimeAttackUnlock()) {
        std::cout << "switch time attack\n";
		this->gameMode--;
	}
	if (this->gameMode < soloMode) {
		this->gameMode = soccerMode;
	}
}

int GameConfig::getGameMode() {
	return this->gameMode;
}

void GameConfig::InitConfiguration() {
	timeAttack = false;
	multi = false;
	for (int i = 0; i < 5; i++) {
		soloOption[i] = false;
		soloOptionUnlock[i] = false;
	}
	for (int i = 0; i < 3; i++) {
		multiOption[i] = false;
		multiOptionUnlock[i] = false;
	}
	for (int i = 0; i < 2; i++) {
		soccerOption[i] = false;
		soccerOptionUnlock[i] = false;
	}
	soccerOptionUnlock[1] = true;
	life = 2;
	light = false;
}

/*
 * time attack mode
 */
void GameConfig::unlockTimeAttackMode() {
	timeAttack = true;
}

bool GameConfig::isTimeAttackUnlock() {
	return timeAttack;
}

/*
 * multi mode
 */
void GameConfig::unlockMulticoopMode() {
	multi = true;
}
bool GameConfig::isMulticoopUnlock() {
	return multi;
}
/*
 * solo mirror
 */

bool GameConfig::isMirror() {
	return soloOption[0];
}
bool GameConfig::isNightmare() {
	return soloOption[1];
}
bool GameConfig::isNinja() {
	return soloOption[2];
}
bool GameConfig::isBombExpert() {
	return soloOption[3];
}
bool GameConfig::isBoost() {
	return soloOption[4];
}
void GameConfig::setSoloOption(int index, bool value) {
	soloOption[index] = value;
}
bool GameConfig::getSoloOption(int index) {
	return soloOption[index];
}
void GameConfig::unlockSoloOption(int index) {
	soloOptionUnlock[index] = true;
}
bool GameConfig::getSoloOptionUnlock(int index) {
	return soloOptionUnlock[index];
}
void GameConfig::toogleSoloOption(int index) {
	if (soloOptionUnlock[index]) {
		if (soloOption[index]) {
			soloOption[index] = false;
		} else {
			soloOption[index] = true;
		}
	}
}

/*
 * unlock multi option
 */
bool GameConfig::isMirrorMulti() {
	return multiOption[0];
}

bool GameConfig::isNightmareMulti() {
	return multiOption[1];
}

bool GameConfig::isLifeSharing() {
	return multiOption[2];
}

void GameConfig::setMultiOption(int index, bool value) {
	multiOption[index] = value;
}

void GameConfig::unlockMultiOption(int index) {
	multiOptionUnlock[index] = true;
}

bool GameConfig::getMultiOptionUnlock(int index) {
	return multiOptionUnlock[index];
}

bool GameConfig::getMultiOption(int index) {
	return multiOption[index];
}

void GameConfig::toogleMultiOption(int index) {
	if (multiOptionUnlock[index]) {
		if (multiOption[index]) {
			multiOption[index] = false;
		} else {
			multiOption[index] = true;
		}
	}
}

/*
 * unlock soccer option
 */
void GameConfig::unlockKickcontrol() {
	soccerOptionUnlock[1] = true;
}
bool GameConfig::isKickcontrolUnlock() {
	return soccerOptionUnlock[1];
}

void GameConfig::toogleSoccerOption(int index) {
	if (soccerOption[index]) {
		soccerOption[index] = false;
	} else {
		soccerOption[index] = true;
	}
}
bool GameConfig::getSoccerOption(int index) {
	return soccerOption[index];
}

void GameConfig::setSoccerMap(int index) {
	soccerMap = index;
}

int GameConfig::getSoccerMap() {
	return soccerMap;
}

int GameConfig::getLife() {
	return life;
}
void GameConfig::incLife() {
	life++;
}

bool GameConfig::getLight() {
	return light;
}
void GameConfig::setLightOn() {
	light = true;
}

std::string GameConfig::getLang() {
	if (lang.empty()) {
		lang = "fr";
	}
	return lang;
}
void GameConfig::setLang(std::string lang) {
	lang = lang;
}

void GameConfig::incLang() {
	if (lang.compare("fr") == 0) {
		lang = "en";
	} else if (lang.compare("en") == 0) {
		lang = "es";
	} else if (lang.compare("es") == 0) {
		lang = "fr";
	}
}

void GameConfig::decLang() {
	if (lang.compare("fr") == 0) {
		lang = "es";
	} else if (lang.compare("en") == 0) {
		lang = "fr";
	} else if (lang.compare("es") == 0) {
		lang = "en";
	}
}
