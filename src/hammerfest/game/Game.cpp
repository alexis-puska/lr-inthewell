#include "Game.h"

/***********************************************
 *               TICK generator
 ***********************************************/
static int metronome(void* data) {
    Game *game = ((Game *) data);
    int t1, t2;
    int delay;
    long warningCount = 0l;
    while (game->isAlive()) {
        t1 = SDL_GetTicks();
        game->tick();
        t2 = SDL_GetTicks();
        delay = gameTick - (t2 - t1);
        if (delay > 0) {
            if (delay < 5) {
                warningCount++;
                std::cout << "warn < 5 " << delay << " " << warningCount << "\n";
            }
            //std::cout << "take time : " << delay << " " << t2 - t1 << "\n";
            SDL_Delay(delay);
        } else {
            warningCount++;
            std::cout << "warn < 0 : " << delay << " " << warningCount << "\n";
        }
    }
    return 0;
}

/***********************************************
 *             Default constructor
 ***********************************************/
Game::Game() {
    srand((unsigned int) time(NULL));
    Uint32 rmask, gmask, bmask, amask;
    amask = 0xff000000;
    rmask = 0x00ff0000;
    gmask = 0x0000ff00;
    bmask = 0x000000ff;
    screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
    darknessBuffer = SDL_CreateRGBSurface(0, 420, 500, 32, rmask, gmask, bmask, amask);
    changeLevelBufferAnimationVertical = SDL_CreateRGBSurface(0, 420, 1000, 32, rmask, gmask, bmask, amask);
    changeLevelBufferAnimationHorizontal = SDL_CreateRGBSurface(0, 840, 500, 32, rmask, gmask, bmask, amask);
    pauseGameBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
    gameState = gameStart;
    isThreadAlive = false;
    configured = false;
    requestStopGame = false;
    bossMusic = false;
    releaseButton = false;
    changeLevelAnimationPosition = 0;
    changeLevelAnimationType = changeLevelNormal;
    idx = 0;
}

/**********************************************
 *                 Constructor
 **********************************************/
Game::Game(SDL_Surface * vout_buf, unsigned short * in_keystate) {
    srand((unsigned int) time(NULL));
    Uint32 rmask, gmask, bmask, amask;
    amask = 0xff000000;
    rmask = 0x00ff0000;
    gmask = 0x0000ff00;
    bmask = 0x000000ff;
    screenBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
    darknessBuffer = SDL_CreateRGBSurface(0, 420, 500, 32, rmask, gmask, bmask, amask);
    changeLevelBufferAnimationVertical = SDL_CreateRGBSurface(0, 420, 1000, 32, rmask, gmask, bmask, amask);
    changeLevelBufferAnimationHorizontal = SDL_CreateRGBSurface(0, 840, 500, 32, rmask, gmask, bmask, amask);
    pauseGameBuffer = SDL_CreateRGBSurface(0, 420, 520, 32, rmask, gmask, bmask, amask);
    this->vout_buf = vout_buf;
    this->in_keystate = in_keystate;
    isThreadAlive = false;
    configured = true;
    requestStopGame = false;
    bossMusic = false;
    releaseButton = false;
    gameState = gameStart;
    changeLevelAnimationPosition = 0;
    currentLevel = LevelService::Instance().getLevel(0);
    currentLevel->generateBackGround(-1);
    ennemies = currentLevel->getEnnemiesList();
    players.push_back(new Player(80, 400, 0, &in_keystate[0]));
    changeLevelAnimationType = changeLevelNormal;
    idx = 0;
    
    startGame();
}

/**********************************************
 *                  Destructor
 **********************************************/
Game::~Game() {
    exitGame();
    in_keystate = NULL;
    vout_buf = NULL;
    SDL_FreeSurface(screenBuffer);
    SDL_FreeSurface(darknessBuffer);
    SDL_FreeSurface(changeLevelBufferAnimationVertical);
    SDL_FreeSurface(changeLevelBufferAnimationHorizontal);
    SDL_FreeSurface(pauseGameBuffer);
}

bool Game::isConfigured() {
    return configured;
}

bool Game::isAlive() {
    return isThreadAlive;
}

bool Game::isRequestStopGame() {
    return requestStopGame;
}

/*******************************************
 * function that initialise totaly a game
 *******************************************/
void Game::startGame() {
    Sound::Instance().stopMusique();
    Sound::Instance().startMusic();
    if (!isThreadAlive) {
        isThreadAlive = true;
        idx = 0;
        mainThread = SDL_CreateThread(metronome, "mainThread", this);
    }
    
}

