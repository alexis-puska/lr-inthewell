#ifndef __MYCLASS_FAMILY
#define __MYCLASS_FAMILY

#include <vector>
#include <string>
#include <iostream>
#include "../definition/IdElement.h"

class Family : public IdElement{
	public:
		~Family();
    Family(int id, std::string name);
		void addItem(int itemId);
		void printName();
		void printJson();
		std::vector<int> getItems();
	private:
        std::string name;
		std::vector <int> items;
};
#endif
