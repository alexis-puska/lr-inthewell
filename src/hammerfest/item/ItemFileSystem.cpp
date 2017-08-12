#include "ItemFileSystem.h"

#include "../utils/resources/json_family_parser.h"
#include "../utils/resources/json_item_parser.h"
#include "../utils/resources/json_quest_parser.h"

enum key {
	gordon = 0,
	passepartout = 1,
	rigordangerous = 2,
	meluzzine = 3,
	bourru = 4,
	furtok = 5,
	rouille = 6,
	boisjoli = 7,
	mondeardus = 8,
	piquante = 9,
	passetuberculoz = 10,
	chauchemar = 11,
	passpyramide = 12
};

enum mode {
	timeattack = 0, multicoop = 1
};

enum disguise {
	carotte = 0, chapeaux = 1, poney = 2, pioupiou = 3, champignon = 4, cape = 5
};

enum option {
	boost = 0, mirror = 1, nightmare = 2, kickcontrol = 3, mirrormulti = 4, nightmaremulti = 5, lifesharing = 6, ninja = 7, bombexpert = 8, set_ta_0 = 9
};

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
void ItemFileSystem::init(std::string path, bool newSaveFile) {
	srand ((unsigned int)time(NULL));
    saveFilePath =  path;
	fprintf(stderr, "init item file system : ");
	if (newSaveFile) {
		fprintf(stderr, "create..........");
		saveFile = fopen(path.c_str(), "r+");
		for (int i = 0; i < 4; i++) {
			for (int i = 0; i < nbOfValueInFile; i++) {
				fprintf(saveFile, "%08x", 0);
			}
		}
		fclose(saveFile);

	}
	fprintf(stderr, "end\n");
	buildDatabase();
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
int ItemFileSystem::loadAccount(int accountId) {
//read some value
	this->accountLoaded = accountId;

	GameConfig::Instance().InitConfiguration();

	availableItemEffect0.clear();
	availableItemEffect1.clear();
	availableItemEffect2.clear();
	availableItemEffect3.clear();
	availableItemEffect4.clear();
	availableItemEffect5.clear();
	availableItemEffect6.clear();

	availableItemPoint0.clear();
	availableItemPoint1.clear();
	availableItemPoint2.clear();
	availableItemPoint3.clear();
	availableItemPoint4.clear();
	availableItemPoint5.clear();
	availableItemPoint6.clear();
	availableItemPoint7.clear();

	fprintf(stderr, "Loading data from file System, Accound : %i\n", accountId);
	saveFile = fopen(saveFilePath.c_str(), "r+");
	rewind(saveFile);
	fseek(saveFile, (nbOfValueInFile * 8) * accountId, SEEK_SET);
	if (fscanf(saveFile, "%08x", &scoreMax) <= 0) {
		fprintf(stderr, "error read file");
		return -1;
	}
	fseek(saveFile, (nbOfValueInFile * 8) * accountId + 8, SEEK_SET);
	if (fscanf(saveFile, "%08x", &scoreLastGame) <= 0) {
		fprintf(stderr, "error read file");
		return -1;
	}
	fseek(saveFile, (nbOfValueInFile * 8) * accountId + 16, SEEK_SET);
	if (fscanf(saveFile, "%08x", &nbGame) <= 0) {
		fprintf(stderr, "error read file");
		return -1;
	}
	fseek(saveFile, (nbOfValueInFile * 8) * accountId + 24, SEEK_SET);
	if (fscanf(saveFile, "%08x", &levelReached) <= 0) {
		fprintf(stderr, "error read file");
		return -1;
	}
	for (int i = 4; i < nbOfValueInFile; i++) {
		fseek(saveFile, (nbOfValueInFile * 8) * accountId + i * 8, SEEK_SET);
		if (fscanf(saveFile, "%08x", &fridge[i - 4]) <= 0) {
			fprintf(stderr, "error read file");
			return -1;
		}
	}

	//fprintf(stderr, "\n\n\n\n---------- LoadAccount ----------\n\n\n\n");

	//for (int i = 0; i < nbOfValueInFile - 4; i++) {
	//	fprintf(stderr, "%i - %6i;\t", i, fridge[i]);
	//}
	//fprintf(stderr, "\n\n\n\n---------- LoadAccount ----------\n\n\n\n");

	fclose(saveFile);
	loadDefaultAvailableItem();
	return 0;
}

void ItemFileSystem::loadDefaultAvailableItem() {

	std::vector<int> familyAvailable;
	std::vector<int> familyToRemove;
	//add default familly 0 for effect, 20 for point.
	familyAvailable.push_back(0);
	familyAvailable.push_back(7);
	familyAvailable.push_back(13);
	familyAvailable.push_back(20);
	familyAvailable.push_back(48);

	//fridge[304]=1;
	//fridge[308]=1;
	//fridge[310]=1;
	//fridge[312]=1;
	//fridge[315]=1;
	//diamant
	//fridge[126]=30;
	//fridge[118]=60;

	/********************
	 *  validate quest
	 ********************/
	questCompleted.clear();
	questStarted.clear();

	for (unsigned int i = 0; i < quests.size(); i++) {
		//fprintf(stderr, "validate quest %i\n", i);
		Quest * tested = quests.at(i);
		std::map<int, int> requiredItem = tested->getRequireItemId();
		bool valide = true;
		bool started = false;
		for (std::map<int, int>::iterator it = requiredItem.begin(); it != requiredItem.end(); ++it) {
			//fprintf(stderr, "%i %i %i\n", i, fridge[it->first], it->second);
			if (fridge[it->first] < it->second) {
				valide = false;
				break;
			}
			if (fridge[it->first] > 0) {
				started = true;
			}

		}
		if (valide) {
			//fprintf(stderr, "quest valide %i %i!!!\n", tested->getGiveFamilly().size(), tested->getRemoveFamilly());
			std::vector<int> givedFamilly = tested->getGiveFamilly();
			for (unsigned int j = 0; j < givedFamilly.size(); j++) {
				//fprintf(stderr, "add family : %i !!!\n", givedFamilly.at(j));
				familyAvailable.push_back(givedFamilly.at(j));
			}
			if (tested->getRemoveFamilly() != -1) {
				familyToRemove.push_back(tested->getRemoveFamilly());
			}
			questCompleted[tested->getId()] = tested;
			unlockSomething(tested);
		}
		if (started && !valide) {
			questStarted[tested->getId()] = tested;
		}

	}
	for (unsigned int i = 0; i < familyToRemove.size(); i++) {
		for (unsigned int j = 0; j < familyAvailable.size(); j++) {
			if (familyAvailable.at(j) == familyToRemove.at(i)) {
				//fprintf(stderr, "remove family : %i !!!\n", familyToRemove.at(i));
				//fprintf(stderr, "\n\nerase\n\n");
				familyAvailable.erase(familyAvailable.begin() + j);
				break;
			}
		}
	}

	for (unsigned int i = 0; i < familyAvailable.size(); i++) {
		familys.at(familyAvailable.at(i))->printName();
	}

	/**************************
	 *  fill available object
	 *  with unlocked familly
	 **************************/
	for (unsigned int i = 0; i < familyAvailable.size(); i++) {
		//fprintf(stderr, "traitment of family id : %i\n", familyAvailable.at(i));

		Family * tested = familys.at(familyAvailable.at(i));

		for (unsigned int j = 0; j < tested->getItems().size(); j++) {
			int id = tested->getItems().at(j);
			//fprintf(stderr, "treatment of item id : %i \n", id);
			Item * item = items.at(id);
			if (item->getValue() == -1) {
				switch (item->getRarity()) {
					case 0:
						availableItemEffect0.push_back(item->getId());
						break;
					case 1:
						availableItemEffect1.push_back(item->getId());
						break;
					case 2:
						availableItemEffect2.push_back(item->getId());
						break;
					case 3:
						availableItemEffect3.push_back(item->getId());
						break;
					case 4:
						availableItemEffect4.push_back(item->getId());
						break;
					case 5:
						availableItemEffect5.push_back(item->getId());
						break;
					case 6:
						availableItemEffect6.push_back(item->getId());
						break;
				}
			} else {
				switch (item->getRarity()) {
					case 0:
						availableItemPoint0.push_back(item->getId());
						break;
					case 1:
						availableItemPoint1.push_back(item->getId());
						break;
					case 2:
						availableItemPoint2.push_back(item->getId());
						break;
					case 3:
						availableItemPoint3.push_back(item->getId());
						break;
					case 4:
						availableItemPoint4.push_back(item->getId());
						break;
					case 5:
						availableItemPoint5.push_back(item->getId());
						break;
					case 6:
						availableItemPoint6.push_back(item->getId());
						break;
					case 7:
						availableItemPoint7.push_back(item->getId());
						break;
				}
			}
		}
	}

	fprintf(stderr, "base item load\n");
	fprintf(stderr, "\nbase available point 7\n");
	for (unsigned int i = 0; i < availableItemPoint7.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint7.at(i));
	}
	fprintf(stderr, "\nbase available point 6\n");
	for (unsigned int i = 0; i < availableItemPoint6.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint6.at(i));
	}
	fprintf(stderr, "\nbase available point 5\n");
	for (unsigned int i = 0; i < availableItemPoint5.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint5.at(i));
	}
	fprintf(stderr, "\nbase available point 4\n");
	for (unsigned int i = 0; i < availableItemPoint4.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint4.at(i));
	}
	fprintf(stderr, "\nbase available point 3\n");
	for (unsigned int i = 0; i < availableItemPoint3.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint3.at(i));
	}
	fprintf(stderr, "\nbase available point 2\n");
	for (unsigned int i = 0; i < availableItemPoint2.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint2.at(i));
	}
	fprintf(stderr, "\nbase available point 1\n");
	for (unsigned int i = 0; i < availableItemPoint1.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint1.at(i));
	}
	fprintf(stderr, "\nbase available point 0\n");
	for (unsigned int i = 0; i < availableItemPoint0.size(); i++) {
		fprintf(stderr, "%i ", availableItemPoint0.at(i));
	}
	fprintf(stderr, "\nbase available effect 6\n");
	for (unsigned int i = 0; i < availableItemEffect6.size(); i++) {
		fprintf(stderr, "%i ", availableItemEffect6.at(i));
	}
	fprintf(stderr, "\nbase available effect 5\n");
	for (unsigned int i = 0; i < availableItemEffect5.size(); i++) {
		fprintf(stderr, "%i ", availableItemEffect5.at(i));
	}
	fprintf(stderr, "\nbase available effect 4\n");
	for (unsigned int i = 0; i < availableItemEffect4.size(); i++) {
		fprintf(stderr, "%i ", availableItemEffect4.at(i));
	}
	fprintf(stderr, "\nbase available effect 3\n");
	for (unsigned int i = 0; i < availableItemEffect3.size(); i++) {
		fprintf(stderr, "%i ", availableItemEffect3.at(i));
	}
	fprintf(stderr, "\nbase available effect 2\n");
	for (unsigned int i = 0; i < availableItemEffect2.size(); i++) {
		fprintf(stderr, "%i ", availableItemEffect2.at(i));
	}
	fprintf(stderr, "\nbase available effect 1\n");
	for (unsigned int i = 0; i < availableItemEffect1.size(); i++) {
		fprintf(stderr, "%i ", availableItemEffect1.at(i));
	}
	fprintf(stderr, "\nbase available effect 0\n");
	for (unsigned int i = 0; i < availableItemEffect0.size(); i++) {
		fprintf(stderr, "%i ", availableItemEffect0.at(i));
	}

}

