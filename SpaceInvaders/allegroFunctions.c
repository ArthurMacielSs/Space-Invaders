#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "invaders.h"

int initialize_Allegro(ALLEGRO_DISPLAY **display, 
                      ALLEGRO_EVENT_QUEUE **event_queue, 
                      ALLEGRO_TIMER **timer, ALLEGRO_FONT **fonte)
{
    if (!al_init())
    {
        fprintf(stderr, "failed to initialize allegro!\n");
        return -1;
    }

    *display = al_create_display(SCREEN_W, SCREEN_H);
    if (!*display)
    {
        fprintf(stderr, "failed to create display!\n");
        return -1;
    }

    //funções necessárias para escrever
    	al_init_font_addon();

    	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to load tff font module!\n");
		return -1;
	}

    *fonte = al_load_ttf_font("OpenSans_Condensed-Bold.ttf", 24, 0);
    if (!*fonte) {
     fprintf(stderr, "Failed to load font.\n");
        return -1;
    }

    // Initialize primitives addon
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "failed to initialize primitives!\n");
        al_destroy_display(*display);
        return -1;
    }


    *event_queue = al_create_event_queue();
    if (!*event_queue)
    {
        fprintf(stderr, "failed to create event_queue!\n");
        al_destroy_display(*display);
        return -1;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "failed to install keyboard!\n");
        al_destroy_event_queue(*event_queue);
        al_destroy_display(*display);
        return -1;
    }

    *timer = al_create_timer(1.0 / FPS);
    if (!*timer)
    {
        fprintf(stderr, "failed to create timer!\n");
        al_destroy_event_queue(*event_queue);
        al_destroy_display(*display);
        return -1;
    }

    al_register_event_source(*event_queue, al_get_display_event_source(*display));
    al_register_event_source(*event_queue, al_get_keyboard_event_source());
    al_register_event_source(*event_queue, al_get_timer_event_source(*timer));

    al_start_timer(*timer);

    return 0;
}