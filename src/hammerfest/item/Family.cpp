#include "Family.h"

Family::~Family() {
	items.clear();
}

Family::Family(int id, const char * name) :
		IdElement(id) {
	strcpy(this->name, name);
}

void Family::addItem(int itemId) {
	items.push_back(itemId);
}

std::vector<int> Family::getItems() {
	return items;
}

void Family::printName() {
	fprintf(stderr, "%i - %s\n", id, name);
}

void Family::printJson() {
	fprintf(stderr, "{\"id\":%i,\"name\":[\n{\"fr\":\"%s\"},\n{\"en\":\"%s\"},\n{\"es\":\"%s\"}\n],\"items\":[", id, name, name, name);
	for(int i = 0;i < items.size();i++){
		if(i < items.size() -1){
			fprintf(stderr, "%i,",items[i]);
		}else{
			fprintf(stderr, "%i",items[i]);
		}
	}
	fprintf(stderr, "]},\n");
}