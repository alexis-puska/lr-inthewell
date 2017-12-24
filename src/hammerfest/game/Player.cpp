#include "Player.h"

Player::Player(int x, int y, int type, unsigned short * in_keystate) :
Position(x, y), Drawable(), HitBox() {
    this->type = type;
    this->state = playerWait;
    this->in_keystate = in_keystate;
    this->playerFalling = false;
    animIdx = 0;
    previousDirection = playerGoRight;
    playerCanRun = false;
    protection = false;
    playerMove = false;
    insidePlatform = false;
    lockLeftDirection = false;
    lockRightDirection = false;
    playerIsSad = false;
    dropBombeInAir = false;
    inactivityCounter = 0;
    animIdxMax = Sprite::Instance().getAnimationSize("igor_right_wait");
    initHitBox(x - (int)floor(playerHitboxWidth / 2), y - playerHitboxHeight, playerHitboxWidth, playerHitboxHeight);
}

Player::~Player() {
}

void Player::doSomething(SDL_Surface * dest, bool * platformGrid) {
    if(state == playerKill){
        if (animIdx >= animIdxMax) {
            changeState(playerDead);
        }
    }else  if(state == playerDead){
        changeState(playerRespawn);
    }else if(state == playerRespawn){
        if (animIdx >= animIdxMax) {
            changeState(playerWait);
        }
    }else{
        
        //acceleration -> -5exp(-0.5x)+5
        //glaçon -> 50 exp(-0.02x)
        
        /***************************
         * --- getKeystateValue ---
         ***************************/
        unsigned short keystate = *in_keystate;
        
        /***************************
         * --- Value correction ---
         ***************************/
        if (y > 561) {
            y = 0;
        }
        
        /*****************************
         * --- keystate treatment ---
         *****************************/
        direction = playerDontMove;
        if (keystate == 0) {
            if (state == playerWalk || state == playerRun) {
                //player don't move
                state = playerWait;
                direction = playerDontMove;
                animIdxMax = Sprite::Instance().getAnimationSize("igor_right_wait");
                animIdx = 0;
            }
            if (state == playerWait) {
                inactivityCounter++;
                if (inactivityCounter > timeBeforeBoring) {
                    changeState(playerChewingGum);
                }
            }
            
        } else {
            inactivityCounter = 0;
            /*********************
             * BOUTON TEMPORAIRE
             ********************/
            /*if (keystate & keyPadUp) {
             y -= 5;
             }
             if (keystate & keyPadDown) {
             y += 5;
             }*/
            /*********************
             * BOUTON TEMPORAIRE
             ********************/
            
            if (keystate & keyPadLeft) {
                direction = playerGoLeft;
                previousDirection = playerGoLeft;
                switch (state) {
                    case playerWait:
                    case playerLanding:
                    case playerDrop:
                    case playerBorder:
                    case playerBoring:
                    case playerChewingGum:
                    case playerRaiseUp:
                    case playerRespawn:
                    case playerCry:
                        if (!dropBombeInAir) {
                            if (playerCanRun) {
                                changeState(playerRun);
                                playerMove = true;
                            } else {
                                changeState(playerWalk);
                                playerMove = true;
                            }
                        }
                        break;
                    case playerShot:
                        if (previousState != playerJump && previousState != playerStartFall && previousState != playerFall) {
                            if (!dropBombeInAir) {
                                if (playerCanRun) {
                                    changeState(playerRun);
                                    playerMove = true;
                                } else {
                                    changeState(playerWalk);
                                    playerMove = true;
                                }
                            }
                        }
                        break;
                    case playerWalk:
                        playerMove = true;
                        break;
                    case playerRun:
                        playerMove = true;
                        break;
                    case playerStartFall:
                    case playerFall:
                    case playerJump:
                        playerMove = true;
                        break;
                    case playerKill:
                    case playerKnockOut:
                    case playerDead:
                        break;
                }
            }
            
            if (keystate & keyPadRight) {
                previousDirection = playerGoRight;
                direction = playerGoRight;
                
                switch (state) {
                    case playerWait:
                    case playerLanding:
                    case playerDrop:
                    case playerBorder:
                    case playerBoring:
                    case playerChewingGum:
                    case playerRaiseUp:
                    case playerRespawn:
                    case playerCry:
                        if (!dropBombeInAir) {
                            if (playerCanRun) {
                                changeState(playerRun);
                                playerMove = true;
                            } else {
                                changeState(playerWalk);
                                playerMove = true;
                            }
                        }
                        break;
                    case playerShot:
                        if (previousState != playerJump && previousState != playerStartFall && previousState != playerFall) {
                            if (!dropBombeInAir) {
                                if (playerCanRun) {
                                    changeState(playerRun);
                                    playerMove = true;
                                } else {
                                    changeState(playerWalk);
                                    playerMove = true;
                                }
                            }
                        }
                        break;
                    case playerWalk:
                        playerMove = true;
                        break;
                    case playerRun:
                        playerMove = true;
                        break;
                    case playerStartFall:
                    case playerFall:
                    case playerJump:
                        playerMove = true;
                        break;
                    case playerKill:
                    case playerKnockOut:
                    case playerDead:
                        break;
                }
                
            }
            /*********************
             * BOUTON SAUT
             ********************/
            if (keystate & keyPadB) {
                switch (state) {
                    case playerWait:
                    case playerWalk:
                    case playerLanding:
                    case playerDead:
                    case playerDrop:
                    case playerBorder:
                    case playerBoring:
                    case playerChewingGum:
                    case playerRaiseUp:
                    case playerRespawn:
                    case playerRun:
                    case playerCry:
                        if (!dropBombeInAir) {
                            changeState(playerJump);
                        }
                        break;
                    case playerShot:
                        if (previousState != playerJump && previousState != playerStartFall && previousState != playerFall) {
                            if (!dropBombeInAir) {
                                changeState(playerJump);
                            }
                            
                        }
                        break;
                    case playerStartFall:
                    case playerFall:
                    case playerJump:
                    case playerKill:
                    case playerKnockOut:
                        break;
                }
            }
            /********************************
             * BOUTON POUSSE BOMBE VERS HAUT
             *******************************/
            if (keystate & keyPadY) {
                
                switch (state) {
                    case playerWait:
                    case playerWalk:
                    case playerLanding:
                    case playerBorder:
                    case playerBoring:
                    case playerChewingGum:
                    case playerRun:
                    case playerCry:
                    case playerStartFall:
                    case playerJump:
                    case playerFall:
                        adjustPositionBottom();
                        changeState(playerShot);
                        shotBombeUpper = true;
                        break;
                    case playerDrop:
                        if (animIdx > 0) {
                            adjustPositionBottom();
                            changeState(playerShot);
                            shotBombeUpper = true;
                        }
                        break;
                    case playerRaiseUp:
                    case playerRespawn:
                    case playerKill:
                    case playerDead:
                    case playerShot:
                    case playerKnockOut:
                        break;
                }
                
            }
            /********************************
             * BOUTON POSE / POUSSE BOMBE
             *******************************/
            if (keystate & keyPadA) {
                //std::cout<<"pousse pose\n";
                switch (state) {
                    case playerWait:
                    case playerWalk:
                    case playerLanding:
                        
                    case playerBoring:
                    case playerChewingGum:
                    case playerRaiseUp:
                    case playerRespawn:
                    case playerRun:
                    case playerCry:
                        //TODO verifier la présence d'une bombe
                        if (!dropBombeInAir) {
                            changeState(playerDrop);
                            adjustPositionBottom();
                        }
                        break;
                    case playerDrop:
                        //TODO verifier la présence d'une bombe
                        //					if (animIdx > 0) {
                        //						changeState(playerShot);
                        //						shotBombeUpper = false;
                        //					}
                        break;
                    case playerJump:
                    case playerStartFall:
                    case playerFall:
                        //std::cout<<"ici";
                        if (!dropBombeInAir) {
                            dropBombeInAir = true;
                            Sound::Instance().playSoundPutBombe();
                            //TODO Ajouter une bombe
                            changeState(playerShot);
                        }
                        break;
                    case playerShot:
                    case playerBorder:
                    case playerKill:
                    case playerDead:
                    case playerKnockOut:
                        break;
                }
            }
        }
        
        int acc = 0;
        switch (state) {
            case playerWait:
                break;
            case playerWalk:
                break;
            case playerJump:
                if (animIdx >= animIdxMax) {
                    changeState(playerStartFall);
                } else {
                    switch (animIdx) {
                        case 0:
                            acc = 13;
                            break;
                        case 1:
                            acc = 13;
                            break;
                        case 2:
                            acc = 10;
                            break;
                        case 3:
                            acc = 8;
                            break;
                        case 4:
                            acc = 7;
                            break;
                        case 5:
                            acc = 4;
                            break;
                        case 6:
                            acc = 4;
                            break;
                        case 7:
                            acc = 3;
                            break;
                        case 8:
                            acc = 2;
                            break;
                        case 9:
                            acc = 1;
                            break;
                            
                    }
                    //acc = round(10 * exp(-0.22 * animIdx) + 1);
                    //std::cout<<"jump acc: "<<acc<<"\n";
                    y -= acc;
                }
                break;
            case playerStartFall:
                if (animIdx >= animIdxMax) {
                    changeState(playerFall);
                    playerFalling = true;
                } else {
                    if (animIdx == 1) {
                        acc = 2;
                    } else if (animIdx == 2) {
                        if (y % 5 == 0) {
                            acc = 5;
                        } else {
                            acc = 3;
                        }
                    } else {
                        acc = 5;
                    }
                    y += acc;
                    
                }
                break;
            case playerFall:
                break;
            case playerLanding:
                if (animIdx >= animIdxMax) {
                    if (playerIsSad) {
                        changeState(playerCry);
                    } else {
                        changeState(playerWait);
                    }
                }
                break;
            case playerKill:
                if (animIdx >= animIdxMax) {
                    changeState(playerDead);
                }
                break;
            case playerDead:
                break;
            case playerShot:
                if (dropBombeInAir) {
                    if (playerFalling) {
                        //std::cout<<"shot + falling ! ";
                        acc = (int)round(10 * exp(-0.22 * (animIdx + 5)) + 1);
                        y -= acc;
                        y -= 6;
                    } else {
                        //std::cout<<"shot + et non falling ! ";
                        y -= 2;
                    }
                    if (animIdx >= animIdxMax - 2) {
                        changeState(playerStartFall);
                        dropBombeInAir = false;
                    }
                } else {
                    if (animIdx >= animIdxMax) {
                        if ((!hitboxPoint[2] && !hitboxPoint[3]) || (!hitboxPoint[3] && !hitboxPoint[4])) {
                            changeState(playerFall);
                            playerFalling = true;
                        } else {
                            if (playerIsSad) {
                                changeState(playerCry);
                            } else {
                                changeState(playerWait);
                            }
                        }
                    }
                }
                break;
            case playerDrop:
                
                if (animIdx >= animIdxMax) {
                    if (playerIsSad) {
                        changeState(playerCry);
                    } else {
                        changeState(playerWait);
                    }
                }
                
                break;
            case playerBorder:
                break;
            case playerBoring:
                if (animIdx >= animIdxMax) {
                    inactivityCounter = 0;
                    if (playerIsSad) {
                        changeState(playerCry);
                    } else {
                        changeState(playerWait);
                    }
                }
                break;
            case playerChewingGum:
                if (animIdx >= animIdxMax) {
                    inactivityCounter = 0;
                    if (playerIsSad) {
                        changeState(playerCry);
                    } else {
                        changeState(playerWait);
                    }
                }
                break;
            case playerKnockOut:
                if (animIdx >= animIdxMax) {
                    changeState(playerRaiseUp);
                }
                break;
            case playerRaiseUp:
                if (animIdx >= animIdxMax) {
                    if (playerIsSad) {
                        changeState(playerCry);
                    } else {
                        changeState(playerWait);
                    }
                }
                break;
            case playerRespawn:
                if (animIdx >= animIdxMax) {
                    if (playerIsSad) {
                        changeState(playerCry);
                    } else {
                        changeState(playerWait);
                        protection = false;
                    }
                }
                break;
            case playerRun:
                break;
            case playerCry:
                break;
        }
        
        /***********************************************************************
         * Gestion des colisions avec les platformes
         ***********************************************************************/
        calcPoint(platformGrid);
        
        if (hitboxPoint[0] && hitboxPoint[1] && !lockLeftDirection && y > 0) {
            adjustPositionLeft();
            //std::cout<<"je cogne par la gauche\n";
        }
        
        if (hitboxPoint[6] && hitboxPoint[5] && !lockRightDirection && y > 0) {
            adjustPositionRight();
            //std::cout<<"je cogne par la droite\n";
        }
        
        if ((hitboxPoint[0] || hitboxPoint[1]) && !lockLeftDirection) {
            //std::cout<<"Bloque gauche\n";
            lockLeftDirection = true;
        }
        
        if (!hitboxPoint[0] && !hitboxPoint[1] && lockLeftDirection) {
            //std::cout<<"Debloque gauche\n";
            lockLeftDirection = false;
        }
        
        if ((hitboxPoint[5] || hitboxPoint[6]) && !lockRightDirection) {
            lockRightDirection = true;
            //std::cout<<"Bloque droite\n";
        }
        
        if (!hitboxPoint[5] && !hitboxPoint[6] && lockRightDirection) {
            lockRightDirection = false;
            //std::cout<<"Debloque droite\n";
        }
        
        if (!hitboxPoint[2] && hitboxPoint[3] && hitboxPoint[4] && (state == playerWait || state == playerCry) && previousDirection == playerGoLeft) {
            //std::cout<<"Sur le bord GAUCHE\n";
            changeState(playerBorder);
        }
        
        if (hitboxPoint[2] && hitboxPoint[3] && !hitboxPoint[4] && (state == playerWait || state == playerCry) && previousDirection == playerGoRight) {
            //std::cout<<"Sur le bord DROIT\n";
            changeState(playerBorder);
        }
        
        /****************************************
         * Gestion de l'attérissage
         ****************************************/
        if (((hitboxPoint[2] && hitboxPoint[3]) || (hitboxPoint[3] && hitboxPoint[4])) && (y % 20 <= 5 || y % 20 == 0)
            && (playerFalling || state == playerStartFall)) {
            if (!hitboxPoint[7]) {
                //std::cout<<"j'atteris\n";
                y = y - (y % 20);
                changeState(playerLanding);
                playerFalling = false;
            }
        }
        
        /****************************************
         * Gestion de la chute d'une plateform
         ****************************************/
        if (hitboxPoint[2] && !hitboxPoint[3] && !hitboxPoint[4] && state != playerStartFall && !playerFalling && state != playerJump) {
            changeState(playerStartFall);
            //std::cout<<"je tombe par la droite\n";
        }
        
        if (!hitboxPoint[2] && !hitboxPoint[3] && hitboxPoint[4] && state != playerStartFall && !playerFalling && state != playerJump) {
            changeState(playerStartFall);
            //std::cout<<"je tombe par la gauche\n";
        }
        
        /****************************************
         * rattrapage du bord d'une plateforme
         ****************************************/
        if (hitboxPoint[8] && !hitboxPoint[3] && !hitboxPoint[0] && playerMove && y % 20 <= 12 && direction == playerGoLeft) {
            //std::cout<<"je me rattrape \n";
            lockLeftDirection = false;
            if (state != playerJump) {
                if (playerCanRun) {
                    changeState(playerRun);
                } else {
                    changeState(playerWalk);
                }
                playerFalling = false;
                y = y - (y % 20);
            }
        }
        
        if (hitboxPoint[9] && !hitboxPoint[3] && !hitboxPoint[6] && playerMove && y % 20 <= 12 && direction == playerGoRight) {
            //std::cout<<"je me rattrape \n";
            lockRightDirection = false;
            if (state != playerJump) {
                y = y - (y % 20);
                if (playerCanRun) {
                    changeState(playerRun);
                } else {
                    changeState(playerWalk);
                }
                playerFalling = false;
            }
        }
        
        /****************************************
         * Déplacement joueur gauche ou droite
         ****************************************/
        if (playerMove) {
            if (direction == playerGoLeft && !lockLeftDirection) {
                if (playerCanRun) {
                    x -= playerSpeedRun;
                } else {
                    x -= playerSpeed;
                }
                //bloquage gauche bord d'écran
                if (x <= playerHitboxWidth / 2) {
                    //std::cout<< "je touche l'écran\n";
                    x = playerHitboxWidth / 2;
                }
            } else if (direction == playerGoRight && !lockRightDirection) {
                if (playerCanRun) {
                    x += playerSpeedRun;
                } else {
                    x += playerSpeed;
                }
                //bloquage droit bord d'écran
                if (x + (playerHitboxWidth / 2) >= 400 - playerHitboxWidth / 2) {
                    //std::cout<<"je touche l'ecran\n";
                    x = 400 - playerHitboxWidth / 2;
                }
            }
        }
        
        /****************************************
         * Chute du joueur
         ****************************************/
        if (playerFalling && state != playerStartFall) {
            y += playerFallSpeed;
        }
        
        /****************************************
         * Mise à jour de la hitbox
         ****************************************/
        updateHitBox(x - (int)floor(playerHitboxWidth / 2), y - playerHitboxHeight);
    }
    
    /****************************************
     * Incrément animation
     ****************************************/
    if (animIdx >= animIdxMax) {
        if (state == playerBorder) {
            animIdx = 10;
        } else {
            animIdx = 0;
        }
    }
    
    /****************************************
     * Dessin
     ****************************************/
    drawHimself(dest);
}

