#include "Ennemie.h"
#include "../../level/Level.h"

Ennemie::Ennemie(int id, int x, int y, int type, Level * level) :
	Position((x * 20) + 10, (y * 20) + 20), Drawable(), HitBox(), IdElement(id) {
	this->type = type;
	this->animIdx = 0;
	this->state = angry;
	if (type == scie && state == angry) {
		this->state = walk;
	}
	else if (type == bombinos && state == angry) {
		this->state = walk;
	}
	this->level = level;
	direction = left;
	initHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight, ennemieHitboxWidth, ennemieHitboxHeight);
}

Ennemie::~Ennemie() {}
void Ennemie::doSomething(SDL_Surface * dest, std::vector<Player *> players) {}
void Ennemie::iMove(){}

/*
 * Dessine l'ennemie
 */
void Ennemie::drawHimself(SDL_Surface * sprite, SDL_Surface * dest) {
	copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y - (sprite->h));
	updateHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight);
	SDL_Rect * rect = new SDL_Rect;
	rect->h = this->getRect().h;
	rect->w = this->getRect().w;
	rect->x = this->getRect().x + leftPadding;
	rect->y = this->getRect().y;
	SDL_FillRect(dest, rect, SDL_MapRGB(dest->format, 255, 0, 0));
	
	animIdx++;
}

/*
 * retourne le sprite correspondant au type d'ennemie et de son �tat.
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
 * effectue un d�placement de l'ennemie
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
		if (direction == left) {
			this->setX(getX() - ennemieSpeed);
		}
		else {
			this->setX(getX() + ennemieSpeed);
		}
	}
}

/*
 * ennemis au bord d'une plateforme, fonction qui renseigne si l'ennemis � une plateforme devant lui et peut sauter de 2 cases.
 */
bool Ennemie::plateformFrontMe() {
	if (direction == left) {
		return getGridValue(getGidPosition(0) + 17);
	}
	else {
		return getGridValue(getGidPosition(0) + 23);
	}
}

/*
 * D�termine si l'ennemis touche : 
 * - un mur
 * - devant un escalier
 * - en haut d'un escalier
 * - au bord d'une plateform
 * - peut sauter de la plateforme
 * - si il n'y a rien de sp�cifique devant l'ennemis
 */
int Ennemie::whatITouch() {
	//Bordure de l'�cran
	if (getX() - 10 < 0) {
		return wall;
	}
	else if (getX() + 10 > 400) {
		return wall;
	}

	if (direction == left) {
		if (!getGridValue(getGidPosition(-5))) {
			if (!getGridValue(getGidPosition(-5) + 20) && !getGridValue(getGidPosition(-5) + 40)) {
				if (searchPlatformBelow(getGidPosition(-5))) {
					return edgeCanJump;
				}
				else {
					return edge;
				}
			}
			else if (!getGridValue(getGidPosition(-5) + 20) && getGridValue(getGidPosition(-5) + 40)) {
				return topStaires;
			}
			return nothing;
		}
		else if (getGridValue(getGidPosition(-5)) && getGridValue(getGidPosition(-10) - 20)) {
			return wall;
		}
		else if (getGridValue(getGidPosition(-5)) && !getGridValue(getGidPosition(-10) - 20)) {
			return bottomStairs;
		}
	}
	else {
		if (!getGridValue(getGidPosition(5))) {
			if (!getGridValue(getGidPosition(5) + 20) && !getGridValue(getGidPosition(5) + 40)) {
				if (searchPlatformBelow(getGidPosition(5) + 40)) {
					return edgeCanJump;
				}
				else {
					return edge;
				}
			}
			else if (!getGridValue(getGidPosition(5) + 20) && getGridValue(getGidPosition(5) + 40))
			{
				return topStaires;
			}
			return nothing;
		}
		else if (getGridValue(getGidPosition(5)) && getGridValue(getGidPosition(10) - 20)) {
			return wall;
		}
		else if (getGridValue(getGidPosition(5)) && !getGridValue(getGidPosition(10) - 20)) {
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
 * calcule la case de la grille par rapport � la position de l'enemie en pixel. inclus un d�calage sur l'axe X
 */
int Ennemie::getGidPosition(int offset) {
	int column = floor((getX() + offset) / 20);
	int line = floor(getY() / 20);
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
 * retourne l'�tat d'une plateforme
 */
bool Ennemie::getGridValue(int cell) {
	if (cell < 0) {
		//ahut de l'�cran donc mur, evite que l'�nemie se barre de l'�cran
		return true;
	}
	else if (cell >= 500) {
		//bas de l'�cran donc vide, evite que l'ennemie ne saute et ce suicide
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

