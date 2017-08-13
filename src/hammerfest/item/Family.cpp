#include "Family.h"

Family::~Family() {
	items.clear();
}

Family::Family(int id, std::string name) :
		IdElement(id) {
	this->name = name;
}

void Family::addItem(int itemId) {
	items.push_back(itemId);
}

std::vector<int> Family::getItems() {
	return items;
}

void Family::printName() {
    std::cout<< id << " - " << name<<"\n";
}

void Family::printJson() {
    std::cout<<"{\"id\":"<<id<<",\"name\":[\n{\"fr\":\""<<name<<"\"},\n{\"en\":\""<<name<<"\"},\n{\"es\":\""<<name<<"\"}\n],\"items\":[";
	for(unsigned int i = 0;i < items.size();i++){
		if(i < items.size() -1){
            std::cout<<items[i]<<",";
		}else{
            std::cout<<items[i];
		}
	}
    std::cout <<"]},\n";
}