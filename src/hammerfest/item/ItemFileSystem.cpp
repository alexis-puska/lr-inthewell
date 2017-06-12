#include "ItemFileSystem.h"

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
void ItemFileSystem::init(char * path, bool newSaveFile) {
	srand (time(NULL));strcpy(this->saveFilePath, path);
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
	saveFile = fopen(saveFilePath, "r+");
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

	fprintf(stderr, "\n\n\n\n---------- LoadAccount ----------\n\n\n\n");

	for (int i = 0; i < nbOfValueInFile - 4; i++) {
		fprintf(stderr, "%i - %6i;\t", i, fridge[i]);
	}
	fprintf(stderr, "\n\n\n\n---------- LoadAccount ----------\n\n\n\n");

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

	//fprintf(stderr, "\n\n\n\n\n");

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

	SDL_Surface * surface = NULL;

	Family * family = new Family(0, "Objets de base");
	family->addItem(0);
	family->addItem(3);
	family->addItem(4);
	family->addItem(7);
	family->addItem(13);
	family->addItem(21);
	family->addItem(24);
	family->addItem(64);
	family->addItem(74);
	family->addItem(77);
	family->addItem(84);
	family->addItem(102);
	family->addItem(113);
	family->addItem(115);
	family->addItem(116);
	family->addItem(117);
	familys.push_back(family);

	family = new Family(1, "Kit de premiers secours");
	family->addItem(1);
	family->addItem(5);
	family->addItem(8);
	family->addItem(11);
	family->addItem(18);
	family->addItem(22);
	family->addItem(23);
	family->addItem(25);
	family->addItem(27);
	family->addItem(28);
	family->addItem(38);
	family->addItem(39);
	family->addItem(65);
	family->addItem(66);
	family->addItem(69);
	family->addItem(71);
	family->addItem(82);
	family->addItem(106);
	family->addItem(107);
	familys.push_back(family);

	family = new Family(2, "Destruction massive");
	family->addItem(2);
	family->addItem(6);
	family->addItem(9);
	family->addItem(12);
	family->addItem(19);
	family->addItem(30);
	family->addItem(31);
	family->addItem(36);
	family->addItem(70);
	family->addItem(72);
	family->addItem(73);
	family->addItem(75);
	family->addItem(76);
	family->addItem(80);
	family->addItem(81);
	family->addItem(86);
	family->addItem(87);
	family->addItem(88);
	family->addItem(89);
	family->addItem(90);
	family->addItem(93);
	family->addItem(95);
	family->addItem(96);
	family->addItem(99);
	family->addItem(101);
	family->addItem(112);
	familys.push_back(family);

	family = new Family(3, "Champignons");
	family->addItem(14);
	family->addItem(15);
	family->addItem(16);
	family->addItem(17);
	familys.push_back(family);

	family = new Family(4, "Cartes a jouer");
	family->addItem(32);
	family->addItem(33);
	family->addItem(34);
	family->addItem(35);
	familys.push_back(family);

	family = new Family(5, "Signes du zodiaque");
	family->addItem(40);
	family->addItem(41);
	family->addItem(42);
	family->addItem(43);
	family->addItem(44);
	family->addItem(45);
	family->addItem(46);
	family->addItem(47);
	family->addItem(48);
	family->addItem(49);
	family->addItem(50);
	family->addItem(51);
	familys.push_back(family);

	family = new Family(6, "Potions du zodiaque");
	family->addItem(52);
	family->addItem(53);
	family->addItem(54);
	family->addItem(55);
	family->addItem(56);
	family->addItem(57);
	family->addItem(58);
	family->addItem(59);
	family->addItem(60);
	family->addItem(61);
	family->addItem(62);
	family->addItem(63);
	familys.push_back(family);

	family = new Family(7, "Coeur 1");
	family->addItem(103);
	familys.push_back(family);

	family = new Family(8, "Coeur 2");
	family->addItem(104);
	familys.push_back(family);

	family = new Family(9, "Coeur 3");
	family->addItem(105);
	familys.push_back(family);

	family = new Family(10, "Tresor des pirates");
	family->addItem(20);
	family->addItem(78);
	family->addItem(79);
	family->addItem(91);
	family->addItem(94);
	familys.push_back(family);

	family = new Family(11, "Gadgets Motion-Twin");
	family->addItem(83);
	family->addItem(97);
	family->addItem(98);
	family->addItem(100);
	family->addItem(108);
	familys.push_back(family);

	family = new Family(12, "Armement norvegien experimental");
	family->addItem(29);
	family->addItem(37);
	family->addItem(67);
	family->addItem(85);
	family->addItem(92);
	familys.push_back(family);

	family = new Family(13, "Eclairage antique");
	family->addItem(68);
	familys.push_back(family);

	family = new Family(14, "Igor-Newton");
	family->addItem(26);
	familys.push_back(family);

	family = new Family(15, "Flocon 1");
	family->addItem(109);
	familys.push_back(family);

	family = new Family(16, "Flocon 2");
	family->addItem(110);
	familys.push_back(family);

	family = new Family(17, "Flocon 3");
	family->addItem(111);
	familys.push_back(family);

	family = new Family(18, "Kit d'appel main libre");
	family->addItem(10);
	familys.push_back(family);

	family = new Family(19, "Mario party");
	family->addItem(114);
	familys.push_back(family);

	family = new Family(20, "Petites gâteries");
	family->addItem(118);
	family->addItem(121);
	family->addItem(126);
	family->addItem(131);
	family->addItem(135);
	family->addItem(145);
	family->addItem(159);
	family->addItem(161);
	family->addItem(165);
	family->addItem(166);
	family->addItem(167);
	family->addItem(168);
	family->addItem(169);
	family->addItem(287);
	family->addItem(303);
	familys.push_back(family);

	family = new Family(21, "Aliments classiques");
	family->addItem(140);
	family->addItem(142);
	family->addItem(143);
	family->addItem(144);
	family->addItem(146);
	family->addItem(158);
	family->addItem(187);
	family->addItem(188);
	family->addItem(189);
	family->addItem(191);
	family->addItem(192);
	family->addItem(193);
	family->addItem(195);
	family->addItem(196);
	family->addItem(197);
	family->addItem(198);
	family->addItem(199);
	family->addItem(200);
	familys.push_back(family);

	family = new Family(22, "Friandises");
	family->addItem(120);
	family->addItem(122);
	family->addItem(123);
	family->addItem(124);
	family->addItem(125);
	family->addItem(130);
	family->addItem(132);
	family->addItem(133);
	family->addItem(134);
	family->addItem(136);
	family->addItem(137);
	family->addItem(141);
	family->addItem(163);
	family->addItem(164);
	familys.push_back(family);

	family = new Family(23, "Pierres precieuses");
	family->addItem(127);
	family->addItem(128);
	family->addItem(129);
	familys.push_back(family);

	family = new Family(24, "Junk food");
	family->addItem(119);
	family->addItem(139);
	family->addItem(160);
	family->addItem(173);
	family->addItem(174);
	family->addItem(175);
	family->addItem(260);
	family->addItem(267);
	family->addItem(284);
	familys.push_back(family);

	family = new Family(25, "Exotic !");
	family->addItem(138);
	family->addItem(157);
	family->addItem(162);
	family->addItem(178);
	family->addItem(179);
	family->addItem(180);
	family->addItem(194);
	family->addItem(279);
	family->addItem(280);
	family->addItem(281);
	family->addItem(285);
	familys.push_back(family);

	family = new Family(26, "Aperitifs");
	family->addItem(147);
	family->addItem(148);
	family->addItem(149);
	family->addItem(150);
	family->addItem(151);
	family->addItem(152);
	family->addItem(153);
	family->addItem(154);
	family->addItem(155);
	family->addItem(156);
	family->addItem(282);
	familys.push_back(family);

	family = new Family(27, "Kapital Risk");
	family->addItem(170);
	family->addItem(171);
	family->addItem(172);
	familys.push_back(family);

	family = new Family(28, "Trophees de Grand Predateur");
	family->addItem(209);
	family->addItem(210);
	family->addItem(211);
	family->addItem(212);
	family->addItem(213);
	family->addItem(214);
	family->addItem(215);
	family->addItem(216);
	family->addItem(217);
	familys.push_back(family);

	family = new Family(29, "Delices de Harry 'le beau'");
	family->addItem(181);
	family->addItem(182);
	family->addItem(183);
	family->addItem(184);
	family->addItem(185);
	family->addItem(186);
	familys.push_back(family);

	family = new Family(30, "Chocolats");
	family->addItem(201);
	family->addItem(202);
	family->addItem(203);
	family->addItem(204);
	family->addItem(205);
	family->addItem(206);
	family->addItem(207);
	family->addItem(208);
	familys.push_back(family);

	family = new Family(31, "Fromages");
	family->addItem(224);
	family->addItem(225);
	family->addItem(226);
	family->addItem(227);
	family->addItem(228);
	family->addItem(229);
	familys.push_back(family);

	family = new Family(32, "Conserves");
	family->addItem(218);
	family->addItem(219);
	family->addItem(220);
	family->addItem(221);
	family->addItem(222);
	family->addItem(223);
	family->addItem(286);
	familys.push_back(family);

	family = new Family(33, "Legumes");
	family->addItem(230);
	family->addItem(231);
	family->addItem(232);
	family->addItem(233);
	family->addItem(234);
	family->addItem(235);
	family->addItem(236);
	family->addItem(237);
	family->addItem(238);
	family->addItem(239);
	family->addItem(240);
	family->addItem(241);
	family->addItem(242);
	family->addItem(243);
	family->addItem(244);
	family->addItem(245);
	family->addItem(246);
	family->addItem(247);
	family->addItem(248);
	family->addItem(249);
	family->addItem(250);
	family->addItem(251);
	family->addItem(252);
	family->addItem(253);
	family->addItem(254);
	familys.push_back(family);

	family = new Family(34, "Delices MT");
	family->addItem(259);
	family->addItem(261);
	familys.push_back(family);

	family = new Family(35, "Kit de survie MT");
	family->addItem(255);
	family->addItem(256);
	family->addItem(257);
	family->addItem(258);
	familys.push_back(family);

	family = new Family(36, "L'heure du gouter");
	family->addItem(262);
	family->addItem(263);
	family->addItem(264);
	family->addItem(265);
	family->addItem(266);
	family->addItem(268);
	family->addItem(269);
	family->addItem(270);
	family->addItem(271);
	family->addItem(272);
	family->addItem(273);
	family->addItem(277);
	family->addItem(278);
	familys.push_back(family);

	family = new Family(37, "Garcon patissier");
	family->addItem(176);
	family->addItem(177);
	family->addItem(190);
	family->addItem(274);
	family->addItem(275);
	family->addItem(276);
	family->addItem(283);
	familys.push_back(family);

	family = new Family(38, "Les lois de la robotique");
	family->addItem(288);
	family->addItem(289);
	family->addItem(290);
	family->addItem(291);
	family->addItem(292);
	family->addItem(293);
	family->addItem(294);
	family->addItem(295);
	familys.push_back(family);

	family = new Family(39, "Trophees de baroudeur");
	family->addItem(296);
	family->addItem(297);
	family->addItem(298);
	family->addItem(299);
	family->addItem(300);
	family->addItem(301);
	family->addItem(302);
	familys.push_back(family);

	family = new Family(40, "Cles des Glaces");
	family->addItem(304);
	family->addItem(305);
	family->addItem(308);
	family->addItem(311);
	family->addItem(312);
	family->addItem(313);
	family->addItem(314);
	familys.push_back(family);

	family = new Family(41, "Cle avinee");
	family->addItem(307);
	familys.push_back(family);

	family = new Family(42, "Paperasse");
	family->addItem(310);
	familys.push_back(family);

	family = new Family(43, "Cles perdues");
	family->addItem(306);
	family->addItem(309);
	familys.push_back(family);

	family = new Family(44, "Batons de joie");
	family->addItem(315);
	family->addItem(316);
	family->addItem(317);
	family->addItem(318);
	family->addItem(319);
	family->addItem(320);
	family->addItem(321);
	family->addItem(322);
	familys.push_back(family);

	family = new Family(45, "Boissons rigolotes");
	family->addItem(323);
	family->addItem(324);
	family->addItem(325);
	family->addItem(326);
	family->addItem(327);
	familys.push_back(family);

	family = new Family(46, "Materiel administratif d'El Papah");
	family->addItem(328);
	family->addItem(329);
	family->addItem(330);
	family->addItem(331);
	family->addItem(332);
	familys.push_back(family);

	family = new Family(47, "Artefacts mythiques");
	family->addItem(333);
	family->addItem(334);
	family->addItem(339);
	family->addItem(340);
	family->addItem(341);
	family->addItem(351);
	familys.push_back(family);

	family = new Family(48, "Sandy en kit");
	family->addItem(334);
	family->addItem(336);
	family->addItem(337);
	family->addItem(338);
	familys.push_back(family);

	family = new Family(49, "Recompenses du Ninjutsu");
	family->addItem(342);
	family->addItem(350);
	familys.push_back(family);

	family = new Family(50, "Artefacts du Ninjutsu");
	family->addItem(343);
	family->addItem(344);
	family->addItem(345);
	family->addItem(346);
	family->addItem(347);
	family->addItem(348);
	family->addItem(349);
	familys.push_back(family);

//	for (unsigned int i = 0; i < familys.size(); i++) {
//		familys[i]->printName();
//	}

	items.push_back(new Item(surface, 0, "Alphabet Cristallin", 0, -1, -1));
	items.push_back(new Item(surface, 1, "Bouclidur en or", 1, -1, -1));
	items.push_back(new Item(surface, 2, "Bouclidur argente", 3, -1, -1));
	items.push_back(new Item(surface, 3, "Ballon de banquise", 2, -1, -1));
	items.push_back(new Item(surface, 4, "Lampe Fetvoveu", 1, -1, -1));
	items.push_back(new Item(surface, 5, "Lampe Leveussonfe", 2, -1, -1));
	items.push_back(new Item(surface, 6, "Paix interieure", 1, -1, -1));
	items.push_back(new Item(surface, 7, "Basket IcePump", 1, -1, -1));
	items.push_back(new Item(surface, 8, "Etoile des neiges", 2, -1, -1));
	items.push_back(new Item(surface, 9, "Mauvais-oeil", 3, -1, -1));
	items.push_back(new Item(surface, 10, "Telephone-phone-phone", 1, -1, -1));
	items.push_back(new Item(surface, 11, "Parapluie rouge", 1, -1, -1));
	items.push_back(new Item(surface, 12, "Parapluie bleu", 2, -1, -1));
	items.push_back(new Item(surface, 13, "Cass-Tet", 1, -1, -1));
	items.push_back(new Item(surface, 14, "Delice hallucinogene bleu", 2, -1, -1));
	items.push_back(new Item(surface, 15, "Champignon rigolo rouge", 4, -1, -1));
	items.push_back(new Item(surface, 16, "Figonassee grimpante", 5, -1, -1));
	items.push_back(new Item(surface, 17, "Petit Waoulalu des bois", 6, -1, -1));
	items.push_back(new Item(surface, 18, "Pissenlit tropical", 2, -1, -1));
	items.push_back(new Item(surface, 19, "Tournelune", 3, -1, -1));
	items.push_back(new Item(surface, 20, "Coffre d\'Anarchipel", 1, -1, -1));
	items.push_back(new Item(surface, 21, "Enceinte Bessel-Son", 2, -1, -1));
	items.push_back(new Item(surface, 22, "Vieille chaussure trouee", 2, -1, -1));
	items.push_back(new Item(surface, 23, "Boule cristalline", 1, -1, -1));
	items.push_back(new Item(surface, 24, "Hippo-flocon", 3, -1, -1));
	items.push_back(new Item(surface, 25, "Flamme froide", 3, -1, -1));
	items.push_back(new Item(surface, 26, "Ampoule 30 watts", 3, -1, -1));
	items.push_back(new Item(surface, 27, "Porte-grenouilles", 2, -1, -1));
	items.push_back(new Item(surface, 28, "Bibelot en argent", 2, -1, -1));
	items.push_back(new Item(surface, 29, "Bague \'Thermostat 8\'", 3, -1, -1));
	items.push_back(new Item(surface, 30, "Lunettes tournantes bleues", 2, -1, -1));
	items.push_back(new Item(surface, 31, "Lunettes renversantes rouges", 2, -1, -1));
	items.push_back(new Item(surface, 32, "As de pique", 1, -1, -1));
	items.push_back(new Item(surface, 33, "As de trefle", 2, -1, -1));
	items.push_back(new Item(surface, 34, "As de carreau", 5, -1, -1));
	items.push_back(new Item(surface, 35, "As de coeur", 6, -1, -1));
	items.push_back(new Item(surface, 36, "Ig\'or", 3, -1, -1));
	items.push_back(new Item(surface, 37, "Collier rafraichissant", 2, -1, -1));
	items.push_back(new Item(surface, 38, "Totem des dinoz", 3, -1, -1));
	items.push_back(new Item(surface, 39, "Tete de granit lestee de plomb", 3, -1, -1));
	items.push_back(new Item(surface, 40, "Sagittaire", 3, -1, 1));
	items.push_back(new Item(surface, 41, "Capricorne", 3, -1, 1));
	items.push_back(new Item(surface, 42, "Lion", 3, -1, 1));
	items.push_back(new Item(surface, 43, "Taureau", 3, -1, 1));
	items.push_back(new Item(surface, 44, "Balance", 3, -1, 1));
	items.push_back(new Item(surface, 45, "Belier", 3, -1, 1));
	items.push_back(new Item(surface, 46, "Scorpion", 3, -1, 1));
	items.push_back(new Item(surface, 47, "Cancer", 3, -1, 1));
	items.push_back(new Item(surface, 48, "Verseau", 3, -1, 1));
	items.push_back(new Item(surface, 49, "Gemeaux", 3, -1, 1));
	items.push_back(new Item(surface, 50, "Poisson", 3, -1, 1));
	items.push_back(new Item(surface, 51, "Vierge", 3, -1, 1));
	items.push_back(new Item(surface, 52, "Elixir du Sagittaire", 3, -1, 1));
	items.push_back(new Item(surface, 53, "Elixir du Capricorne", 3, -1, 1));
	items.push_back(new Item(surface, 54, "Elixir du Lion", 3, -1, 1));
	items.push_back(new Item(surface, 55, "Elixir du Taureau", 3, -1, 1));
	items.push_back(new Item(surface, 56, "Elixir de la Balance", 3, -1, 1));
	items.push_back(new Item(surface, 57, "Elixir du Belier", 3, -1, 1));
	items.push_back(new Item(surface, 58, "Elixir du Scorpion", 3, -1, 1));
	items.push_back(new Item(surface, 59, "Elixir du Cancer", 3, -1, 1));
	items.push_back(new Item(surface, 60, "Elixir du Verseau", 3, -1, 1));
	items.push_back(new Item(surface, 61, "Elixir des Gemeaux", 3, -1, 1));
	items.push_back(new Item(surface, 62, "Elixir du Poisson", 3, -1, 1));
	items.push_back(new Item(surface, 63, "Elixir de la Vierge", 3, -1, 1));
	items.push_back(new Item(surface, 64, "Arc-en-miel", 2, -1, -1));
	items.push_back(new Item(surface, 65, "Bouee canard", 2, -1, -1));
	items.push_back(new Item(surface, 66, "Branche de Kipik", 3, -1, -1));
	items.push_back(new Item(surface, 67, "Anneau de Guillaume Tell", 2, -1, -1));
	items.push_back(new Item(surface, 68, "Bougie", 2, -1, -1));
	items.push_back(new Item(surface, 69, "Koulraoule des iles", 2, -1, -1));
	items.push_back(new Item(surface, 70, "Trefle commun", 1, -1, -1));
	items.push_back(new Item(surface, 71, "Chaud devant !", 1, -1, -1));
	items.push_back(new Item(surface, 72, "Chapeau de Mage-Gris", 3, -1, -1));
	items.push_back(new Item(surface, 73, "Feuille de sinopee", 2, -1, -1));
	items.push_back(new Item(surface, 74, "Esprit de l\'orange", 1, -1, -1));
	items.push_back(new Item(surface, 75, "Esprit de la pluie", 2, -1, -1));
	items.push_back(new Item(surface, 76, "Esprit des arbres", 3, -1, -1));
	items.push_back(new Item(surface, 77, "Lucidjane a crete bleue", 2, -1, -1));
	items.push_back(new Item(surface, 78, "Filandreux rougeoyant", 2, -1, -1));
	items.push_back(new Item(surface, 79, "Poisson empereur", 3, -1, -1));
	items.push_back(new Item(surface, 80, "Escargot Poussepa", 1, -1, -1));
	items.push_back(new Item(surface, 81, "Perle nacree des murlocs", 2, -1, -1));
	items.push_back(new Item(surface, 82, "Jugement avant-dernier", 2, -1, -1));
	items.push_back(new Item(surface, 83, "Jugement dernier", 3, -1, -1));
	items.push_back(new Item(surface, 84, "Talisman scorpide", 3, -1, -1));
	items.push_back(new Item(surface, 85, "Baton tonnerre", 3, -1, -1));
	items.push_back(new Item(surface, 86, "Surprise de paille", 4, -1, -1));
	items.push_back(new Item(surface, 87, "Larve d\'oenopterius", 1, -1, -1));
	items.push_back(new Item(surface, 88, "Pokute", 3, -1, -1));
	items.push_back(new Item(surface, 89, "Oeuf de Tzongre", 3, -1, -1));
	items.push_back(new Item(surface, 90, "Fulguro pieds-en-mousse", 3, -1, -1));
	items.push_back(new Item(surface, 91, "Couvre-chef de Luffy", 3, -1, -1));
	items.push_back(new Item(surface, 92, "Chapeau violin", 4, -1, -1));
	items.push_back(new Item(surface, 93, "Boit\'a\'messages", 3, -1, -1));
	items.push_back(new Item(surface, 94, "Anneau Antok", 3, -1, -1));
	items.push_back(new Item(surface, 95, "Cagnotte de Tuberculoz", 5, -1, -1));
	items.push_back(new Item(surface, 96, "Perle flamboyante", 4, -1, -1));
	items.push_back(new Item(surface, 97, "Perle vertillante", 5, -1, -1));
	items.push_back(new Item(surface, 98, "Grosse pe-perle ", 6, -1, -1));
	items.push_back(new Item(surface, 99, "Poils de Chourou", 5, -1, -1));
	items.push_back(new Item(surface, 100, "Pocket-Guu", 4, -1, -1));
	items.push_back(new Item(surface, 101, "Colis surprise", 0, -1, -1));
	items.push_back(new Item(surface, 102, "La Carotte d\'Igor", 0, -1, 1));
	items.push_back(new Item(surface, 103, "Vie palpitante", 1, -1, 1));
	items.push_back(new Item(surface, 104, "Vie aventureuse", 1, -1, 1));
	items.push_back(new Item(surface, 105, "Vie epique", 3, -1, 1));
	items.push_back(new Item(surface, 106, "Livre des champignons", 5, -1, -1));
	items.push_back(new Item(surface, 107, "Livre des etoiles", 5, -1, -1));
	items.push_back(new Item(surface, 108, "Parapluie Frutiparc", 2, -1, -1));
	items.push_back(new Item(surface, 109, "Flocon simple", 3, -1, 1));
	items.push_back(new Item(surface, 110, "Flocon bizarre", 4, -1, 1));
	items.push_back(new Item(surface, 111, "Flocon ENORME !", 5, -1, 1));
	items.push_back(new Item(surface, 112, "Pioupiou carnivore", 6, -1, 1));
	items.push_back(new Item(surface, 113, "Cape de Tuberculoz", 0, -1, -1));
	items.push_back(new Item(surface, 114, "Mode Mario", 4, -1, -1));
	items.push_back(new Item(surface, 115, "Casque de Volleyfest", 0, -1, -1));
	items.push_back(new Item(surface, 116, "Joyau d\'Ankhel", 0, -1, -1));
	items.push_back(new Item(surface, 117, "Cle de Gordon", 0, -1, -1));
	items.push_back(new Item(surface, 118, "Cristaux d\'Hammerfest", 0, -2, -1));
	items.push_back(new Item(surface, 119, "Pain a la viande", 1, 1000, -1));
	items.push_back(new Item(surface, 120, "Canne de Bobble", 7, 100000, -1));
	items.push_back(new Item(surface, 121, "Bonbon Berlinmauve", 1, 500, -1));
	items.push_back(new Item(surface, 122, "Bonbon Chamagros", 1, 1000, -1));
	items.push_back(new Item(surface, 123, "Bonbon rosamelle-praline", 2, 2500, -1));
	items.push_back(new Item(surface, 124, "Sucette aux fruits bleus", 2, 5000, -1));
	items.push_back(new Item(surface, 125, "Sucette chlorophylle", 3, 15000, -1));
	items.push_back(new Item(surface, 126, "Diamant Oune-difained", 0, -2, -1));
	items.push_back(new Item(surface, 127, "Oeil de tigre", 1, 5000, -1));
	items.push_back(new Item(surface, 128, "Jade de 12kg", 2, 15000, -1));
	items.push_back(new Item(surface, 129, "Reflet-de-lune", 3, 25000, -1));
	items.push_back(new Item(surface, 130, "Surprise de Cerises", 1, 800, -1));
	items.push_back(new Item(surface, 131, "Muffin aux cailloux", 1, 300, -1));
	items.push_back(new Item(surface, 132, "Gelee des bois", 1, 1700, -1));
	items.push_back(new Item(surface, 133, "Supreme aux framboises", 3, 12000, -1));
	items.push_back(new Item(surface, 134, "Petit petillant", 3, 8000, -1));
	items.push_back(new Item(surface, 135, "Pierres du Changement", 0, -2, -1));
	items.push_back(new Item(surface, 136, "Glace Fraise", 2, 1200, -1));
	items.push_back(new Item(surface, 137, "Coupe Glacee", 2, 3500, -1));
	items.push_back(new Item(surface, 138, "Noodles", 2, 5600, -1));
	items.push_back(new Item(surface, 139, "Poulet Surgele", 1, 10, -1));
	items.push_back(new Item(surface, 140, "Liquide bizarre", 3, 10000, -1));
	items.push_back(new Item(surface, 141, "Gros acidule", 2, 5000, -1));
	items.push_back(new Item(surface, 142, "Liquide etrange", 3, 20000, -1));
	items.push_back(new Item(surface, 143, "Oeuf cru", 1, 500, -1));
	items.push_back(new Item(surface, 144, "Gland gnan-gnan", 1, 1300, -1));
	items.push_back(new Item(surface, 145, "Reglisse rouge", 1, 600, -1));
	items.push_back(new Item(surface, 146, "Oeuf Au Plat", 1, 1000, -1));
	items.push_back(new Item(surface, 147, "Saucisse piquee", 1, 300, -1));
	items.push_back(new Item(surface, 148, "Cerise-apero confite", 1, 400, -1));
	items.push_back(new Item(surface, 149, "Fromage pique", 1, 600, -1));
	items.push_back(new Item(surface, 150, "Olive pas mure", 1, 1000, -1));
	items.push_back(new Item(surface, 151, "Olive noire", 2, 1500, -1));
	items.push_back(new Item(surface, 152, "Oeil de pomme", 2, 2000, -1));
	items.push_back(new Item(surface, 153, "Blob intrusif", 2, 2500, -1));
	items.push_back(new Item(surface, 154, "Gouda mou", 3, 5000, -1));
	items.push_back(new Item(surface, 155, "Poulpi empale", 3, 10000, -1));
	items.push_back(new Item(surface, 156, "Olive oubliee", 4, 50000, -1));
	items.push_back(new Item(surface, 157, "Monsieur radis", 4, 50000, -1));
	items.push_back(new Item(surface, 158, "Sushi thon", 3, 9000, -1));
	items.push_back(new Item(surface, 159, "Sucette acidulee", 1, 750, -1));
	items.push_back(new Item(surface, 160, "Delice d\'Arale", 5, 1, -1));
	items.push_back(new Item(surface, 161, "Sorbet au plastique", 1, 900, -1));
	items.push_back(new Item(surface, 162, "Manda", 5, 60000, -1));
	items.push_back(new Item(surface, 163, "Petale mysterieuse", 2, 3000, -1));
	items.push_back(new Item(surface, 164, "Gump", 4, 35000, -1));
	items.push_back(new Item(surface, 165, "Bleuet", 0, 5, -1));
	items.push_back(new Item(surface, 166, "Rougeoyant", 0, 10, -1));
	items.push_back(new Item(surface, 167, "Verdifiant", 0, 15, -1));
	items.push_back(new Item(surface, 168, "KassDent", 0, 25, -1));
	items.push_back(new Item(surface, 169, "Piece d\'or secrete", 0, 2500, -1));
	items.push_back(new Item(surface, 170, "Sou d\'argent", 1, 5000, -1));
	items.push_back(new Item(surface, 171, "Sou d\'or", 3, 25000, -1));
	items.push_back(new Item(surface, 172, "Gros tas de sous", 4, 75000, -1));
	items.push_back(new Item(surface, 173, "Boisson kipik", 1, 1200, -1));
	items.push_back(new Item(surface, 174, "Doigts-de-tuberculoz", 1, 900, -1));
	items.push_back(new Item(surface, 175, "Pizza de Donatello", 1, 1400, -1));
	items.push_back(new Item(surface, 176, "Canele du sud-ouest", 3, 15500, -1));
	items.push_back(new Item(surface, 177, "Eclair noisette choco caramel et sucre", 3, 18500, -1));
	items.push_back(new Item(surface, 178, "Bleuette rouge", 3, 10000, -1));
	items.push_back(new Item(surface, 179, "Perroquet decapite en sauce", 4, 45000, -1));
	items.push_back(new Item(surface, 180, "Morvo-morphe", 4, 70000, -1));
	items.push_back(new Item(surface, 181, "Fraise Tagada", 1, 1000, -1));
	items.push_back(new Item(surface, 182, "Car-En-Sac", 1, 1400, -1));
	items.push_back(new Item(surface, 183, "Dragibus", 1, 1600, -1));
	items.push_back(new Item(surface, 184, "Krokodile", 2, 12250, -1));
	items.push_back(new Item(surface, 185, "Demi Cocobats", 1, 1800, -1));
	items.push_back(new Item(surface, 186, "Happy Cola", 1, 1750, -1));
	items.push_back(new Item(surface, 187, "Cacahuete secrete", 2, 50, -1));
	items.push_back(new Item(surface, 188, "P\'tit fantome", 2, 2500, -1));
	items.push_back(new Item(surface, 189, "Cookie deshydrate", 2, 1800, -1));
	items.push_back(new Item(surface, 190, "Arbuche de noel", 3, 8000, -1));
	items.push_back(new Item(surface, 191, "Piment farceur", 4, 12000, -1));
	items.push_back(new Item(surface, 192, "Soja Max IceCream", 2, 2250, -1));
	items.push_back(new Item(surface, 193, "Bouquet de steack", 4, 7777, -1));
	items.push_back(new Item(surface, 194, "Daruma-Pasteque", 5, 60000, -1));
	items.push_back(new Item(surface, 195, "Graine de tournesol", 3, 5, -1));
	items.push_back(new Item(surface, 196, "Croissant confit", 5, 1500, -1));
	items.push_back(new Item(surface, 197, "Haricot paresseux", 1, 800, -1));
	items.push_back(new Item(surface, 198, "Lapin-choco", 3, 1200, -1));
	items.push_back(new Item(surface, 199, "Biloo", 1, 900, -1));
	items.push_back(new Item(surface, 200, "Graine de pechume en gelee", 2, 3000, -1));
	items.push_back(new Item(surface, 201, "Sombrino aux amandes", 3, 1650, -1));
	items.push_back(new Item(surface, 202, "Emi-Praline", 3, 1500, -1));
	items.push_back(new Item(surface, 203, "Frogmaliet aux pepites de chocolat", 3, 1600, -1));
	items.push_back(new Item(surface, 204, "Yumi au cafe", 3, 1800, -1));
	items.push_back(new Item(surface, 205, "Bouchee mielleuse nappee au gel de Vodka", 3, 1700, -1));
	items.push_back(new Item(surface, 206, "Escargot au chocolat persille", 3, 1750, -1));
	items.push_back(new Item(surface, 207, "Fossile de cacao marbre au fois gras", 3, 1550, -1));
	items.push_back(new Item(surface, 208, "Cerisot marine a la biere", 3, 3000, -1));
	items.push_back(new Item(surface, 209, "Jambon de Bayonne", 2, 12000, -1));
	items.push_back(new Item(surface, 210, "Saucisson entame", 2, 6000, -1));
	items.push_back(new Item(surface, 211, "Raide red reste", 1, 800, -1));
	items.push_back(new Item(surface, 212, "Torchon madrangeais au sirop d\'erable", 1, 500, -1));
	items.push_back(new Item(surface, 213, "Saucisson de marcassin sauvage", 2, 4000, -1));
	items.push_back(new Item(surface, 214, "Tranches de Jaret de Kangourou", 1, 1200, -1));
	items.push_back(new Item(surface, 215, "Saucissaille de St-Morgelet", 1, 1600, -1));
	items.push_back(new Item(surface, 216, "Pate d\'ongles au truffes", 3, 400, -1));
	items.push_back(new Item(surface, 217, "Saucisson maudit scelle", 4, 16000, -1));
	items.push_back(new Item(surface, 218, "Manquereau-sauce-au-citron", 4, 2500, -1));
	items.push_back(new Item(surface, 219, "Mini-saucisses en boite", 2, 575, -1));
	items.push_back(new Item(surface, 220, "Haricots blanc", 2, 575, -1));
	items.push_back(new Item(surface, 221, "Lychees premier prix", 2, 575, -1));
	items.push_back(new Item(surface, 222, "Zion\'s Calamar", 1, 175, -1));
	items.push_back(new Item(surface, 223, "Aubergines au sirop", 1, 175, -1));
	items.push_back(new Item(surface, 224, "Camembert", 1, 25, -1));
	items.push_back(new Item(surface, 225, "Emmental", 1, 75, -1));
	items.push_back(new Item(surface, 226, "Fromage verni", 2, 225, -1));
	items.push_back(new Item(surface, 227, "Roquefort", 2, 250, -1));
	items.push_back(new Item(surface, 228, "Fromage frais vigne", 2, 400, -1));
	items.push_back(new Item(surface, 229, "Pâte dessert fromagee", 2, 325, -1));
	items.push_back(new Item(surface, 230, "Saladou", 2, 700, -1));
	items.push_back(new Item(surface, 231, "Poire d\'eau", 2, 800, -1));
	items.push_back(new Item(surface, 232, "Cacahuete mauve et juteuse", 4, 3700, -1));
	items.push_back(new Item(surface, 233, "Pommes de pierre", 2, 200, -1));
	items.push_back(new Item(surface, 234, "Patates douces", 2, 400, -1));
	items.push_back(new Item(surface, 235, "Matraque bio", 3, 700, -1));
	items.push_back(new Item(surface, 236, "Tomate pacifique", 1, 500, -1));
	items.push_back(new Item(surface, 237, "Radix", 1, 600, -1));
	items.push_back(new Item(surface, 238, "Haricots verts", 3, 15, -1));
	items.push_back(new Item(surface, 239, "Pomme Sapik", 3, 5500, -1));
	items.push_back(new Item(surface, 240, "Pomme Sapu", 4, 28000, -1));
	items.push_back(new Item(surface, 241, "Echalottes", 5, 70000, -1));
	items.push_back(new Item(surface, 242, "Sel rieur", 3, 2600, -1));
	items.push_back(new Item(surface, 243, "Poivron vert", 3, 3500, -1));
	items.push_back(new Item(surface, 244, "Poivron jaune", 4, 15000, -1));
	items.push_back(new Item(surface, 245, "Poivron rouge", 1, 700, -1));
	items.push_back(new Item(surface, 246, "Brocolis digeres", 3, 3, -1));
	items.push_back(new Item(surface, 247, "Grappe de Radix", 3, 6000, -1));
	items.push_back(new Item(surface, 248, "Lance-poix", 3, 7000, -1));
	items.push_back(new Item(surface, 249, "Haricots blancs", 5, 35000, -1));
	items.push_back(new Item(surface, 250, "Poires d\'eau en grappe", 4, 9000, -1));
	items.push_back(new Item(surface, 251, "Artifroid", 3, 700, -1));
	items.push_back(new Item(surface, 252, "Choux-flou", 5, 90000, -1));
	items.push_back(new Item(surface, 253, "Chourou", 3, 1400, -1));
	items.push_back(new Item(surface, 254, "Pom pom pom..", 1, 350, -1));
	items.push_back(new Item(surface, 255, "Hollandais", 2, 1250, -1));
	items.push_back(new Item(surface, 256, "Fondant XXL au choco-beurre", 2, 1250, -1));
	items.push_back(new Item(surface, 257, "Petillante", 3, 2500, -1));
	items.push_back(new Item(surface, 258, "Warpoquiche", 2, 1250, -1));
	items.push_back(new Item(surface, 259, "Brioche doree", 6, 150000, -1));
	items.push_back(new Item(surface, 260, "Cafe de fin de projet", 1, 600, -1));
	items.push_back(new Item(surface, 261, "Laxatif aux amandes", 5, 150000, -1));
	items.push_back(new Item(surface, 262, "Smiley croquant", 2, 900, -1));
	items.push_back(new Item(surface, 263, "Barquette de lave", 1, 400, -1));
	items.push_back(new Item(surface, 264, "Nonoix", 3, 3000, -1));
	items.push_back(new Item(surface, 265, "Amande croquante", 3, 3000, -1));
	items.push_back(new Item(surface, 266, "Noisette", 3, 3000, -1));
	items.push_back(new Item(surface, 267, "Noodles crus", 1, 550, -1));
	items.push_back(new Item(surface, 268, "Brioche vapeur", 4, 21000, -1));
	items.push_back(new Item(surface, 269, "Tartine chocolat-noisette", 1, 650, -1));
	items.push_back(new Item(surface, 270, "Tartine hemoglobine", 2, 1650, -1));
	items.push_back(new Item(surface, 271, "Tartine a l\'orange collante", 3, 5800, -1));
	items.push_back(new Item(surface, 272, "Tartine au miel", 2, 1650, -1));
	items.push_back(new Item(surface, 273, "Lombric nature", 4, 15, -1));
	items.push_back(new Item(surface, 274, "Grenade de chantilly", 2, 5000, -1));
	items.push_back(new Item(surface, 275, "Profies tres drôles", 4, 35000, -1));
	items.push_back(new Item(surface, 276, "Chouchocos", 4, 35000, -1));
	items.push_back(new Item(surface, 277, "Blob perime", 6, 250000, -1));
	items.push_back(new Item(surface, 278, "Bonbon Helene-fraiche", 3, 200, -1));
	items.push_back(new Item(surface, 279, "Nem aux anchois", 3, 9000, -1));
	items.push_back(new Item(surface, 280, "Surimi pamplemousse", 2, 150, -1));
	items.push_back(new Item(surface, 281, "Poulpi a l\'encre", 5, 80000, -1));
	items.push_back(new Item(surface, 282, "Curly", 5, 70000, -1));
	items.push_back(new Item(surface, 283, "Tartelette framboise", 1, 2500, -1));
	items.push_back(new Item(surface, 284, "Oeuf de Poire", 6, 57000, -1));
	items.push_back(new Item(surface, 285, "Truffe collante sans gout", 6, 300000, -1));
	items.push_back(new Item(surface, 286, "Sardines", 3, 6000, -1));
	items.push_back(new Item(surface, 287, "Etoile Toulaho", 0, 1500, -1));
	items.push_back(new Item(surface, 288, "Transformer en sucre", 3, 25000, -1));
	items.push_back(new Item(surface, 289, "Kitchissime", 3, 25000, -1));
	items.push_back(new Item(surface, 290, "Igorocop", 3, 25000, -1));
	items.push_back(new Item(surface, 291, "Tidouli didi", 3, 25000, -1));
	items.push_back(new Item(surface, 292, "Dalek ! Exterminate !", 3, 35000, -1));
	items.push_back(new Item(surface, 293, "Robo-malin", 3, 25000, -1));
	items.push_back(new Item(surface, 294, "Johnny 6", 3, 25000, -1));
	items.push_back(new Item(surface, 295, "Biscuit Transformer", 4, 50000, -1));
	items.push_back(new Item(surface, 296, "Statue: Citron Sorbex", 0, 1000, -1));
	items.push_back(new Item(surface, 297, "Statue: Bombino", 0, 4000, -1));
	items.push_back(new Item(surface, 298, "Statue: Poire Melbombe", 0, 8000, -1));
	items.push_back(new Item(surface, 299, "Statue: Tagada", 0, 10000, -1));
	items.push_back(new Item(surface, 300, "Statue: Sapeur-kiwi", 0, 15000, -1));
	items.push_back(new Item(surface, 301, "Statue: Bondissante", 0, 20000, -1));
	items.push_back(new Item(surface, 302, "Statue: Ananargeddon", 0, 25000, -1));
	items.push_back(new Item(surface, 303, "Anneau herisse", 0, 250, -1));
	items.push_back(new Item(surface, 304, "Passe-partout en bois", 6, 10000, -1));
	items.push_back(new Item(surface, 305, "Cle de Rigor Dangerous", 6, 10000, -1));
	items.push_back(new Item(surface, 306, "Meluzzine", 5, 10000, -1));
	items.push_back(new Item(surface, 307, "Cle du Bourru", 1, 10000, 1));
	items.push_back(new Item(surface, 308, "Furtok Glaciale", 6, 10000, -1));
	items.push_back(new Item(surface, 309, "Vieille cle rouillee", 4, 10000, -1));
	items.push_back(new Item(surface, 310, "Autorisation du Bois-Joli", 1, 10000, 1));
	items.push_back(new Item(surface, 311, "Cle des Mondes Ardus", 6, 10000, -1));
	items.push_back(new Item(surface, 312, "Cle piquante", 6, 10000, -1));
	items.push_back(new Item(surface, 313, "Passe-partout de Tuberculoz", 6, 10000, -1));
	items.push_back(new Item(surface, 314, "Cle des cauchemars", 6, 10000, -1));
	items.push_back(new Item(surface, 315, "Pad Sounie", 6, 17000, -1));
	items.push_back(new Item(surface, 316, "Pad Frusion 64", 6, 100000, -1));
	items.push_back(new Item(surface, 317, "Pad Game-Pyramid", 6, 17000, -1));
	items.push_back(new Item(surface, 318, "Pad Sey-Ga", 6, 17000, -1));
	items.push_back(new Item(surface, 319, "Pad Super Frusion", 6, 17000, -1));
	items.push_back(new Item(surface, 320, "Pad du Systeme Maitre", 6, 17000, -1));
	items.push_back(new Item(surface, 321, "Pad Frusion Entertainment System", 6, 17000, -1));
	items.push_back(new Item(surface, 322, "Manette S-Tehef", 6, 20000, -1));
	items.push_back(new Item(surface, 323, "Canette Express", 1, 500, -1));
	items.push_back(new Item(surface, 324, "Bouteille aux 2064 bulles", 2, 1200, -1));
	items.push_back(new Item(surface, 325, "Mousse volante", 3, 3000, -1));
	items.push_back(new Item(surface, 326, "Vin Merveilleux", 4, 20000, -1));
	items.push_back(new Item(surface, 327, "Liqueur malefique", 5, 100000, -1));
	items.push_back(new Item(surface, 328, "Tampon MT", 1, 2000, -1));
	items.push_back(new Item(surface, 329, "Facture gratuite", 2, 10, -1));
	items.push_back(new Item(surface, 330, "Post-It de Francois", 3, 3000, -1));
	items.push_back(new Item(surface, 331, "Pot a crayon solitaire", 4, 5500, -1));
	items.push_back(new Item(surface, 332, "Agrafeuse du Chaos", 5, 100000, -1));
	items.push_back(new Item(surface, 333, "Miroir bancal", 0, 69, -1));
	items.push_back(new Item(surface, 334, "Etoile du Diable", 0, 666, -1));
	items.push_back(new Item(surface, 335, "Poudre de plage magique", 1, 700, 5));
	items.push_back(new Item(surface, 336, "Materiel d\'architecte", 1, 600, 10));
	items.push_back(new Item(surface, 337, "Maquette en sable", 2, 1200, 5));
	items.push_back(new Item(surface, 338, "Winkel", 2, 900, 3));
	items.push_back(new Item(surface, 339, "Miroir des Sables", 0, 69, -1));
	items.push_back(new Item(surface, 340, "Etoile des Diables Jumeaux", 0, 666, -1));
	items.push_back(new Item(surface, 341, "Sceau d\'amitie", 0, 100, -1));
	items.push_back(new Item(surface, 342, "Insigne de l\'ordre des Ninjas", 0, 900, -1));
	items.push_back(new Item(surface, 343, "Couteau suisse japonais", 2, 1200, -1));
	items.push_back(new Item(surface, 344, "Shuriken de second rang", 3, 1600, -1));
	items.push_back(new Item(surface, 345, "Shuriken d\'entrainement", 1, 250, -1));
	items.push_back(new Item(surface, 346, "Najinata", 2, 600, -1));
	items.push_back(new Item(surface, 347, "Lance-boulettes de Precision", 4, 5000, -1));
	items.push_back(new Item(surface, 348, "Ocarina chantant", 4, 6500, -1));
	items.push_back(new Item(surface, 349, "Armure de la nuit", 4, 10000, -1));
	items.push_back(new Item(surface, 350, "Insigne du Merite", 0, 10000, -1));
	items.push_back(new Item(surface, 351, "Neige-o-glycerine", 0, 150000, -1));
	items.push_back(new Item(surface, 352, "Pass-Pyramide", 0, 30000, -1));

//	for (unsigned int i = 0; i < items.size(); i++) {
//		items[i]->printName();
//	}

	Quest * quest = new Quest(0, true, false, false, false, -1, -1, -1, -1, 5, "Les constellations",
			"Igor peut maintenant poser 2 bombes au lieu d\'une seule a la fois, et ce, de maniere permanente !");
	quest->addRequireItemId(40, 1);
	quest->addRequireItemId(41, 1);
	quest->addRequireItemId(42, 1);
	quest->addRequireItemId(43, 1);
	quest->addRequireItemId(44, 1);
	quest->addRequireItemId(45, 1);
	quest->addRequireItemId(46, 1);
	quest->addRequireItemId(47, 1);
	quest->addRequireItemId(48, 1);
	quest->addRequireItemId(49, 1);
	quest->addRequireItemId(50, 1);
	quest->addRequireItemId(51, 1);
	quest->addGiveFamilly(6);
	quests.push_back(quest);

	quest = new Quest(1, false, true, false, false, -1, -1, -1, -1, 6, "Mixtures du zodiaque",
			"Igor sait desormais envoyer ses bombes a l\'etage superieur ! Maintenez BAS enfonce pendant que vous tapez dans une bombe posee.");
	quest->addRequireItemId(53, 1);
	quest->addRequireItemId(54, 1);
	quest->addRequireItemId(55, 1);
	quest->addRequireItemId(56, 1);
	quest->addRequireItemId(57, 1);
	quest->addRequireItemId(58, 1);
	quest->addRequireItemId(59, 1);
	quest->addRequireItemId(60, 1);
	quest->addRequireItemId(61, 1);
	quest->addRequireItemId(62, 1);
	quest->addRequireItemId(63, 1);
	quests.push_back(quest);

	quest = new Quest(2, false, false, true, false, -1, -1, -1, -1, 7, "Premiers pas", "Igor debutera desormais la partie avec une vie supplementaire.");
	quest->addRequireItemId(103, 1);
	quests.push_back(quest);

	quest = new Quest(3, false, false, true, false, -1, -1, -1, -1, 8, "L\'aventure commence", "Igor debutera desormais la partie avec une autre vie supplementaire.");
	quest->addRequireItemId(104, 1);
	quest->addGiveFamilly(9);
	quests.push_back(quest);

	quest = new Quest(4, false, false, true, false, -1, -1, -1, -1, 9, "Une destinee epique", "Igor debutera desormais la partie avec encore une vie supplementaire !");
	quest->addRequireItemId(105, 1);
	quests.push_back(quest);

	quest = new Quest(5, false, false, true, false, -1, -1, -1, -1, -1, "Perseverance", "Igor debutera desormais la partie avec une vie supplementaire.");
	quest->addRequireItemId(36, 5);
	quests.push_back(quest);

	quest = new Quest(6, false, false, false, false, -1, -1, -1, -1, -1, "Gourmandise", "De nouveaux aliments (plus sains) apparaitront desormais en jeu !");
	quest->addRequireItemId(118, 5);
	quest->addRequireItemId(121, 1);
	quest->addRequireItemId(131, 1);
	quest->addRequireItemId(145, 1);
	quest->addRequireItemId(159, 1);
	quest->addRequireItemId(161, 1);
	quest->addGiveFamilly(21);
	quests.push_back(quest);

	quest = new Quest(7, false, false, false, false, -1, -1, -1, -1, -1, "Du sucre !", "Igor veut encore plus de sucre ! Des delicieuses friandises apparaitront desormais en jeu.");
	quest->addRequireItemId(121, 10);
	quest->addRequireItemId(145, 10);
	quest->addRequireItemId(159, 10);
	quest->addRequireItemId(188, 2);
	quest->addRequireItemId(192, 2);
	quest->addGiveFamilly(22);
	quests.push_back(quest);

	quest = new Quest(8, false, false, false, false, -1, -1, -1, -1, -1, "Malnutrition",
			"Le gout d\'Igor pour les aliments peu equilibres lui permettra de trouver des aliments encore plus... \"douteux\" en jeu.");
	quest->addRequireItemId(140, 5);
	quest->addRequireItemId(142, 5);
	quest->addRequireItemId(146, 20);
	quest->addRequireItemId(143, 10);
	quest->addGiveFamilly(24);
	quests.push_back(quest);

	quest = new Quest(9, false, false, false, false, -1, -1, -1, -1, -1, "Gout raffine", "Le regime bizarre d\'Igor a amene de nouveaux aliments exotiques en jeu !");
	quest->addRequireItemId(120, 1);
	quest->addRequireItemId(164, 2);
	quest->addRequireItemId(158, 10);
	quest->addGiveFamilly(25);
	quests.push_back(quest);

	quest = new Quest(10, false, false, false, false, -1, -1, -1, -1, -1, "Avancee technologique",
			"Pour vous aider dans votre aventure, tout un tas d\'objets aux effets bizarres font leur apparition en jeu !");
	quest->addRequireItemId(4, 1);
	quest->addRequireItemId(7, 1);
	quest->addRequireItemId(13, 1);
	quest->addGiveFamilly(1);
	quest->addGiveFamilly(8);
	quest->addGiveFamilly(13);
	quest->addGiveFamilly(15);
	quests.push_back(quest);

	quest = new Quest(11, false, false, false, false, -1, -1, -1, -1, -1, "Le petit guide des Champignons",
			"Igor a decouvert un etrange ouvrage, une sorte de livre de cuisine traitant des champignons hallucinogenes. Il pourra desormais en trouver lors de ses explorations.");
	quest->addRequireItemId(106, 1);
	quest->addGiveFamilly(3);
	quests.push_back(quest);

	quest = new Quest(12, false, false, false, false, -1, -1, -1, -1, -1, "Trouver les pieces d\'or secretes !",
			"Des richesses supplementaires de tres grande valeur apparaitront maintenant en jeu !");
	quest->addRequireItemId(169, 150);
	quest->addGiveFamilly(27);
	quests.push_back(quest);

	quest = new Quest(13, false, false, false, false, -1, -1, -1, -1, -1, "Le grimoire des Etoiles",
			"Cet ouvrage mysterieux en dit long sur les 12 constellations du Zodiaque. Vous pourrez desormais les collectionner en jeu !");
	quest->addRequireItemId(107, 1);
	quest->addGiveFamilly(5);
	quests.push_back(quest);

	quest = new Quest(14, false, false, false, false, -1, -1, -1, -1, -1, "Armageddon", "Des objets aux effets ravageurs vont maintenant apparaitre en jeu !");
	quest->addRequireItemId(1, 10);
	quest->addRequireItemId(5, 5);
	quest->addRequireItemId(11, 5);
	quest->addRequireItemId(21, 10);
	quest->addRequireItemId(22, 5);
	quest->addRequireItemId(24, 1);
	quest->addRequireItemId(25, 1);
	quest->addRequireItemId(28, 3);
	quest->addRequireItemId(38, 1);
	quest->addRequireItemId(82, 5);
	quest->addGiveFamilly(2);
	quests.push_back(quest);

	quest =
			new Quest(15, false, false, false, false, -1, -1, -1, -1, -1, "Regime MotionTwin",
					"A force de manger n\'importe quoi, Igor a acquis la maitrise des jeux ! Il pourra collectionner des objets rarissimes pendant son exploration et trouver des aliments d\'exception !");
	quest->addRequireItemId(175, 11);
	quest->addRequireItemId(192, 11);
	quest->addRequireItemId(255, 11);
	quest->addRequireItemId(256, 11);
	quest->addRequireItemId(257, 11);
	quest->addRequireItemId(258, 11);
	quest->addRequireItemId(267, 20);
	quest->addRequireItemId(163, 30);
	quest->addRequireItemId(199, 11);
	quest->addGiveFamilly(11);
	quest->addGiveFamilly(34);
	quests.push_back(quest);

	quest =
			new Quest(16, false, false, false, false, -1, -1, -1, -1, -1, "Createur de jeu en devenir",
					"Igor semble apprecier les aliments basiques, une belle carriere dans le monde du jeu video pourrait s\'offrir a lui ! Des aliments adaptes lui seront dorenavant proposes et quelques cartes a jouer pour se faire la main.");
	quest->addRequireItemId(260, 20);
	quest->addGiveFamilly(4);
	quest->addGiveFamilly(35);
	quests.push_back(quest);

	quest = new Quest(17, false, false, false, false, -1, -1, -1, -1, -1, "La vie est une boite de chocolats", "De delicieux chocolats sont maintenant distribues en Hammerfest !");
	quest->addRequireItemId(164, 5);
	quest->addGiveFamilly(30);
	quests.push_back(quest);

	quest = new Quest(18, false, false, false, false, -1, -1, -1, -1, -1, "Le tresor Oune-difained",
			"A force de ramasser des diamants apparus on ne sait comment, Igor a acquis la faculte de reperer des pierres precieuses rares ! Il en trouvera au cours de ses explorations.");
	quest->addRequireItemId(126, 30);
	quest->addGiveFamilly(23);
	quests.push_back(quest);

	quest = new Quest(19, false, false, false, false, -1, -1, -1, -1, -1, "Super size me !",
			"Toujours plus loin dans la malnutrition, Igor a decouvert qu\'il pouvait aussi se nourrir de produits en boite.");
	quest->addRequireItemId(119, 20);
	quest->addRequireItemId(173, 20);
	quest->addRequireItemId(174, 20);
	quest->addGiveFamilly(32);
	quests.push_back(quest);

	quest = new Quest(20, false, false, false, false, -1, -1, -1, -1, -1, "Maitre joaillier",
			"Igor est devenu un veritable expert en pierres precieuses. Il pourra maintenant decouvrir de puissants bijoux magiques au fil de ses explorations !");
	quest->addRequireItemId(127, 10);
	quest->addRequireItemId(128, 5);
	quest->addRequireItemId(129, 1);
	quest->addGiveFamilly(10);
	quest->addGiveFamilly(12);
	quests.push_back(quest);

	quest = new Quest(21, false, false, false, false, -1, -1, -1, -1, -1, "Grand predateur",
			"Igor en a plus qu\'assez de chasser des choses sucrees ! Desormais devenu un predateur sans pitie, il pourra traquer et devorer toute sorte de charcuteries.");
	quest->addRequireItemId(119, 20);
	quest->addRequireItemId(139, 10);
	quest->addRequireItemId(143, 20);
	quest->addRequireItemId(179, 1);
	quest->addRequireItemId(280, 10);
	quest->addGiveFamilly(28);
	quests.push_back(quest);

	quest =
			new Quest(22, false, false, false, false, -1, -1, -1, -1, -1, "Expert en salades et potages",
					"On raconte partout qu\'Igor serait la reincarnation de Saladou, le maitre mondialement reconnu de la salade. Fort de ce don, il pourra a l\'avenir cueillir une tres grande variete de legumes !");
	quest->addRequireItemId(138, 15);
	quest->addRequireItemId(157, 1);
	quest->addRequireItemId(178, 2);
	quest->addRequireItemId(222, 5);
	quest->addRequireItemId(221, 3);
	quest->addGiveFamilly(33);
	quests.push_back(quest);

	quest = new Quest(23, false, false, false, false, -1, -1, -1, -1, -1, "Festin d\'Hammerfest",
			"Avec un repas aussi complet, Igor est fin pret pour avoir acces aux patisseries les plus raffinees qui existent.");
	quest->addRequireItemId(209, 1);
	quest->addRequireItemId(230, 1);
	quest->addRequireItemId(244, 1);
	quest->addRequireItemId(281, 1);
	quest->addRequireItemId(227, 1);
	quest->addRequireItemId(256, 1);
	quest->addRequireItemId(260, 1);
	quest->addGiveFamilly(37);
	quests.push_back(quest);

	quest = new Quest(24, false, false, false, false, -1, -1, -1, -1, -1, "Gouter d\'anniversaire",
			"Igor a trouve tous les elements pour assurer a son prochain gouter d\'anniversaire ! Il trouvera maintenant pleins de petits en-cas pour patienter jusque la.");
	quest->addRequireItemId(68, 1);
	quest->addRequireItemId(122, 10);
	quest->addRequireItemId(123, 10);
	quest->addRequireItemId(125, 1);
	quest->addRequireItemId(133, 1);
	quest->addRequireItemId(134, 3);
	quest->addRequireItemId(136, 5);
	quest->addRequireItemId(137, 5);
	quest->addRequireItemId(141, 10);
	quest->addRequireItemId(188, 10);
	quest->addGiveFamilly(36);
	quests.push_back(quest);

	quest = new Quest(25, false, false, false, false, -1, -1, -1, -1, -1, "Bon vivant",
			"Un bon repas ne peu se concevoir sans des petits trucs a grignotter a l\'aperitif. Igor le sait, maintenant, et il pourra trouver ce qu\'il faut en jeu.");
	quest->addRequireItemId(187, 10);
	quest->addRequireItemId(199, 10);
	quest->addRequireItemId(212, 10);
	quest->addGiveFamilly(26);
	quests.push_back(quest);

	quest =
			new Quest(26, false, false, false, false, -1, -1, -1, -1, -1, "Fondue norvegienne",
					"Les odeurs qui emanent de la taniere d\'Igor ne laissent aucun doute la-dessus: il est devenu un grand amateur de fromages. De nouveaux produits laitiers apparaitront dans les cavernes.");
	quest->addRequireItemId(149, 10);
	quest->addRequireItemId(175, 10);
	quest->addRequireItemId(255, 1);
	quest->addGiveFamilly(31);
	quests.push_back(quest);

	quest =
			new Quest(27, false, false, false, false, -1, -1, -1, -1, -1, "Mystere de Guu",
					"Cette quete n\'a aucun interet, a part vous conseiller de decouvrir au plus vite l\'excellent dessin anime \"Hare + Guu\" disponible en DVD dans toutes les bonnes boutiques ! Banyaaaaaii. ^^");
	quest->addRequireItemId(88, 1);
	quest->addRequireItemId(99, 1);
	quest->addRequireItemId(100, 1);
	quest->addRequireItemId(162, 1);
	quests.push_back(quest);

	quest = new Quest(28, false, false, false, false, -1, -1, -1, -1, -1, "Friandises divines",
			"Les sucreries n\'ont plus aucun secret pour Igor. Il saura, a compter de ce jour, debusquer les delices legendaires de Harry \"le beau\" dissemines a travers tout Hammerfest.");
	quest->addRequireItemId(177, 2);
	quest->addRequireItemId(202, 2);
	quest->addRequireItemId(206, 2);
	quest->addRequireItemId(262, 2);
	quest->addRequireItemId(269, 2);
	quest->addRequireItemId(270, 2);
	quest->addRequireItemId(271, 2);
	quest->addRequireItemId(272, 2);
	quest->addGiveFamilly(29);
	quests.push_back(quest);

	quest = new Quest(29, false, false, false, false, -1, -1, -1, -1, -1, "Igor et Cortex",
			"Igor a entrepris la fabrication de gadgets mysterieux... Attendez-vous a collectionner des machines etranges en jeu !");
	quest->addRequireItemId(21, 10);
	quest->addRequireItemId(26, 10);
	quest->addRequireItemId(31, 10);
	quest->addRequireItemId(85, 10);
	quest->addRequireItemId(90, 10);
	quest->addGiveFamilly(38);
	quests.push_back(quest);

	quest = new Quest(30, false, false, false, true, -1, -1, -1, -1, 13, "Affronter l\'obscurite",
			"Igor sait maintenant s\'eclairer ! Il pensera maintenant a apporter avec lui une torche pour ne pas trop se perdre dans l\'obscurite des niveaux avances !");
	quest->addRequireItemId(68, 10);
	quest->addGiveFamilly(14);
	quests.push_back(quest);

	quest = new Quest(31, false, false, false, true, -1, -1, -1, -1, 14, "Et la lumiere fut !",
			"Prepare a tous les dangers, le courageux Igor ne craint plus du tout l\'obscurite dans les niveaux avances !");
	quest->addRequireItemId(26, 10);
	quests.push_back(quest);

	quest = new Quest(32, false, false, false, false, -1, -1, -1, -1, 15, "Noel sur Hammerfest !", "Vous avez gagne 5 parties supplementaires.");
	quest->addRequireItemId(109, 1);
	quest->addGiveFamilly(16);
	quests.push_back(quest);

	quest = new Quest(33, false, false, false, false, -1, -1, -1, -1, 16, "Joyeux anniversaire Igor", "Vous avez gagne 10 parties supplementaires !");
	quest->addRequireItemId(110, 2);
	quest->addGiveFamilly(17);
	quests.push_back(quest);

	quest = new Quest(34, false, false, false, false, -1, -1, -1, -1, 17, "Cadeau celeste", "Vous avez gagne 20 parties supplementaires !");
	quest->addRequireItemId(111, 2);
	quests.push_back(quest);

	quest = new Quest(35, false, false, false, false, -1, -1, -1, -1, 18, "Achat de parties ameliore", "Vos appels dans la boutique vous rapporteront dorenavant plus de flocons !");
	quest->addRequireItemId(10, 5);
	quests.push_back(quest);

	quest = new Quest(36, false, false, false, false, -1, -1, -1, -1, -1, "Exterminateur de Sorbex", "Vous avez presse sans pitie les Citrons Sorbex !");
	quest->addRequireItemId(296, 1);
	quests.push_back(quest);

	quest = new Quest(37, false, false, false, false, -1, -1, -1, -1, -1, "Desamorceur de Bombinos", "Vous avez survecu aux explosions des Bombinos !");
	quest->addRequireItemId(297, 1);
	quests.push_back(quest);

	quest = new Quest(38, false, false, false, false, -1, -1, -1, -1, -1, "Tueur de poires", "Vous avez vaincu un nouveau boss: les Poires-Melbombes !");
	quest->addRequireItemId(298, 1);
	quests.push_back(quest);

	quest = new Quest(39, false, false, false, false, -1, -1, -1, -1, -1, "Mixeur de Tagadas", "Vous n\'avez fait qu\'une bouchee des Fraises-Tagada !");
	quest->addRequireItemId(299, 1);
	quests.push_back(quest);

	quest = new Quest(40, false, false, false, false, -1, -1, -1, -1, -1, "Kiwi frotte s\'y pique", "Vous avez su eviter tous les pieges des Sapeur-kiwis !");
	quest->addRequireItemId(300, 1);
	quests.push_back(quest);

	quest = new Quest(41, false, false, false, false, -1, -1, -1, -1, -1, "Chasseur de Bondissantes", "Vous ne vous etes pas laisse impressionner par la meute de Bondissantes !");
	quest->addRequireItemId(301, 1);
	quests.push_back(quest);

	quest = new Quest(42, false, false, false, false, -1, -1, -1, -1, -1, "Tronconneur d\'Ananargeddons", "Vous etes venu a bout d\'un groupe d\'Ananargeddons surentraines !");
	quest->addRequireItemId(302, 1);
	quests.push_back(quest);

	quest =
			new Quest(43, false, false, false, false, carotte, -1, -1, -1, -1, "Roi de Hammerfest",
					"Votre perseverance et votre tenacite ont eu raison du sorcier Tuberculoz: vous avez retrouve la carotte de Igor ! Vous debuterez vos prochaines parties avec une vie supplementaire et Igor portera fierement sa carotte preferee.");
	quest->addRequireItemId(102, 1);
	quests.push_back(quest);

	quest = new Quest(44, false, false, false, false, chapeaux, -1, -1, -1, -1, "Chapelier fou",
			"Igor s\'est decouvert une passion nouvelle pour les coiffes. Vous pourrez maintenant appuyer sur la touche \"D\" pendant la partie pour changer de deguisement !");
	quest->addRequireItemId(72, 5);
	quest->addRequireItemId(91, 5);
	quest->addRequireItemId(92, 10);
	quests.push_back(quest);

	quest =
			new Quest(45, false, false, false, false, poney, -1, -1, -1, -1, "Poney eco-terroriste",
					"Igor a accumule suffisament de richesses pour financer ses activites louches en Hammerfest. Il peut maintenant se deguiser en appuyant sur la touche \"D\" pendant la partie ! Et sinon, si ca n\'est pas deja fait, avez-vous deja visite www.dinoparc.com ?");
	quest->addRequireItemId(171, 10);
	quest->addRequireItemId(172, 10);
	quest->addRequireItemId(95, 3);
	quests.push_back(quest);

	quest =
			new Quest(46, false, false, false, false, pioupiou, -1, -1, -1, -1, "Le Pioupiouz est en toi",
					"Il fallait s\'y attendre: a force de ramasser n\'importe quoi, Igor s\'est fait gober par un Pioupiou ! Appuyez sur la touche \"D\" pendant la partie pour changer de deguisement (au fait, vous connaissiez le site www.pioupiouz.com ?)");
	quest->addRequireItemId(112, 1);
	quests.push_back(quest);

	quest =
			new Quest(47, false, false, false, false, champignon, -1, -1, -1, -1, "Chasseur de champignons",
					"Comme son homologue italien (plombier de son etat), Igor a une passion bizarre pour les champignons. Il pourra desormais se deguiser en appuyant sur la touche \"D\" pendant la partie !");
	quest->addRequireItemId(14, 1);
	quest->addRequireItemId(15, 1);
	quest->addRequireItemId(16, 1);
	quest->addRequireItemId(17, 1);
	quest->addGiveFamilly(19);
	quests.push_back(quest);

	quest =
			new Quest(48, false, false, false, false, cape, -1, -1, -1, -1, "Successeur de Tuberculoz",
					"Igor semble avoir... change.. Son regard est maintenant plus froid. Il affiche une mine sombre et se cache maintenant sous une grande cape pourpre. Petit a petit, il devient ce qu\'il a combattu... Vous pouvez maintenant revetir l\'apparence du sorcier Tuberculoz en appuyant sur \"D\" pendant la partie !");
	quest->addRequireItemId(113, 1);
	quests.push_back(quest);

	quest = new Quest(49, false, false, false, false, -1, passepartout, -1, -1, -1, "La premiere cle !",
			"Igor a trouve une sorte de Passe-partout en Bois. Nul doute qu\'il ouvre une porte quelque part dans les cavernes...");
	quest->addRequireItemId(304, 1);
	quest->addGiveFamilly(43);
	quest->addGiveFamilly(45);
	quest->addGiveFamilly(46);
	quests.push_back(quest);

	quest = new Quest(50, false, false, false, false, -1, rigordangerous, -1, -1, -1, "Rigor Dangerous",
			"Vous avez decouvert dans votre aventure une vieille cle rouillee mysterieuse ! Elle comporte une petite mention gravee: \"Rick\". Sans doute son ancien proprietaire...");
	quest->addRequireItemId(305, 1);
	quests.push_back(quest);

	quest = new Quest(51, false, false, false, false, -1, meluzzine, -1, -1, -1, "La Meluzzine perdue",
			"La Meluzzine, cle legendaire sortie des vieux contes hammerfestiens, ouvre a ce qu\'on raconte la porte de grandes richesses. Reste a savoir où ?");
	quest->addRequireItemId(306, 1);
	quests.push_back(quest);

	quest = new Quest(52, false, false, false, false, -1, bourru, -1, -1, 41, "Enfin le Bourru !", "Cette etrange petite cle sent le vin.");
	quest->addRequireItemId(307, 1);
	quests.push_back(quest);

	quest =
			new Quest(53, false, false, false, false, -1, furtok, -1, -1, -1, "Congelation",
					"Bien qu\'etant un bonhomme de neige, Igor lui-meme a du mal a garder cette cle en main, tant le froid qu\'elle degage est intense. La porte qu\'elle ouvre donne surement sur les endroits les plus recules de Hammerfest.");
	quest->addRequireItemId(308, 1);
	quests.push_back(quest);

	quest =
			new Quest(54, false, false, false, false, -1, rouille, -1, -1, -1, "Une cle rouillee",
					"Ce petit bout de ferraille difforme n\'a pas l\'air d\'avoir une grande valeur. Mais il faut parfois ce mefier des apparences ! Qui peut savoir quel genre d\'aventure se cache au dela de la porte qu\'elle ouvre ?");
	quest->addRequireItemId(309, 1);
	quests.push_back(quest);

	quest = new Quest(55, false, false, false, false, -1, boisjoli, -1, -1, 42, "Laissez passer !",
			"Votre toute puissance administrative sera dorenavant appuyee par le formulaire d\'Autorisation du Bois-Joli BJ22a.");
	quest->addRequireItemId(310, 1);
	quests.push_back(quest);

	quest = new Quest(56, false, false, false, false, -1, mondeardus, -1, -1, -1, "Les mondes ardus", "Pour avoir atteint le niveau 50 en mode Cauchemar, vous avez gagne la Cle des Mondes Ardus.");
	quest->addRequireItemId(311, 1);
	quests.push_back(quest);

	quest = new Quest(57, false, false, false, false, -1, piquante, -1, -1, -1, "Viiiite !",
			"Sans trop savoir pourquoi, la Cle Piquante que vous avez trouve vous donne une folle envie de courir partout et de vous rouler en boule.");
	quest->addRequireItemId(312, 1);
	quests.push_back(quest);

	quest = new Quest(58, false, false, false, false, -1, passetuberculoz, -1, -1, -1, "Faire les poches a Tubz", "Tuberculoz, le vilain sorcier, portait sur lui une cle...");
	quest->addRequireItemId(313, 1);
	quests.push_back(quest);

	quest = new Quest(59, false, false, false, false, -1, chauchemar, -1, -1, -1, "Tuberculoz, seigneur des enfers",
			"Votre toute puissance et votre maitrise absolue des techniques de combat de Hammerfest vous ont permi de gagner une cle unique en terrassant Tuberculoz en mode Cauchemar !");
	quest->addRequireItemId(314, 1);
	quests.push_back(quest);

	quest =
			new Quest(60, false, false, false, false, -1, -1, -1, -1, -1, "L\'eau ferrigineuneuse",
					"Votre exces dans la consommation de boissons alcoolisees vous a permis de debloquer la Cle du Bourru ! Vous aurez maintenant de bonnes chances de la trouver au cours de vos explorations.");
	quest->addRequireItemId(323, 20);
	quest->addRequireItemId(324, 10);
	quest->addRequireItemId(325, 5);
	quest->addRequireItemId(326, 3);
	quest->addRequireItemId(327, 2);
	quest->addGiveFamilly(41);
	quests.push_back(quest);

	quest = new Quest(61, false, false, false, false, -1, -1, -1, -1, -1, "Paperasse administrative",
			"Igor est un maitre dans l\'art de remplir des formulaires administratifs. Il trouvera donc sans probleme bientôt l\'Autorisation du Bois-Joli dans les dedales des cavernes...");
	quest->addRequireItemId(328, 10);
	quest->addRequireItemId(329, 15);
	quest->addRequireItemId(330, 3);
	quest->addRequireItemId(331, 2);
	quest->addRequireItemId(332, 1);
	quest->addGiveFamilly(42);
	quests.push_back(quest);

	quest =
			new Quest(62, false, false, false, false, -1, -1, boost, -1, -1, "Meilleur joueur",
					"Le meilleur joueur du net, c\'est vous, plus personne n\'a de doute la dessus ! Votre collection de manettes de jeu fera sans nul doute des envieux ^^ Igor dispose maintenant de l\'option Tornade qui procure un boost de vitesse au debut de chaque partie, quelques soient les options choisies !");
	quest->addRequireItemId(315, 1);
	quest->addRequireItemId(316, 1);
	quest->addRequireItemId(317, 1);
	quest->addRequireItemId(318, 1);
	quest->addRequireItemId(319, 1);
	quest->addRequireItemId(320, 1);
	quest->addRequireItemId(321, 1);
	quest->addRequireItemId(322, 1);
	quests.push_back(quest);

	quest = new Quest(63, false, false, false, false, -1, -1, mirror, -1, -1, "Miroir, mon beau miroir",
			"Le Miroir Bancal que vous avez trouve en jeu vous permet maintenant de voir les choses sous un angle nouveau. L\'option de jeu \"Miroir\" a ete debloquee !");
	quest->addRequireItemId(333, 1);
	quests.push_back(quest);

	quest = new Quest(64, false, false, false, false, -1, -1, nightmare, -1, -1, "Mode cauchemar",
			"Vous etes doue. Surement tres doue meme... Mais saurez-vous aider Igor en mode Cauchemar ? Cette option a ete debloquee !");
	quest->addRequireItemId(334, 1);
	quests.push_back(quest);

	quest = new Quest(65, false, false, false, false, -1, gordon, -1, -1, -1, "L\'aventure continue !",
			"Le conseil des Carotteux vous a choisi pour explorer plus en avant les cavernes de Hammerfest. La Cle de Gordon est une premiere etape dans cette nouvelle mission.");
	quest->addRequireItemId(117, 1);
	quests.push_back(quest);

	quest = new Quest(66, false, false, false, false, -1, -1, kickcontrol, -1, -1, "Joyau d\'Ankhel",
			"Vous avez fait preuve d\'une dexterite et d\'une perspicacite sans egal en retrouvant le Joyau d\'Ankhel. L\'option Controle du Ballon a ete debloquee pour le mode SoccerFest !");
	quest->addRequireItemId(116, 1);
	quests.push_back(quest);

	quest =
			new Quest(67, false, false, false, false, -1, -1, -1, multicoop, 48, "Sandy commence l\'aventure !",
					"Tous les elements sont reunis pour donner naissance a Sandy, le bonhomme de sable ! Ce nouveau personnage pourra se joindre a vous dans le mode Multi Cooperatif, jouable a deux sur le meme ordinateur. Re-decouvrez la grande aventure avec un ami !");
	quest->addRequireItemId(334, 5);
	quest->addRequireItemId(336, 10);
	quest->addRequireItemId(337, 5);
	quest->addRequireItemId(338, 3);
	quests.push_back(quest);

	quest = new Quest(68, false, false, false, false, -1, -1, mirrormulti, -1, -1, "Miroir, NOTRE beau miroir",
			"Avec le Miroir des Sables, vous pouvez maintenant voir les choses sous un angle nouveau mais a deux ! L\'option de jeu \"Miroir\" a ete debloquee pour le mode Multi Cooperatif !");
	quest->addRequireItemId(339, 1);
	quests.push_back(quest);

	quest = new Quest(69, false, false, false, false, -1, -1, nightmaremulti, -1, -1, "Mode double cauchemar",
			"De toute evidence, vous etes capables de grandes choses a deux ! L\'option de jeu \"Cauchemar\" a ete debloquee pour le mode Multi Cooperatif !");
	quest->addRequireItemId(340, 1);
	quests.push_back(quest);

	quest =
			new Quest(70, false, false, false, false, -1, -1, lifesharing, -1, -1, "Une grande Amitie",
					"Mieux vaut tard que jamais ! Igor et Sandy ont enfin compris qu\'il valait mieux s\'entraider s\'ils voulaient survivre a deux dans les Cavernes de Hammerfest. L\'option de jeu \"Partage de vies\" a ete debloquee pour le mode Multi Cooperatif ! Si cette option est activee, lorsqu\'un joueur perd sa derniere vie, il en prend une au second joueur et peut ainsi continuer la partie !");
	quest->addRequireItemId(341, 2);
	quests.push_back(quest);

	quest =
			new Quest(71, false, false, false, false, -1, -1, -1, -1, -1, "Apprentissage des canifs volants",
					"A toujours sauter partout, Igor a fini par acquerir une souplesse digne d\'un ninja et une dexterite hors du commun ! Mais pour prouver sa valeur, il doit maintenant collecter les artefacts ninjas disperses en Hammerfest !");
	quest->addRequireItemId(342, 1);
	quests.push_back(quest);

	quest =
			new Quest(72, false, false, false, false, -1, -1, ninja, -1, -1, "Shinobi do !",
					"Igor a rempli sa quete initiatique et maitrise maintenant a la perfection un grand nombre d\'armes du Ninjutsu ! Mais comme son nouveau de l\'honneur le lui interdit, il ne pourra pas s\'en servir. Toutefois, il pourra mettre a l\'epreuve ses competences grâce a l\'option de jeu \"Ninjutsu\" qu\'il vient de debloquer pour le mode Aventure !");
	quest->addRequireItemId(343, 5);
	quest->addRequireItemId(344, 2);
	quest->addRequireItemId(345, 7);
	quest->addRequireItemId(346, 7);
	quest->addRequireItemId(347, 1);
	quest->addRequireItemId(348, 1);
	quest->addRequireItemId(349, 1);
	quests.push_back(quest);

	quest =
			new Quest(73, false, false, false, false, -1, -1, set_ta_0, timeattack, -1, "Rapide comme l\'eclair !",
					"Igor est imbattable des lors qu\'il s\'agit de viser juste et se deplacer avec precision... Il faut maintenant le prouver aux autres ! Le mode TIME ATTACK est debloque et vous ouvre en plus l\'acces a un nouveau classement sur le site. Soyez le bonhomme de neige le plus rapide de tout Hammerfest !");
	quest->addRequireItemId(350, 100);
	quests.push_back(quest);

	quest =
			new Quest(74, false, false, false, false, -1, -1, bombexpert, -1, -1, "Maitre des Bombes",
					"Vous etes l\'expert repute dans tout Hammerfest en matiere d\'explosifs. Et pour montrer qu\'on ne vous ne la fait pas, a vous, l\'option \"Explosifs instables\" a ete debloquee pour le mode Aventure ! Gare a TOUT ce qui explose en jeu ! De plus, vous pouvez pousser toutes vos bombes plus loin en avancant en meme temps que vous la frappez.");
	quest->addRequireItemId(351, 1);
	quests.push_back(quest);

	quest = new Quest(75, false, false, false, false, -1, passpyramide, -1, -1, -1, "Tombeau de Tuberculoz", "Vous avez decouvert une etrange pyramide de poche dans le tombeau de Tuberculoz.");
	quest->addRequireItemId(352, 1);
	quests.push_back(quest);

	//for (unsigned int i = 0; i < quests.size(); i++) {
	//	quests[i]->printName();
	//}
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
				return availableItemEffect1.at(random(availableItemEffect1.size()) - 1);
			}
		} else if (randCoef <= probaCoef2) {
			if (availableItemEffect2.size() > 0) {
				return availableItemEffect2.at(random(availableItemEffect2.size()) - 1);
			}
		} else if (randCoef <= probaCoef3) {
			if (availableItemEffect3.size() > 0) {
				return availableItemEffect3.at(random(availableItemEffect3.size()) - 1);
			}
		} else if (randCoef <= probaCoef4) {
			if (availableItemEffect4.size() > 0) {
				return availableItemEffect4.at(random(availableItemEffect4.size()) - 1);
			}
		} else if (randCoef <= probaCoef5) {
			if (availableItemEffect5.size() > 0) {
				return availableItemEffect5.at(random(availableItemEffect5.size()) - 1);
			}
		} else if (randCoef <= probaCoef6) {
			if (availableItemEffect6.size() > 0) {
				return availableItemEffect6.at(random(availableItemEffect6.size()) - 1);
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
				return availableItemPoint1.at(random(availableItemPoint1.size()) - 1);
			}
		} else if (randCoef <= probaCoef2) {
			if (availableItemPoint2.size() > 0) {
				return availableItemPoint2.at(random(availableItemPoint2.size()) - 1);
			}
		} else if (randCoef <= probaCoef3) {
			if (availableItemPoint3.size() > 0) {
				return availableItemPoint3.at(random(availableItemPoint3.size()) - 1);
			}
		} else if (randCoef <= probaCoef4) {
			if (availableItemPoint4.size() > 0) {
				return availableItemPoint4.at(random(availableItemPoint4.size()) - 1);
			}
		} else if (randCoef <= probaCoef5) {
			if (availableItemPoint5.size() > 0) {
				return availableItemPoint5.at(random(availableItemPoint5.size()) - 1);
			}
		} else if (randCoef <= probaCoef6) {
			if (availableItemPoint6.size() > 0) {
				return availableItemPoint6.at(random(availableItemPoint6.size()) - 1);
			}
		} else if (randCoef <= probaCoef7) {
			if (availableItemPoint7.size() > 0) {
				return availableItemPoint7.at(random(availableItemPoint7.size()) - 1);
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

