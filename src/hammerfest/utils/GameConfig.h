#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <vector>
#include <algorithm>
#include <math.h>

#ifndef __MYCLASS_GAMECONFIG
#define __MYCLASS_GAMECONFIG

class GameConfig {

	public:
		GameConfig();
		~GameConfig();
		static GameConfig& Instance();


		void getGameLoaded(int i);
		int getGameLoaded();

	private:
		GameConfig& operator=(const GameConfig&);
		GameConfig(const GameConfig&);
		static GameConfig m_instance;


		int gameLoaded;

};
#endif