/***************************************************************
 * Save a account.
 * - score to save
 * - boolean if a game was played to incremente the game counter
 * - level reached in the last game
 **************************************************************/
void ItemFileSystem::save(int score, bool gamePlayed, int level) {
	saveFile = fopen(saveFilePath.c_str(), "r+");
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
		fprintf(saveFile, "%08x", fridge[i - 4]);
	}
	fclose(saveFile);
}

/***************************************************************
 * build database structure
 * -familly
 * -item
 * -quest
 **************************************************************/
void ItemFileSystem::buildDatabase() {
	parseFamilys();
	parseItems();
	parseQuests();
}

void ItemFileSystem::simulateGame() {

	for (int i = 0; i < 103; i++) {
		int point = getEffectItemId();
		int effect = getPointItemId();

		fridge[point] = fridge[point] + 1;
		fridge[effect] = fridge[effect] + 1;
		fprintf(stderr, "level %i - effect %i - point %i\n", i, effect, point);
	}
}

int ItemFileSystem::getEffectItemId() {
	int itemId = -1;
	int randCoef = 0;
	while (itemId == -1) {
		randCoef = random(probaCoef7);
		if (randCoef <= probaCoef1) {
			if (availableItemEffect1.size() > 0) {
				return availableItemEffect1.at(random((int)availableItemEffect1.size()) - 1);
			}
		} else if (randCoef <= probaCoef2) {
			if (availableItemEffect2.size() > 0) {
				return availableItemEffect2.at(random((int)availableItemEffect2.size()) - 1);
			}
		} else if (randCoef <= probaCoef3) {
			if (availableItemEffect3.size() > 0) {
				return availableItemEffect3.at(random((int)availableItemEffect3.size()) - 1);
			}
		} else if (randCoef <= probaCoef4) {
			if (availableItemEffect4.size() > 0) {
				return availableItemEffect4.at(random((int)availableItemEffect4.size()) - 1);
			}
		} else if (randCoef <= probaCoef5) {
			if (availableItemEffect5.size() > 0) {
				return availableItemEffect5.at(random((int)availableItemEffect5.size()) - 1);
			}
		} else if (randCoef <= probaCoef6) {
			if (availableItemEffect6.size() > 0) {
				return availableItemEffect6.at(random((int)availableItemEffect6.size()) - 1);
			}
		}
	}
	return itemId;
}
int ItemFileSystem::getPointItemId() {
	int itemId = -1;
	int randCoef = 0;
	while (itemId == -1) {
		randCoef = random(probaCoef7);
		if (randCoef <= probaCoef1) {
			if (availableItemPoint1.size() > 0) {
				return availableItemPoint1.at(random((int)
                                                     availableItemPoint1.size()) - 1);
			}
		} else if (randCoef <= probaCoef2) {
			if (availableItemPoint2.size() > 0) {
				return availableItemPoint2.at(random((int)availableItemPoint2.size()) - 1);
			}
		} else if (randCoef <= probaCoef3) {
			if (availableItemPoint3.size() > 0) {
				return availableItemPoint3.at(random((int)availableItemPoint3.size()) - 1);
			}
		} else if (randCoef <= probaCoef4) {
			if (availableItemPoint4.size() > 0) {
				return availableItemPoint4.at(random((int)availableItemPoint4.size()) - 1);
			}
		} else if (randCoef <= probaCoef5) {
			if (availableItemPoint5.size() > 0) {
				return availableItemPoint5.at(random((int)availableItemPoint5.size()) - 1);
			}
		} else if (randCoef <= probaCoef6) {
			if (availableItemPoint6.size() > 0) {
				return availableItemPoint6.at(random((int)availableItemPoint6.size()) - 1);
			}
		} else if (randCoef <= probaCoef7) {
			if (availableItemPoint7.size() > 0) {
				return availableItemPoint7.at(random((int)availableItemPoint7.size()) - 1);
			}
		}
	}
	return itemId;
}

