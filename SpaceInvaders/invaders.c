#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "invaders.h"

int main(int argc, char **argv)
{

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_FONT *font = NULL;
	ALLEGRO_FONT *bigFont = NULL;
	ALLEGRO_BITMAP *alien_sprite = NULL;
	ALLEGRO_SAMPLE *background_music = NULL;
	ALLEGRO_SAMPLE *collision_sound = NULL;
	

	FILE *arq;

	if (initialize_Allegro(&display, &event_queue, &timer, &font, &bigFont, &alien_sprite, &background_music,&collision_sound) != 0)
	{
		return -1;
	}

	al_play_sample(background_music, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, NULL);


	char text[50];
	int playing = 1, waitingToStart, waitingToEnd;
	int score = 0, record, phase = 4, result;

	if (pega_recorde(&arq, &record))
	{

		Alien **alien;
		if (!alloca_alien(ROW_ALIEN[phase], COLUMN_ALIEN[phase], &alien))
		{
			printf("Falha na alocação de memória!\n");
			return -1;
		}

		struct Shot shots;
		Nave ship;

		init_shots(&shots);
		initNave(&ship);
		initAllAliens(ROW_ALIEN[phase], COLUMN_ALIEN[phase], alien, phase);

		show_start_screen(&font, &bigFont);

		ALLEGRO_EVENT ev;
		waitingToStart = 1;
		while (waitingToStart)
		{
			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
			{
				waitingToStart = 0;
			}
		}

		while (playing)
		{

			al_wait_for_event(event_queue, &ev);
			if (ev.type == ALLEGRO_EVENT_TIMER)
			{
				update_nave(&ship);
				update_all_aliens(ROW_ALIEN[phase], COLUMN_ALIEN[phase], alien);
				update_shots(&shots);
				shot_hit(&shots, ROW_ALIEN[phase], COLUMN_ALIEN[phase], alien, &score,collision_sound);

				draw_scenario();
				draw_nave(ship);
				draw_shots(&shots);

				result = drawAllAliens(ROW_ALIEN[phase], COLUMN_ALIEN[phase], alien, &phase, alien_sprite);

				if (result == 2)
				{
					if (free_alien(ROW_ALIEN[phase], &alien))
					{
						phase++;

						if (!alloca_alien(ROW_ALIEN[phase], COLUMN_ALIEN[phase], &alien))
						{
							printf("Falha na alocação de memória!\n");
							return -1;
						}
						initAllAliens(ROW_ALIEN[phase], COLUMN_ALIEN[phase], alien, phase);
						init_shots(&shots);
						playing = 1;
					}
				}
				else if (result == 0)
				{
					show_end_screen(&font, &bigFont, score, record);

					waitingToEnd = 1;
					while (waitingToEnd)
					{
						al_wait_for_event(event_queue, &ev);
						if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
						{
							waitingToEnd = 0;
						}
					}
					playing = 0;
				}

				sprintf(text, "Score: %d", score);
				al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W - 150, 10, 0, text);

				sprintf(text, "Fase: %d", phase + 1);
				al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2 - 60, 10, 0, text);

				sprintf(text, "Record: %d", record);
				al_draw_text(font, al_map_rgb(255, 255, 255), 10, 10, 0, text);

				if (playing)
				{
					int temp= !colisao_all_alien_solo(playing, ROW_ALIEN[phase], COLUMN_ALIEN[phase], alien, &score);
					if(temp==0){
					show_end_screen(&font, &bigFont, score, record);

					waitingToEnd = 1;
					while (waitingToEnd)
					{
						al_wait_for_event(event_queue, &ev);
						if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
						{
							waitingToEnd = 0;
						}
					}
				}
					playing = temp;
				}
				if (playing)
				{	
					int temp= !colisao_all_alien_solo(playing, ROW_ALIEN[phase], COLUMN_ALIEN[phase], alien, &score);
					if(temp==0){
					show_end_screen(&font, &bigFont, score, record);

					waitingToEnd = 1;
					while (waitingToEnd)
					{
						al_wait_for_event(event_queue, &ev);
						if (ev.type == ALLEGRO_EVENT_KEY_DOWN || ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN || ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
						{
							waitingToEnd = 0;
						}
					}
				}
					playing = temp;
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

				switch (ev.keyboard.keycode)
				{
				case ALLEGRO_KEY_A:
					ship.esq = 1;
					break;

				case ALLEGRO_KEY_D:
					ship.dir = 1;
					break;

				case ALLEGRO_KEY_LEFT:
					ship.esq = 1;
					break;

				case ALLEGRO_KEY_RIGHT:
					ship.dir = 1;
					break;

				case ALLEGRO_KEY_SPACE:
					fire_shot(&shots, ship.x, (SCREEN_H - GRASS_H - NAVE_H));
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
					ship.esq = 0;
					break;

				case ALLEGRO_KEY_D:
					ship.dir = 0;
					break;

				case ALLEGRO_KEY_LEFT:
					ship.esq = 0;
					break;

				case ALLEGRO_KEY_RIGHT:
					ship.dir = 0;
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
	if (adiciona_recorde(&arq, &record, &score))
	{
		printf("\nparabéns, recorde atualizado");
		return 0;
	}
	else
	{
		printf("\n recorde não atualizado, o recorde do jogo ainda eh %d pontos", record);
		return -1;
	}

	if (alien_sprite) {
    al_destroy_bitmap(alien_sprite);}
	if(background_music){
	al_destroy_sample(background_music);}
	if(collision_sound){
	al_destroy_sample(collision_sound);}
	return 0;



}
