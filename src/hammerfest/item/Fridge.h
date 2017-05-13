#ifndef __MYCLASS_FRIDGE
#define __MYCLASS_FRIDGE

#include <Map>

class Fridge {
	public:
		Fridge();
		~Fridge();
	private:
		std::map <int, int> items;
};
#endif
