#ifndef __MYCLASS_QUEST
#define __MYCLASS_QUEST

#include "Item.h"
#include <Vector>
#include <Map>

class Quest {
	public:
		Quest();
		~Quest();
		Quest(char * titre,char * description, int giveOption, int giveMode, int removeFamilly, int giveFamilly);
		Quest(char * titre,char * description, int giveOption, int giveMode, int removeFamilly);
		char * getTitre();
		char * getDescription();
		int getGiveOption();
		int getGiveMode();
		int getRemoveFamilly();
		std::vector<int> getGiveFamilly();
		std::map<int, int> getRequireItemId();
		void addRequireItemId(int itemId, int quantity);
		void addGiveFamilly(int famillyId);
	private:
		std::map<int, int> requireItemId;
		char titre[40];
		char description[512];
		int giveOption;
		int giveMode;
		int removeFamilly;
		std::vector<int> giveFamilly;
};
#endif