int ItemFileSystem::random(int max) {
	return (rand() % (max) + 1);
}

Item * ItemFileSystem::getItem(int index) {
	return items.at(index);
}
int ItemFileSystem::getQuantity(int index) {
	return fridge[index];
}
Quest * ItemFileSystem::getQuest(int index) {
	return quests.at(index);
}

std::map<int, Quest *> ItemFileSystem::getQuestStarted() {
	return questStarted;
}
std::map<int, Quest *> ItemFileSystem::getQuestCompleted() {
	return questCompleted;
}

void ItemFileSystem::unlockSomething(Quest * tested) {
	switch (tested->getGiveMode()) {
		case timeattack:
			GameConfig::Instance().unlockTimeAttackMode();
			break;
		case multicoop:
			GameConfig::Instance().unlockMulticoopMode();
			break;
	}
	switch (tested->getGiveOption()) {
		case mirror:
			GameConfig::Instance().unlockSoloOption(0);
			break;
		case nightmare:
			GameConfig::Instance().unlockSoloOption(1);
			break;
		case ninja:
			GameConfig::Instance().unlockSoloOption(2);
			break;
		case bombexpert:
			GameConfig::Instance().unlockSoloOption(3);
			break;
		case boost:
			GameConfig::Instance().unlockSoloOption(4);
			break;
		case mirrormulti:
			GameConfig::Instance().unlockMultiOption(0);
			break;
		case nightmaremulti:
			GameConfig::Instance().unlockMultiOption(1);
			break;
		case lifesharing:
			GameConfig::Instance().unlockMultiOption(2);
			break;
		case kickcontrol:
			GameConfig::Instance().unlockKickcontrol();
	}
	if (tested->giveLife()) {
		GameConfig::Instance().incLife();
	}
	if (tested->turnLightOn()) {
		GameConfig::Instance().setLightOn();
	}

}