/****************************
 *
 * ----- DRAWING PART -----
 *
 ****************************/

void Player::drawHimself(SDL_Surface * dest) {
    SDL_Surface * t = NULL;
    if (type == 0) {
        /****************************
         *   ----- IGOR PART -----
         ****************************/
        switch (state) {
            case playerWait:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_wait", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_wait_flip", animIdx);
                }
                break;
            case playerWalk:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_walk", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_walk_flip", animIdx);
                }
                break;
            case playerJump:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_jump", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_jump_flip", animIdx);
                }
                break;
            case playerStartFall:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_startFall", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_startFall_flip", animIdx);
                }
                break;
            case playerFall:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_fall", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_fall_flip", animIdx);
                }
                break;
            case playerLanding:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_landing", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_landing_flip", animIdx);
                }
                break;
            case playerKill:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_kill", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_kill_flip", animIdx);
                }
                break;
            case playerDead:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_wait", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_wait_flip", animIdx);
                }
                break;
            case playerShot:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_shotbombe", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_shotbombe_flip", animIdx);
                }
                break;
            case playerDrop:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_dropbombe", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_dropbombe_flip", animIdx);
                }
                break;
            case playerBorder:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_bordplateform", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_bordplateform_flip", animIdx);
                }
                break;
            case playerBoring:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_boring", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_boring_flip", animIdx);
                }
                break;
            case playerChewingGum:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_chewinggum", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_chewinggum_flip", animIdx);
                }
                break;
            case playerKnockOut:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_knockout", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_knockout_flip", animIdx);
                }
                break;
            case playerRaiseUp:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_raise_up", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_raise_up_flip", animIdx);
                }
                break;
            case playerRespawn:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_respawn", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_respawn_flip", animIdx);
                }
                break;
            case playerRun:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_run", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_run_flip", animIdx);
                }
                break;
            case playerCry:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("igor_right_cry", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("igor_right_cry_flip", animIdx);
                }
                break;
        }
    } else {
        /****************************
         *   ----- SANDY PART -----
         ****************************/
        switch (state) {
            case playerWait:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_wait", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_wait_flip", animIdx);
                }
                break;
            case playerWalk:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_walk", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_walk_flip", animIdx);
                }
                break;
            case playerJump:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_jump", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_jump_flip", animIdx);
                }
                break;
            case playerStartFall:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_startFall", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_startFall_flip", animIdx);
                }
                break;
            case playerFall:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_fall", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_fall_flip", animIdx);
                }
                break;
            case playerLanding:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_landing", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_landing_flip", animIdx);
                }
                break;
            case playerKill:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_kill", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_kill_flip", animIdx);
                }
                break;
            case playerDead:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_wait", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_wait_flip_flip", animIdx);
                }
                break;
            case playerShot:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_shotbombe", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_shotbombe_flip", animIdx);
                }
                break;
            case playerDrop:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_dropbombe", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_dropbombe_flip", animIdx);
                }
                break;
            case playerBorder:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_bordplateform", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_bordplateform_flip", animIdx);
                }
                break;
            case playerBoring:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_boring", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_boring_flip", animIdx);
                }
                break;
            case playerChewingGum:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_chewinggum", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_chewinggum_flip", animIdx);
                }
                break;
            case playerKnockOut:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_knockout", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_knockout_flip", animIdx);
                }
                break;
            case playerRaiseUp:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_raise_up", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_raise_up_flip", animIdx);
                }
                break;
            case playerRespawn:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_respawn", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_respawn_flip", animIdx);
                }
                break;
            case playerRun:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_run", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_run_flip", animIdx);
                }
                break;
            case playerCry:
                if (previousDirection == playerGoRight) {
                    t = Sprite::Instance().getAnimation("sandy_right_cry", animIdx);
                } else {
                    t = Sprite::Instance().getAnimation("sandy_right_cry_flip", animIdx);
                }
                break;
        }
    }
    
    
    switch (state) {
        case playerShot:
            copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h) + 17);
            break;
         case playerRespawn:
            copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h) + 22);
            break;
            
        case playerWait:
        case playerWalk:
        case playerLanding:
        case playerBoring:
        case playerRaiseUp:
        case playerRun:
        case playerCry:
        case playerStartFall:
        case playerFall:
        case playerDrop:
        case playerJump:
        case playerKill:
        case playerDead:
        case playerKnockOut:
            copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h));
            break;
        case playerChewingGum:
            if (previousDirection == playerGoLeft) {
                copySurfaceToBackRenderer(t, dest, (x - (t->w / 2) - 3) + leftPadding, y - (t->h) + 6);
            } else {
                copySurfaceToBackRenderer(t, dest, (x - (t->w / 2) + 3) + leftPadding, y - (t->h) + 6);
            }
            break;
        case playerBorder:
            if (previousDirection == playerGoLeft) {
                copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) - 10 + leftPadding, y - (t->h) + 10);
            } else {
                copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + 10 + leftPadding, y - (t->h) + 10);
            }
            break;
    }
    /*
    SDL_Rect * rectt = new SDL_Rect;
    rectt->h = this->getRect().h;
    rectt->w = this->getRect().w;
    rectt->x = this->getRect().x+leftPadding;
    rectt->y = this->getRect().y;
    SDL_FillRect(dest, rectt, SDL_MapRGB(dest->format, 255, 0, 0));
    */
    animIdx++;
}

