#ifndef __MYCLASS_POSITION
#define __MYCLASS_POSITION

class Position
{
  public:
	int getX();
	int getY();
	void setX(int x);
	void setY(int y);
	Position(int x, int y);
	virtual ~Position();

  protected:
	int x;
	int y;
};

#endif
