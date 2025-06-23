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

void initAlien (Alien *alien){
	alien->x=0;
	alien->y=0;
	alien->x_vel=1;
	alien->y_vel= ALIEN_H;
	alien->cor=al_map_rgb(rand()%256,rand()%256,rand()%256);
}


void draw_alien(Alien alien){
	al_draw_filled_rectangle(alien.x, alien.y, alien.x+ALIEN_W, alien.y + ALIEN_H, alien.cor);
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