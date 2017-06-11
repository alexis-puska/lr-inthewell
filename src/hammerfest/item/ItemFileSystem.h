#ifndef __MYCLASS_ITEM_FILE_SYSTEM
#define __MYCLASS_ITEM_FILE_SYSTEM

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <map>

#include "Family.h"
#include "Quest.h"
#include "Item.h"
#include "../utils/GameConfig.h"

// Score + nb of game + level reached + 353 item
#define nbOfValueInFile 357

#define probaCoef1 2000
#define probaCoef2 3000
#define probaCoef3 3300
#define probaCoef4 3400
#define probaCoef5 3410
#define probaCoef6 3411
#define probaCoef7 3471

class ItemFileSystem {
	public:
		static ItemFileSystem& Instance();

		ItemFileSystem();
		~ItemFileSystem();
		void init(char * saveFile, bool newSaveFile);
		int loadAccount(int accountId);
		void save(int score, bool gamePlayed, int level);
		Quest * getQuest(int index);
		std::map<int, Quest *> getQuestStarted();
		std::map<int, Quest *> getQuestCompleted();
		Item * getItem(int index);
		int getQuantity(int index);
		int getEffectItemId();
		int getPointItemId();
		void simulateGame();
	private:
		ItemFileSystem& operator=(const ItemFileSystem&);
		ItemFileSystem(const ItemFileSystem&);
		static ItemFileSystem m_instance;

		void buildDatabase();
		void loadDefaultAvailableItem();
		int random(int max);
		void unlockSomething(Quest * tested);

		int accountId;
		char saveFilePath[255];
		FILE* saveFile;

		int accountLoaded;
		int scoreMax;
		int scoreLastGame;
		int nbGame;
		int levelReached;
		std::map<int, int> fridge;

		std::vector<Family *> familys;
		std::vector<Quest *> quests;
		std::vector<Item *> items;

		std::map<int, Quest *> questStarted;
		std::map<int, Quest *> questCompleted;

		std::vector<int> availableItemEffect0;
		std::vector<int> availableItemEffect1;
		std::vector<int> availableItemEffect2;
		std::vector<int> availableItemEffect3;
		std::vector<int> availableItemEffect4;
		std::vector<int> availableItemEffect5;
		std::vector<int> availableItemEffect6;

		std::vector<int> availableItemPoint0;
		std::vector<int> availableItemPoint1;
		std::vector<int> availableItemPoint2;
		std::vector<int> availableItemPoint3;
		std::vector<int> availableItemPoint4;
		std::vector<int> availableItemPoint5;
		std::vector<int> availableItemPoint6;
		std::vector<int> availableItemPoint7;

};
#endif

/*
 <give option=\"boost\"/>
 <give option=\"mirror\"/>
 <give option=\"nightmare\"/>
 <give option=\"kickcontrol\"/>
 <give mode=\"multicoop\"/>
 <give option=\"mirrormulti\"/>
 <give option=\"nightmaremulti\"/>
 <give option=\"lifesharing\"/>
 <give option=\"ninja\"/>
 <give mode=\"timeattack\"/>
 <give option=\"set_ta_0\"/>
 <give option=\"bombexpert\"/>
 */