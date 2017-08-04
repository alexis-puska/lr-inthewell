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
	playerMove = false;
	insidePlatform = false;
	lockLeftDirection = false;
	lockRightDirection = false;
	animIdxMax = Sprite::Instance().getAnimationSize("igor_right_wait");
	initHitBox(x - floor(playerHitboxWidth / 2), y - playerHitboxHeight, playerHitboxWidth, playerHitboxHeight);
}

Player::~Player() {
}

void Player::doSomething(SDL_Surface * dest, bool * platformGrid) {

	//acceleration -> -5exp(-0.5x)+5
	//glaçon -> 50 exp(-0.02x)

	/***************************
	 * --- getKeystateValue ---
	 ***************************/
	unsigned short keystate = *in_keystate;

	/***************************
	 * --- Value correction ---
	 ***************************/
	if (y > 500) {
		y = -50;
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
	} else {

		/*********************
		 * BOUTON TEMPORAIRE
		 ********************/
		if (keystate & keyPadUp) {
			y -= 5;
		}
		if (keystate & keyPadDown) {
			y += 5;
		}
		/*********************
		 * BOUTON TEMPORAIRE
		 ********************/

		if (keystate & keyPadLeft) {
			direction = playerGoLeft;
			previousDirection = playerGoLeft;
			switch (state) {
				case playerWait:
				case playerLanding:
				case playerKill:
				case playerShot:
				case playerDrop:
				case playerBorder:
				case playerBoring:
				case playerChewingGum:
				case playerKnockOut:
				case playerRaiseUp:
				case playerRespawn:
				case playerCry:
					if (playerCanRun) {
						changeState(playerRun);
						playerMove = true;
					} else {
						changeState(playerWalk);
						playerMove = true;
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
				case playerKill:
				case playerShot:
				case playerDrop:
				case playerBorder:
				case playerBoring:
				case playerChewingGum:
				case playerKnockOut:
				case playerRaiseUp:
				case playerRespawn:
				case playerCry:
					if (playerCanRun) {
						changeState(playerRun);
						playerMove = true;
					} else {
						changeState(playerWalk);
						playerMove = true;
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
				case playerKill:
				case playerDead:
				case playerShot:
				case playerDrop:
				case playerBorder:
				case playerBoring:
				case playerChewingGum:
				case playerKnockOut:
				case playerRaiseUp:
				case playerRespawn:
				case playerRun:
				case playerCry:
					changeState(playerJump);
					break;
				case playerStartFall:
				case playerFall:
				case playerJump:
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
				case playerRaiseUp:
				case playerRespawn:
				case playerRun:
				case playerCry:
				case playerStartFall:
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
				case playerJump:
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
			fprintf(stderr, "pousse pose\n");
			switch (state) {
				case playerWait:
				case playerWalk:
				case playerLanding:
				case playerShot:
				case playerBoring:
				case playerChewingGum:
				case playerRaiseUp:
				case playerRespawn:
				case playerRun:
				case playerCry:
				case playerStartFall:
				case playerFall:
					//TODO verifier la présence d'une bombe
					changeState(playerDrop);
					adjustPositionBottom();
					shotBombeUpper = false;
					break;
				case playerDrop:
					//TODO verifier la présence d'une bombe
//					if (animIdx > 0) {
//						changeState(playerShot);
//						shotBombeUpper = false;
//					}
					break;
				case playerBorder:
				case playerJump:
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
				playerFalling = true;
			} else {
				acc = round(10 * exp(-0.22 * animIdx) + 1);
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
				changeState(playerWait);
			}
			break;
		case playerKill:
			break;
		case playerDead:
			break;
		case playerShot:
			if (animIdx >= animIdxMax) {
				changeState(playerWait);
			}
			break;
		case playerDrop:
			if (animIdx >= animIdxMax) {
				changeState(playerWait);
			}
			break;
		case playerBorder:
			break;
		case playerBoring:
			if (animIdx >= animIdxMax) {
				changeState(playerWait);
			}
			break;
		case playerChewingGum:
			if (animIdx >= animIdxMax) {
				changeState(playerWait);
			}
			break;
		case playerKnockOut:
			if (animIdx >= animIdxMax) {
				changeState(playerDead);
			}
			break;
		case playerRaiseUp:
			if (animIdx >= animIdxMax) {
				changeState(playerWait);
			}
			break;
		case playerRespawn:
			if (animIdx >= animIdxMax) {
				changeState(playerWait);
			}
			break;
		case playerRun:
			break;
		case playerCry:
			break;
	}

	if (hitboxPoint[3]) {
		fprintf(stderr, "x,y : %i %i %s %i\n", x, y, hitboxPoint[3] ? "true" : "false", y % 20);
	}

	updateHitBox(x - floor(playerHitboxWidth / 2), y - playerHitboxHeight);

	/***********************************************************************
	 * Gestion des colisions avec les platformes
	 ***********************************************************************/

	calcPoint(platformGrid);

	if (hitboxPoint[0] && hitboxPoint[1] && !lockLeftDirection && y > 0) {
		adjustPositionLeft();
		fprintf(stderr, "je cogne par la gauche\n");
	}
	if (hitboxPoint[6] && hitboxPoint[5] && !lockRightDirection && y > 0) {
		adjustPositionRight();
		fprintf(stderr, "je cogne par la droite\n");
	}

	if ((hitboxPoint[0] || hitboxPoint[1]) && !lockLeftDirection) {
		lockLeftDirection = true;
	}

	if (!hitboxPoint[0] && !hitboxPoint[1] && lockLeftDirection) {
		lockLeftDirection = false;
	}

	if ((hitboxPoint[5] || hitboxPoint[6]) && !lockRightDirection) {
		lockRightDirection = true;
	}

	if (!hitboxPoint[5] && !hitboxPoint[6] && lockRightDirection) {
		lockRightDirection = false;
	}

	if (y <= 0) {
		lockRightDirection = false;
		lockLeftDirection = false;
	}

//Gestion de l'attérissage
	if (((hitboxPoint[2] && hitboxPoint[3]) || (hitboxPoint[3] && hitboxPoint[4])) && (y % 20 <= 5 || y % 20 == 0)
			&& (playerFalling || state == playerStartFall)) {
		if (!hitboxPoint[7]) {
			y = y - (y % 20);
			changeState(playerLanding);
			playerFalling = false;
		}
	}

	if (!hitboxPoint[2] && !hitboxPoint[3] && hitboxPoint[4] && state != playerStartFall && !playerFalling && state != playerJump) {
		changeState(playerStartFall);
		fprintf(stderr, "je tombe par la gauche\n");
	}

//on commance a tomber d'une platforme pas la droite, on ajustera pas la position du joueur par la gauche.
	if (hitboxPoint[2] && !hitboxPoint[3] && !hitboxPoint[4] && state != playerStartFall && !playerFalling && state != playerJump) {
		changeState(playerStartFall);
		fprintf(stderr, "je tombe par la droite\n");
	}

	if (playerMove) {
		if (direction == playerGoLeft && !lockLeftDirection) {
			if (playerCanRun) {
				x -= playerSpeedRun;
			} else {
				x -= playerSpeed;
			}
			//bloquage gauche bord d'écran
			if (x <= playerHitboxWidth / 2) {
				fprintf(stderr, "je touche l'écran\n");
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
				fprintf(stderr, "je touche l'ecran\n");
				x = 400 - playerHitboxWidth / 2;
			}
		}
	}

//chute du joueur
	if (playerFalling && state != playerStartFall) {
		y += playerFallSpeed;
	}

//increment animation
	if (animIdx >= animIdxMax) {
		animIdx = 0;
	}

//dessin joueur
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
					t = Sprite::Instance().getAnimation("igor_right_wait_flip_flip", animIdx);
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
	if (state == playerShot) {
		copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h) + 17);
	} else {
		copySurfaceToBackRenderer(t, dest, (x - (t->w / 2)) + leftPadding, y - (t->h));
	}

	animIdx++;
}

void Player::changeState(int newState) {
	state = newState;
	animIdx = 0;
//fprintf(stderr, "change state : %i\n", newState);
	switch (state) {
		case playerWait:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_wait");
			break;
		case playerWalk:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_walk");
			break;
		case playerJump:
			Sound::Instance().playSoundIgorJump();
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_jump");
			break;
		case playerStartFall:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_startFall");
			break;
		case playerFall:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_fall");
			break;
		case playerLanding:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_landing");
			break;
		case playerKill:
			Sound::Instance().playSoundDead();
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_kill");
			break;
		case playerDead:
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
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_bordplateform");
			break;
		case playerBoring:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_boring");
			break;
		case playerChewingGum:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_chewinggum");
			break;
		case playerKnockOut:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_knockout");
			break;
		case playerRaiseUp:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_raise_up");
			break;
		case playerRespawn:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_respawn");
			break;
		case playerRun:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_run");
			break;
		case playerCry:
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_cry");
			break;
	}
}

void Player::calcPoint(bool * platformGrid) {
//reset point table
	memset(hitboxPoint, false, 8);
	int xx = x - playerHitboxWidth / 2;
	int yy = y - playerHitboxHeight;
	int xCalc = 0;
	int yCalc = 0;

	for (int i = 0; i < 8; i++) {
		switch (i) {
			case 0:
				xCalc = xx;
				yCalc = yy;
				break;
			case 1:
				xCalc = xx;
				yCalc = y - 4;
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
				yCalc = y - 4;
				break;
			case 6:
				xCalc = xx + playerHitboxWidth;
				yCalc = yy;
				break;
			case 7:
				xCalc = x;
				yCalc = yy;
				break;
		}
		xCalc = (xCalc - (xCalc % 20)) / 20;
		yCalc = (yCalc - (yCalc % 20)) / 20;
		if (xCalc < 0) {
			xCalc = 0;
		}
		if (xCalc > 400) {
			xCalc = 400;
		}
		if (yCalc < 0) {
			yCalc = 0;
		} else if (yCalc > 500) {
			yCalc = 500;
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
