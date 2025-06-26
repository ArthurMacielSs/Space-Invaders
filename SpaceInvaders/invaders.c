#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "invaders.h"

int main(int argc, char **argv)
{

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;

	FILE *arq;

	struct Shot shots;
	Nave nave;
	Alien alien[ROW_ALIEN][COLUMN_ALIEN];

	// rever pq endereço
	if (initialize_Allegro(&display, &event_queue, &timer, &font) != 0)
	{
		// Handle error
		return -1;
	}

	init_shots(&shots);
	initNave(&nave);
	initAllAliens(ROW_ALIEN, COLUMN_ALIEN, alien);

	char text[50];
	int playing = 1;
	int pontuacao = 0, recorde;

	if (pega_recorde(&arq, &recorde))
	{
		while (playing)
		{

			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				update_nave(&nave);
				update_all_aliens(ROW_ALIEN, COLUMN_ALIEN, alien);
				update_shots(&shots);
				shot_hit(&shots, ROW_ALIEN, COLUMN_ALIEN, alien, &pontuacao);

				draw_scenario();
				draw_nave(nave);
				playing = drawAllAliens(ROW_ALIEN, COLUMN_ALIEN, alien);
				draw_shots(&shots);

				sprintf(text, "Score: %d", pontuacao);
				al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W - 150, 10, 0, text);

				sprintf(text, "Record: %d", recorde);
				al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, text);

				// printf("\n %d playing" ,playing);

				// desenha nave em cima do cenario (dps)
				if (playing)
				{
					playing = !colisao_all_alien_solo(playing, ROW_ALIEN, COLUMN_ALIEN, alien, &pontuacao);
				}
				if (playing)
				{
					playing = colisao_all_alien_nave(ROW_ALIEN, COLUMN_ALIEN, alien, nave, &pontuacao);
				}

				al_flip_display();
				if (al_get_timer_count(timer) % (int)FPS == 0)
				{
					printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer) / FPS));
				}
			}

			else if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				playing = 0;
			}

			else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
			{
				// printf("\ncodigo tecla: %d", ev.keyboard.keycode);

				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_A:
					nave.esq = 1;
					break;

				case ALLEGRO_KEY_D:
					nave.dir = 1;
					break;

				case ALLEGRO_KEY_SPACE:
					fire_shot(&shots, nave.x, (SCREEN_H - GRASS_H - NAVE_H));
					break;

				default:
					break;
				}
			}
			else if (ev.type == ALLEGRO_EVENT_KEY_UP)
			{
				// printf("\ncodigo tecla: %d", ev.keyboard.keycode);

				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_A:
					nave.esq = 0;
					break;

				case ALLEGRO_KEY_D:
					nave.dir = 0;
					break;

				case ALLEGRO_KEY_SPACE:
					break;

				default:
					break;
				}
			}
		}
	}
	else
	{
		printf("\n código encerrado");
		return -1;
	}
	if (adiciona_recorde(&arq, &recorde, &pontuacao))
	{
		printf("\nparabéns, recorde atualizado");
		return 0;
	}
	else
	{
		printf("\nfalha ao atualizar o recorde");
		return -1;
	}

	return 0;
}

// pq qnd acessa vetor n precisa