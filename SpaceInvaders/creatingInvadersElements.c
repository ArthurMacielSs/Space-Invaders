#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "invaders.h"

void initNave(Nave *nave)
{
	nave->x = SCREEN_W / 2;
	nave->y = SCREEN_H - GRASS_H / 2 - NAVE_H;
	nave->vel = SHIP_SPEED;
	nave->dir = 0;
	nave->esq = 0;
	nave->cor = al_map_rgb(0, 0, 255);
}

void initAlien(Alien *alien, int x, int y, int phase)
{
	alien->x = x;
	alien->y = y;
	alien->x_vel = ALIEN_X_SPEED[phase];
	alien->y_vel = ALIEN_H;
	alien->cor = al_map_rgb(rand() % 256, rand() % 256, rand() % 256);
	alien->is_active = 1;
}

void initAllAliens(int linha, int coluna, Alien **bloco, int phase)
{
	int x = 0, y = 0;
	for (int i = 0; i < linha; i++)
	{
		for (int j = 0; j < coluna; j++)
		{
			initAlien(&bloco[i][j], x, y, phase);
			x = x + ALIEN_W + ALIEN_SPACEMENT;
		}
		x = 0;
		y = y + ALIEN_H + ALIEN_SPACEMENT;
	}
}

void draw_alien(Alien alien)
{
	al_draw_filled_rectangle(alien.x, alien.y, alien.x + ALIEN_W, alien.y + ALIEN_H, alien.cor);
}

int drawAllAliens(int linha, int coluna, Alien **bloco, int *phase)
{
	int active = 0;
	int verifica = 0;
	for (int i = 0; i < linha; i++)
	{
		for (int j = 0; j < coluna; j++)
		{
			if (bloco[i][j].is_active)
			{
				draw_alien(bloco[i][j]);
				verifica = 1;
				active = 1;
			}
		}
	}
	if (active)
	{
		return verifica;
	}
	else if (*phase < PHASES_NUMBER - 1)
	{
		return 2;
	}
	else
	{
		return verifica;
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

void init_shots(struct Shot *shots)
{
	shots->active = 0;
}

void fire_shot(struct Shot *shots, float ship_x, float ship_y)
{
	if (!shots->active)
	{
		shots->x = ship_x;
		shots->y = ship_y;
		shots->speed = -SHOT_SPEED; // negative because it goes up
		shots->active = 1;
	}
}

void draw_shots(struct Shot *shots)
{
	if (shots->active)
	{
		al_draw_filled_rectangle(shots->x - 2, shots->y, shots->x + 2, shots->y + 10, al_map_rgb(255, 255, 0));
	}
}

int alloca_alien(int rows, int cols, Alien ***alien)
{
	*alien = (Alien **)malloc(rows * sizeof(Alien *));
	if (*alien == NULL)
	{
		return 0;
	}

	for (int i = 0; i < rows; i++)
	{
		(*alien)[i] = (Alien *)malloc(cols * sizeof(Alien));

		if ((*alien)[i] == NULL)
		{
			for (int j = 0; j < i; j++)
			{
				free((*alien)[j]);
			}
			free(*alien);
			*alien = NULL;
			return 0; 
		}
	}

	return 1;
}

int free_alien(int rows, Alien ***alien)
{
	    if (*alien == NULL)
    {
        return 1; 
    }

    for (int i = 0; i < rows; i++)
    {
        free((*alien)[i]); 
    }

    free(*alien);          
    *alien = NULL;         
    return 1;
}
	

