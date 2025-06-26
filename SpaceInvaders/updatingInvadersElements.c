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

//certificar que entendi 
void update_all_aliens(int linha, int coluna, Alien bloco[linha][coluna]) {
    int should_reverse = 0;
    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
            Alien *teste = &bloco[i][j];
			//pq usa teste->is_active ao inves de *teste->is_active
			if(teste->is_active==1){
            if ((teste->x + ALIEN_W + teste->x_vel > SCREEN_W) || (teste->x + teste->x_vel < 0)) {
                should_reverse = 1;
                break;
            }
		}
        }
        if (should_reverse) break;
    }

    for (int i = 0; i < linha; i++) {
        for (int j = 0; j < coluna; j++) {
			//pq usa &
			if(&bloco[i][j]){
            Alien *teste = &bloco[i][j];
            if (should_reverse) {
                teste->y += teste->y_vel;
                teste->x_vel *= -1;
            }
            teste->x += teste->x_vel;
        }
	}
    }
}
int colisao_alien_solo(Alien alien){
	if(alien.y + ALIEN_H>=SCREEN_H-GRASS_H){
		printf("\n morreu por grama");
		return 1;
	}
	else{
		return 0;
	}
	
}



int colisao_all_alien_solo(int playng, int linha, int coluna, Alien bloco [linha][coluna], int *pontuacao ){
	playng=0;
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			playng =colisao_alien_solo(bloco[i][j]);
			if(playng==1){
				*pontuacao -=500;
				break;
				return playng;
			}

		}
	}
	return playng;
}
int colisao_alien_nave(Alien alien, Nave nave, int *pontuacao){
	if(alien.is_active==1){
	if((alien.y+ALIEN_H>=nave.y)&&(((alien.x>=nave.x-NAVE_W/2)&&(alien.x<=nave.x+NAVE_W/2))||((alien.x+ALIEN_W>=nave.x-NAVE_W/2)&&(alien.x+ALIEN_W<=nave.x+NAVE_W/2)))){
		printf("\ncolidiu");
		*pontuacao -= 500;
		return 0;
	}
	else{
		return 1;
	}
}
//ver pq pus esse return1
return 1;

}

int colisao_all_alien_nave(int linha, int coluna, Alien bloco[linha][coluna], Nave nave, int *pontuacao){
	int playing=1;
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			playing=colisao_alien_nave(bloco[i][j], nave, pontuacao);
			if(playing==0){
				return playing;
				break;
			}
		}
		if(playing==0){
				return playing;
				break;
			}
	}
	return playing;
}
//pq não usa ponteiro ou referencia
void update_shots(struct Shot *shots) {
        if (shots->active) {
            shots->y += shots->speed;
            if (shots->y < 0) {
                shots->active = 0;  
            }
        }
    }


void shot_hit(struct Shot *shot, int linha, int coluna, Alien bloco [linha][coluna], int *pontuacao){
	if(shot->active){
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			if(bloco[i][j].is_active){
			if(((shot->y>=bloco[i][j].y)&& (shot->y<=bloco[i][j].y+ALIEN_H))&&((shot->x+2>=bloco[i][j].x)&&(shot->x+2<=bloco[i][j].x+ALIEN_W))){
			shot->active=0;
			bloco[i][j].is_active=0;
			*pontuacao+=100;
			printf("\n %d",bloco[i][j].is_active);
		}
		
	}
}
}

}
}
