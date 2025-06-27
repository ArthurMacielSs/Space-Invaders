#include "invaders.h"
#include <stdio.h>
#include <allegro5/allegro_primitives.h>

void update_nave(Nave *ship)
{
	if (ship->dir && ship->x + ship->vel <= SCREEN_W)
	{
		ship->x += ship->vel;
	}
	if (ship->esq && ship->x - ship->vel >= 0)
	{
		ship->x -= ship->vel;
	}
}

void update_all_aliens(int row, int col, Alien **matrix_alien)
{
	int should_reverse = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			Alien *teste = &matrix_alien[i][j];
			if (teste->is_active == 1)
			{
				if ((teste->x + ALIEN_W + teste->x_vel > SCREEN_W) || (teste->x + teste->x_vel < 0))
				{
					should_reverse = 1;
					break;
				}
			}
		}
		if (should_reverse)
			break;
	}

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			if (&matrix_alien[i][j])
			{
				Alien *teste = &matrix_alien[i][j];
				if (should_reverse)
				{
					teste->y += teste->y_vel;
					teste->x_vel *= -1;
				}
				teste->x += teste->x_vel;
			}
		}
	}
}
int colisao_alien_solo(Alien alien)
{
	if (alien.is_active == 1)
	{
		if (alien.y + ALIEN_H >= SCREEN_H - GRASS_H)
		{
			printf("\n os aliens chegaram ao chao");
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

int colisao_all_alien_solo(int playng, int row, int col, Alien **matrix_alien, int *score)
{
	playng = 0;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			playng = colisao_alien_solo(matrix_alien[i][j]);
			if (playng == 1)
			{
				break;
				return playng;
			}
		}
		if (playng == 1)
		{
			break;
		}
	}
	return playng;
}
int colisao_alien_nave(Alien alien, Nave ship, int *score)
{
	if (alien.is_active == 1)
	{
		if ((alien.y + ALIEN_H >= ship.y) && (((alien.x >= ship.x - NAVE_W / 2) && (alien.x <= ship.x + NAVE_W / 2)) || ((alien.x + ALIEN_W >= ship.x - NAVE_W / 2) && (alien.x + ALIEN_W <= ship.x + NAVE_W / 2))))
		{
			printf("\ncolidiu com a nave");
			return 0;
		}
		else
		{
			return 1;
		}
	}
	return 1;
}

int colisao_all_alien_nave(int row, int col, Alien **matrix_alien, Nave ship, int *score)
{
	int playing = 1;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			playing = colisao_alien_nave(matrix_alien[i][j], ship, score);
			if (playing == 0)
			{
				return playing;
				break;
			}
		}
		if (playing == 0)
		{
			return playing;
			break;
		}
	}
	return playing;
}

void update_shots(struct Shot *shots)
{
	if (shots->active)
	{
		shots->y += shots->speed;
		if (shots->y < 0)
		{
			shots->active = 0;
		}
	}
}

void shot_hit(struct Shot *shot, int row, int col, Alien **alien_matrix, int *score)
{
	if (shot->active)
	{
		for (int i = 0; i < row; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (alien_matrix[i][j].is_active)
				{
					if (((shot->y >= alien_matrix[i][j].y) && (shot->y <= alien_matrix[i][j].y + ALIEN_H)) && ((shot->x + 2 >= alien_matrix[i][j].x) && (shot->x + 2 <= alien_matrix[i][j].x + ALIEN_W)))
					{
						shot->active = 0;
						alien_matrix[i][j].is_active = 0;
						*score += 100;
					}
				}
			}
		}
	}
}
