#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

const int SCREEN_W = 960/4;
const int SCREEN_H = 540/4;
const int GRASS_H = 60;
const float FPS = 100;
const int NAVE_W = 100;
const int NAVE_H = 50;

const int ALIEN_W = 50;
const int ALIEN_H = 25;

typedef struct Nave
{
	float x;
	ALLEGRO_COLOR cor;
	float vel;
	int dir, esq;

} Nave;

typedef struct Alien {
	float x, y;
	float x_vel, y_vel;
	ALLEGRO_COLOR cor;
} Alien;

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

int colisao_alien_solo(Alien alien){
	if(alien.y + ALIEN_H>SCREEN_H-GRASS_H){
		return 1;
	}
	else{
		return 0;
	}
}

int main(int argc, char **argv)
{

	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;

	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if (!display)
	{
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}

	// inicializa o módulo de primitivas do Allegro
	if (!al_init_primitives_addon())
	{
		fprintf(stderr, "failed to initialize primitives!\n");
		return -1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue)
	{
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	if (!al_install_keyboard())
	{
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer)
	{
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);

	Nave nave;
	initNave(&nave);

	Alien alien;
	initAlien(&alien);

	int playing = 1;
	while (playing)
	{

		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER)
		{

			draw_scenario();

			update_nave(&nave);

			update_alien(&alien);

			// desenha nave em cima do cenario (dps)

			draw_nave(nave);

			draw_alien(alien);

			playing = !colisao_alien_solo(alien);

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