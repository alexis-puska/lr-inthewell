#include <iostream>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <map>

#ifndef __MYCLASS_LEVEL_SERVICE
#define __MYCLASS_LEVEL_SERVICE

#include "json/json.h"
#include "../level/Level.h"

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
		std::map<int, Json::Value> values;
		Level * currentLevel;
		int currentLevelId;
		/***********************
		 *      FUNCTIONS
		 ***********************/
		void parseJsonFile();

};
#endif