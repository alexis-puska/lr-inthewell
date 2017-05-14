#include "ItemFileSystem.h"

ItemFileSystem::ItemFileSystem() {

}

ItemFileSystem::~ItemFileSystem() {

}

ItemFileSystem ItemFileSystem::m_instance = ItemFileSystem();

ItemFileSystem& ItemFileSystem::Instance() {
	return m_instance;
}

/***************************************************************
 * Create the save file on disk, 4 account
 * each account containe in this order :
 * - max score of player
 * - score of the last game played
 * - number of game player
 * - level maximum reached
 * - the number of each 353 item contained in fridge
 **************************************************************/
void ItemFileSystem::init(char * path, bool newSaveFile) {
	strcpy(this->saveFilePath, path);
	fprintf(stderr, "init item file system : ");
	if (newSaveFile) {
		fprintf(stderr, "create..........");
		saveFile = fopen(path, "r+");
		for (int i = 0; i < 4; i++) {
			for (int i = 0; i < nbOfValueInFile; i++) {
				fprintf(saveFile, "%08x", 0);
			}
		}
		fclose(saveFile);

	}
	fprintf(stderr, "end\n");
}

/***************************************************************
 * Load a account from the saved file. 4 account by file
 * - position of account to load
 * each account containe in this order :
 * - max score of player
 * - score of the last game played
 * - number of game player
 * - level maximum reached
 * - the number of each 353 item contained in fridge
 **************************************************************/
void ItemFileSystem::loadAccount(int accountId) {
	//read some value
	this->accountLoaded = accountId;
	fprintf(stderr, "Loading data from file System, Accound : %i\n", accountId);
	saveFile = fopen(saveFilePath, "r+");
	rewind(saveFile);
	fseek(saveFile, (nbOfValueInFile * 8) * accountId, SEEK_SET);
	fscanf(saveFile, "%08x", &scoreMax);
	//fprintf(stderr, "Score max : %u\n", scoreMax);
	fseek(saveFile, (nbOfValueInFile * 8) * accountId + 8, SEEK_SET);
	fscanf(saveFile, "%08x", &scoreLastGame);
	//fprintf(stderr, "Score max : %u\n", scoreMax);
	fseek(saveFile, (nbOfValueInFile * 8) * accountId + 16, SEEK_SET);
	fscanf(saveFile, "%08x", &nbGame);
	//fprintf(stderr, "Nb of game played : %u\n", nbGame);
	fseek(saveFile, (nbOfValueInFile * 8) * accountId + 24, SEEK_SET);
	fscanf(saveFile, "%08x", &levelReached);
	//fprintf(stderr, "level reach : %u\n", levelReached);
	for (int i = 4; i < nbOfValueInFile; i++) {
		fseek(saveFile, (nbOfValueInFile * 8) * accountId + i * 8, SEEK_SET);
		fscanf(saveFile, "%08x", &fridge[i - 3]);
		//	fprintf(stderr, "%u ", fridge[i-3]);
	}
	fclose(saveFile);
	//fprintf(stderr,"\n");
}

/***************************************************************
 * Save a account.
 * - score to save
 * - boolean if a game was played to incremente the game counter
 * - level reached in the last game
 **************************************************************/
void ItemFileSystem::save(int score, bool gamePlayed, int level) {
	saveFile = fopen(saveFilePath, "r+");
	fseek(saveFile, (nbOfValueInFile * 8) * accountLoaded, SEEK_SET);
	if (score > scoreMax) {
		fprintf(saveFile, "%08x", score);
	} else {
		fseek(saveFile, (nbOfValueInFile * 8) * accountLoaded + 8, SEEK_SET);
	}
	fprintf(saveFile, "%08x", score);
	if (gamePlayed) {
		nbGame++;
	}
	fprintf(saveFile, "%08x", nbGame);
	if (levelReached < level) {
		levelReached = level;
	}
	fprintf(saveFile, "%08x", levelReached);
	for (int i = 4; i < nbOfValueInFile; i++) {
		fprintf(saveFile, "%08x", fridge[i - 3]);
	}
	fclose(saveFile);
}
