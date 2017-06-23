#ifndef __MYCLASS_ID_ELEMENT
#define __MYCLASS_ID_ELEMENT

class IdElement {
	public:
		IdElement(int id);
		virtual ~IdElement();
		int getId();
	protected:
		int id;
};

#endif
