#include <iostream>
#include <fstream>
#include <vector>
#include <map>

#ifndef __MYCLASS_LEVEL_SERVICE
#define __MYCLASS_LEVEL_SERVICE

#include "json/json.h"

#include "../level/Level.h"
#include "../level/Door.h"
#include "../level/Event.h"
#include "../level/ennemies/Ennemie.h"
#include "../level/ennemies/Cerise.h"
#include "../level/ennemies/Orange.h"
#include "../level/ennemies/Pomme.h"
#include "../level/ennemies/Banane.h"
#include "../level/ennemies/Citron.h"
#include "../level/ennemies/Bombinos.h"
#include "../level/ennemies/Poire.h"
#include "../level/ennemies/Abricot.h"
#include "../level/ennemies/Litchi.h"
#include "../level/ennemies/Fraise.h"
#include "../level/ennemies/Kiwi.h"
#include "../level/ennemies/Pasteque.h"
#include "../level/ennemies/Ananas.h"
#include "../level/ennemies/Blob.h"
#include "../level/ennemies/Framboise.h"
#include "../level/ennemies/NainBricot.h"
#include "../level/ennemies/Scie.h"
#include "../level/Vortex.h"
#include "../level/Platform.h"
#include "../level/Rayon.h"
#include "../level/Teleporter.h"
#include "../definition/Position.h"

class LevelService
{

  public:
	static LevelService &Instance();
	LevelService();
	~LevelService();
	Level *getLevel(int id);

  private:
	LevelService &operator=(const LevelService &);
	LevelService(const LevelService &);

	/***********************
	 *      VARIABLES
	 ***********************/
	std::map<int, Json::Value> levelJson;
	Level *currentLevel;
	int currentLevelId;
	/***********************
	 *      FUNCTIONS
	 ***********************/
	void parseJsonFile();
};
#endif