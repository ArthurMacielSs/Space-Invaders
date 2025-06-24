#include "invaders.h"
#include <stdio.h>
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
void update_all_aliens (int linha, int coluna, Alien bloco [linha][coluna]){
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			update_alien(&bloco[i][j]);

		}
	}
}
int colisao_alien_solo(Alien alien){
	if(alien.y + ALIEN_H>SCREEN_H-GRASS_H){
		printf("foi \n");
		return 1;
	}
	else{
		return 0;
	}
}

int colisao_all_alien_solo(int playng, int linha, int coluna, Alien bloco [linha][coluna] ){
	playng=0;
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			playng =colisao_alien_solo(bloco[i][j]);
			if(playng==1){
				break;
				return playng;
			}

		}
	}
	return playng;
}