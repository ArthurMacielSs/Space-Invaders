#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "invaders.h"



void initNave(Nave *nave)
{
	nave->x = SCREEN_W / 2;
	nave->vel = 1;
	nave->dir = 0;
	nave->esq = 0;
	nave->cor = al_map_rgb(0, 0, 255);
}

void initAlien (Alien *alien, int x, int y){
	alien->x=x;
	alien->y=y;
	alien->x_vel=ALIEN_X_SPEED;
	alien->y_vel= ALIEN_H;
	alien->cor=al_map_rgb(rand()%256,rand()%256,rand()%256);
}

void initAllAliens (int linha, int coluna,Alien bloco[linha][coluna]){
	int x=0, y=0;
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			initAlien(&bloco[i][j],x, y);
			x = x + ALIEN_W + ALIEN_SPACEMENT;
			
		}
		x=0;
		y = y + ALIEN_H + ALIEN_SPACEMENT;
	}

}


void draw_alien(Alien alien){
	al_draw_filled_rectangle(alien.x, alien.y, alien.x+ALIEN_W, alien.y + ALIEN_H, alien.cor);
}

void drawAllAliens (int linha, int coluna, Alien bloco [linha][coluna]){
	for(int i=0; i<linha; i++){
		for(int j=0; j<coluna; j++){
			draw_alien(bloco[i][j]);

		}
	}
}

void draw_scenario()
{
	// pinta a tela de preto
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_filled_rectangle(0, (SCREEN_H - GRASS_H), SCREEN_W, SCREEN_H, al_map_rgb(0, 245, 0));
}

void draw_nave(Nave nave)
{
	float y_base = SCREEN_H - GRASS_H / 2;
	al_draw_filled_triangle(nave.x, y_base - NAVE_H, nave.x - NAVE_W / 2, y_base, nave.x + NAVE_W / 2, y_base, nave.cor);
}