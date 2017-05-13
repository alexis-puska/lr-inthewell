#include "Familly.h"

Familly::Familly(){

}

Familly::~Familly(){
	items.clear();
}

Familly::Familly(int id, char * name){
	this->id = id;
	strcpy(this->name, name);
}

void Familly::addItem(int itemId){
	items.push_back(itemId);
}