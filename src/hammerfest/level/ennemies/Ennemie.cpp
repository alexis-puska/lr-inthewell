#include "Ennemie.h"
#include "../../level/Level.h"

Ennemie::Ennemie(int id, int x, int y, int type, Level * level) :
	Position((x * 20) + 10, (y * 20) + 20), Drawable(), HitBox(), IdElement(id) {
	this->type = type;
	this->animIdx = 0;
	this->state = walk;
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

Ennemie::~Ennemie() {
}

void Ennemie::doSomething(SDL_Surface * dest, std::vector<Player *> players) {
}

void Ennemie::drawHimself(SDL_Surface * sprite, SDL_Surface * dest) {
	copySurfaceToBackRenderer(sprite, dest, (x - (sprite->w / 2)) + leftPadding, y - (sprite->h));
	updateHitBox(x - (int)floor(ennemieHitboxWidth / 2), y - ennemieHitboxHeight);
	/*SDL_Rect * rect = new SDL_Rect;
	rect->h = this->getRect().h;
	rect->w = this->getRect().w;
	rect->x = this->getRect().x + leftPadding;
	rect->y = this->getRect().y;
	SDL_FillRect(dest, rect, SDL_MapRGB(dest->format, 255, 0, 0));
	*/
	animIdx++;
}

std::string Ennemie::getStateString() {
	std::stringstream ss;
	ss << ennemieTypeString[this->type] << "_" << ennemieStateString[this->state];
	if (direction == left) {
		ss << "_flip";
	}
	return ss.str();
}

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

bool Ennemie::isOnEdge() {
	bool * grid = level->getPlatformGrid();
	if (direction == left) {
		return !grid[getGidPosition(-1) + 20];
	}
	else {
		return !grid[getGidPosition(1) + 20];
	}
}

bool Ennemie::isOnStairStep() {
	bool * grid = level->getPlatformGrid();
	if (direction == left) {
		return !grid[getGidPosition(-1) + 20] && grid[getGidPosition(-1) + 40];
	}
	else {
		return !grid[getGidPosition(1) + 20] && grid[getGidPosition(1) + 40];
	}
}

bool Ennemie::touchWall() {
	bool * grid = level->getPlatformGrid();
	if (getX() - 10 < 0) {
		return true;
	}
	else if (getX() + 10 > 400) {
		return true;
	}
	if (direction == left) {
		return grid[getGidPosition(-10)];
	}
	else {
		return grid[getGidPosition(10)];
	}
}


bool Ennemie::touchStairStep() {
	bool * grid = level->getPlatformGrid();
	//bord de l'écran
	if (getX() - 10 < 0) {
		return false;
	}
	else if (getX() + 10 > 400) {
		return false;
	}

	if (direction == left) {
		return grid[getGidPosition(-10)] && !grid[getGidPosition(-10) - 20];
	}
	else {
		return grid[getGidPosition(10)] && !grid[getGidPosition(10) + 20];
	}
}


bool Ennemie::plateformFrontMe() {
	bool * grid = level->getPlatformGrid();
	if (direction == left) {
		return grid[getGidPosition(0) + 17];
	}
	else {
		return grid[getGidPosition(0) + 23];
	}
}

bool Ennemie::onEdgePlateformBelowMe() {
	return false;
}

bool Ennemie::plateformAboveMe() {
	return false;
}

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

//dessous
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

void Ennemie::makeShot() {
}

void Ennemie::rumbleLevel() {
}

int Ennemie::getGidPosition(int offset) {
	int column = floor((getX() + offset) / 20);
	int line = floor(getY() / 20);
	if (line >= 1) {
		line -= 1;
	}
	return (line * 20) + column;
}