/*******************************************
 * function to kill the main thread
 *******************************************/
void Game::stopGame() {
    if (isThreadAlive) {
        Sound::Instance().stopMusique();
        Sound::Instance().startMusicBoss();
        isThreadAlive = false;
        configured = false;
        requestStopGame = false;
        int treadResult = 0;
        SDL_WaitThread(mainThread, &treadResult);
        std::cout << "result stop thread" << treadResult << "\n";
    }
}

/*******************************************
 * function to exit Game
 *******************************************/
void Game::exitGame() {
    stopGame();
}

/*******************************************
 *           main function of game
 *******************************************/
void Game::tick() {
    if (in_keystate[0] == 0) {
        releaseButton = true;
    }
    
    switch (gameState) {
        case gameStart:
            //START TEMPORARY LINE
            
            //CHANGEMENT MUSIQUE POUR BOSS
            if (!bossMusic && (idx == 30 || idx == 40 || idx == 50 || idx == 60 || idx == 70 || idx == 80 || idx == 90 || idx == 100)) {
                Sound::Instance().stopMusique();
                Sound::Instance().startMusicBoss();
                bossMusic = true;
            }
            
            //Changement musique niveau normal
            if (bossMusic) {
                bool bossLevel = false;
                if (idx == 30 || idx == 40 || idx == 50 || idx == 60 || idx == 70 || idx == 80 || idx == 90 || idx == 100 || idx == 101
                    || idx == 102 || idx == 103) {
                    bossLevel = true;
                }
                if (!bossLevel) {
                    Sound::Instance().stopMusique();
                    Sound::Instance().startMusic();
                    bossMusic = false;
                }
            }
            
            if (in_keystate[0] & keyPadSelect && !requestStopGame && releaseButton) {
                copySurfaceToBackRenderer(screenBuffer, pauseGameBuffer, 0, 0);
                gameState = gamePause;
                releaseButton = false;
            } else if (in_keystate[0] & keyPadStart && !requestStopGame && releaseButton) {
                copySurfaceToBackRenderer(screenBuffer, pauseGameBuffer, 0, 0);
                gameState = gameShowMap;
                releaseButton = false;
            } else if (in_keystate[0] & keyPadL1 && !requestStopGame) {
                idx--;
                if (idx < 0) {
                    idx = 103;
                }
                currentLevel = LevelService::Instance().getLevel(idx);
                currentLevel->generateBackGround(-1);
                ennemies = currentLevel->getEnnemiesList();
            } else if (in_keystate[0] & keyPadR1 && !requestStopGame) {
                idx++;
                if (idx > 103) {
                    idx = 0;
                }
                currentLevel = LevelService::Instance().getLevel(idx);
                currentLevel->generateBackGround(-1);
                ennemies = currentLevel->getEnnemiesList();
            }
            //END TEMPORARY LINE
            
            drawLevelBackground();
            
            //TODO
            //Draw Player
            for (unsigned int i = 0; i < players.size(); i++) {
                players[i]->doSomething(screenBuffer, currentLevel->getPlatformGrid());
                if (currentLevel->getId() > 15) {
                    excludeDarkness(players[i]->getX() + 10, players[i]->getY() - 10, 1.5);
                }
                
            }
            
            //TODO
            //Draw Ennemies
            for (unsigned int i = 0; i < ennemies.size(); i++) {
                ennemies[i]->doSomething(screenBuffer);
            }
            
            //Gestion des collisions
            for (unsigned int i = 0; i < ennemies.size(); i++) {
                for (unsigned int p = 0; p < players.size(); p++) {
                    if(players[p]->playerIsAlive() && !players[p]->playerIsProtected()){
                        if(ennemies[i]->hit(players[p]->getHitbox())){
                            std::cout<<"hit\n";
                            //players[p]->playerKilled();
                            if(ennemies[i]->hitMeByBottonOrTopSide(players[p]->getHitbox())){
                                std::cout<<"bottom or top\n";
                                //players[p]->playerKilled();
                            }
                        }
                    }
                }
            }
            
            
            
            
            drawLevelForeground();
            
            for (unsigned int i = 0; i < players.size(); i++) {
                if ((players[i] != NULL && players[i]->getY() >= 560)) {
                    gameState = gameChangeLevel;
                }
            }
            
            copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
            
            //si on change de niveau et que l'on a pas sauvegarder l'état du précédent niveau on le savegarde dans un buffer (nécessaire à l'animation)
            if (gameState == gameChangeLevel) {
                
                for (unsigned int i = 0; i < players.size(); i++) {
                    players[i]->changeLevel(true);
                }
                idx++;
                
                if (idx == 2) {
                    Sound::Instance().playSoundTuberculoz();
                }
                
                currentLevel = LevelService::Instance().getLevel(idx);
                currentLevel->generateBackGround(-1);
                ennemies = currentLevel->getEnnemiesList();
                
                Sound::Instance().playSoundNextLevel();
                switch (changeLevelAnimationType) {
                    case changeLevelImmediat:
                        changeLevelAnimationPosition = 0;
                        break;
                    case changeLevelToRight:
                        changeLevelAnimationPosition = 0;
                        copySurfaceToBackRenderer(screenBuffer, changeLevelBufferAnimationHorizontal, 0, 0);
                        drawLevelBackground();
                        drawLevelForeground();
                        copySurfaceToBackRenderer(screenBuffer, changeLevelBufferAnimationHorizontal, 420, 0);
                        break;
                    case changeLevelToLeft:
                        changeLevelAnimationPosition = 420;
                        copySurfaceToBackRenderer(screenBuffer, changeLevelBufferAnimationHorizontal, 420, 0);
                        drawLevelBackground();
                        drawLevelForeground();
                        copySurfaceToBackRenderer(screenBuffer, changeLevelBufferAnimationHorizontal, 0, 0);
                        break;
                    case changeLevelNormal:
                        changeLevelAnimationPosition = 0;
                        copySurfaceToBackRenderer(screenBuffer, changeLevelBufferAnimationVertical, 0, 0);
                        drawLevelBackground();
                        drawLevelForeground();
                        copySurfaceToBackRenderer(screenBuffer, changeLevelBufferAnimationVertical, 0, 500);
                        break;
                }
                
            }
            break;
        case gameChangeLevel:
            drawChangeLevel();
            copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
            break;
        case gamePause:
            if (in_keystate[0] & keyPadSelect && !requestStopGame && releaseButton) {
                gameState = gameStart;
                releaseButton = false;
            } else if (in_keystate[0] & keyPadStart && !requestStopGame && releaseButton) {
                requestStopGame = true;
                releaseButton = false;
            }
            drawPauseScreen();
            copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
            break;
        case gameEnd:
            if (in_keystate[0] & keyPadStart && !requestStopGame && releaseButton) {
                requestStopGame = true;
                releaseButton = false;
            }
            break;
        case gameShowMap:
            if (in_keystate[0] & keyPadStart && !requestStopGame && releaseButton) {
                gameState = gameStart;
                releaseButton = false;
            }
            drawMapScreen();
            copySurfaceToBackRenderer(screenBuffer, vout_buf, 0, 0);
            break;
    }
}