void ItemFileSystem::parseFamilys() {
	Json::Reader reader;
	Json::Value root;
	Family * family;
	std::string jsonString(json_family_parser_json, json_family_parser_json + sizeof json_family_parser_json / sizeof json_family_parser_json[0]);
	reader.parse(jsonString, root);
	std::stringstream ss;
	for (unsigned int i = 0; i < root.size(); i++) {
		Json::Value idValue = root[i]["id"];
		Json::Value nameValue = root[i]["name"];
		Json::Value frNameValue = nameValue["fr"];
		Json::Value enNameValue = nameValue["en"];
		Json::Value esNameValue = nameValue["es"];
		ss.str(std::string());
		ss << "family." << idValue.asInt() << ".name";
		Text::Instance().addTraduction("fr", ss.str(), frNameValue.asString());
		ss.str(std::string());
		ss << "family." << idValue.asInt() << ".name";
		Text::Instance().addTraduction("en", ss.str(), enNameValue.asString());
		ss.str(std::string());
		ss << "family." << idValue.asInt() << ".name";
		Text::Instance().addTraduction("es", ss.str(), esNameValue.asString());
		family = new Family(idValue.asInt(), frNameValue.asString().c_str());
		for (unsigned int j = 0; j < root[i]["items"].size(); j++) {
			family->addItem(root[i]["items"][j].asInt());
		}
		familys.push_back(family);
	}

}

