#include "GameConfig.h"

GameConfig GameConfig::m_instance = GameConfig();

GameConfig& GameConfig::Instance() {
	return m_instance;
}

GameConfig::GameConfig() {

}

GameConfig::~GameConfig() {
}

void GameConfig::getGameLoaded(int i){
	this->gameLoaded = i;
}

int GameConfig::getGameLoaded(){
	return gameLoaded;
}
