#ifndef __MYCLASS_FAMILY
#define __MYCLASS_FAMILY

#include <vector>
#include <stdio.h>
#include <string.h>
#include "../definition/IdElement.h"

class Family : public IdElement{
	public:
		~Family();
		Family(int id, const char * name);
		void addItem(int itemId);
		void printName();
		std::vector<int> getItems();
	private:
		char name[50];
		std::vector <int> items;
};
#endif