void Player::changeState(int newState) {
    //stockage de l'état précédent
    previousState = state;
    state = newState;
    prevAnimIdx = animIdx;
    prevAnimIdxMax = animIdxMax;
    animIdx = 0;
    //std::cout<<"change state : "<<newState<<"\n";
    switch (state) {
        case playerWait:
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_wait");
            dropBombeInAir = false;
            break;
        case playerWalk:
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_walk");
            dropBombeInAir = false;
            break;
        case playerJump:
            Sound::Instance().playSoundIgorJump();
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_jump");
            break;
        case playerStartFall:
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_startFall");
            dropBombeInAir = false;
            break;
        case playerFall:
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_fall");
            dropBombeInAir = false;
            break;
        case playerLanding:
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_landing");
            dropBombeInAir = false;
            break;
        case playerKill:
            dropBombeInAir = false;
            Sound::Instance().playSoundDead();
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_kill");
            break;
        case playerDead:
            dropBombeInAir = false;
            break;
        case playerShot:
            Sound::Instance().playSoundKickBombe();
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_shotbombe");
            break;
        case playerDrop:
            Sound::Instance().playSoundPutBombe();
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_dropbombe");
            break;
        case playerBorder:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_bordplateform");
            break;
        case playerBoring:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_boring");
            break;
        case playerChewingGum:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_chewinggum");
            break;
        case playerKnockOut:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_knockout");
            break;
        case playerRaiseUp:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_raise_up");
            break;
        case playerRespawn:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_respawn");
            break;
        case playerRun:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_run");
            break;
        case playerCry:
            dropBombeInAir = false;
            animIdxMax = Sprite::Instance().getAnimationSize("igor_right_cry");
            break;
    }
}