void ItemFileSystem::parseItems() {
	Json::Reader reader;
	Json::Value root;
	Item * item;
	std::string jsonString(json_item_parser_json, json_item_parser_json + sizeof json_item_parser_json / sizeof json_item_parser_json[0]);
	reader.parse(jsonString, root);
	std::stringstream ss;
	for (unsigned int i = 0; i < root.size(); i++) {
		Json::Value idValue = root[i]["id"];
		Json::Value nameValue = root[i]["name"];
		Json::Value frNameValue = nameValue["fr"];
		Json::Value enNameValue = nameValue["en"];
		Json::Value esNameValue = nameValue["es"];
		ss.str(std::string());
		ss << "item." << idValue.asInt() << ".name";
		Text::Instance().addTraduction("fr", ss.str(), frNameValue.asString());
		ss.str(std::string());
		ss << "item." << idValue.asInt() << ".name";
		Text::Instance().addTraduction("en", ss.str(), enNameValue.asString());
		ss.str(std::string());
		ss << "item." << idValue.asInt() << ".name";
		Text::Instance().addTraduction("es", ss.str(), esNameValue.asString());
		Json::Value rarityValue = root[i]["rarity"];
		Json::Value valueValue = root[i]["value"];
		Json::Value unlockValue = root[i]["unlock"];
		item = new Item(idValue.asInt(), frNameValue.asString(), rarityValue.asInt(), valueValue.asInt(), unlockValue.asInt());
		items.push_back(item);
	}
}

