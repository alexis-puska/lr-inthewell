#ifndef __MYCLASS_PLATFORM
#define __MYCLASS_PLATFORM

#include "../definition/Drawable.h"
#include "../definition/Position.h"
#include "../definition/IdElement.h"
#include "../definition/HitBox.h"

#define gridSize 20
#define shadowPlatformValue 70

class Platform : public Drawable, public Position, public IdElement, public HitBox
{
  public:
	Platform(int id, int x, int y, bool vertical, bool visible, int length, int surfaceId);
	~Platform();
	void drawHimself(SDL_Surface *surface);
	void drawHimself(SDL_Surface *surface, bool drawShadow);
	bool isVertical();
	int getLength();

  private:
	bool vertical;
	bool visible;
	int length;
	int surfaceId;
};
#endif
