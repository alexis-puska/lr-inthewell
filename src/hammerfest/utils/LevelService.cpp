#include "LevelService.h"
#include "resources/json_level_parser.h"

LevelService::LevelService()
{
	std::cout << "Init levelService system\n";
	currentLevelId = -1;
	parseJsonFile();
}

LevelService::~LevelService()
{
	std::cout << "close levelService system\n";
}

LevelService &LevelService::Instance()
{
	static LevelService m_instance;
	return m_instance;
}

/*********************************************
 * Parse JSON File and split it in different
 * elements to be parsed later in each level
 * load
 *********************************************/
void LevelService::parseJsonFile()
{
    Json::Reader reader;
    Json::Value root;
    std::string jsonString(json_level_parser_json, json_level_parser_json + sizeof json_level_parser_json / sizeof json_level_parser_json[0]);
    reader.parse(jsonString, root);
    
    Json::Value type = root["type"][0];
    for (unsigned int i = 0; i < type["level"].size(); i++)
    {
        adventureLevelJson[type["level"][i]["id"].asInt()] = type["level"][i];
    }
    
    type = root["type"][1];
    for (unsigned int i = 0; i < type["level"].size(); i++)
    {
        tutorialLevelJson[type["level"][i]["id"].asInt()] = type["level"][i];
    }
    
    type = root["type"][2];
    for (unsigned int i = 0; i < type["level"].size(); i++)
    {
        soccerFestLevelJson[type["level"][i]["id"].asInt()] = type["level"][i];
    }
    
    type = root["type"][3];
    for (unsigned int i = 0; i < type["level"].size(); i++)
    {
        timeAttackLevelJson[type["level"][i]["id"].asInt()] = type["level"][i];
    }
}

/*********************************************
 * Get Level function
 * Parse the JSON Element and build level
 *********************************************/
Level *LevelService::getLevel(int type, int id)
{
    
	if (currentLevel == NULL || currentLevel->getId() != id)
	{
		if (currentLevel != NULL)
		{
			delete currentLevel;
		}
		currentLevelId = id;
		Json::Value level = adventureLevelJson[id];
		currentLevel = new Level(level["id"].asInt(), level["showPlatform"].asBool(), level["background"].asInt(),
								 level["verticalPlateform"].asInt(), level["horizontalPlateform"].asInt(), level["next"].asInt());

		//BUILD LEVEL

		for (unsigned int i = 0; i < level["platform"].size(); i++)
		{
            Json::Value platform =level["platform"][i];
			currentLevel->addPlatform(
				new Platform(platform["id"].asInt(), platform["x"].asInt(), platform["y"].asInt(),
							 platform["vertical"].asBool(), platform["displayed"].asBool(), platform["length"].asInt(),
                             platform["vertical"].asBool() ? level["verticalPlateform"].asInt() : level["horizontalPlateform"].asInt(), platform["enable"].asBool()));
		}

		for (unsigned int i = 0; i < level["rayon"].size(); i++)
		{
            Json::Value rayon = level["rayon"][i];
			currentLevel->addRayons(
				new Rayon(rayon["x"].asInt(), rayon["y"].asInt(), rayon["length"].asInt(),
						  rayon["type"].asInt(),

						  rayon["vertical"].asBool()));
		}

		for (unsigned int i = 0; i < level["teleporter"].size(); i++)
		{
            Json::Value teleporter = level["teleporter"][i];
			currentLevel->AddTeleporter(
				new Teleporter(teleporter["id"].asInt(), teleporter["x"].asInt(),
							   teleporter["y"].asInt(), teleporter["length"].asInt(),
							   teleporter["vertical"].asBool(), teleporter["toId"].asInt()));
		}

		for (unsigned int i = 0; i < level["decor"].size(); i++)
		{
            Json::Value decor = level["decor"][i];
			currentLevel->addDecor(
				new Decor(decor["id"].asInt(), decor["x"].asInt(), decor["y"].asInt(),
						  decor["display"].asBool(), decor["back"].asBool(),
						  decor["anim"].asString(), decor["toId"].asInt()));
		}

		for (unsigned int i = 0; i < level["ennemies"].size(); i++)
		{
            Json::Value ennemies = level["ennemies"][i];
			int id = ennemies["id"].asInt();
			int x = ennemies["x"].asInt();
			int y = ennemies["y"].asInt();

			switch (ennemies["type"].asInt())
			{
			case cerise:
				currentLevel->addEnnemie(new Cerise(id, x, y, currentLevel));
				break;
			case orange:
				currentLevel->addEnnemie(new Orange(id, x, y, currentLevel));
				break;
			case pomme:
				currentLevel->addEnnemie(new Pomme(id, x, y, currentLevel));
				break;
			case citron:
				currentLevel->addEnnemie(new Citron(id, x, y, currentLevel));
				break;
			case banane:
				currentLevel->addEnnemie(new Banane(id, x, y, currentLevel));
				break;
			case bombinos:
				currentLevel->addEnnemie(new Bombinos(id, x, y, currentLevel));
				break;
			case poire:
				currentLevel->addEnnemie(new Poire(id, x, y, currentLevel));
				break;
			case abricot:
				currentLevel->addEnnemie(new Abricot(id, x, y, currentLevel));
				break;
			case litchi:
				currentLevel->addEnnemie(new Litchi(id, x, y, currentLevel));
				break;
			case fraise:
				currentLevel->addEnnemie(new Fraise(id, x, y, currentLevel));
				break;
			case kiwi:
				currentLevel->addEnnemie(new Kiwi(id, x, y, currentLevel));
				break;
			case pasteque:
				currentLevel->addEnnemie(new Pasteque(id, x, y, currentLevel));
				break;
			case ananas:
				currentLevel->addEnnemie(new Ananas(id, x, y, currentLevel));
				break;
			case blob:
				currentLevel->addEnnemie(new Blob(id, x, y, currentLevel));
				break;
			case framboise:
				currentLevel->addEnnemie(new Framboise(id, x, y, currentLevel));
				break;
			case nainbricot:
				currentLevel->addEnnemie(new NainBricot(id, x, y, currentLevel));
				break;
			case scie:
				currentLevel->addEnnemie(new Scie(id, x, y, currentLevel));
				break;
			}
		}

		//TODO
		for (unsigned int i = 0; i < level["events"].size(); i++)
		{
			currentLevel->addEvent(NULL);
		}

		for (unsigned int i = 0; i < level["doors"].size(); i++)
		{
			currentLevel->addDoor(NULL);
		}

		for (unsigned int i = 0; i < level["vortexs"].size(); i++)
		{
			currentLevel->addVortex(NULL);
		}

		for (unsigned int i = 0; i < level["startPlayers"].size(); i++)
		{
			currentLevel->addStartPlayer(NULL);
		}

		for (unsigned int i = 0; i < level["startEffectObjets"].size(); i++)
		{
			currentLevel->addStartEffectObject(NULL);
		}

		for (unsigned int i = 0; i < level["startPointObjets"].size(); i++)
		{
			currentLevel->addStartPointObject(NULL);
		}
 
        std::cout<< "get level end " << type << " " << id <<"\n";
	}
	return currentLevel;
}
