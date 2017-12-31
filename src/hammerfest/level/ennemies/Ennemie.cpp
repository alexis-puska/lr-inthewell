#include "Ennemie.h"
#include "../../level/Level.h"

static const int decelerate[tableSize] = { 10, 5, 3, 2 };
static const int accelerate[tableSize] = { 2, 3, 5, 10 };

Ennemie::Ennemie(int id, int x, int y, int type, Level * level) :
	Position((x * 20) + 10, (y * 20) + 20), Drawable(), HitBox(), IdElement(id) {
	std::srand((int)std::time(NULL));
	this->type = type;
	isAngry = false;
	changeState(walk);
	this->level = level;
	direction = left;
	initHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight, ennemieHitboxWidth, ennemieHitboxHeight);
}

Ennemie::~Ennemie() {}
void Ennemie::doSomething(SDL_Surface * dest, std::vector<Player *> players) {}
void Ennemie::iMove() {}

/*
 * Dessine l'ennemie
 */
void Ennemie::drawHimself(SDL_Surface * sprite, SDL_Surface * dest) {
	copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y - (sprite->h));
	updateHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight);
	/*
	SDL_Rect * rect = new SDL_Rect;
	rect->h = this->getRect().h;
	rect->w = this->getRect().w;
	rect->x = this->getRect().x + leftPadding;
	rect->y = this->getRect().y;
	SDL_FillRect(dest, rect, SDL_MapRGB(dest->format, 255, 0, 0));
	*/
	animIdx++;
}

/*
 * change Žtat de l'ennemie
 */
void Ennemie::changeState(int newState) {
	this->state = newState;
	this->animIdx = 0;
	this->animIdxMax = Sprite::Instance().getAnimationSize(getStateString());
}

/*
 * retourne le sprite correspondant au type d'ennemie et de son Žtat.
 */
std::string Ennemie::getStateString() {
	std::stringstream ss;
	ss << ennemieTypeString[this->type] << "_" << ennemieStateString[this->state];
	if (direction == left) {
		ss << "_flip";
	}
	return ss.str();
}

/*
 * effectue un dŽplacement de l'ennemie
 */
void Ennemie::move() {
	if (state == angry) {
		if (direction == left) {
			this->setX(getX() - ennemieAngrySpeed);
		}
		else {
			this->setX(getX() + ennemieAngrySpeed);
		}
	}
	else {
		if (getY() % 20 != 0 && state == walk) {
			std::cout << "warn alignement ennemie" << getY() % 20 << "\n";
		}
		if (direction == left) {
			this->setX(getX() - ennemieSpeed);
		}
		else {
			this->setX(getX() + ennemieSpeed);
		}
	}
}

/*
 * ennemis au bord d'une plateforme, fonction qui renseigne si l'ennemis ˆ une plateforme devant lui et peut sauter de 2 cases.
 */
bool Ennemie::plateformFrontMe() {
	if (direction == left && getGridPositionX(0) % 20 > 3) {
		return getGridValue(getGridPositionX(0) + 17) && !getGridValue(getGridPositionX(0) - 3);
	}
	else if (direction == right && getGridPositionX(0) % 20 < 17){
		return getGridValue(getGridPositionX(0) + 23) && !getGridValue(getGridPositionX(0) + 3);
	}
	return false;
}

int Ennemie::getStepSize() {
	if (direction == left) {
		if (getGridValue(getGridPositionX(-5)) && getGridValue(getGridPositionX(-10) - 20) && getGridValue(getGridPositionX(-10) - 40) && getGridValue(getGridPositionX(-10) - 60)) {
			return 3;
		}
		else {
			return 2;
		}
	}
	else {
		if (getGridValue(getGridPositionX(5)) && getGridValue(getGridPositionX(10) - 20) && getGridValue(getGridPositionX(10) - 40) && getGridValue(getGridPositionX(10) - 60)) {
			return 3;
		}
		else {
			return 2;
		}
	}
}


int Ennemie::plateformAbove() {
	if (getY() <= 440 && getY() >= 60 && getGridValue(getGridPositionX(0) - 20) && !getGridValue(getGridPositionX(0) - 40)) {
		return 2;
	}
	else if (getY() <= 420 && getY() >= 80 && getGridValue(getGridPositionX(0) - 40) && !getGridValue(getGridPositionX(0) - 60)) {
		return 3;
	}
	else {
		return -1;
	}
}

int Ennemie::plateformBelow() {
	if (getY() >= 60 && getY() <= 440 && getGridValue(getGridPositionX(0) + 60) && !getGridValue(getGridPositionX(0) + 40)) {
		return 2;
	}
	else if (getY() >= 80 && getY() <= 420 && getGridValue(getGridPositionX(0) + 80) && !getGridValue(getGridPositionX(0) + 60) && !getGridValue(getGridPositionX(0) + 40)) {
		return 3;
	}
	else {
		return -1;
	}
}

