#ifndef __MYCLASS_FAMILY
#define __MYCLASS_FAMILY

#include <vector>
#include <stdio.h>
#include <string.h>

class Family {
	public:
		Family();
		~Family();
		Family(int id, const char * name);
		void addItem(int itemId);
		void printName();
		std::vector<int> getItems();
	private:
		int id;
		char name[50];
		std::vector <int> items;
};
#endif
