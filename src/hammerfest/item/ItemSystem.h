#ifndef __MYCLASS_ITEM_SYSTEM
#define __MYCLASS_ITEM_SYSTEM


class ItemSystem {
	public:
		ItemSystem();
		~ItemSystem();
		void loadAccount(char * saveFile, int accountId);
		int saveAccount();
		int getItemId();
	private:

};
#endif


/*
	<give option=\"boost\"/>
	<give option=\"mirror\"/>
	<give option=\"nightmare\"/>
	<give option=\"kickcontrol\"/>
	<give mode=\"multicoop\"/>
	<give option=\"mirrormulti\"/>
	<give option=\"nightmaremulti\"/>
	<give option=\"lifesharing\"/>
	<give option=\"ninja\"/>
	<give mode=\"timeattack\"/>
	<give option=\"set_ta_0\"/>
	<give option=\"bombexpert\"/>
*/