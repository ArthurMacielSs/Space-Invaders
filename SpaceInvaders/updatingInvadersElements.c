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

/*void update_alien (Alien *alien){
// alien x vel fica neg
	if(alien->x + ALIEN_W + alien->x_vel > SCREEN_W || alien->x + alien->x_vel < 0) {
		alien->y += alien->y_vel;
		alien->x_vel *= -1;
	}
	alien->x += alien->x_vel;
}*/

void update_all_aliens(int linha, int coluna, Alien bloco[linha][coluna]) {
    int should_reverse = 0;
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            Alien *teste = &bloco[i][j];
            if ((teste->x + ALIEN_W + teste->x_vel > SCREEN_W) || (teste->x + teste->x_vel < 0)) {
                should_reverse = 1;
                break;
            }
        }
        if (should_reverse) break;
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            Alien *teste = &bloco[i][j];
            if (should_reverse) {
                teste->y += teste->y_vel;
                teste->x_vel *= -1;
            }
            teste->x += teste->x_vel;
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

//pq não usa ponteiro ou referencia
void update_shots(int tam,struct Shot shots[tam]) {
    for (int i = 0; i < tam; i++) {
        if (shots[i].active) {
            shots[i].y += shots[i].speed;
            if (shots[i].y < 0) {
                shots[i].active = 0;  
            }
        }
    }
}
