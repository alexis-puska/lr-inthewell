#include "LevelService.h"


#include "../level/Door.h"
#include "../level/Event.h"
#include "../level/Ennemie.h"
#include "../level/Vortex.h"
#include "../level/Platform.h"
#include "../level/Rayon.h"
#include "../level/Teleporter.h"
#include "../definition/Position.h"
#include "resources/json_level_parser.h"

LevelService LevelService::m_instance = LevelService();

LevelService::LevelService() {
	fprintf(stderr, "Init levelService system\n");
	parseJsonFile();
}

LevelService::~LevelService() {
	fprintf(stderr, "close levelService system\n");
}

LevelService& LevelService::Instance() {
	return m_instance;
}

void LevelService::parseJsonFile() {
	Json::Reader reader;
	Json::Value root;
	Json::Value element;

	std::string jsonString(json_level_parser_json, json_level_parser_json + sizeof json_level_parser_json / sizeof json_level_parser_json[0]);
	reader.parse(jsonString, root);
	int idx = 0;

	for (unsigned int i = 0; i < root.size(); i++) {
		fprintf(stderr, "level id : %i", root[i]["id"].asInt());
	}
}
