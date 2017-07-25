#include "Player.h"

Player::Player(int x, int y, int type, unsigned short * in_keystate) :
		Position(x, y), Drawable() {
	this->type = type;
	this->state = playerWait;
	this->in_keystate = in_keystate;
	animIdx = 0;
	direction = playerGoRight;
	playerCanRun = false;
	animIdxMax = Sprite::Instance().getAnimationSize("igor_right_wait");
}

Player::~Player() {
}

void Player::doSomething(SDL_Surface * dest) {

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
	if (keystate == 0 && (state == playerWalk || state == playerRun)) {
		//player don't move
		state = playerWait;
	} else {
		if (keystate & keyPadUp) {
			y -= 5;
		}
		if (keystate & keyPadLeft) {

			if (state != playerWalk || state != playerRun) {
				if (playerCanRun) {
					state = playerRun;
					animIdxMax = Sprite::Instance().getAnimationSize("igor_right_run");
				} else {
					state = playerWalk;
					animIdxMax = Sprite::Instance().getAnimationSize("igor_right_walk");

				}
			}
			direction = playerGoLeft;
			x -= 5;
			if (playerCanRun) {
				x -= 5;
			}
		}
		if (keystate & keyPadDown) {
			y += 5;
		}
		if (keystate & keyPadRight) {
			if (state != playerWalk || state != playerRun) {
				if (playerCanRun) {
					state = playerRun;
					animIdxMax = Sprite::Instance().getAnimationSize("igor_right_run");
				} else {
					state = playerWalk;
					animIdxMax = Sprite::Instance().getAnimationSize("igor_right_walk");

				}
			}
			direction = playerGoRight;
			x += 5;
			if (playerCanRun) {
				x += 5;
			}

		}
		if (keystate & keyPadA) {
			if (state == playerWalk || state == playerRun || state == playerWait) {
				state = playerJump;
				Sound::Instance().playSoundIgorJump();
				animIdxMax = Sprite::Instance().getAnimationSize("igor_right_jump");
				animIdx = 0;
			}
		}
		if (keystate & keyPadX) {
			state = playerStartFall;
		}
		if (keystate & keyPadY) {
			if (playerCanRun) {
				playerCanRun = false;
			} else {
				playerCanRun = true;
			}
		}
	}

	if (state == playerJump) {
		int acc = 0;
		if (animIdx >= animIdxMax) {
			state = playerWait;
			animIdxMax = Sprite::Instance().getAnimationSize("igor_right_wait");
		} else {
			acc = floor(10 * exp(-0.2 * animIdx) + 1);
			y -= acc;
		}
	}

	switch (state) {
		case playerWait:
			break;
		case playerWalk:
			break;
		case playerJump:
			break;
		case playerStartFall:
			break;
		case playerFall:
			break;
		case playerLanding:
			break;
		case playerKill:
			break;
		case playerDead:
			break;
		case playerShot:
			break;
		case playerDrop:
			break;
		case playerBorder:
			break;
		case playerBoring:
			break;
		case playerChewingGum:
			break;
		case playerKnockOut:
			break;
		case playerRaiseUp:
			break;
		case playerRespawn:
			break;
		case playerRun:
			break;
		case playerCry:
			break;
	}

	/****************************
	 * ----- DRAWING PART -----
	 ****************************/
	if (animIdx >= animIdxMax) {
		animIdx = 0;
	}

	/****************************
	 *
	 * ----- DRAWING PART -----
	 *
	 ****************************/
	SDL_Surface * t = NULL;
	if (type == 0) {
		/****************************
		 *   ----- IGOR PART -----
		 ****************************/
		switch (state) {
			case playerWait:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_wait", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_wait_flip", animIdx);
				}
				break;
			case playerWalk:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_walk", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_walk_flip", animIdx);
				}
				break;
			case playerJump:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_jump", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_jump_flip", animIdx);
				}
				break;
			case playerStartFall:
			case playerFall:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_fall", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_fall_flip", animIdx);
				}
				break;
			case playerLanding:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_landing", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_landing_flip", animIdx);
				}
				break;
			case playerKill:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_kill", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_kill_flip", animIdx);
				}
				break;
			case playerDead:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_wait", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_wait_flip_flip", animIdx);
				}
				break;
			case playerShot:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_shotbombe", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_shotbombe_flip", animIdx);
				}
				break;
			case playerDrop:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_dropbombe", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_dropbombe_flip", animIdx);
				}
				break;
			case playerBorder:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_bordplateform", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_bordplateform_flip", animIdx);
				}
				break;
			case playerBoring:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_boring", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_boring_flip", animIdx);
				}
				break;
			case playerChewingGum:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_chewinggum", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_chewinggum_flip", animIdx);
				}
				break;
			case playerKnockOut:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_knockout", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_knockout_flip", animIdx);
				}
				break;
			case playerRaiseUp:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_raise_up", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_raise_up_flip", animIdx);
				}
				break;
			case playerRespawn:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_respawn", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_respawn_flip", animIdx);
				}
				break;
			case playerRun:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("igor_right_run", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("igor_right_run_flip", animIdx);
				}
				break;
			case playerCry:
				if (direction == playerGoRight) {
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
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_wait", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_wait_flip", animIdx);
				}
				break;
			case playerWalk:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_walk", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_walk_flip", animIdx);
				}
				break;
			case playerJump:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_jump", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_jump_flip", animIdx);
				}
				break;
			case playerStartFall:
			case playerFall:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_fall", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_fall_flip", animIdx);
				}
				break;
			case playerLanding:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_landing", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_landing_flip", animIdx);
				}
				break;
			case playerKill:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_kill", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_kill_flip", animIdx);
				}
				break;
			case playerDead:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_wait", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_wait_flip_flip", animIdx);
				}
				break;
			case playerShot:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_shotbombe", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_shotbombe_flip", animIdx);
				}
				break;
			case playerDrop:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_dropbombe", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_dropbombe_flip", animIdx);
				}
				break;
			case playerBorder:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_bordplateform", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_bordplateform_flip", animIdx);
				}
				break;
			case playerBoring:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_boring", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_boring_flip", animIdx);
				}
				break;
			case playerChewingGum:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_chewinggum", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_chewinggum_flip", animIdx);
				}
				break;
			case playerKnockOut:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_knockout", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_knockout_flip", animIdx);
				}
				break;
			case playerRaiseUp:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_raise_up", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_raise_up_flip", animIdx);
				}
				break;
			case playerRespawn:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_respawn", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_respawn_flip", animIdx);
				}
				break;
			case playerRun:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_run", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_run_flip", animIdx);
				}
				break;
			case playerCry:
				if (direction == playerGoRight) {
					t = Sprite::Instance().getAnimation("sandy_right_cry", animIdx);
				} else {
					t = Sprite::Instance().getAnimation("sandy_right_cry_flip", animIdx);
				}
				break;
		}
	}
	copySurfaceToBackRenderer(t, dest, x - (t->w / 2), y - (t->h));
	animIdx++;
}
