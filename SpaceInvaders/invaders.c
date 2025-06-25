#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "invaders.h"


int main(int argc, char **argv)
{

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	//rever pq endereço
	if (initialize_Allegro(&display, &event_queue, &timer) != 0) {
    // Handle error
    return -1;
}
	struct Shot shots;
	init_shots(&shots);

	Nave nave;
	initNave(&nave);

	Alien alien[ROW_ALIEN][COLUMN_ALIEN];
	initAllAliens(ROW_ALIEN, COLUMN_ALIEN,alien);

	int playing = 1;
	while (playing)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			update_nave(&nave);
			update_all_aliens(ROW_ALIEN,COLUMN_ALIEN,alien);
			update_shots(&shots);
			shot_hit(&shots,ROW_ALIEN,COLUMN_ALIEN,alien);


			draw_scenario();
			draw_nave(nave);
			playing=drawAllAliens(ROW_ALIEN,COLUMN_ALIEN,alien);
			draw_shots(&shots);

			//printf("\n %d playing" ,playing);
			
			
			
			

			// desenha nave em cima do cenario (dps)

			
			if(playing){
			playing = !colisao_all_alien_solo(playing,ROW_ALIEN, COLUMN_ALIEN,alien);
			
			}
			if(playing){
				playing= colisao_all_alien_nave(ROW_ALIEN, COLUMN_ALIEN, alien, nave);
				
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
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);

			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_A:
				nave.esq = 1;
				break;

			case ALLEGRO_KEY_D:
				nave.dir = 1;
				break;
			
			case ALLEGRO_KEY_SPACE:
				fire_shot(&shots,nave.x, (SCREEN_H-GRASS_H-NAVE_H));
			break;

			default:
				break;
			}
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP)
		{
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);

			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_A:
				nave.esq = 0;
				break;

			case ALLEGRO_KEY_D:
				nave.dir = 0;
				break;

			case ALLEGRO_KEY_SPACE:
				printf("\n espaco solto");
				break;

			default:
				break;
			}
		}
	
	}

	return 0;

	// fila de eventos
	// qualquer evento entra nela e começa do final
	// pode mandar quantos eventos quiser mas todos ficam no final da fila
	// o programa é um loop que verifica a fila de eventos e faz ela
}


// pq qnd acessa vetor n precisa