/*******************************************
 *	Dessine l fond du niveau + élément
 *	en arrière plan
 ******************************************/
void Game::drawLevelBackground() {
    if (currentLevel->getId() > 15) {
        generateDarkness();
    }
    
    //getBackGround
    copySurfaceToBackRenderer(currentLevel->getBackground(), screenBuffer, 0, 0);
    
    //draw all Element of the level. (Vortex, teleporter, rayon...)
    currentLevel->drawHimself(screenBuffer);
}

/*******************************************
 *	Dessine les elements au premier plan
 *	du niveau + ombre
 ******************************************/
void Game::drawLevelForeground() {
    //merge score and left/right border before the foreground decor for level1
    if (currentLevel->getId() == 1) {
        mergeScoreAndBorder();
        currentLevel->drawForeGroundElement(screenBuffer);
    } else {
        currentLevel->drawForeGroundElement(screenBuffer);
        mergeScoreAndBorder();
    }
    
    //merge darkness
    if (currentLevel->getId() > 15) {
        copySurfaceToBackRenderer(darknessBuffer, screenBuffer, 0, 0);
    }
}

/*******************************************
 *   merge score and border
 *   Copie les bordure gauche et droite
 *   ainsi que la barre de score
 ******************************************/
void Game::mergeScoreAndBorder() {
    if (currentLevel->getId() != 0) {
        copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_left", 0), screenBuffer, 0, 0);
        copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_right", 0), screenBuffer, 404, 0);
    }
    copySurfaceToBackRenderer(Sprite::Instance().getAnimation("border_score", 0), screenBuffer, 0, 500);
}

