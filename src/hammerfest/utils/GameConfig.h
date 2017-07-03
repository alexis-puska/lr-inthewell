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
	soloMode = 0, learningMode = 1, timeAttackMode = 2, multicoopMode = 3, soccerMode = 4
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

		void InitConfiguration();

		/*
		 * unlock Mode
		 */
		void unlockTimeAttackMode();
		bool isTimeAttackUnlock();

		void unlockMulticoopMode();
		bool isMulticoopUnlock();
		/*
		 * unlock Solo option
		 */
		bool isMirror();
		bool isNightmare();
		bool isNinja();
		bool isBombExpert();
		bool isBoost();

		bool getSoloOption(int index);
		void setSoloOption(int index, bool value);
		void toogleSoloOption(int index);

		void unlockSoloOption(int index);
		bool getSoloOptionUnlock(int index);

		/*
		 * unlock multi option
		 */
		bool isMirrorMulti();
		bool isNightmareMulti();
		bool isLifeSharing();

		bool getMultiOption(int index);
		void setMultiOption(int index, bool value);
		void toogleMultiOption(int index);

		void unlockMultiOption(int index);
		bool getMultiOptionUnlock(int index);

		/*
		 * unlock soccer option
		 */
		void unlockKickcontrol();
		bool isKickcontrolUnlock();
		void toogleSoccerOption(int index);
		bool getSoccerOption(int index);
		void setSoccerMap(int index);
		int getSoccerMap();


		int getLife();
		void incLife();
		bool getLight();
		void setLightOn();

		std::string getLang();
		void setLang(std::string lang);
		void incLang();
		void decLang();

	private:
		GameConfig& operator=(const GameConfig&);
		GameConfig(const GameConfig&);
		static GameConfig m_instance;

		int gameLoaded;
		int gameMode;

		bool timeAttack;
		bool multi;

		std::string lang;

		/*
		 * 0 - miroir
		 * 1 - cauchemar
		 * 2 - ninjutstu
		 * 3 - explosif instable
		 * 4 - tornade
		 */
		bool soloOption[5];
		bool soloOptionUnlock[5];
		/*
		 * 0 - miroir
		 * 1 - cauchemar
		 * 2 - partage de vie
		 * 3 - bombotopia <-- ????
		 */
		bool multiOption[3];
		bool multiOptionUnlock[3];

		/*
		 * 0 - controle avancés
		 * 1 - bombe
		 */
		bool soccerOption[2];
		bool soccerOptionUnlock[2];
		/*
		 * 0 - gazon maudit
		 * 1 - temple du ballon
		 * 2 - volleyfest
		 * 3 - maitrise aerienne
		 */
		int soccerMap;

		int life;
		bool light;

};
#endif
