/*
 * Game.cpp
 *
 *  Created on: Jun 6, 2017
 *      Author: Inisigme
 */

#include "Game.h"

void updatePos(float *pfData) {



	float dX = pfData[1];
	float dY = pfData[0];

	if(dX < 1500.f && dX > -1500.f) dX = 0;
	if(dY < 1500.f && dY > -1500.f) dY = 0;

	dX /= 1200.f;
	dY /= 1200.f;

	if(dX > 5.f) dX = 5.f;
	if(dY > 5.f) dY = 5.f;
	if(dX < -5.f) dX = -5.f;
	if(dY < -5.f) dY = -5.f;

	dX*=3;
	dY*=3;

	state.velX += dX;
	state.velY += dY;

	float threshold = 40.f;

	if(state.velX > threshold) state.velX = threshold;
	if(state.velX < -threshold) state.velX = -threshold;

	if(state.velY > threshold) state.velY = threshold;
	if(state.velY < -threshold) state.velY = -threshold;

	if(state.playerPosX < 235 && state.playerPosX > 5)
		state.playerPosX += state.velX *state.dTime;
	else {
		state.velX = 0.f;
		state.velY = 0.f;
		if(state.playerPosX > 235) state.playerPosX = 230;
		else state.playerPosX = 6;
	}

	if(state.playerPosY < 315 && state.playerPosY > 5){
		if ( !state.locked)
			state.playerPosY += state.velY *state.dTime;
	} else {
		state.velX = 0.f;
		state.velY = 0.f;
		if(state.playerPosY > 315) state.playerPosY = 314;
		else state.playerPosY = 6;
	}

}

void initState() {
	state.locked = 0;
	state.size = 1000;
	state.playerPosX = 100.f;
	state.playerPosY = 300.f;
	state.velX = 0.f;
	state.velY = 0.f;
	state.dTime = 0.1f;
	state.offset = 150.0f;
	state.hp = 3.0f;
	state.time = 0.0f;
	RNG_Init();
	for(int i = 0; i < state.size; i++){
		state.meteors[i][0] =  ((float)RNG_Rand()/(float)UINT32_MAX) * 240.0;
		state.meteors[i][1] =  -((float)RNG_Rand()/(float)UINT32_MAX) * 18110.0;
		state.meteors[i][2] =  ((float)RNG_Rand()/(float)UINT32_MAX) * 5.f;
	}
}

void drawState() {
	for(int i = 0; i < state.size; i++) {
		//drawSquare(state.meteors[i][0],state.meteors[i][1],2);
		//BSP_LCD_DrawPixel(state.meteors[i][0], state.meteors[i][1], 0);
	}

}
