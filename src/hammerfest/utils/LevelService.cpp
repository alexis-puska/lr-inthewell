#include "LevelService.h"
#include "resources/json_level_parser.h"

LevelService LevelService::m_instance = LevelService();

LevelService::LevelService() {
	fprintf(stderr, "Init levelService system\n");
	currentLevelId = -1;
	parseJsonFile();
}

LevelService::~LevelService() {
	fprintf(stderr, "close levelService system\n");
}

LevelService& LevelService::Instance() {
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
	fprintf(stderr, "init string\n");
	std::string jsonString(json_level_parser_json, json_level_parser_json + sizeof json_level_parser_json / sizeof json_level_parser_json[0]);
	fprintf(stderr, "parse string : %s\n", jsonString.c_str());
	reader.parse(jsonString, root);
	fprintf(stderr, "file map\n");
	for (unsigned int i = 0; i < root.size(); i++) {
		values[root[i]["id"].asInt()] = root[i];
	}
	fprintf(stderr, "end init\n");
}

/*********************************************
 * Get Level function
 * Parse the JSON Element and build level
 *********************************************/
Level * LevelService::getLevel(int id) {
	if (currentLevel == NULL || currentLevel->getId() != id) {
		currentLevelId = id;
		Json::Value Element = values[id];
		currentLevel = new Level(Element["id"].asInt(), true, 0, 0, 0);
		//BUILD LEVEL
		//TODO
	}
	return currentLevel;
}
