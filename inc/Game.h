/*
 * Game.h
 *
 *  Created on: Jun 6, 2017
 *      Author: Inisigme
 */

#ifndef GAME_H_
#define GAME_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "random.h"
#include "simpleLCD.h"

struct State {
	float playerPosX;
	float playerPosY;
	float velX;
	float velY;
	float dTime;
	int scores;
	float meteors [1000][3];
	float offset;
	float hp;
	float time;
	unsigned int size;
	int locked;
} state;

void initState();
void updatePos(float *);
int colisions();
void drawState();

#endif /* GAME_H_ */
