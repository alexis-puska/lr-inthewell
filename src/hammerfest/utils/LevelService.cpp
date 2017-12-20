#include "LevelService.h"
#include "resources/json_level_parser.h"

LevelService::LevelService() {
	std::cout << "Init levelService system\n";
	currentLevelId = -1;
	parseJsonFile();
}

LevelService::~LevelService() {
	std::cout << "close levelService system\n";
}

LevelService& LevelService::Instance() {
	static LevelService m_instance;
	return m_instance;
}

/*********************************************
 * Parse JSON File and split it in different
 * elements to be parsed later in each level
 * load
 *********************************************/
void LevelService::parseJsonFile() {
	Json::Reader reader;
	Json::Value root;
	std::string jsonString(json_level_parser_json, json_level_parser_json + sizeof json_level_parser_json / sizeof json_level_parser_json[0]);
	reader.parse(jsonString, root);
	for (unsigned int i = 0; i < root.size(); i++) {
		levelJson[root[i]["id"].asInt()] = root[i];
	}
}

/*********************************************
 * Get Level function
 * Parse the JSON Element and build level
 *********************************************/
Level * LevelService::getLevel(int id) {
	if (currentLevel == NULL || currentLevel->getId() != id) {
		if (currentLevel != NULL) {
			delete currentLevel;
		}
		currentLevelId = id;
		Json::Value level = levelJson[id];
		currentLevel = new Level(level["id"].asInt(), level["showPlatform"].asBool(), level["background"].asInt(),
			level["verticalPlateform"].asInt(), level["horizontalPlateform"].asInt(), level["next"].asInt());

		//BUILD LEVEL

		for (unsigned int i = 0; i < level["platform"].size(); i++) {
			currentLevel->addPlatform(
				new Platform(level["platform"][i]["id"].asInt(), level["platform"][i]["x"].asInt(), level["platform"][i]["y"].asInt(),
					level["platform"][i]["vertical"].asBool(), level["showPlatform"].asBool(),
					level["platform"][i]["length"].asInt(),
					level["platform"][i]["vertical"].asBool() ?
					level["verticalPlateform"].asInt() : level["horizontalPlateform"].asInt()));
		}

		for (unsigned int i = 0; i < level["rayon"].size(); i++) {
			currentLevel->addRayons(
				new Rayon(level["rayon"][i]["x"].asInt(), level["rayon"][i]["y"].asInt(), level["rayon"][i]["length"].asInt(),
					level["rayon"][i]["type"].asInt(),

					level["rayon"][i]["vertical"].asBool()));
		}

		for (unsigned int i = 0; i < level["teleporter"].size(); i++) {
			currentLevel->AddTeleporter(
				new Teleporter(level["teleporter"][i]["id"].asInt(), level["teleporter"][i]["x"].asInt(),
					level["teleporter"][i]["y"].asInt(), level["teleporter"][i]["length"].asInt(),
					level["teleporter"][i]["vertical"].asBool(), level["teleporter"][i]["toId"].asInt()));
		}

		for (unsigned int i = 0; i < level["decor"].size(); i++) {
			currentLevel->addDecor(
				new Decor(level["decor"][i]["id"].asInt(), level["decor"][i]["x"].asInt(), level["decor"][i]["y"].asInt(),
					level["decor"][i]["display"].asBool(), level["decor"][i]["back"].asBool(),
					level["decor"][i]["anim"].asString(), level["decor"][i]["toId"].asInt()));
		}

		for (unsigned int i = 0; i < level["ennemies"].size(); i++) {
			switch (level["ennemies"][i]["type"].asInt()) {
			case cerise:
				currentLevel->addEnnemie(
					new Cerise(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case orange:
				currentLevel->addEnnemie(
					new Orange(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case pomme:
				currentLevel->addEnnemie(
					new Pomme(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case banane:
				currentLevel->addEnnemie(
					new Banane(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case bombinos:
				currentLevel->addEnnemie(
					new Bombinos(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case poire:
				currentLevel->addEnnemie(
					new Poire(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case abricot:
				currentLevel->addEnnemie(
					new Abricot(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case litchi:
				currentLevel->addEnnemie(
					new Litchi(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case fraise:
				currentLevel->addEnnemie(
					new Fraise(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case kiwi:
				currentLevel->addEnnemie(
					new Kiwi(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case pasteque:
				currentLevel->addEnnemie(
					new Pasteque(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case ananas:
				currentLevel->addEnnemie(
					new Ananas(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case blob:
				currentLevel->addEnnemie(
					new Blob(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case framboise:
				currentLevel->addEnnemie(
					new Framboise(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case nainbricot:
				currentLevel->addEnnemie(
					new NainBricot(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			case scie:
				currentLevel->addEnnemie(
					new Scie(level["ennemies"][i]["id"].asInt(), level["ennemies"][i]["x"].asInt(), level["ennemies"][i]["y"].asInt()));
				break;
			}

		}

		//TODO
		for (unsigned int i = 0; i < level["events"].size(); i++) {
			currentLevel->addEvent(NULL);
		}

		for (unsigned int i = 0; i < level["doors"].size(); i++) {
			currentLevel->addDoor(NULL);
		}

		for (unsigned int i = 0; i < level["vortexs"].size(); i++) {
			currentLevel->addVortex(NULL);
		}

		for (unsigned int i = 0; i < level["startPlayers"].size(); i++) {
			currentLevel->addStartPlayer(NULL);
		}

		for (unsigned int i = 0; i < level["startEffectObjets"].size(); i++) {
			currentLevel->addStartEffectObject(NULL);
		}

		for (unsigned int i = 0; i < level["startPointObjets"].size(); i++) {
			currentLevel->addStartPointObject(NULL);
		}
	}
	return currentLevel;
}
