#include "ItemFileSystem.h"

ItemFileSystem::ItemFileSystem() {

}

ItemFileSystem::~ItemFileSystem() {

}

ItemFileSystem ItemFileSystem::m_instance = ItemFileSystem();

ItemFileSystem& ItemFileSystem::Instance() {
	return m_instance;
}

void ItemFileSystem::init(char * path, bool newSaveFile) {
	strcpy(this->saveFilePath, path);
	fprintf(stderr,"init item file system : ");
	if (newSaveFile) {

		fprintf(stderr,"create..........");
		saveFile = fopen(path, "r+");
		int i = 0;

		if (!writeInFile) {
			for (i = 0; i < 353; i++) {
				fprintf(saveFile, "%08x", 150);
			}
			fseek(saveFile, 16, SEEK_SET);
			fprintf(saveFile, "%08x", 4018716481);
		}
		fclose(saveFile);
	}
	fprintf(stderr,"end\n");
}

void ItemFileSystem::loadAccount(int accountId) {
	//read some value
	fprintf(stderr,"Loading data from file System\n");
	saveFile = fopen(saveFilePath, "r+");
	int read = 0;
	rewind(saveFile);
	for (int i = 0; i < 353; i++) {
		fseek(saveFile, i * 8, SEEK_SET);
		fscanf(saveFile, "%08x", &read);
	//	fprintf(stderr, "%010u ", read);
	}
	fclose(saveFile);
}
