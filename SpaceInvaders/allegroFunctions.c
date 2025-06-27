#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include "invaders.h"

int initialize_Allegro(ALLEGRO_DISPLAY **display,
                       ALLEGRO_EVENT_QUEUE **event_queue,
                       ALLEGRO_TIMER **timer, ALLEGRO_FONT **font, ALLEGRO_FONT **bigFont, ALLEGRO_BITMAP **alien_sprite)
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
    al_init_image_addon(); 


        *alien_sprite = al_load_bitmap("alien.png");
        if (!alien_sprite) {
            fprintf(stderr, "Failed to load alien sprite!\n");
            return -1;
        }
    // funções necessárias para escrever
    al_init_font_addon();

    if (!al_init_ttf_addon())
    {
        fprintf(stderr, "failed to load tff font module!\n");
        return -1;
    }

    *font = al_load_ttf_font("VT323-Regular.ttf", 24, 0);
    if (!*font)
    {
        fprintf(stderr, "Failed to load font.\n");
        return -1;
    }

     *bigFont = al_load_ttf_font("VT323-Regular.ttf", 80, 0);
    if (!*font)
    {
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

void show_start_screen(ALLEGRO_FONT **font,ALLEGRO_FONT **big_font )
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_text(*big_font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 60, ALLEGRO_ALIGN_CENTER, "SPACE INVADERS");
    al_draw_text(*font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 20, ALLEGRO_ALIGN_CENTER, "Click or press any key to start");
    al_flip_display();
}


void show_end_screen(ALLEGRO_FONT **font, ALLEGRO_FONT **big_font,int pontuacao, int recorde) {
	al_clear_to_color(al_map_rgb(0, 0, 0));

    al_draw_text(*big_font, al_map_rgb(255, 255, 255), SCREEN_W / 2, 60, ALLEGRO_ALIGN_CENTER, "Game Over!");
	
	char text[100];
	sprintf(text, " Pontuacao: %d", pontuacao);
	al_draw_text(*font, al_map_rgb(255, 255, 255),  SCREEN_W / 2, SCREEN_H / 2 - 30, ALLEGRO_ALIGN_CENTER, text);

    if(pontuacao>recorde){
        recorde=pontuacao;
    }
	sprintf(text, "Recorde: %d", recorde);
	al_draw_text(*font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 + 10, ALLEGRO_ALIGN_CENTER, text);

	al_draw_text(*font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H - 60, ALLEGRO_ALIGN_CENTER, "Aperte qualquer tecla para fechar...");

	al_flip_display();
}
