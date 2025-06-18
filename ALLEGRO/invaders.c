#include <stdio.h>
#include <allegro5/allegro.h>


const int SCREEN_W = 960;
const int SCREEN_H = 540;

const int GRASS_H =60;

const float FPS =10;

void draw_scenario () {
    al_clear_to_color(al_map_rgb(0,0,0));

    //parei no 4 min
}


int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer =NULL;

   
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	


		
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

   	
	    al_register_event_source(event_queue, al_get_display_event_source(display));
		al_register_event_source(event_queue, al_get_keyboard_event_source());
		al_register_event_source(event_queue, al_get_timer_event_source(timer));
      
	al_clear_to_color(al_map_rgb (0,255,0));
 			al_flip_display();
        
	al_start_timer(timer);

    int playing=1;
    while(playing){ 
  

        ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);    
		if(ev.type == ALLEGRO_EVENT_TIMER){

            draw_scneario();
                         	
			al_flip_display();
			if(al_get_timer_count(timer)%(int)FPS==0){
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
			}
		}

        	
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
	
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
		}	
    }


   
            return 0;




//fila de eventos
//qualquer evento entra nela e começa do final 
//pode mandar quantos eventos quiser mas todos ficam no final da fila 
//o programa é um loop que verifica a fila de eventos e faz ela 

}