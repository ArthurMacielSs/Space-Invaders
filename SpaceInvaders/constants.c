#include "invaders.h"



const int SCREEN_W = 1800;
const int SCREEN_H = 900;
const int GRASS_H = 30;
const float FPS = 100;

const int NAVE_W = 50;
const int NAVE_H = 40;
const int SHIP_SPEED = 6*2;

const int ALIEN_W = 50;
const int ALIEN_H = 40;
const int ROW_ALIEN[PHASES_NUMBER] = {4, 5,5,6,6,6};
const int COLUMN_ALIEN[PHASES_NUMBER] = {6,7,8,9,10,11};
const int ALIEN_X_SPEED[PHASES_NUMBER] = {2,3,4,5,6,6};
const int ALIEN_SPACEMENT = 30;

const int SHOT_SPEED = 8*5;