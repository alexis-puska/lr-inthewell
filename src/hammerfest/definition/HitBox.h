#include <stdio.h>

#ifndef __MYCLASS_HITBOX
#define __MYCLASS_HITBOX

class HitBox {
	public:
		HitBox();
		void initHitBox(int x, int y, int width, int height);
		virtual ~HitBox();
		void updateHitBox(int x, int y);
		bool hit(HitBox other);
		int getXMin();
		int getXMax();
		int getYMin();
		int getYMax();
	private:
		int yMax;
		int yMin;
		int xMax;
		int xMin;
		int hitBoxWidth;
		int hitBoxHeight;
};

#endif