/*
 * DŽtermine si l'ennemis touche :
 * - un mur
 * - devant un escalier
 * - en haut d'un escalier
 * - au bord d'une plateform
 * - peut sauter de la plateforme
 * - si il n'y a rien de spŽcifique devant l'ennemis
 */
int Ennemie::whatITouch() {
	//Bordure de l'Žcran
	if (getX() - 10 < 0) {
		return wall;
	}
	else if (getX() + 10 > 400) {
		return wall;
	}

	if (direction == left) {
		if (!getGridValue(getGridPositionX(-5))) {
			if (!getGridValue(getGridPositionX(-5) + 20) && !getGridValue(getGridPositionX(-5) + 40)) {
				if (searchPlatformBelow(getGridPositionX(-5))) {
					return edgeCanJump;
				}
				else {
					return edge;
				}
			}
			else if (!getGridValue(getGridPositionX(-5) + 20) && getGridValue(getGridPositionX(-5) + 40)) {
				return topStaires;
			}
			return nothing;
		}
		else if (getGridValue(getGridPositionX(-5)) && getGridValue(getGridPositionX(-10) - 20) && getGridValue(getGridPositionX(-10) - 40) && getGridValue(getGridPositionX(-10) - 60)) {
			return wall;
		}
		else if ((getGridValue(getGridPositionX(-5)) && getGridValue(getGridPositionX(-10) - 20) && !getGridValue(getGridPositionX(-10) - 40) && !getGridValue(getGridPositionX(-10) - 60))
			|| (getGridValue(getGridPositionX(-5)) && getGridValue(getGridPositionX(-10) - 20) && getGridValue(getGridPositionX(-10) - 40) && !getGridValue(getGridPositionX(-10) - 60))) {
			return bottomHighStairs;
		}
		else if (getGridValue(getGridPositionX(-5)) && !getGridValue(getGridPositionX(-10) - 20)) {
			return bottomStairs;
		}
	}
	else {
		if (!getGridValue(getGridPositionX(5))) {
			if (!getGridValue(getGridPositionX(5) + 20) && !getGridValue(getGridPositionX(5) + 40)) {
				if (searchPlatformBelow(getGridPositionX(5) + 40)) {
					return edgeCanJump;
				}
				else {
					return edge;
				}
			}
			else if (!getGridValue(getGridPositionX(5) + 20) && getGridValue(getGridPositionX(5) + 40))
			{
				return topStaires;
			}
			return nothing;
		}
		else if (getGridValue(getGridPositionX(5)) && getGridValue(getGridPositionX(10) - 20) && getGridValue(getGridPositionX(10) - 40) && getGridValue(getGridPositionX(10) - 60)) {
			return wall;
		}
		else if ((getGridValue(getGridPositionX(5)) && getGridValue(getGridPositionX(10) - 20) && !getGridValue(getGridPositionX(10) - 40) && !getGridValue(getGridPositionX(10) - 60))
			|| (getGridValue(getGridPositionX(5)) && getGridValue(getGridPositionX(10) - 20) && getGridValue(getGridPositionX(10) - 40) && !getGridValue(getGridPositionX(10) - 60))) {
			return bottomHighStairs;
		}
		else if (getGridValue(getGridPositionX(5)) && !getGridValue(getGridPositionX(10) - 20)) {
			return bottomStairs;
		}
	}
	return wall;
}

/*
 * joueur devant ennemie
 */
bool Ennemie::playerFrontOfMe(std::vector<Player *> players) {
	int yMax = getY();
	int yMin = yMax - 20;
	for (unsigned int i = 0; i < players.size(); i++) {
		int playerY = players[i]->getY();
		int playerX = players[i]->getX();
		if (playerY >= yMin &&playerY <= yMax) {
			if (direction == left && playerX < getX()) {
				return true;
			}
			else if (direction == right && playerX > getX()) {
				return true;
			}
		}
	}
	return false;
}
/*
 * joueur au dessus
 */
bool Ennemie::playerBelowMe(std::vector<Player *> players) {
	int xMin = getX() - 10;
	int xMax = getX() + 10;
	for (unsigned int i = 0; i < players.size(); i++) {
		int playerY = players[i]->getY();
		int playerX = players[i]->getX();
		if (playerX >= xMin &&playerX <= xMax && playerY > getY()) {
			return true;
		}
	}
	return false;
}

/*
 * joueur en dessous
 */
bool Ennemie::playerAboveMe(std::vector<Player *> players) {
	int xMin = getX() - 10;
	int xMax = getX() + 10;
	for (unsigned int i = 0; i < players.size(); i++) {
		int playerY = players[i]->getY();
		int playerX = players[i]->getX();
		if (playerX >= xMin &&playerX <= xMax && playerY < getY()) {
			return true;
		}
	}
	return false;
}

