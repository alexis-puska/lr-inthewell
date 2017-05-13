#ifndef __MYCLASS_FAMILLY
#define __MYCLASS_FAMILLY

#include <Vector>
#include <string.h>

class Familly {
	public:
		Familly();
		~Familly();
		Familly(int id, char * name);
		void addItem(int itemId);
	private:
		int id;
		char name[50];
		std::vector <int> items;
};
#endif
