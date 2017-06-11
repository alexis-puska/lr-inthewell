#ifndef __MYCLASS_QUEST
#define __MYCLASS_QUEST

#include "Item.h"
#include <stdio.h>
#include <vector>
#include <map>
#include <string>

class Quest {
	public:
		Quest();
		~Quest();
		Quest(int id, bool bombe, bool bombeUp, bool life, bool light, int disguise, int key, int giveOption, int giveMode, int removeFamilly, int giveFamilly, std::string titre, std::string description);
		Quest(int id, bool bombe, bool bombeUp, bool life, bool light, int disguise, int key, int giveOption, int giveMode, int removeFamilly, std::string titre, std::string description);
		std::string getTitre();
		std::string getDescription();
		int getId();
		int getGiveOption();
		int getGiveMode();
		int getRemoveFamilly();
		std::vector<int> getGiveFamilly();
		std::map<int, int> getRequireItemId();
		void addRequireItemId(int itemId, int quantity);
		void addGiveFamilly(int famillyId);
		void printName();
		bool giveLife();
		bool turnLightOn();
	private:
		std::map<int, int> requireItemId;
		int id;
		std::string titre;
		std::string description;
		int giveOption;
		int giveMode;
		int removeFamilly;
		bool life;
		bool light;
		std::vector<int> giveFamilly;
};
#endif
