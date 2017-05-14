#ifndef __MYCLASS_ITEM_FILE_SYSTEM
#define __MYCLASS_ITEM_FILE_SYSTEM

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <map>

#include "Family.h"
#include "Quest.h"
#include "Item.h"

// Score + nb of game + level reached + 353 item
#define nbOfValueInFile 357

class ItemFileSystem {
	public:
		static ItemFileSystem& Instance();

		ItemFileSystem();
		~ItemFileSystem();
		void init(char * saveFile, bool newSaveFile);
		int loadAccount(int accountId);
		void save(int score, bool gamePlayed, int level);
	private:

		ItemFileSystem& operator=(const ItemFileSystem&);
		ItemFileSystem(const ItemFileSystem&);
		static ItemFileSystem m_instance;

		void buildDatabase();


		int accountId;
		char saveFilePath[255];
		FILE* saveFile;

		int accountLoaded;
		int scoreMax;
		int scoreLastGame;
		int nbGame;
		int levelReached;
		std::map<int, int> fridge;

		std::vector<Family *> familys;
		std::vector<Quest *> quests;
		std::vector<Item *> items;
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



<quest id="0">
		<require item="40" qty="1"/>
		<require item="41" qty="1"/>
		<require item="42" qty="1"/>
		<require item="43" qty="1"/>
		<require item="44" qty="1"/>
		<require item="45" qty="1"/>
		<require item="46" qty="1"/>
		<require item="47" qty="1"/>
		<require item="48" qty="1"/>
		<require item="49" qty="1"/>
		<require item="50" qty="1"/>
		<require item="51" qty="1"/>
		??<give family="100"/>
		<give family="6"/>
		<remove family="5"/>
	</quest>
	<quest id="1">
		<require item="52" qty="1"/>
		<require item="53" qty="1"/>
		<require item="54" qty="1"/>
		<require item="55" qty="1"/>
		<require item="56" qty="1"/>
		<require item="57" qty="1"/>
		<require item="58" qty="1"/>
		<require item="59" qty="1"/>
		<require item="60" qty="1"/>
		<require item="61" qty="1"/>
		<require item="62" qty="1"/>
		<require item="63" qty="1"/>
		??<give family="101"/>
		<remove family="6"/>
	</quest>
	<quest id="2">
		<require item="103" qty="1"/>
		??<give family="102"/>
		<remove family="7"/>
	</quest>
	<quest id="3">
		<require item="104" qty="1"/>
		??<give family="103"/>
		<give family="9"/>
		<remove family="8"/>
	</quest>
	<quest id="4">
		<require item="105" qty="1"/>
		??<give family="104"/>
		<remove family="9"/>
	</quest>
	<quest id="5">
		<require item="36" qty="5"/>
		??<give family="105"/>
	</quest>
	<quest id="6">
		<require item="118" qty="5"/>
		<require item="121" qty="1"/>
		<require item="131" qty="1"/>
		<require item="145" qty="1"/>
		<require item="159" qty="1"/>
		<require item="161" qty="1"/>
		<give family="21"/>
	</quest>
	<quest id="7">
		<require item="121" qty="10"/>
		<require item="145" qty="10"/>
		<require item="159" qty="10"/>
		<require item="188" qty="2"/>
		<require item="192" qty="2"/>
		<give family="22"/>
	</quest>
	<quest id="8">
		<require item="140" qty="5"/>
		<require item="142" qty="5"/>
		<require item="146" qty="20"/>
		<require item="143" qty="10"/>
		<give family="24"/>
	</quest>
	<quest id="9">
		<require item="120" qty="1"/>
		<require item="164" qty="2"/>
		<require item="158" qty="10"/>
		<give family="25"/>
	</quest>
	<quest id="10">
		<require item="4" qty="1"/>
		<require item="7" qty="1"/>
		<require item="13" qty="1"/>
		<give family="1"/>
		<give family="8"/>
		<give family="13"/>
		<give family="15"/>
	</quest>
	<quest id="11">
		<require item="106" qty="1"/>
		<give family="3"/>
	</quest>
	<quest id="12">
		<require item="169" qty="150"/>
		<give family="27"/>
	</quest>
	<quest id="13">
		<require item="107" qty="1"/>
		<give family="5"/>
	</quest>
	<quest id="14">
		<require item="1" qty="10"/>
		<require item="5" qty="5"/>
		<require item="11" qty="5"/>
		<require item="21" qty="10"/>
		<require item="22" qty="5"/>
		<require item="24" qty="1"/>
		<require item="25" qty="1"/>
		<require item="28" qty="3"/>
		<require item="38" qty="1"/>
		<require item="82" qty="5"/>
		<give family="2"/>
	</quest>
	<quest id="15">
		<require item="175" qty="11"/>
		<require item="192" qty="11"/>
		<require item="255" qty="11"/>
		<require item="256" qty="11"/>
		<require item="257" qty="11"/>
		<require item="258" qty="11"/>
		<require item="267" qty="20"/>
		<require item="163" qty="30"/>
		<require item="199" qty="11"/>
		<give family="11"/>
		<give family="34"/>
	</quest>
	<quest id="16">
		<require item="260" qty="20"/>
		<give family="4"/>
		<give family="35"/>
	</quest>
	<quest id="17">
		<require item="164" qty="5"/>
		<give family="30"/>
	</quest>
	<quest id="18">
		<require item="126" qty="30"/>
		<give family="23"/>
	</quest>
	<quest id="19">
		<require item="119" qty="20"/>
		<require item="173" qty="20"/>
		<require item="174" qty="20"/>
		<give family="32"/>
	</quest>
	<quest id="20">
		<require item="127" qty="10"/>
		<require item="128" qty="5"/>
		<require item="129" qty="1"/>
		<give family="10"/>
		<give family="12"/>
	</quest>
	<quest id="21">
		<require item="119" qty="20"/>
		<require item="139" qty="10"/>
		<require item="143" qty="20"/>
		<require item="179" qty="1"/>
		<require item="280" qty="10"/>
		<give family="28"/>
	</quest>
	<quest id="22">
		<require item="138" qty="15"/>
		<require item="157" qty="1"/>
		<require item="178" qty="2"/>
		<require item="222" qty="5"/>
		<require item="221" qty="3"/>
		<give family="33"/>
	</quest>
	<quest id="23">
		<require item="209" qty="1"/>
		<require item="230" qty="1"/>
		<require item="244" qty="1"/>
		<require item="281" qty="1"/>
		<require item="227" qty="1"/>
		<require item="256" qty="1"/>
		<require item="260" qty="1"/>
		<give family="37"/>
	</quest>
	<quest id="24">
		<require item="68" qty="1"/>
		<require item="122" qty="10"/>
		<require item="123" qty="10"/>
		<require item="125" qty="1"/>
		<require item="133" qty="1"/>
		<require item="134" qty="3"/>
		<require item="136" qty="5"/>
		<require item="137" qty="5"/>
		<require item="141" qty="10"/>
		<require item="188" qty="10"/>
		<give family="36"/>
	</quest>
	<quest id="25">
		<require item="187" qty="10"/>
		<require item="199" qty="10"/>
		<require item="212" qty="10"/>
		<give family="26"/>
	</quest>
	<quest id="26">
		<require item="149" qty="10"/>
		<require item="175" qty="10"/>
		<require item="255" qty="1"/>
		<give family="31"/>
	</quest>
	<quest id="27">
		<require item="88" qty="1"/>
		<require item="99" qty="1"/>
		<require item="100" qty="1"/>
		<require item="162" qty="1"/>
	</quest>
	<quest id="28">
		<require item="177" qty="2"/>
		<require item="202" qty="2"/>
		<require item="206" qty="2"/>
		<require item="262" qty="2"/>
		<require item="269" qty="2"/>
		<require item="270" qty="2"/>
		<require item="271" qty="2"/>
		<require item="272" qty="2"/>
		<give family="29"/>
	</quest>
	<quest id="29">
		<require item="21" qty="10"/>
		<require item="26" qty="10"/>
		<require item="31" qty="10"/>
		<require item="85" qty="10"/>
		<require item="90" qty="10"/>
		<give family="38"/>
	</quest>
	<quest id="30">
		<require item="68" qty="10"/>
		<remove family="13"/>
		<give family="14"/>
		<give family="106"/>
	</quest>
	<quest id="31">
		<require item="26" qty="10"/>
		<remove family="14"/>
		<give family="107"/>
	</quest>
	<quest id="32">
		<require item="109" qty="1"/>
		<remove family="15"/>
		<give family="16"/>
		<give tokens="5"/>
	</quest>
	<quest id="33">
		<require item="110" qty="2"/>
		<remove family="16"/>
		<give family="17"/>
		<give tokens="10"/>
	</quest>
	<quest id="34">
		<require item="111" qty="2"/>
		<remove family="17"/>
		<give tokens="20"/>
	</quest>
	<quest id="35">
		<require item="10" qty="5"/>
		<give bank="25"/>
		<remove family="18"/>
	</quest>
	<quest id="36">
		<require item="296" qty="1"/>
	</quest>
	<quest id="37">
		<require item="297" qty="1"/>
	</quest>
	<quest id="38">
		<require item="298" qty="1"/>
	</quest>
	<quest id="39">
		<require item="299" qty="1"/>
	</quest>
	<quest id="40">
		<require item="300" qty="1"/>
	</quest>
	<quest id="41">
		<require item="301" qty="1"/>
	</quest>
	<quest id="42">
		<require item="302" qty="1"/>
	</quest>
	<quest id="43">
		<require item="102" qty="1"/>
		<give family="108"/>
	</quest>
	<quest id="44">
		<require item="72" qty="5"/>
		<require item="91" qty="5"/>
		<require item="92" qty="10"/>
		<give family="109"/>
	</quest>
	<quest id="45">
		<require item="171" qty="10"/>
		<require item="172" qty="10"/>
		<require item="95" qty="3"/>
		<give family="110"/>
	</quest>
	<quest id="46">
		<require item="112" qty="1"/>
		<give family="111"/>
	</quest>
	<quest id="47">
		<require item="14" qty="1"/>
		<require item="15" qty="1"/>
		<require item="16" qty="1"/>
		<require item="17" qty="1"/>
		<give family="19"/>
		<give family="112"/>
	</quest>
	<quest id="48">
		<require item="113" qty="1"/>
		<give family="113"/>
	</quest>
	<quest id="49">
		<require item="304" qty="1"/>
		<give family="5000"/>
		<give family="43"/>
		<give family="45"/>
		<give family="46"/>
	</quest>
	<quest id="50">
		<require item="305" qty="1"/>
		<give family="5001"/>
	</quest>
	<quest id="51">
		<require item="306" qty="1"/>
		<give family="5002"/>
	</quest>
	<quest id="52">
		<require item="307" qty="1"/>
		<give family="5003"/>
		<remove family="41"/>
	</quest>
	<quest id="53">
		<require item="308" qty="1"/>
		<give family="5004"/>
	</quest>
	<quest id="54">
		<require item="309" qty="1"/>
		<give family="5005"/>
	</quest>
	<quest id="55">
		<require item="310" qty="1"/>
		<remove family="42"/>
		<give family="5006"/>
	</quest>
	<quest id="56">
		<require item="311" qty="1"/>
		<give family="5007"/>
	</quest>
	<quest id="57">
		<require item="312" qty="1"/>
		<give family="5008"/>
	</quest>
	<quest id="58">
		<require item="313" qty="1"/>
		<give family="5009"/>
	</quest>
	<quest id="59">
		<require item="314" qty="1"/>
		<give family="5010"/>
	</quest>
	<quest id="60">
		<require item="323" qty="20"/>
		<require item="324" qty="10"/>
		<require item="325" qty="5"/>
		<require item="326" qty="3"/>
		<require item="327" qty="2"/>
		<give family="41"/>
	</quest>
	<quest id="61">
		<require item="328" qty="10"/>
		<require item="329" qty="15"/>
		<require item="330" qty="3"/>
		<require item="331" qty="2"/>
		<require item="332" qty="1"/>
		<give family="42"/>
	</quest>
	<quest id="62">
		<require item="315" qty="1"/>
		<require item="316" qty="1"/>
		<require item="317" qty="1"/>
		<require item="318" qty="1"/>
		<require item="319" qty="1"/>
		<require item="320" qty="1"/>
		<require item="321" qty="1"/>
		<require item="322" qty="1"/>
		<give option="boost"/>
	</quest>
	<quest id="63">
		<require item="333" qty="1"/>
		<give option="mirror"/>
	</quest>
	<quest id="64">
		<require item="334" qty="1"/>
		<give option="nightmare"/>
	</quest>
	<quest id="65">
		<require item="117" qty="1"/>
		<give family="5012"/>
	</quest>
	<quest id="66">
		<require item="116" qty="1"/>
		<give option="kickcontrol"/>
	</quest>
	<quest id="67">
		<require item="334" qty="5"/>
		<require item="336" qty="10"/>
		<require item="337" qty="5"/>
		<require item="338" qty="3"/>
		<remove family="48"/>
		<give mode="multicoop"/>
	</quest>
	<quest id="68">
		<require item="339" qty="1"/>
		<give option="mirrormulti"/>
	</quest>
	<quest id="69">
		<require item="340" qty="1"/>
		<give option="nightmaremulti"/>
	</quest>
	<quest id="70">
		<require item="341" qty="2"/>
		<give option="lifesharing"/>
	</quest>
	<quest id="71">
		<require item="342" qty="1"/>
		<give family="50"/>
	</quest>
	<quest id="72">
		<require item="343" qty="5"/>
		<require item="344" qty="2"/>
		<require item="345" qty="7"/>
		<require item="346" qty="7"/>
		<require item="347" qty="1"/>
		<require item="348" qty="1"/>
		<require item="349" qty="1"/>
		<give option="ninja"/>
	</quest>
	<quest id="73">
		<require item="350" qty="100"/>
		<give mode="timeattack"/>
		<give option="set_ta_0"/>
	</quest>
	<quest id="74">
		<require item="351" qty="1"/>
		<give option="bombexpert"/>
		<give log="1"/>
	</quest>
	<quest id="75">
		<require item="352" qty="1"/>
		<give family="5014"/>
	</quest>
	 */