/*******************************************
 *
 * 	-------------DARKNESS-------------
 *   		Génère l'ombre du niveau
 *
 ******************************************/
void Game::generateDarkness() {
    int darknessValue = (int)ceil((float) (255 / 85) * (float) (currentLevel->getId() - 15));
    if (darknessValue >= 255) {
        darknessValue = 255;
    }
    SDL_FillRect(darknessBuffer, NULL, SDL_MapRGBA(darknessBuffer->format, 0, 0, 0, darknessValue));
}

/****************************************
 *
 * Fonction pour supprimer un disque
 * 		de l'ombre du niveau
 *
 ****************************************/

void Game::excludeDarkness(int in_X, int in_Y, double zoom) {
    if (darknessBuffer != NULL) {
        SDL_Surface * temp = rotozoomSurfaceXY(Sprite::Instance().getAnimation("shadow", 0), 0, zoom, zoom, 0);
        
        const int halfWidth = temp->w / 2;
        const int halfHeight = temp->h / 2;
        
        SDL_Rect sourceRect = { 0, 0, temp->w, temp->h };
        SDL_Rect destRect = { in_X - halfWidth, in_Y - halfHeight, temp->w, temp->h };
        
        // Make sure our rects stays within bounds
        if (destRect.x < 0) {
            sourceRect.x -= destRect.x; // remove the pixels outside of the surface
            sourceRect.w -= sourceRect.x; // shrink to the surface, not to offset fog
            destRect.x = 0;
            destRect.w -= sourceRect.x; // shrink the width to stay within bounds
        }
        if (destRect.y < 0) {
            sourceRect.y -= destRect.y; // remove the pixels outside
            sourceRect.h -= sourceRect.y; // shrink to the surface, not to offset fog
            destRect.y = 0;
            destRect.h -= sourceRect.y; // shrink the height to stay within bounds
        }
        
        int xDistanceFromEdge = (destRect.x + destRect.w) - darknessBuffer->w;
        if (xDistanceFromEdge > 0) {
            // we're busting
            sourceRect.w -= xDistanceFromEdge;
            destRect.w -= xDistanceFromEdge;
        }
        int yDistanceFromEdge = (destRect.y + destRect.h) - darknessBuffer->h;
        if (yDistanceFromEdge > 0) {
            // we're busting
            sourceRect.h -= yDistanceFromEdge;
            destRect.h -= yDistanceFromEdge;
        }
        
        SDL_LockSurface(darknessBuffer);
        
        Uint32* destPixels = (Uint32*) darknessBuffer->pixels;
        Uint32* srcPixels = (Uint32*) temp->pixels;
        for (int x = 0; x < destRect.w; ++x) {
            for (int y = 0; y < destRect.h; ++y) {
                Uint32* destPixel = destPixels + (y + destRect.y) * darknessBuffer->w + destRect.x + x;
                Uint32* srcPixel = srcPixels + (y + sourceRect.y) * temp->w + sourceRect.x + x;
                unsigned char* destAlpha = (unsigned char*) destPixel + 3; // fetch alpha channel
                unsigned char* srcAlpha = (unsigned char*) srcPixel + 3; // fetch alpha channel
                if (*destAlpha > *srcAlpha) {
                    *destAlpha = *srcAlpha;
                }
            }
        }
        SDL_UnlockSurface(darknessBuffer);
        SDL_FreeSurface(temp);
    }
}

/*******************************************
 *
 * -------- LEVEL CHANGE ANIMATION --------
 *
 ******************************************/
void Game::drawChangeLevel() {
    switch (changeLevelAnimationType) {
        case changeLevelImmediat:
            gameState = gameStart;
            changeLevelAnimationPosition = 0;
            break;
        case changeLevelToRight:
            if (changeLevelAnimationPosition > 420) {
                gameState = gameStart;
                changeLevelAnimationPosition = 0;
            } else {
                copySurfaceToBackRendererWithStartOffset(changeLevelBufferAnimationHorizontal, screenBuffer, 0, 0, 420, 500,
                                                         changeLevelAnimationPosition, 0);
                changeLevelAnimationPosition += 20;
            }
            break;
        case changeLevelToLeft:
            if (changeLevelAnimationPosition < 0) {
                gameState = gameStart;
                changeLevelAnimationPosition = 0;
            } else {
                copySurfaceToBackRendererWithStartOffset(changeLevelBufferAnimationHorizontal, screenBuffer, 0, 0, 420, 500,
                                                         changeLevelAnimationPosition, 0);
                changeLevelAnimationPosition -= 20;
            }
            break;
        case changeLevelNormal:
            if (changeLevelAnimationPosition > 500) {
                gameState = gameStart;
                changeLevelAnimationPosition = 0;
            } else {
                copySurfaceToBackRendererWithStartOffset(changeLevelBufferAnimationVertical, screenBuffer, 0, 0, 420, 500, 0,
                                                         changeLevelAnimationPosition);
                changeLevelAnimationPosition += 15;
            }
            break;
    }
}

