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
#include "../level/Ennemie.h"
#include "../level/Vortex.h"
#include "../level/Platform.h"
#include "../level/Rayon.h"
#include "../level/Teleporter.h"
#include "../definition/Position.h"

class LevelService {

	public:
		static LevelService& Instance();
		LevelService();
		~LevelService();
		Level * getLevel(int id);
	private:
		LevelService& operator=(const LevelService&);
		LevelService(const LevelService&);
		static LevelService m_instance;

		/***********************
		 *      VARIABLES
		 ***********************/
		std::map<int, Json::Value> levelJson;
		Level * currentLevel;
		int currentLevelId;
		/***********************
		 *      FUNCTIONS
		 ***********************/
		void parseJsonFile();

};
#endif