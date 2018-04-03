#ifndef __MYCLASS_ITEM
#define __MYCLASS_ITEM

#include <iostream>
#include <string>
#include "../definition/IdElement.h"

#define sizeX 32
#define sizeY 32

class Item : public IdElement
{
  public:
	~Item();
	Item(int id, std::string name, int rarity, int value, int unlock);
	std::string getName();
	int getRarity();
	int getUnlock();
	int getValue();
	void printName();
	void printJson();

  private:
	std::string name;
	int value;
	int rarity;
	int unlock;
};
#endif