void Game::drawPauseScreen() {
    copySurfaceToBackRenderer(pauseGameBuffer, screenBuffer, 0, 0);
    copySurfaceToBackRenderer(Sprite::Instance().getAnimation("message2", 0), screenBuffer, 0, 0);
    Text::Instance().drawTextTranslated(screenBuffer, "verdanaBold20", 210, 80, "menu.lang.title", white, true);
}

void Game::drawMapScreen() {
    copySurfaceToBackRenderer(pauseGameBuffer, screenBuffer, 0, 0);
    copySurfaceToBackRenderer(Sprite::Instance().getAnimation("map", 0), screenBuffer, 0, 0);
}

/**********************************************
 * function to copy a surface inside an other.
 **********************************************/
void Game::copySurfaceToBackRenderer(SDL_Surface * src, SDL_Surface * dest, int x, int y) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    dstRect.w = src->w;
    dstRect.h = src->h;
    SDL_Rect srcRect;
    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = src->w;
    srcRect.h = src->h;
    SDL_BlitSurface(src, &srcRect, dest, &dstRect);
}

void Game::copySurfaceToBackRendererWithStartOffset(SDL_Surface * src, SDL_Surface * dest, int x, int y, int lengthX, int lengthY, int offsetX,
                                                    int offsetY) {
    SDL_Rect dstRect;
    dstRect.x = x;
    dstRect.y = y;
    if (lengthX == -1) {
        dstRect.w = src->w;
    } else {
        dstRect.w = lengthX;
    }
    if (lengthY == -1) {
        dstRect.h = src->h;
    } else {
        dstRect.h = lengthY;
    }
    SDL_Rect srcRect;
    srcRect.x = offsetX;
    srcRect.y = offsetY;
    if (lengthX == -1) {
        srcRect.w = src->w;
    } else {
        srcRect.w = lengthX;
    }
    if (lengthY == -1) {
        srcRect.h = src->h;
    } else {
        srcRect.h = lengthY;
    }
    SDL_BlitSurface(src, &srcRect, dest, &dstRect);
}

/*******************************************
 * fill surface with another surface
 *******************************************/
void Game::fillScreenBufferWithSurface(std::string name, int index, SDL_Surface * destination) {
    SDL_Surface * temp2 = Sprite::Instance().getAnimation(name, index);
    int x = 0;
    int y = 0;
    while (y < 500) {
        while (x < 420) {
            copySurfaceToBackRenderer(temp2, destination, x, y);
            x += temp2->w;
        }
        x = 0;
        y += temp2->h;
    }
}





/*
 
 Réponse envoyée sur Twinoïd ;)
 
 Au passage, EternalBot vient de faire une remarque pertinente quant à la formule d'apparition de la boule de feu : elle vient à la même vitesse de 0 à 3 vies, ce qui signifie qu'il n'y a pas besoin de suicider toutes ses vies pour le défi du Pad de la Crypte.
 
 Pour les curieux, voici le pseudocode pour calculer la durée :
 
 vies = max(viesIgor, viesSandy);
 coeffMode = 1 + 0.4 * modeCauchemar;
 coeffVies = 1 + 0.05 * max(0, vies - 3);
 coeff = coeffMode * coeffVies;
 
 secondesAvantPremierVite = 35 / coeff;
 secondesAvantSecondVite = 25 / coeff;
 
 Compressée pour le fun :D
 
 secondesAvantPremierVite = 35 / ((1 + 0.4 * modeCauchemar) * (1 + 0.05 * (max(0, max(viesIgor, viesSandy) - 3))));
 secondesAvantSecondVite = 25 / ((1 + 0.4 * modeCauchemar) * (1 + 0.05 * (max(0, max(viesIgor, viesSandy) - 3))));
 
 Si j'ai pas fait de fautes :P
 
 */
 