void ItemFileSystem::parseQuests() {
	Json::Reader reader;
	Json::Value root;
	Quest * quest;
	std::string jsonString(json_quest_parser_json, json_quest_parser_json + sizeof json_quest_parser_json / sizeof json_quest_parser_json[0]);
	reader.parse(jsonString, root);
	std::stringstream ss;
	for (unsigned int i = 0; i < root.size(); i++) {
		Json::Value idValue = root[i]["id"];
		Json::Value lightValue = root[i]["light"];
		Json::Value lifeValue = root[i]["life"];
		Json::Value titreValue = root[i]["titre"];
		Json::Value frTitreValue = titreValue["fr"];
		Json::Value enTitreValue = titreValue["en"];
		Json::Value esTitreValue = titreValue["es"];
		ss.str(std::string());
		ss << "quest." << idValue.asInt() << ".title";
		Text::Instance().addTraduction("fr", ss.str(), frTitreValue.asString());

		ss.str(std::string());
		ss << "quest." << idValue.asInt() << ".title";
		Text::Instance().addTraduction("en", ss.str(), enTitreValue.asString());

		ss.str(std::string());
		ss << "quest." << idValue.asInt() << ".title";
		Text::Instance().addTraduction("es", ss.str(), esTitreValue.asString());

		Json::Value descriptionValue = root[i]["description"];
		Json::Value frDescriptionValue = descriptionValue["fr"];
		Json::Value enDescriptionValue = descriptionValue["en"];
		Json::Value esDescriptionValue = descriptionValue["es"];
		ss.str(std::string());
		ss << "quest." << idValue.asInt() << ".description";
		Text::Instance().addTraduction("fr", ss.str(), frDescriptionValue.asString());
		ss.str(std::string());
		ss << "quest." << idValue.asInt() << ".description";
		Text::Instance().addTraduction("en", ss.str(), enDescriptionValue.asString());
		ss.str(std::string());
		ss << "quest." << idValue.asInt() << ".description";
		Text::Instance().addTraduction("es", ss.str(), esDescriptionValue.asString());

		Json::Value optionValue = root[i]["option"];
		Json::Value modeValue = root[i]["mode"];
		Json::Value bombeValue = root[i]["bombe"];
		Json::Value bombeUpValue = root[i]["bombeUp"];
		Json::Value disguiseValue = root[i]["disguise"];
		Json::Value keyValue = root[i]["key"];
		Json::Value removeValue = root[i]["remove"];
		quest = new Quest(idValue.asInt(), bombeValue.asBool(), bombeUpValue.asBool(), lifeValue.asBool(), lightValue.asBool(), disguiseValue.asInt(), keyValue.asInt(), optionValue.asInt(),
				modeValue.asInt(), removeValue.asInt(), frTitreValue.asString(), frDescriptionValue.asString());
		Json::Value familyValue = root[i]["family"];
		for (unsigned int j = 0; j < familyValue.size(); j++) {
			quest->addGiveFamilly(familyValue[j].asInt());
		}
		Json::Value requireValue = root[i]["require"];
		for (unsigned int k = 0; k < requireValue.size(); k++) {
			quest->addRequireItemId(requireValue[k]["id"].asInt(), requireValue[k]["val"].asInt());
		}
		quests.push_back(quest);
	}
}
