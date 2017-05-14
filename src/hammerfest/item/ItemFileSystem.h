#ifndef __MYCLASS_ITEM_FILE_SYSTEM
#define __MYCLASS_ITEM_FILE_SYSTEM

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <map>

// Score + nb of game + level reached + 353 item
#define nbOfValueInFile 357

class ItemFileSystem {
	public:
		static ItemFileSystem& Instance();

		ItemFileSystem();
		~ItemFileSystem();
		void init(char * saveFile, bool newSaveFile);
		void loadAccount(int accountId);
		void save(int score, bool gamePlayed, int level);
		int getItemId();
	private:

		ItemFileSystem& operator=(const ItemFileSystem&);
		ItemFileSystem(const ItemFileSystem&);
		static ItemFileSystem m_instance;

		int accountId;
		char saveFilePath[255];
		FILE* saveFile;

		int accountLoaded;
		int scoreMax;
		int scoreLastGame;
		int nbGame;
		int levelReached;
		std::map<int, int> fridge;
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