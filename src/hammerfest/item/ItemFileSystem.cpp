#include "ItemFileSystem.h"

enum key {
	tuberculoz, chapeaux, poney, pioupiou, deguisement, passepartout, rigordangerous, meluzzine, bourru, furtok, rouille, boisjoli, mondeardus, piquante, passetuberculoz, carotte, champignon, cape, chauchemar, boost,

	mirror, gordon, kickcontrol, mirrormulti, nightmaremulti, lifesharing,

	ninja, timeattack, bombexpert, passpyramide

};

enum mode {

};

enum disguise {
	multicoop
};

enum option {
	nightmare = 0,
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
		if (fscanf(saveFile, "%08x", &fridge[i - 3]) <= 0) {
			fprintf(stderr, "error read file");
			return -1;
		}
	}
	fclose(saveFile);
	return 0;
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

	family = new Family(4, "Cartes à jouer");
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

	family = new Family(10, "Trésor des pirates");
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

	family = new Family(12, "Armement norvégien expérimental");
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

	family = new Family(23, "Pierres précieuses");
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

	family = new Family(26, "Apéritifs");
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

	family = new Family(28, "Trophées de Grand Prédateur");
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

	family = new Family(29, "Délices de Harry 'le beau'");
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

	family = new Family(33, "Légumes");
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

	family = new Family(34, "Délices MT");
	family->addItem(259);
	family->addItem(261);
	familys.push_back(family);

	family = new Family(35, "Kit de survie MT");
	family->addItem(255);
	family->addItem(256);
	family->addItem(257);
	family->addItem(258);
	familys.push_back(family);

	family = new Family(36, "L'heure du goûter");
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

	family = new Family(37, "Garçon patissier");
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

	family = new Family(39, "Trophées de baroudeur");
	family->addItem(296);
	family->addItem(297);
	family->addItem(298);
	family->addItem(299);
	family->addItem(300);
	family->addItem(301);
	family->addItem(302);
	familys.push_back(family);

	family = new Family(40, "Clés des Glaces");
	family->addItem(304);
	family->addItem(305);
	family->addItem(308);
	family->addItem(311);
	family->addItem(312);
	family->addItem(313);
	family->addItem(314);
	familys.push_back(family);

	family = new Family(41, "Clé avinée");
	family->addItem(307);
	familys.push_back(family);

	family = new Family(42, "Paperasse");
	family->addItem(310);
	familys.push_back(family);

	family = new Family(43, "Clés perdues");
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

	family = new Family(46, "Matériel administratif d'El Papah");
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

	family = new Family(49, "Récompenses du Ninjutsu");
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

	for (unsigned int i = 0; i < familys.size(); i++) {
		familys[i]->printName();
	}

	items.push_back(new Item(surface, 0, "Alphabet Cristallin", 0, -1, -1));
	items.push_back(new Item(surface, 1, "Bouclidur en or", 1, -1, -1));
	items.push_back(new Item(surface, 2, "Bouclidur argenté", 3, -1, -1));
	items.push_back(new Item(surface, 3, "Ballon de banquise", 2, -1, -1));
	items.push_back(new Item(surface, 4, "Lampe Fétvoveu", 1, -1, -1));
	items.push_back(new Item(surface, 5, "Lampe Léveussonfé", 2, -1, -1));
	items.push_back(new Item(surface, 6, "Paix intérieure", 1, -1, -1));
	items.push_back(new Item(surface, 7, "Basket IcePump", 1, -1, -1));
	items.push_back(new Item(surface, 8, "Etoile des neiges", 2, -1, -1));
	items.push_back(new Item(surface, 9, "Mauvais-oeil", 3, -1, -1));
	items.push_back(new Item(surface, 10, "Téléphone-phone-phone", 1, -1, -1));
	items.push_back(new Item(surface, 11, "Parapluie rouge", 1, -1, -1));
	items.push_back(new Item(surface, 12, "Parapluie bleu", 2, -1, -1));
	items.push_back(new Item(surface, 13, "Cass-Tet", 1, -1, -1));
	items.push_back(new Item(surface, 14, "Délice hallucinogène bleu", 2, -1, -1));
	items.push_back(new Item(surface, 15, "Champignon rigolo rouge", 4, -1, -1));
	items.push_back(new Item(surface, 16, "Figonassée grimpante", 5, -1, -1));
	items.push_back(new Item(surface, 17, "Petit Waoulalu des bois", 6, -1, -1));
	items.push_back(new Item(surface, 18, "Pissenlit tropical", 2, -1, -1));
	items.push_back(new Item(surface, 19, "Tournelune", 3, -1, -1));
	items.push_back(new Item(surface, 20, "Coffre d\'Anarchipel", 1, -1, -1));
	items.push_back(new Item(surface, 21, "Enceinte Bessel-Son", 2, -1, -1));
	items.push_back(new Item(surface, 22, "Vieille chaussure trouée", 2, -1, -1));
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
	items.push_back(new Item(surface, 33, "As de trêfle", 2, -1, -1));
	items.push_back(new Item(surface, 34, "As de carreau", 5, -1, -1));
	items.push_back(new Item(surface, 35, "As de coeur", 6, -1, -1));
	items.push_back(new Item(surface, 36, "Ig\'or", 3, -1, -1));
	items.push_back(new Item(surface, 37, "Collier rafraîchissant", 2, -1, -1));
	items.push_back(new Item(surface, 38, "Totem des dinoz", 3, -1, -1));
	items.push_back(new Item(surface, 39, "Tête de granit lestée de plomb", 3, -1, -1));
	items.push_back(new Item(surface, 40, "Sagittaire", 3, -1, 1));
	items.push_back(new Item(surface, 41, "Capricorne", 3, -1, 1));
	items.push_back(new Item(surface, 42, "Lion", 3, -1, 1));
	items.push_back(new Item(surface, 43, "Taureau", 3, -1, 1));
	items.push_back(new Item(surface, 44, "Balance", 3, -1, 1));
	items.push_back(new Item(surface, 45, "Bélier", 3, -1, 1));
	items.push_back(new Item(surface, 46, "Scorpion", 3, -1, 1));
	items.push_back(new Item(surface, 47, "Cancer", 3, -1, 1));
	items.push_back(new Item(surface, 48, "Verseau", 3, -1, 1));
	items.push_back(new Item(surface, 49, "Gémeaux", 3, -1, 1));
	items.push_back(new Item(surface, 50, "Poisson", 3, -1, 1));
	items.push_back(new Item(surface, 51, "Vierge", 3, -1, 1));
	items.push_back(new Item(surface, 52, "Elixir du Sagittaire", 3, -1, 1));
	items.push_back(new Item(surface, 53, "Elixir du Capricorne", 3, -1, 1));
	items.push_back(new Item(surface, 54, "Elixir du Lion", 3, -1, 1));
	items.push_back(new Item(surface, 55, "Elixir du Taureau", 3, -1, 1));
	items.push_back(new Item(surface, 56, "Elixir de la Balance", 3, -1, 1));
	items.push_back(new Item(surface, 57, "Elixir du Bélier", 3, -1, 1));
	items.push_back(new Item(surface, 58, "Elixir du Scorpion", 3, -1, 1));
	items.push_back(new Item(surface, 59, "Elixir du Cancer", 3, -1, 1));
	items.push_back(new Item(surface, 60, "Elixir du Verseau", 3, -1, 1));
	items.push_back(new Item(surface, 61, "Elixir des Gémeaux", 3, -1, 1));
	items.push_back(new Item(surface, 62, "Elixir du Poisson", 3, -1, 1));
	items.push_back(new Item(surface, 63, "Elixir de la Vierge", 3, -1, 1));
	items.push_back(new Item(surface, 64, "Arc-en-miel", 2, -1, -1));
	items.push_back(new Item(surface, 65, "Bouée canard", 2, -1, -1));
	items.push_back(new Item(surface, 66, "Branche de Kipik", 3, -1, -1));
	items.push_back(new Item(surface, 67, "Anneau de Guillaume Tell", 2, -1, -1));
	items.push_back(new Item(surface, 68, "Bougie", 2, -1, -1));
	items.push_back(new Item(surface, 69, "Koulraoule des îles", 2, -1, -1));
	items.push_back(new Item(surface, 70, "Trêfle commun", 1, -1, -1));
	items.push_back(new Item(surface, 71, "Chaud devant !", 1, -1, -1));
	items.push_back(new Item(surface, 72, "Chapeau de Mage-Gris", 3, -1, -1));
	items.push_back(new Item(surface, 73, "Feuille de sinopée", 2, -1, -1));
	items.push_back(new Item(surface, 74, "Esprit de l\'orange", 1, -1, -1));
	items.push_back(new Item(surface, 75, "Esprit de la pluie", 2, -1, -1));
	items.push_back(new Item(surface, 76, "Esprit des arbres", 3, -1, -1));
	items.push_back(new Item(surface, 77, "Lucidjané à crête bleue", 2, -1, -1));
	items.push_back(new Item(surface, 78, "Filandreux rougeoyant", 2, -1, -1));
	items.push_back(new Item(surface, 79, "Poisson empereur", 3, -1, -1));
	items.push_back(new Item(surface, 80, "Escargot Poussépa", 1, -1, -1));
	items.push_back(new Item(surface, 81, "Perle nacrée des murlocs", 2, -1, -1));
	items.push_back(new Item(surface, 82, "Jugement avant-dernier", 2, -1, -1));
	items.push_back(new Item(surface, 83, "Jugement dernier", 3, -1, -1));
	items.push_back(new Item(surface, 84, "Talisman scorpide", 3, -1, -1));
	items.push_back(new Item(surface, 85, "Baton tonnerre", 3, -1, -1));
	items.push_back(new Item(surface, 86, "Surprise de paille", 4, -1, -1));
	items.push_back(new Item(surface, 87, "Larve d\'oenopterius", 1, -1, -1));
	items.push_back(new Item(surface, 88, "Pokuté", 3, -1, -1));
	items.push_back(new Item(surface, 89, "Oeuf de Tzongre", 3, -1, -1));
	items.push_back(new Item(surface, 90, "Fulguro pieds-en-mousse", 3, -1, -1));
	items.push_back(new Item(surface, 91, "Couvre-chef de Luffy", 3, -1, -1));
	items.push_back(new Item(surface, 92, "Chapeau violin", 4, -1, -1));
	items.push_back(new Item(surface, 93, "Boit\'a\'messages", 3, -1, -1));
	items.push_back(new Item(surface, 94, "Anneau Antok", 3, -1, -1));
	items.push_back(new Item(surface, 95, "Cagnotte de Tuberculoz", 5, -1, -1));
	items.push_back(new Item(surface, 96, "Perle flamboyante", 4, -1, -1));
	items.push_back(new Item(surface, 97, "Perle vertillante", 5, -1, -1));
	items.push_back(new Item(surface, 98, "Grosse pé-perle ", 6, -1, -1));
	items.push_back(new Item(surface, 99, "Poils de Chourou", 5, -1, -1));
	items.push_back(new Item(surface, 100, "Pocket-Guu", 4, -1, -1));
	items.push_back(new Item(surface, 101, "Colis surprise", 0, -1, -1));
	items.push_back(new Item(surface, 102, "La Carotte d\'Igor", 0, -1, 1));
	items.push_back(new Item(surface, 103, "Vie palpitante", 1, -1, 1));
	items.push_back(new Item(surface, 104, "Vie aventureuse", 1, -1, 1));
	items.push_back(new Item(surface, 105, "Vie épique", 3, -1, 1));
	items.push_back(new Item(surface, 106, "Livre des champignons", 5, -1, -1));
	items.push_back(new Item(surface, 107, "Livre des étoiles", 5, -1, -1));
	items.push_back(new Item(surface, 108, "Parapluie Frutiparc", 2, -1, -1));
	items.push_back(new Item(surface, 109, "Flocon simple", 3, -1, 1));
	items.push_back(new Item(surface, 110, "Flocon bizarre", 4, -1, 1));
	items.push_back(new Item(surface, 111, "Flocon ENORME !", 5, -1, 1));
	items.push_back(new Item(surface, 112, "Pioupiou carnivore", 6, -1, 1));
	items.push_back(new Item(surface, 113, "Cape de Tuberculoz", 0, -1, -1));
	items.push_back(new Item(surface, 114, "Mode Mario", 4, -1, -1));
	items.push_back(new Item(surface, 115, "Casque de Volleyfest", 0, -1, -1));
	items.push_back(new Item(surface, 116, "Joyau d\'Ankhel", 0, -1, -1));
	items.push_back(new Item(surface, 117, "Clé de Gordon", 0, -1, -1));
	items.push_back(new Item(surface, 118, "Cristaux d\'Hammerfest", 0, -2, -1));
	items.push_back(new Item(surface, 119, "Pain à la viande", 1, 1000, -1));
	items.push_back(new Item(surface, 120, "Canne de Bobble", 7, 100000, -1));
	items.push_back(new Item(surface, 121, "Bonbon Berlinmauve", 1, 500, -1));
	items.push_back(new Item(surface, 122, "Bonbon Chamagros", 1, 1000, -1));
	items.push_back(new Item(surface, 123, "Bonbon rosamelle-praline", 2, 2500, -1));
	items.push_back(new Item(surface, 124, "Sucette aux fruits bleus", 2, 5000, -1));
	items.push_back(new Item(surface, 125, "Sucette chlorophylle", 3, 15000, -1));
	items.push_back(new Item(surface, 126, "Diamant Oune-difaïned", 0, -2, -1));
	items.push_back(new Item(surface, 127, "Oeil de tigre", 1, 5000, -1));
	items.push_back(new Item(surface, 128, "Jade de 12kg", 2, 15000, -1));
	items.push_back(new Item(surface, 129, "Reflet-de-lune", 3, 25000, -1));
	items.push_back(new Item(surface, 130, "Surprise de Cerises", 1, 800, -1));
	items.push_back(new Item(surface, 131, "Muffin aux cailloux", 1, 300, -1));
	items.push_back(new Item(surface, 132, "Gelée des bois", 1, 1700, -1));
	items.push_back(new Item(surface, 133, "Suprême aux framboises", 3, 12000, -1));
	items.push_back(new Item(surface, 134, "Petit pétillant", 3, 8000, -1));
	items.push_back(new Item(surface, 135, "Pierres du Changement", 0, -2, -1));
	items.push_back(new Item(surface, 136, "Glace Fraise", 2, 1200, -1));
	items.push_back(new Item(surface, 137, "Coupe Glacée", 2, 3500, -1));
	items.push_back(new Item(surface, 138, "Noodles", 2, 5600, -1));
	items.push_back(new Item(surface, 139, "Poulet Surgelé", 1, 10, -1));
	items.push_back(new Item(surface, 140, "Liquide bizarre", 3, 10000, -1));
	items.push_back(new Item(surface, 141, "Gros acidulé", 2, 5000, -1));
	items.push_back(new Item(surface, 142, "Liquide étrange", 3, 20000, -1));
	items.push_back(new Item(surface, 143, "Oeuf cru", 1, 500, -1));
	items.push_back(new Item(surface, 144, "Gland gnan-gnan", 1, 1300, -1));
	items.push_back(new Item(surface, 145, "Réglisse rouge", 1, 600, -1));
	items.push_back(new Item(surface, 146, "Oeuf Au Plat", 1, 1000, -1));
	items.push_back(new Item(surface, 147, "Saucisse piquée", 1, 300, -1));
	items.push_back(new Item(surface, 148, "Cerise-apéro confite", 1, 400, -1));
	items.push_back(new Item(surface, 149, "Fromage piqué", 1, 600, -1));
	items.push_back(new Item(surface, 150, "Olive pas mûre", 1, 1000, -1));
	items.push_back(new Item(surface, 151, "Olive noire", 2, 1500, -1));
	items.push_back(new Item(surface, 152, "Oeil de pomme", 2, 2000, -1));
	items.push_back(new Item(surface, 153, "Blob intrusif", 2, 2500, -1));
	items.push_back(new Item(surface, 154, "Gouda mou", 3, 5000, -1));
	items.push_back(new Item(surface, 155, "Poulpi empalé", 3, 10000, -1));
	items.push_back(new Item(surface, 156, "Olive oubliée", 4, 50000, -1));
	items.push_back(new Item(surface, 157, "Monsieur radis", 4, 50000, -1));
	items.push_back(new Item(surface, 158, "Sushi thon", 3, 9000, -1));
	items.push_back(new Item(surface, 159, "Sucette acidulée", 1, 750, -1));
	items.push_back(new Item(surface, 160, "Délice d\'Aralé", 5, 1, -1));
	items.push_back(new Item(surface, 161, "Sorbet au plastique", 1, 900, -1));
	items.push_back(new Item(surface, 162, "Manda", 5, 60000, -1));
	items.push_back(new Item(surface, 163, "Pétale mystérieuse", 2, 3000, -1));
	items.push_back(new Item(surface, 164, "Gump", 4, 35000, -1));
	items.push_back(new Item(surface, 165, "Bleuet", 0, 5, -1));
	items.push_back(new Item(surface, 166, "Rougeoyant", 0, 10, -1));
	items.push_back(new Item(surface, 167, "Verdifiant", 0, 15, -1));
	items.push_back(new Item(surface, 168, "KassDent", 0, 25, -1));
	items.push_back(new Item(surface, 169, "Pièce d\'or secrète", 0, 2500, -1));
	items.push_back(new Item(surface, 170, "Sou d\'argent", 1, 5000, -1));
	items.push_back(new Item(surface, 171, "Sou d\'or", 3, 25000, -1));
	items.push_back(new Item(surface, 172, "Gros tas de sous", 4, 75000, -1));
	items.push_back(new Item(surface, 173, "Boisson kipik", 1, 1200, -1));
	items.push_back(new Item(surface, 174, "Doigts-de-tuberculoz", 1, 900, -1));
	items.push_back(new Item(surface, 175, "Pizza de Donatello", 1, 1400, -1));
	items.push_back(new Item(surface, 176, "Canelé du sud-ouest", 3, 15500, -1));
	items.push_back(new Item(surface, 177, "Eclair noisette choco caramel et sucre", 3, 18500, -1));
	items.push_back(new Item(surface, 178, "Bleuette rouge", 3, 10000, -1));
	items.push_back(new Item(surface, 179, "Perroquet décapité en sauce", 4, 45000, -1));
	items.push_back(new Item(surface, 180, "Morvo-morphe", 4, 70000, -1));
	items.push_back(new Item(surface, 181, "Fraise Tagada", 1, 1000, -1));
	items.push_back(new Item(surface, 182, "Car-En-Sac", 1, 1400, -1));
	items.push_back(new Item(surface, 183, "Dragibus", 1, 1600, -1));
	items.push_back(new Item(surface, 184, "Krokodile", 2, 12250, -1));
	items.push_back(new Item(surface, 185, "Demi Cocobats", 1, 1800, -1));
	items.push_back(new Item(surface, 186, "Happy Cola", 1, 1750, -1));
	items.push_back(new Item(surface, 187, "Cacahuete secrète", 2, 50, -1));
	items.push_back(new Item(surface, 188, "P\'tit fantome", 2, 2500, -1));
	items.push_back(new Item(surface, 189, "Cookie deshydraté", 2, 1800, -1));
	items.push_back(new Item(surface, 190, "Arbuche de noël", 3, 8000, -1));
	items.push_back(new Item(surface, 191, "Piment farceur", 4, 12000, -1));
	items.push_back(new Item(surface, 192, "Soja Max IceCream", 2, 2250, -1));
	items.push_back(new Item(surface, 193, "Bouquet de steack", 4, 7777, -1));
	items.push_back(new Item(surface, 194, "Daruma-Pastèque", 5, 60000, -1));
	items.push_back(new Item(surface, 195, "Graine de tournesol", 3, 5, -1));
	items.push_back(new Item(surface, 196, "Croissant confit", 5, 1500, -1));
	items.push_back(new Item(surface, 197, "Haricot paresseux", 1, 800, -1));
	items.push_back(new Item(surface, 198, "Lapin-choco", 3, 1200, -1));
	items.push_back(new Item(surface, 199, "Biloo", 1, 900, -1));
	items.push_back(new Item(surface, 200, "Graine de pechume en gelée", 2, 3000, -1));
	items.push_back(new Item(surface, 201, "Sombrino aux amandes", 3, 1650, -1));
	items.push_back(new Item(surface, 202, "Emi-Praline", 3, 1500, -1));
	items.push_back(new Item(surface, 203, "Frogmaliet aux pepites de chocolat", 3, 1600, -1));
	items.push_back(new Item(surface, 204, "Yumi au café", 3, 1800, -1));
	items.push_back(new Item(surface, 205, "Bouchée mielleuse nappée au gel de Vodka", 3, 1700, -1));
	items.push_back(new Item(surface, 206, "Escargot au chocolat persillé", 3, 1750, -1));
	items.push_back(new Item(surface, 207, "Fossile de cacao marbré au fois gras", 3, 1550, -1));
	items.push_back(new Item(surface, 208, "Cerisot mariné a la bière", 3, 3000, -1));
	items.push_back(new Item(surface, 209, "Jambon de Bayonne", 2, 12000, -1));
	items.push_back(new Item(surface, 210, "Saucisson entamé", 2, 6000, -1));
	items.push_back(new Item(surface, 211, "Raide red reste", 1, 800, -1));
	items.push_back(new Item(surface, 212, "Torchon madrangeais au sirop d\'érable", 1, 500, -1));
	items.push_back(new Item(surface, 213, "Saucisson de marcassin sauvage", 2, 4000, -1));
	items.push_back(new Item(surface, 214, "Tranches de Jaret de Kangourou", 1, 1200, -1));
	items.push_back(new Item(surface, 215, "Saucissaille de St-Morgelet", 1, 1600, -1));
	items.push_back(new Item(surface, 216, "Paté d\'ongles au truffes", 3, 400, -1));
	items.push_back(new Item(surface, 217, "Saucisson maudit scellé", 4, 16000, -1));
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
	items.push_back(new Item(surface, 228, "Fromage frais vigné", 2, 400, -1));
	items.push_back(new Item(surface, 229, "Pâte dessert fromagée", 2, 325, -1));
	items.push_back(new Item(surface, 230, "Saladou", 2, 700, -1));
	items.push_back(new Item(surface, 231, "Poire d\'eau", 2, 800, -1));
	items.push_back(new Item(surface, 232, "Cacahuète mauve et juteuse", 4, 3700, -1));
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
	items.push_back(new Item(surface, 246, "Brocolis digérés", 3, 3, -1));
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
	items.push_back(new Item(surface, 257, "Pétillante", 3, 2500, -1));
	items.push_back(new Item(surface, 258, "Warpoquiche", 2, 1250, -1));
	items.push_back(new Item(surface, 259, "Brioche dorée", 6, 150000, -1));
	items.push_back(new Item(surface, 260, "Café de fin de projet", 1, 600, -1));
	items.push_back(new Item(surface, 261, "Laxatif aux amandes", 5, 150000, -1));
	items.push_back(new Item(surface, 262, "Smiley croquant", 2, 900, -1));
	items.push_back(new Item(surface, 263, "Barquette de lave", 1, 400, -1));
	items.push_back(new Item(surface, 264, "Nonoix", 3, 3000, -1));
	items.push_back(new Item(surface, 265, "Amande croquante", 3, 3000, -1));
	items.push_back(new Item(surface, 266, "Noisette", 3, 3000, -1));
	items.push_back(new Item(surface, 267, "Noodles crus", 1, 550, -1));
	items.push_back(new Item(surface, 268, "Brioche vapeur", 4, 21000, -1));
	items.push_back(new Item(surface, 269, "Tartine chocolat-noisette", 1, 650, -1));
	items.push_back(new Item(surface, 270, "Tartine hémoglobine", 2, 1650, -1));
	items.push_back(new Item(surface, 271, "Tartine à l\'orange collante", 3, 5800, -1));
	items.push_back(new Item(surface, 272, "Tartine au miel", 2, 1650, -1));
	items.push_back(new Item(surface, 273, "Lombric nature", 4, 15, -1));
	items.push_back(new Item(surface, 274, "Grenade de chantilly", 2, 5000, -1));
	items.push_back(new Item(surface, 275, "Profies très drôles", 4, 35000, -1));
	items.push_back(new Item(surface, 276, "Chouchocos", 4, 35000, -1));
	items.push_back(new Item(surface, 277, "Blob périmé", 6, 250000, -1));
	items.push_back(new Item(surface, 278, "Bonbon Hélène-fraiche", 3, 200, -1));
	items.push_back(new Item(surface, 279, "Nem aux anchois", 3, 9000, -1));
	items.push_back(new Item(surface, 280, "Surimi pamplemousse", 2, 150, -1));
	items.push_back(new Item(surface, 281, "Poulpi à l\'encre", 5, 80000, -1));
	items.push_back(new Item(surface, 282, "Curly", 5, 70000, -1));
	items.push_back(new Item(surface, 283, "Tartelette framboise", 1, 2500, -1));
	items.push_back(new Item(surface, 284, "Oeuf de Poire", 6, 57000, -1));
	items.push_back(new Item(surface, 285, "Truffe collante sans goût", 6, 300000, -1));
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
	items.push_back(new Item(surface, 303, "Anneau hérissé", 0, 250, -1));
	items.push_back(new Item(surface, 304, "Passe-partout en bois", 6, 10000, -1));
	items.push_back(new Item(surface, 305, "Clé de Rigor Dangerous", 6, 10000, -1));
	items.push_back(new Item(surface, 306, "Méluzzine", 5, 10000, -1));
	items.push_back(new Item(surface, 307, "Clé du Bourru", 1, 10000, 1));
	items.push_back(new Item(surface, 308, "Furtok Glaciale", 6, 10000, -1));
	items.push_back(new Item(surface, 309, "Vieille clé rouillée", 4, 10000, -1));
	items.push_back(new Item(surface, 310, "Autorisation du Bois-Joli", 1, 10000, 1));
	items.push_back(new Item(surface, 311, "Clé des Mondes Ardus", 6, 10000, -1));
	items.push_back(new Item(surface, 312, "Clé piquante", 6, 10000, -1));
	items.push_back(new Item(surface, 313, "Passe-partout de Tuberculoz", 6, 10000, -1));
	items.push_back(new Item(surface, 314, "Clé des cauchemars", 6, 10000, -1));
	items.push_back(new Item(surface, 315, "Pad Sounie", 6, 17000, -1));
	items.push_back(new Item(surface, 316, "Pad Frusion 64", 6, 100000, -1));
	items.push_back(new Item(surface, 317, "Pad Game-Pyramid", 6, 17000, -1));
	items.push_back(new Item(surface, 318, "Pad Sey-Ga", 6, 17000, -1));
	items.push_back(new Item(surface, 319, "Pad Super Frusion", 6, 17000, -1));
	items.push_back(new Item(surface, 320, "Pad du Système Maitre", 6, 17000, -1));
	items.push_back(new Item(surface, 321, "Pad Frusion Entertainment System", 6, 17000, -1));
	items.push_back(new Item(surface, 322, "Manette S-Téhéf", 6, 20000, -1));
	items.push_back(new Item(surface, 323, "Canette Express", 1, 500, -1));
	items.push_back(new Item(surface, 324, "Bouteille aux 2064 bulles", 2, 1200, -1));
	items.push_back(new Item(surface, 325, "Mousse volante", 3, 3000, -1));
	items.push_back(new Item(surface, 326, "Vin Merveilleux", 4, 20000, -1));
	items.push_back(new Item(surface, 327, "Liqueur maléfique", 5, 100000, -1));
	items.push_back(new Item(surface, 328, "Tampon MT", 1, 2000, -1));
	items.push_back(new Item(surface, 329, "Facture gratuite", 2, 10, -1));
	items.push_back(new Item(surface, 330, "Post-It de François", 3, 3000, -1));
	items.push_back(new Item(surface, 331, "Pot à crayon solitaire", 4, 5500, -1));
	items.push_back(new Item(surface, 332, "Agrafeuse du Chaos", 5, 100000, -1));
	items.push_back(new Item(surface, 333, "Miroir bancal", 0, 69, -1));
	items.push_back(new Item(surface, 334, "Etoile du Diable", 0, 666, -1));
	items.push_back(new Item(surface, 334, "Poudre de plage magique", 1, 700, 5));
	items.push_back(new Item(surface, 336, "Matériel d\'architecte", 1, 600, 10));
	items.push_back(new Item(surface, 337, "Maquette en sable", 2, 1200, 5));
	items.push_back(new Item(surface, 338, "Winkel", 2, 900, 3));
	items.push_back(new Item(surface, 339, "Miroir des Sables", 0, 69, -1));
	items.push_back(new Item(surface, 340, "Etoile des Diables Jumeaux", 0, 666, -1));
	items.push_back(new Item(surface, 341, "Sceau d\'amitié", 0, 100, -1));
	items.push_back(new Item(surface, 342, "Insigne de l\'ordre des Ninjas", 0, 900, -1));
	items.push_back(new Item(surface, 343, "Couteau suisse japonais", 2, 1200, -1));
	items.push_back(new Item(surface, 344, "Shuriken de second rang", 3, 1600, -1));
	items.push_back(new Item(surface, 345, "Shuriken d\'entraînement", 1, 250, -1));
	items.push_back(new Item(surface, 346, "Najinata", 2, 600, -1));
	items.push_back(new Item(surface, 347, "Lance-boulettes de Précision", 4, 5000, -1));
	items.push_back(new Item(surface, 348, "Ocarina chantant", 4, 6500, -1));
	items.push_back(new Item(surface, 349, "Armure de la nuit", 4, 10000, -1));
	items.push_back(new Item(surface, 350, "Insigne du Mérite", 0, 10000, -1));
	items.push_back(new Item(surface, 351, "Neige-o-glycérine", 0, 150000, -1));
	items.push_back(new Item(surface, 352, "Pass-Pyramide", 0, 30000, -1));

	for (unsigned int i = 0; i < items.size(); i++) {
		items[i]->printName();
	}

	Quest * quest = new Quest(0, true, false, false, false, -1, -1, -1, -1, 5, "Les constellations", "Igor peut maintenant poser 2 bombes au lieu d&apos;une seule à la fois, et ce,\n\t\t\tde manière permanente !");
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

	quests.push_back(quest);

	quest = new Quest(1, false, true, false, false, -1, -1, -1, -1, 6, "Mixtures du zodiaque", "Igor sait désormais envoyer ses bombes à l&apos;étage supérieur ! Maintenez BAS enfoncé\n\t\t\tpendant que vous tapez dans une bombe posée.");
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

	quest = new Quest(2, false, false, true, false, -1, -1, -1, -1, 7, "Premiers pas", "Igor débutera désormais la partie avec une vie supplémentaire.");
	quest->addRequireItemId(103, 1);
	quests.push_back(quest);

	quest = new Quest(3, false, false, true, false, -1, -1, -1, -1, 8, "L\'aventure commence", "Igor débutera désormais la partie avec une autre vie supplémentaire.");
	quest->addRequireItemId(104, 1);
	quests.push_back(quest);

	quest = new Quest(4, false, false, true, false, -1, -1, -1, -1, 9, "Une destinée épique", "Igor débutera désormais la partie avec encore une vie supplémentaire !");
	quest->addRequireItemId(105, 1);
	quests.push_back(quest);

	quest = new Quest(5, false, false, true, false, -1, -1, -1, -1, -1, "Persévérance", "Igor débutera désormais la partie avec une vie supplémentaire.");
	quest->addRequireItemId(36, 5);
	quests.push_back(quest);

	quest = new Quest(6, false, false, false, false, -1, -1, -1, -1, -1, "Gourmandise", "De nouveaux aliments (plus sains) apparaîtront désormais en jeu !");
	quest->addRequireItemId(118, 5);
	quest->addRequireItemId(121, 1);
	quest->addRequireItemId(131, 1);
	quest->addRequireItemId(145, 1);
	quest->addRequireItemId(159, 1);
	quest->addRequireItemId(161, 1);

	quests.push_back(quest);

	quest = new Quest(7, false, false, false, false, -1, -1, -1, -1, -1, "Du sucre !", "Igor veut encore plus de sucre ! Des délicieuses friandises apparaîtront\n\t\t\tdésormais en jeu.");
	quest->addRequireItemId(121, 10);
	quest->addRequireItemId(145, 10);
	quest->addRequireItemId(159, 10);
	quest->addRequireItemId(188, 2);
	quest->addRequireItemId(192, 2);
	quests.push_back(quest);

	quest = new Quest(8, false, false, false, false, -1, -1, -1, -1, -1, "Malnutrition", "Le goût d&apos;Igor pour les aliments peu équilibrés lui permettra de trouver\n\t\t\tdes aliments encore plus... &quot;douteux&quot; en jeu.");
	quest->addRequireItemId(140, 5);
	quest->addRequireItemId(142, 5);
	quest->addRequireItemId(146, 20);
	quest->addRequireItemId(143, 10);
	quests.push_back(quest);

	quest = new Quest(9, false, false, false, false, -1, -1, -1, -1, -1, "Goût raffiné", "Le régime bizarre d&apos;Igor a amené de nouveaux aliments exotiques en jeu !");
	quest->addRequireItemId(120, 1);
	quest->addRequireItemId(164, 2);
	quest->addRequireItemId(158, 10);
	quests.push_back(quest);

	quest = new Quest(10, false, false, false, false, -1, -1, -1, -1, -1, "Avancée technologique", "Pour vous aider dans votre aventure, tout un tas d&apos;objets aux effets bizarres\n\t\t\tfont leur apparition en jeu !");
	quest->addRequireItemId(4, 1);
	quest->addRequireItemId(7, 1);
	quest->addRequireItemId(13, 1);
	quests.push_back(quest);

	quest = new Quest(11, false, false, false, false, -1, -1, -1, -1, -1, "Le petit guide des Champignons", "Igor a découvert un étrange ouvrage, une sorte de livre de cuisine traitant\n\t\t\tdes champignons hallucinogènes. Il pourra désormais en trouver lors de ses\n\t\t\texplorations.");
	quest->addRequireItemId(106, 1);
	quests.push_back(quest);

	quest = new Quest(12, false, false, false, false, -1, -1, -1, -1, -1, "Trouver les pièces d\'or secrètes !", "Des richesses supplémentaires de très grande valeur apparaitront maintenant\n\t\t\ten jeu !");
	quest->addRequireItemId(169, 150);
	quests.push_back(quest);

	quest = new Quest(13, false, false, false, false, -1, -1, -1, -1, -1, "Le grimoire des Etoiles", "Cet ouvrage mystérieux en dit long sur les 12 constellations du Zodiaque.\n\t\t\tVous pourrez désormais les collectionner en jeu !");
	quest->addRequireItemId(107, 1);
	quests.push_back(quest);

	quest = new Quest(14, false, false, false, false, -1, -1, -1, -1, -1, "Armageddon", "Des objets aux effets ravageurs vont maintenant apparaître en jeu !");
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
	quests.push_back(quest);

	quest = new Quest(15, false, false, false, false, -1, -1, -1, -1, -1, "Régime MotionTwin", "A force de manger n&apos;importe quoi, Igor a acquis la maîtrise des jeux ! Il\n\t\t\tpourra collectionner des objets rarissimes pendant son exploration et\n\t\t\ttrouver\tdes aliments d&apos;exception !");
	quest->addRequireItemId(175, 11);
	quest->addRequireItemId(192, 11);
	quest->addRequireItemId(255, 11);
	quest->addRequireItemId(256, 11);
	quest->addRequireItemId(257, 11);
	quest->addRequireItemId(258, 11);
	quest->addRequireItemId(267, 20);
	quest->addRequireItemId(163, 30);
	quest->addRequireItemId(199, 11);
	quests.push_back(quest);

	quest = new Quest(16, false, false, false, false, -1, -1, -1, -1, -1, "Créateur de jeu en devenir", "Igor semble apprécier les aliments basiques, une belle carrière dans le monde\n\t\t\tdu jeu vidéo pourrait s&apos;offrir à lui ! Des aliments adaptés lui seront\n\t\t\tdorénavant proposés et quelques cartes à jouer pour se faire la main.");
	quest->addRequireItemId(260, 20);
	quests.push_back(quest);

	quest = new Quest(17, false, false, false, false, -1, -1, -1, -1, -1, "La vie est une boîte de chocolats", "De délicieux chocolats sont maintenant distribués en Hammerfest !");
	quest->addRequireItemId(164, 5);
	quests.push_back(quest);

	quest = new Quest(18, false, false, false, false, -1, -1, -1, -1, -1, "Le trésor Oune-difaïned", "A force de ramasser des diamants apparus on ne sait comment, Igor a acquis\n\t\t\tla faculté de repérer des pierres précieuses rares ! Il en trouvera au cours\n\t\t\tde ses explorations.");
	quest->addRequireItemId(126, 30);
	quests.push_back(quest);

	quest = new Quest(19, false, false, false, false, -1, -1, -1, -1, -1, "Super size me !", "Toujours plus loin dans la malnutrition, Igor a découvert qu&apos;il pouvait aussi\n\t\t\tse nourrir de produits en boite.");
	quest->addRequireItemId(119, 20);
	quest->addRequireItemId(173, 20);
	quest->addRequireItemId(174, 20);
	quests.push_back(quest);

	quest = new Quest(20, false, false, false, false, -1, -1, -1, -1, -1, "Maître joaillier", "Igor est devenu un véritable expert en pierres précieuses. Il pourra maintenant\n\t\t\tdécouvrir de puissants bijoux magiques au fil de ses explorations !");
	quest->addRequireItemId(127, 10);
	quest->addRequireItemId(128, 5);
	quest->addRequireItemId(129, 1);
	quests.push_back(quest);

	quest = new Quest(21, false, false, false, false, -1, -1, -1, -1, -1, "Grand prédateur", "Igor en a plus qu&apos;assez de chasser des choses sucrées ! Désormais devenu un prédateur\n\t\t\tsans pitié, il pourra traquer et dévorer toute sorte de charcuteries.");
	quest->addRequireItemId(119, 20);
	quest->addRequireItemId(139, 10);
	quest->addRequireItemId(143, 20);
	quest->addRequireItemId(179, 1);
	quest->addRequireItemId(280, 10);
	quests.push_back(quest);

	quest = new Quest(22, false, false, false, false, -1, -1, -1, -1, -1, "Expert en salades et potages", "On raconte partout qu&apos;Igor serait la réincarnation de Saladou, le maître mondialement\n\t\t\treconnu de la salade. Fort de ce don, il pourra à l&apos;avenir cueillir une très grande variété\n\t\t\tde légumes !");
	quest->addRequireItemId(138, 15);
	quest->addRequireItemId(157, 1);
	quest->addRequireItemId(178, 2);
	quest->addRequireItemId(222, 5);
	quest->addRequireItemId(221, 3);
	quests.push_back(quest);

	quest = new Quest(23, false, false, false, false, -1, -1, -1, -1, -1, "Festin d\'Hammerfest", "Avec un repas aussi complet, Igor est fin prêt pour avoir accès aux patisseries les\n\t\t\tplus raffinées qui existent.");
	quest->addRequireItemId(209, 1);
	quest->addRequireItemId(230, 1);
	quest->addRequireItemId(244, 1);
	quest->addRequireItemId(281, 1);
	quest->addRequireItemId(227, 1);
	quest->addRequireItemId(256, 1);
	quest->addRequireItemId(260, 1);
	quests.push_back(quest);

	quest = new Quest(24, false, false, false, false, -1, -1, -1, -1, -1, "Goûter d\'anniversaire", "Igor a trouvé tous les éléments pour assurer à son prochain goûter d&apos;anniversaire !\n\t\t\tIl trouvera maintenant pleins de petits en-cas pour patienter jusque là.");
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
	quests.push_back(quest);

	quest = new Quest(25, false, false, false, false, -1, -1, -1, -1, -1, "Bon vivant", "Un bon repas ne peu se concevoir sans des petits trucs à grignotter à l&apos;apéritif.\n\t\t\tIgor le sait, maintenant, et il pourra trouver ce qu&apos;il faut en jeu.");
	quest->addRequireItemId(187, 10);
	quest->addRequireItemId(199, 10);
	quest->addRequireItemId(212, 10);
	quests.push_back(quest);

	quest = new Quest(26, false, false, false, false, -1, -1, -1, -1, -1, "Fondue norvégienne", "Les odeurs qui émanent de la tanière d&apos;Igor ne laissent aucun doute là-dessus:\n\t\t\til est devenu un grand amateur de fromages. De nouveaux produits laitiers\n\t\t\tapparaîtront dans les cavernes.");
	quest->addRequireItemId(149, 10);
	quest->addRequireItemId(175, 10);
	quest->addRequireItemId(255, 1);
	quests.push_back(quest);

	quest = new Quest(27, false, false, false, false, -1, -1, -1, -1, -1, "Mystère de Guu", "Cette quête n&apos;a aucun intérêt, à part vous conseiller de découvrir au plus vite\n\t\t\tl&apos;excellent dessin animé &quot;Haré + Guu&quot; disponible en DVD dans toutes les bonnes\n\t\t\tboutiques ! Banyaaaaaïï. ^^");
	quest->addRequireItemId(88, 1);
	quest->addRequireItemId(99, 1);
	quest->addRequireItemId(100, 1);
	quest->addRequireItemId(162, 1);
	quests.push_back(quest);

	quest = new Quest(28, false, false, false, false, -1, -1, -1, -1, -1, "Friandises divines", "Les sucreries n&apos;ont plus aucun secret pour Igor. Il saura, à compter de ce jour,\n\t\t\tdébusquer les délices légendaires de Harry &quot;le beau&quot; disséminés à travers tout\n\t\t\tHammerfest.");
	quest->addRequireItemId(177, 2);
	quest->addRequireItemId(202, 2);
	quest->addRequireItemId(206, 2);
	quest->addRequireItemId(262, 2);
	quest->addRequireItemId(269, 2);
	quest->addRequireItemId(270, 2);
	quest->addRequireItemId(271, 2);
	quest->addRequireItemId(272, 2);
	quests.push_back(quest);

	quest = new Quest(29, false, false, false, false, -1, -1, -1, -1, -1, "Igor et Cortex", "Igor a entrepris la fabrication de gadgets mystérieux... Attendez-vous à\n\t\t\tcollectionner des machines étranges en jeu !");
	quest->addRequireItemId(21, 10);
	quest->addRequireItemId(26, 10);
	quest->addRequireItemId(31, 10);
	quest->addRequireItemId(85, 10);
	quest->addRequireItemId(90, 10);
	quests.push_back(quest);

	quest = new Quest(30, false, false, false, true, -1, -1, -1, -1, 13, "Affronter l\'obscurité", "Igor sait maintenant s&apos;éclairer ! Il pensera maintenant à apporter avec lui une\n\t\t\ttorche pour ne pas trop se perdre dans l&apos;obscurité des niveaux avancés !");
	quest->addRequireItemId(68, 10);
	quests.push_back(quest);

	quest = new Quest(31, false, false, false, true, -1, -1, -1, -1, 14, "Et la lumière fût !", "Préparé à tous les dangers, le courageux Igor ne craint plus du tout\n\t\t\tl&apos;obscurité dans les niveaux avancés !");
	quest->addRequireItemId(26, 10);
	quests.push_back(quest);

	quest = new Quest(32, false, false, false, false, -1, -1, -1, -1, 15, "Noël sur Hammerfest !", "Vous avez gagné 5 parties supplémentaires.");
	quest->addRequireItemId(109, 1);
	quests.push_back(quest);

	quest = new Quest(33, false, false, false, false, -1, -1, -1, -1, 16, "Joyeux anniversaire Igor", "Vous avez gagné 10 parties supplémentaires !");
	quest->addRequireItemId(110, 2);
	quests.push_back(quest);

	quest = new Quest(34, false, false, false, false, -1, -1, -1, -1, 17, "Cadeau céleste", "Vous avez gagné 20 parties supplémentaires !");
	quest->addRequireItemId(111, 2);
	quests.push_back(quest);

	quest = new Quest(35, false, false, false, false, -1, -1, -1, -1, 18, "Achat de parties amélioré", "Vos appels dans la boutique vous rapporteront dorénavant plus de flocons !");
	quest->addRequireItemId(10, 5);
	quests.push_back(quest);

	quest = new Quest(36, false, false, false, false, -1, -1, -1, -1, -1, "Exterminateur de Sorbex", "Vous avez pressé sans pitié les Citrons Sorbex !");
	quest->addRequireItemId(296, 1);
	quests.push_back(quest);

	quest = new Quest(37, false, false, false, false, -1, -1, -1, -1, -1, "Désamorceur de Bombinos", "Vous avez survécu aux explosions des Bombinos !");
	quest->addRequireItemId(297, 1);
	quests.push_back(quest);

	quest = new Quest(38, false, false, false, false, -1, -1, -1, -1, -1, "Tueur de poires", "Vous avez vaincu un nouveau boss: les Poires-Melbombes !");
	quest->addRequireItemId(298, 1);
	quests.push_back(quest);

	quest = new Quest(39, false, false, false, false, -1, -1, -1, -1, -1, "Mixeur de Tagadas", "Vous n&apos;avez fait qu&apos;une bouchée des Fraises-Tagada !");
	quest->addRequireItemId(299, 1);
	quests.push_back(quest);

	quest = new Quest(40, false, false, false, false, -1, -1, -1, -1, -1, "Kiwi frotte s\'y pique", "Vous avez su éviter tous les pièges des Sapeur-kiwis !");
	quest->addRequireItemId(300, 1);
	quests.push_back(quest);

	quest = new Quest(41, false, false, false, false, -1, -1, -1, -1, -1, "Chasseur de Bondissantes", "Vous ne vous êtes pas laissé impressionner par la meute de Bondissantes !");
	quest->addRequireItemId(301, 1);
	quests.push_back(quest);

	quest = new Quest(42, false, false, false, false, -1, -1, -1, -1, -1, "Tronçonneur d\'Ananargeddons", "Vous êtes venu à bout d&apos;un groupe d&apos;Ananargeddons surentraînés !");
	quest->addRequireItemId(302, 1);
	quests.push_back(quest);

	quest = new Quest(43, false, false, false, false, carotte, -1, -1, -1, -1, "Roi de Hammerfest", "Votre persévérance et votre ténacité ont eu raison du sorcier Tuberculoz:\n\t\t\tvous avez retrouvé la carotte de Igor ! Vous débuterez vos prochaines parties\n\t\t\tavec une vie supplémentaire et Igor portera fièrement sa carotte préférée.");
	quest->addRequireItemId(102, 1);
	quests.push_back(quest);

	quest = new Quest(44, false, false, false, false, chapeaux, -1, -1, -1, -1, "Chapelier fou", "Igor s&apos;est découvert une passion nouvelle pour les coiffes. Vous pourrez\n\t\t\tmaintenant appuyer sur la touche &quot;D&quot; pendant la partie pour changer de\n\t\t\tdéguisement !");
	quest->addRequireItemId(72, 5);
	quest->addRequireItemId(91, 5);
	quest->addRequireItemId(92, 10);
	quests.push_back(quest);

	quest = new Quest(45, false, false, false, false, poney, -1, -1, -1, -1, "Poney éco-terroriste", "Igor a accumulé suffisament de richesses pour financer ses activités\n\t\t\tlouches en Hammerfest. Il peut maintenant se déguiser en appuyant sur la\n\t\t\ttouche &quot;D&quot; pendant la partie ! Et sinon, si ca n&apos;est pas déjà fait, avez-vous\n\t\t\tdéjà visité www.dinoparc.com ?");
	quest->addRequireItemId(171, 10);
	quest->addRequireItemId(172, 10);
	quest->addRequireItemId(95, 3);
	quests.push_back(quest);

	quest = new Quest(46, false, false, false, false, pioupiou, -1, -1, -1, -1, "Le Pioupiouz est en toi", "Il fallait s&apos;y attendre: à force de ramasser n&apos;importe quoi, Igor s&apos;est\n\t\t\tfait gober par un Pioupiou ! Appuyez sur la touche &quot;D&quot; pendant la partie\n\t\t\tpour changer de déguisement (au fait, vous connaissiez le site\n\t\t\twww.pioupiouz.com ?)");
	quest->addRequireItemId(112, 1);
	quests.push_back(quest);

	quest = new Quest(47, false, false, false, false, champignon, -1, -1, -1, -1, "Chasseur de champignons", "Comme son homologue italien (plombier de son état), Igor a une passion\n\t\t\tbizarre pour les champignons. Il pourra désormais se déguiser\n\t\t\ten appuyant sur la touche &quot;D&quot; pendant la partie !");
	quest->addRequireItemId(14, 1);
	quest->addRequireItemId(15, 1);
	quest->addRequireItemId(16, 1);
	quest->addRequireItemId(17, 1);
	quests.push_back(quest);

	quest = new Quest(48, false, false, false, false, cape, -1, -1, -1, -1, "Successeur de Tuberculoz", "Igor semble avoir... changé.. Son regard est maintenant plus froid. Il\n\t\t\taffiche une mine sombre et se cache maintenant sous une grande cape\n\t\t\tpourpre. Petit à petit, il devient ce qu&apos;il a combattu... Vous pouvez\n\t\t\tmaintenant revêtir l&apos;apparence du sorcier Tuberculoz en appuyant sur &quot;D&quot;\n\t\t\tpendant la partie !");
	quest->addRequireItemId(113, 1);
	quests.push_back(quest);

	quest = new Quest(49, false, false, false, false, -1, passepartout, -1, -1, -1, "La première clé !", "Igor a trouvé une sorte de Passe-partout en Bois. Nul doute qu&apos;il ouvre\n\t\t\tune porte quelque part dans les cavernes...");
	quest->addRequireItemId(304, 1);
	quests.push_back(quest);

	quest = new Quest(50, false, false, false, false, -1, rigordangerous, -1, -1, -1, "Rigor Dangerous", "Vous avez découvert dans votre aventure une vieille clé rouillée\n\t\t\tmystérieuse ! Elle comporte une petite mention gravée: &quot;Rick&quot;. Sans\n\t\t\tdoute son ancien propriétaire...");
	quest->addRequireItemId(305, 1);
	quests.push_back(quest);

	quest = new Quest(51, false, false, false, false, -1, meluzzine, -1, -1, -1, "La Méluzzine perdue", "La Méluzzine, clé légendaire sortie des vieux contes hammerfestiens,\n\t\t\touvre à ce qu&apos;on raconte la porte de grandes richesses. Reste à savoir où ?");
	quest->addRequireItemId(306, 1);
	quests.push_back(quest);

	quest = new Quest(52, false, false, false, false, -1, bourru, -1, -1, 41, "Enfin le Bourru !", "Cette étrange petite clé sent le vin.");
	quest->addRequireItemId(307, 1);
	quests.push_back(quest);

	quest = new Quest(53, false, false, false, false, -1, furtok, -1, -1, -1, "Congélation", "Bien qu&apos;étant un bonhomme de neige, Igor lui-même a du mal à garder cette clé\n\t\t\ten main, tant le froid qu&apos;elle dégage est intense. La porte qu&apos;elle ouvre\n\t\t\tdonne sûrement sur les endroits les plus reculés de Hammerfest.");
	quest->addRequireItemId(308, 1);
	quests.push_back(quest);

	quest = new Quest(54, false, false, false, false, -1, rouille, -1, -1, -1, "Une clé rouillée", "Ce petit bout de ferraille difforme n&apos;a pas l&apos;air d&apos;avoir une grande valeur.\n\t\t\tMais il faut parfois ce méfier des apparences ! Qui peut savoir quel genre d&apos;aventure\n\t\t\tse cache au delà de la porte qu&apos;elle ouvre ?");
	quest->addRequireItemId(309, 1);
	quests.push_back(quest);

	quest = new Quest(55, false, false, false, false, -1, boisjoli, -1, -1, 42, "Laissez passer !", "Votre toute puissance administrative sera dorénavant appuyée par le formulaire\n\t\t\td&apos;Autorisation du Bois-Joli BJ22a.");
	quest->addRequireItemId(310, 1);
	quests.push_back(quest);

	quest = new Quest(56, false, false, false, false, -1, mondeardus, -1, -1, -1, "Les mondes ardus", "Pour avoir atteint le niveau 50 en mode Cauchemar, vous avez gagné la Clé\n\t\t\tdes Mondes Ardus.");
	quest->addRequireItemId(311, 1);
	quests.push_back(quest);

	quest = new Quest(57, false, false, false, false, -1, piquante, -1, -1, -1, "Viiiite !", "Sans trop savoir pourquoi, la Clé Piquante que vous avez trouvé vous donne une\n\t\t\tfolle envie de courir partout et de vous rouler en boule.");
	quest->addRequireItemId(312, 1);
	quests.push_back(quest);

	quest = new Quest(58, false, false, false, false, -1, passetuberculoz, -1, -1, -1, "Faire les poches à Tubz", "Tuberculoz, le vilain sorcier, portait sur lui une clé...");
	quest->addRequireItemId(313, 1);
	quests.push_back(quest);

	quest = new Quest(59, false, false, false, false, -1, chauchemar, -1, -1, -1, "Tuberculoz, seigneur des enfers", "Votre toute puissance et votre maîtrise absolue des techniques de combat de\n\t\t\tHammerfest vous ont permi de gagner une clé unique en terrassant Tuberculoz\n\t\t\ten mode Cauchemar !");
	quest->addRequireItemId(314, 1);
	quests.push_back(quest);

	quest = new Quest(60, false, false, false, false, -1, -1, -1, -1, -1, "L\'eau ferrigineuneuse", "Votre excès dans la consommation de boissons alcoolisées vous a permis de\n\t\t\tdébloquer la Clé du Bourru ! Vous aurez maintenant de bonnes chances de la\n\t\t\ttrouver au cours de vos explorations.");
	quest->addRequireItemId(323, 20);
	quest->addRequireItemId(324, 10);
	quest->addRequireItemId(325, 5);
	quest->addRequireItemId(326, 3);
	quest->addRequireItemId(327, 2);
	quests.push_back(quest);

	quest = new Quest(61, false, false, false, false, -1, -1, -1, -1, -1, "Paperasse administrative", "Igor est un maître dans l&apos;art de remplir des formulaires administratifs.\n\t\t\tIl trouvera donc sans problème bientôt l&apos;Autorisation du Bois-Joli dans\n\t\t\tles dédales des cavernes...");
	quest->addRequireItemId(328, 10);
	quest->addRequireItemId(329, 15);
	quest->addRequireItemId(330, 3);
	quest->addRequireItemId(331, 2);
	quest->addRequireItemId(332, 1);
	quests.push_back(quest);

	quest = new Quest(62, false, false, false, false, -1, -1, boost, -1, -1, "Meilleur joueur", "Le meilleur joueur du net, c&apos;est vous, plus personne n&apos;a de doute là dessus !\n\t\t\tVotre collection de manettes de jeu fera sans nul doute des envieux ^^\n\t\t\tIgor dispose maintenant de l&apos;option Tornade qui procure un boost de vitesse\n\t\t\tau début de chaque partie, quelques soient les options choisies !");
	quest->addRequireItemId(315, 1);
	quest->addRequireItemId(316, 1);
	quest->addRequireItemId(317, 1);
	quest->addRequireItemId(318, 1);
	quest->addRequireItemId(319, 1);
	quest->addRequireItemId(320, 1);
	quest->addRequireItemId(321, 1);
	quest->addRequireItemId(322, 1);
	quests.push_back(quest);

	quest = new Quest(63, false, false, false, false, -1, -1, mirror, -1, -1, "Miroir, mon beau miroir", "Le Miroir Bancal que vous avez trouvé en jeu vous permet maintenant de voir les choses\n\t\t\tsous un angle nouveau. L&apos;option de jeu &quot;Miroir&quot; a été débloquée !");
	quest->addRequireItemId(333, 1);
	quests.push_back(quest);

	quest = new Quest(64, false, false, false, false, -1, -1, nightmare, -1, -1, "Mode cauchemar", "Vous êtes doué. Surement très doué même... Mais saurez-vous aider Igor en mode Cauchemar ?\n\t\t\tCette option a été débloquée !");
	quest->addRequireItemId(334, 1);
	quests.push_back(quest);

	quest = new Quest(65, false, false, false, false, -1, gordon, -1, -1, -1, "L\'aventure continue !", "Le conseil des Carotteux vous a choisi pour explorer plus en avant les cavernes de Hammerfest.\n\t\t\tLa Clé de Gordon est une première étape dans cette nouvelle mission.");
	quest->addRequireItemId(117, 1);
	quests.push_back(quest);

	quest = new Quest(66, false, false, false, false, -1, -1, kickcontrol, -1, -1, "Joyau d\'Ankhel", "Vous avez fait preuve d&apos;une dextérité et d&apos;une perspicacité sans égal en retrouvant le Joyau\n\t\t\td&apos;Ankhel. L&apos;option Controle du Ballon a été débloquée pour le mode SoccerFest !");
	quest->addRequireItemId(116, 1);
	quests.push_back(quest);

	quest = new Quest(67, false, false, false, false, -1, -1, -1, multicoop, 48, "Sandy commence l\'aventure !", "Tous les éléments sont réunis pour donner naissance à Sandy, le bonhomme de sable !\n\t\t\tCe nouveau personnage pourra se joindre à vous dans le mode Multi Coopératif,\n\t\t\tjouable à deux sur le même ordinateur. Re-découvrez la grande aventure avec un ami !");
	quest->addRequireItemId(334, 5);
	quest->addRequireItemId(336, 10);
	quest->addRequireItemId(337, 5);
	quest->addRequireItemId(338, 3);
	quests.push_back(quest);

	quest = new Quest(68, false, false, false, false, -1, -1, mirrormulti, -1, -1, "Miroir, NOTRE beau miroir", "Avec le Miroir des Sables, vous pouvez maintenant voir les choses sous un angle nouveau\n\t\t\tmais à deux ! L&apos;option de jeu &quot;Miroir&quot; a été débloquée pour le mode Multi Coopératif !");
	quest->addRequireItemId(339, 1);
	quests.push_back(quest);

	quest = new Quest(69, false, false, false, false, -1, -1, nightmaremulti, -1, -1, "Mode double cauchemar", "De toute évidence, vous êtes capables de grandes choses à deux ! L&apos;option de jeu &quot;Cauchemar&quot;\n\t\t\ta été débloquée pour le mode Multi Coopératif !");
	quest->addRequireItemId(340, 1);
	quests.push_back(quest);

	quest = new Quest(70, false, false, false, false, -1, -1, lifesharing, -1, -1, "Une grande Amitié",
			"Mieux vaut tard que jamais ! Igor et Sandy ont enfin compris qu&apos;il valait mieux s&apos;entraider\n\t\t\ts&apos;ils voulaient survivre à deux dans les Cavernes de Hammerfest. L&apos;option de jeu &quot;Partage de vies&quot;\n\t\t\ta été débloquée pour le mode Multi Coopératif ! Si cette option est activée, lorsqu&apos;un joueur\n\t\t\tperd sa dernière vie, il en prend une au second joueur et peut ainsi continuer la partie !");
	quest->addRequireItemId(341, 2);
	quests.push_back(quest);

	quest = new Quest(71, false, false, false, false, -1, -1, -1, -1, -1, "Apprentissage des canifs volants", "A toujours sauter partout, Igor a fini par acquérir une souplesse digne d&apos;un ninja et une\n\t\t\tdextérité hors du commun ! Mais pour prouver sa valeur, il doit maintenant collecter les\n\t\t\tartefacts ninjas dispersés en Hammerfest !");
	quest->addRequireItemId(342, 1);
	quests.push_back(quest);

	quest = new Quest(72, false, false, false, false, -1, -1, ninja, -1, -1, "Shinobi do !", "Igor a rempli sa quêté initiatique et maîtrise maintenant à la perfection un grand\n\t\t\tnombre d&apos;armes du Ninjutsu ! Mais comme son nouveau de l&apos;honneur le lui interdit, il ne\n\t\t\tpourra pas s&apos;en servir. Toutefois, il pourra mettre à l&apos;épreuve ses compétences grâce\n\t\t\tà l&apos;option de jeu &quot;Ninjutsu&quot; qu&apos;il vient de débloquer pour le mode Aventure !");
	quest->addRequireItemId(343, 5);
	quest->addRequireItemId(344, 2);
	quest->addRequireItemId(345, 7);
	quest->addRequireItemId(346, 7);
	quest->addRequireItemId(347, 1);
	quest->addRequireItemId(348, 1);
	quest->addRequireItemId(349, 1);
	quests.push_back(quest);

	quest = new Quest(73, false, false, false, false, -1, -1, timeattack, timeattack, -1, "Rapide comme l\'éclair !", "Igor est imbattable dès lors qu&apos;il s&apos;agit de viser juste et se déplacer avec précision...\n\t\t\tIl faut maintenant le prouver aux autres ! Le mode TIME ATTACK est débloqué et vous ouvre\n\t\t\ten plus l&apos;accès à un nouveau classement sur le site. Soyez le bonhomme de neige le\n\t\t\tplus rapide de tout Hammerfest !");
	quest->addRequireItemId(350, 100);
	quests.push_back(quest);

	quest = new Quest(74, false, false, false, false, -1, -1, bombexpert, -1, -1, "Maître des Bombes", "Vous êtes l&apos;expert réputé dans tout Hammerfest en matière d&apos;explosifs. Et pour montrer\n\t\t\tqu&apos;on ne vous ne la fait pas, à vous, l&apos;option &quot;Explosifs instables&quot; a été débloquée\n\t\t\tpour le mode Aventure ! Gare à TOUT ce qui explose en jeu ! De plus, vous pouvez pousser\n\t\t\ttoutes vos bombes plus loin en avançant en même temps que vous la frappez.");
	quest->addRequireItemId(351, 1);
	quests.push_back(quest);

	quest = new Quest(75, false, false, false, false, -1, passpyramide, -1, -1, -1, "Tombeau de Tuberculoz", "Vous avez découvert une étrange pyramide de poche dans le tombeau de Tuberculoz.");
	quest->addRequireItemId(352, 1);
	quests.push_back(quest);

	for (unsigned int i = 0; i < quests.size(); i++) {
		quests[i]->printName();
		}
}
