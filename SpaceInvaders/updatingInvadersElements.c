#include "invaders.h"
#include <allegro5/allegro_primitives.h>


void update_nave(Nave *nave)
{
	if (nave->dir && nave->x+ nave->vel <=SCREEN_W)
	{
		nave->x += nave->vel;
	}
	if (nave->esq && nave->x - nave->vel>=0)
	{
		nave->x -= nave->vel;
	}
}

void update_alien (Alien *alien){
// alien x vel fica neg
	if(alien->x + ALIEN_W + alien->x_vel > SCREEN_W || alien->x + alien->x_vel < 0) {
		alien->y += alien->y_vel;
		alien->x_vel *= -1;
	}
	alien->x += alien->x_vel;
}

int colisao_alien_solo(Alien alien){
	if(alien.y + ALIEN_H>SCREEN_H-GRASS_H){
		return 1;
	}
	else{
		return 0;
	}
}