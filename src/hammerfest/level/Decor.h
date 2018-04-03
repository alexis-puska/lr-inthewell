#ifndef __MYCLASS_DECOR
#define __MYCLASS_DECOR

#include "../definition/Drawable.h"
#include "../definition/IdElement.h"
#include "../definition/Position.h"

class Decor : public Drawable, public Position, public IdElement
{
  public:
	Decor(int id, int x, int y, bool displayed, bool background, std::string animation, int indexAnimation);
	~Decor();
	void display();
	bool isOnBackground();
	std::string getAnimation();
	void drawHimself(SDL_Surface *dest);

  private:
	bool displayed;
	bool background;
	std::string animation;
	int indexAnimation;
};
#endif
