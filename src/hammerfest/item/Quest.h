#ifndef __MYCLASS_QUEST
#define __MYCLASS_QUEST

#include "Item.h"
#include <stdio.h>
#include <vector>
#include <map>

class Quest {
	public:
		Quest();
		~Quest();
		Quest(int id, bool bombe, bool bombeUp, bool life, bool light, int disguise, int key, int giveOption, int giveMode, int removeFamilly, int giveFamilly, const char * titre, const char * description);
		Quest(int id, bool bombe, bool bombeUp, bool life, bool light, int disguise, int key, int giveOption, int giveMode, int removeFamilly, const char * titre, const char * description);
		char * getTitre();
		char * getDescription();
		int getGiveOption();
		int getGiveMode();
		int getRemoveFamilly();
		std::vector<int> getGiveFamilly();
		std::map<int, int> getRequireItemId();
		void addRequireItemId(int itemId, int quantity);
		void addGiveFamilly(int famillyId);
		void printName();
	private:
		std::map<int, int> requireItemId;
		int id;
		char titre[40];
		char description[512];
		int giveOption;
		int giveMode;
		int removeFamilly;
		std::vector<int> giveFamilly;
};
#endif
