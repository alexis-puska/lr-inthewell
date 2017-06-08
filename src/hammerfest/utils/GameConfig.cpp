#include "GameConfig.h"

GameConfig GameConfig::m_instance = GameConfig();

GameConfig& GameConfig::Instance() {
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
	if (this->gameMode > soccer) {
		this->gameMode = solo;
	}
}

void GameConfig::decGameMode() {
	this->gameMode--;
	if (this->gameMode < solo) {
		this->gameMode = soccer;
	}
}

int GameConfig::getGameMode() {
	return this->gameMode;
}

