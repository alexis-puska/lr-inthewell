#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <string>
#include <algorithm>
#include <math.h>

#ifndef __MYCLASS_GAMECONFIG
#define __MYCLASS_GAMECONFIG

enum gameMdeEnum {
	solo = 0, apprentissage = 1, timeAttack = 2, multicoop = 3, soccer = 4
};

class GameConfig {

	public:
		GameConfig();
		~GameConfig();
		static GameConfig& Instance();

		void incGameLoaded();
		void decGameLoaded();
		int getGameLoaded();

		void incGameMode();
		void decGameMode();
		int getGameMode();

	private:
		GameConfig& operator=(const GameConfig&);
		GameConfig(const GameConfig&);
		static GameConfig m_instance;

		int gameLoaded;
		int gameMode;

		bool soloOption;
		int timeAttackLevel;
		bool multiOption;
		bool soccerOption;
		std::string soccerLevel;

};
#endif