void Player::calcPoint(bool * platformGrid) {
    //reset point table
    memset(hitboxPoint, false, 10);
    int xx = x - playerHitboxWidth / 2;
    int yy = y - (playerHitboxHeight);
    int xCalc = 0;
    int yCalc = 0;
    for (int i = 0; i < 10; i++) {
        switch (i) {
            case 0:
                xCalc = xx;
                yCalc = yy;
                break;
            case 1:
                xCalc = xx;
                yCalc = y - 3;
                break;
            case 2:
                xCalc = x - 6;
                yCalc = y;
                break;
            case 3:
                xCalc = x;
                yCalc = y;
                break;
            case 4:
                xCalc = x + 6;
                yCalc = y;
                break;
            case 5:
                xCalc = xx + playerHitboxWidth;
                yCalc = y - 3;
                break;
            case 6:
                xCalc = xx + playerHitboxWidth;
                yCalc = yy;
                break;
            case 7:
                xCalc = x;
                yCalc = yy;
                break;
            case 8:
                xCalc = xx;
                yCalc = y;
                break;
            case 9:
                xCalc = xx + playerHitboxWidth;
                yCalc = y;
                break;
        }
        xCalc = (xCalc - (xCalc % 20)) / 20;
        yCalc = (yCalc - (yCalc % 20)) / 20;
        if (xCalc < 0) {
            xCalc = 0;
        }
        if (xCalc > 19) {
            xCalc = 19;
        }
        if (yCalc < 0) {
            yCalc = 0;
        } else if (yCalc > 24) {
            yCalc = 24;
        }
        hitboxPoint[i] = platformGrid[xCalc + 20 * yCalc];
    }
}