/*
 * calcule la case de la grille par rapport ˆ la position de l'enemie en pixel. inclus un dŽcalage sur l'axe X
 */
int Ennemie::getGridPositionX(int offset) {
	int column = (int)floor((getX() + offset) / 20);
	int line = (int)floor(getY() / 20);
	if (line >= 1) {
		line -= 1;
	}
	return (line * 20) + column;
}

int Ennemie::getGridPositionY(int offset) {
	int column = (int)floor((getX()) / 20);
	int line = (int)floor((getY() + offset) / 20);
	if (line >= 1) {
		line -= 1;
	}
	return (line * 20) + column;
}

/*
 * Changement de direction de l'ennemie
 */
void Ennemie::changeDirection() {
	if (direction == left) {
		direction = right;
	}
	else {
		direction = left;
	}
}

/*
 * retourne l'Žtat d'une plateforme
 */
bool Ennemie::getGridValue(int cell) {
	if (cell < 0) {
		//ahut de l'écran donc mur, evite que l'énemie se barre de l'écran
		return true;
	}
	else if (cell >= 500) {
		//bas de l'écran donc vide, evite que l'ennemie ne saute et ce suicide
		return false;
	}
	else {
		return level->getPlatformGrid()[cell];
	}
}

/*
 * recherche une plateforme en dessous de l'enemie
 */
bool Ennemie::searchPlatformBelow(int cell) {
	int y = cell;
	while (y < 500) {
		if (level->getPlatformGrid()[y]) {
			return true;

		}
		y += 20;
	}
	return false;
}

/*
 *initialise un saut
 */
void Ennemie::initJump(int direction, int distance) {
	this->jumpDistance = distance;
	this->jumpDirection = direction;
	this->jumpCycle = 0;
}

/*
 * effectue un saut
 */
void Ennemie::ennemieJump() {
	if (jumpDirection == up) {
		//saute en l'air
		if (jumpDistance == 1) {
			//saute une marche
			setY(getY() - decelerate[jumpCycle]);
			if (jumpCycle >= 3) {
				move();
				changeState(isAngry ? angry : walk);
				return;
			}
		}
		else if (jumpDistance == 2) {
			//saute sur une palteforme
			if (jumpCycle < 2) {
				setY(getY() - 10);
			}
			else {
				setY(getY() - decelerate[jumpCycle - 2]);
				if (jumpCycle == 5) {
					changeState(isAngry ? angry : walk);
					return;
				}
			}
		}
		else if (jumpDistance == 3) {
			if (jumpCycle < 4) {
				setY(getY() - 10);
			}
			else {
				setY(getY() - decelerate[jumpCycle - 4]);
				if (jumpCycle == 7) {
					changeState(isAngry ? angry : walk);
					return;
				}
			}
		}
	}
	else if (jumpDirection == down) {
		//saut vers plateform en dessous ou tombe d'une plateform

		if (jumpDistance == 2) {
			//saute sur une palteforme
			if (jumpCycle < 5) {
				setY(getY() + jumpCycle);
			}
			else {
				setY(getY() + 5);
				if (jumpCycle == 10) {
					changeState(isAngry ? angry : walk);
					return;
				}
			}
		}
		else if (jumpDistance == 3) {
			if (jumpCycle < 5) {
				setY(getY() + jumpCycle);
			}
			else {
				setY(getY() + 5);
				if (jumpCycle == 14) {
					changeState(isAngry ? angry : walk);
					return;
				}
			}
		}
		else {
			if (jumpCycle < 5) {
				if (jumpCycle <= 2) {
					move();
				}
				setY(getY() + jumpCycle);
			}
			else {
				setY(getY() + 5);
				if (getGridValue(getGridPositionY(1) + 20)) {
					changeState(isAngry ? angry : walk);
					return;
				}
			}
		}
	}
	else if (jumpDirection == left) {
		//saute sur une platforme à gauche
		setX(getX() - 5);
		if (jumpCycle >= 8) {
			changeState(isAngry ? angry : walk);
			return;
		}
		else {
			if (jumpCycle < 4) {
				setY(getY() - decelerate[jumpCycle]);
			}
			else {
				setY(getY() + accelerate[jumpCycle - 4]);
			}
		}
	}
	else if (jumpDirection == right) {
		//saute sur une plateforme à droite
		setX(getX() + 5);
		if (jumpCycle >= 8) {
			changeState(isAngry ? angry : walk);
			return;
		}
		else {
			if (jumpCycle < 4) {
				setY(getY() - decelerate[jumpCycle]);
			}
			else {
				setY(getY() + accelerate[jumpCycle - 4]);
			}
		}
	}
	jumpCycle++;
}

bool Ennemie::choice(int mod) {
	return std::rand() % mod == 0;
}

int Ennemie::getGridPosition(int posX, int posY) {
    int column = (int)floor(posX / 20);
    int line = (int)floor(posY / 20);
    return (line * 20) + column;
}