**Lr-Hammerfest**
===============================

> Hammerfest, core adaptation of hammerfest.fr game
> core for Retroarch emulator.


===============================
**SDL2 Library installation :** 

- Linux / Ubuntu
```
sudo apt-get install -y make libsdl2-dev 
sudo apt-get install -y make libsdl2-image-dev 
sudo apt-get install -y make libsdl2-ttf-dev 
sudo apt-get install -y make libsdl2-mixer-dev 
sudo apt-get install -y make libsdl2-net-dev
sudo apt-get install -y make libsdl2-gfx-dev

- Linux / Fedora (with RPM Fusion)
sudo dnf install SDL2-devel
sudo dnf install SDL2_mixer-devel
sudo dnf install SDL2_ttf-devel
sudo dnf install SDL2_image-devel
sudo dnf install SDL2_net-devel
sudo dnf install SDL2_gfx-devel
```


- Raspberry pi 2/3 : 

```
connection SSH : 
reset ssh token : ssh-keygen -R "ip";

reset smb password : smbpasswd -a pi
sudo apt-get update
sudo apt-get install -y make libsdl2-dev libsdl2-image-dev libsdl2-net-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-gfx-dev libXinerama-dev libXi-dev libXrandr-dev libXss-dev libXCursor-dev 
```


- mac os X : 
```
Download the SDL2 library
https://www.libsdl.org/release/SDL2-2.0.4.dmg
https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.dmg
https://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.1.dmg
https://www.libsdl.org/projects/SDL_mixer/release/SDL2_mixer-2.0.1.dmg
https://www.libsdl.org/projects/SDL_net/release/SDL2_net-2.0.1.dmg
unzip and install the SDL2_image.framework, SDL2_ttf.framework, SDL2.framework inside the folder : /Library/Frameworks/

for SDL_2GFX : 
download source at : http://www.ferzkopp.net/wordpress/2016/01/02/sdl_gfx-sdl2_gfx/
unzip the code, open the unzipped folder, unzip xcode.zip archive inside build it with xcode on release target and install it inse /Library/Frameworks
```




===============================
**Compilation :**

Unix / mac os X : 
```
make clean -f Makefile.libretro
make -f Makefile.libretro
```

Raspberry pi 2/3: 

Change your swapFile default size, since the sprite, sound, musique, image is encode un binary in the code we need to have more swap to compile 
- sudo nano /etc/dphys-swapfile
The default value in Raspbian is:
```
CONF_SWAPSIZE=100
```
change to 
```
CONF_SWAPSIZE=200
```

- edit the file : Makefile.libretro
- uncommente the line : #platform = rpi
- add the version of your raspberry pi
- 2 for the raspberry pi 2
- 3 for the raspberry pi 3

===============================
**Launch :**
```
	/PathToRetroarch/retroarch -L lr_hammerfest_libretro.so
```

===============================
**Installation on retropie :**

add this xml fragment to es_systems.cfg file in /etc/emulationstation/es_systems.cfg
```
  <system>
    <name>hammerfest</name>
    <fullname>hammerfest</fullname>
    <plateform>hammerfest</plateform>
    <path>/home/pi/RetroPie/roms/lr-hammerfest</path>
    <command>sudo %ROM%</command>
    <!--<command>/opt/retropie/emulators/retroarch/bin/retroarch -L %ROM% --config /opt/retropie/configs/all/retroarch.cfg</command>-->
    <extension>.sh</extension>
    <theme>hammerfest</theme>
  </system>
```


in a folder clone the project : 
```
cd /home/pi/RetroPie/roms
git clone https://github.com/alexis-puska/lr-hammerfest.git
cd lr-hammerfest
chmod +x Update.sh
chmod +x Compile\ pi.sh
chmod +x A\ Hammerfest.sh
./Compile\ pi.sh
cd emulationStationTheme
sudo cp -avr hammerfest /etc/emulationstation/themes/carbon
sudo reboot
```

After this step lr-hammerfest is installed, compile, and integrated in emulation station on retropie distribution. If an update of code is made, you can just launch the UPDATE line in emulation station, COMPILE PI and launch the game with HAMMERFEST :) Enjoy !