void Player::adjustPositionLeft() {
    int xcalc = x - playerHitboxWidth / 2;
    if ((xcalc % 20) != 19) {
        x = (((xcalc - (xcalc % 20)) + 20) + playerHitboxWidth / 2) - 1;
    }
}

void Player::adjustPositionRight() {
    int xcalc = x + playerHitboxWidth / 2;
    x = ((xcalc - (xcalc % 20))) - playerHitboxWidth / 2;
}

void Player::adjustPositionBottom() {
    y = y - (y % 5);
}

void Player::changeLevel(bool first) {
    if (first) {
        y = -100;
    } else {
        y = -300;
    }
    playerIsSad = false;
}

void Player::playerKilled() {
    changeState(playerKill);
}

void Player::playerRespawnWithPosition(int x, int y) {
    this->x = x;
    this->y = y;
    playerCanRun = false;
    protection = true;
    changeState(playerRespawn);
}

bool Player::isDead() {
    return state == playerDead;
}

void Player::playerGoSad() {
    playerIsSad = true;
}

void Player::playerCanRunNow() {
    playerCanRun = true;
}

SDL_Rect Player::getHitbox(){
    return this->getRect();
}

bool Player::playerIsAlive(){
    if(state == playerKill ||state == playerDead ||state == playerRespawn){
        return false;
    }
    return true;
}

bool Player::playerIsProtected(){
    return protection;
}
