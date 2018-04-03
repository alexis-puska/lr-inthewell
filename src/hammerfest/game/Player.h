#ifndef __MYCLASS_PLAYER
#define __MYCLASS_PLAYER

#define playerHitboxWidth 14
#define playerHitboxHeight 16
#define playerSpeed 4
#define playerSpeedRun 6
#define playerFallSpeed 6
#define timeBeforeBoring 400

#include "../definition/Position.h"
#include "../definition/Drawable.h"
#include "../definition/HitBox.h"
#include "../utils/Sound.h"
#include "../level/Platform.h"

enum keyPad
{
    keyPadSelect = 1,
    keyPadL3 = 2,
    keyPadR3 = 4,
    keyPadStart = 8,
    keyPadUp = 16,
    keyPadRight = 32,
    keyPadDown = 64,
    keyPadLeft = 128,
    keyPadL2 = 256,
    keyPadR2 = 512,
    keyPadL1 = 1024,
    keyPadR1 = 2048,
    keyPadX = 4096,
    keyPadA = 8192,
    keyPadB = 16384,
    keyPadY = 32768
};

enum playerState
{
    playerWait = 0,
    playerWalk = 1,
    playerJump = 2,
    playerStartFall = 3,
    playerFall = 4,
    playerLanding = 5,
    playerKill = 6,
    playerDead = 7,
    playerShot = 8,
    playerDrop = 9,
    playerBorder = 10,
    playerBoring = 11,
    playerChewingGum = 12,
    playerKnockOut = 13,
    playerRaiseUp = 14,
    playerRespawn = 15,
    playerRun = 16,
    playerCry = 17

};

enum playerDirection
{
    playerDontMove = 0,
    playerGoLeft = 1,
    playerGoRight = 2
};

class Player : public Position, Drawable, HitBox
{
  public:
    Player(int x, int y, int type, unsigned short *in_keystate);
    ~Player();
    void doSomething(SDL_Surface *dest, bool *platformGrid);
    void changeLevel(bool first);
    void playerKilled();
    bool isDead();
    void playerRespawnWithPosition(int x, int y);
    void playerGoSad();
    void playerCanRunNow();
    bool playerIsAlive();
    bool playerIsProtected();
    SDL_Rect getHitbox();

  private:
    int type; //O - igor, 1 - Sandy
    unsigned short *in_keystate;

    bool protection;
    bool playerCanRun;
    bool playerMove;

    bool lockLeftDirection;
    bool lockRightDirection;

    bool hitboxPoint[10];

    bool shotBombeUpper;
    bool playerIsSad;
    bool dropBombeInAir;

    bool playerFalling;
    bool insidePlatform;

    int state;
    int direction;
    int animIdx;
    int animIdxMax;

    int previousState;
    int previousDirection;
    int prevAnimIdx;
    int prevAnimIdxMax;

    int inactivityCounter;

    void changeState(int newState);
    void drawHimself(SDL_Surface *dest);
    void calcPoint(bool *platformGrid);
    void adjustPositionLeft();
    void adjustPositionRight();
    void adjustPositionBottom();
};
#endif
