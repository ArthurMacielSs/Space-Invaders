#include <stdio.h>
#include <allegro5/allegro.h>

//tamanho da tela
const int SCREEN_W = 960;
const int SCREEN_H = 540;


int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;

    //inicializa o Allegro
	if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

    //cria uma tela com dimensoes de SCREEN_W, SCREEN_H pixels
	display = al_create_display(SCREEN_W, SCREEN_H);
	if(!display) {
		fprintf(stderr, "failed to create display!\n");
		return -1;
	}
         	//cria a fila de eventos
	event_queue = al_create_event_queue();
	if(!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		return -1;
	}

    	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));

    int playing=1;
    while(playing){ 
        al_clear_to_color(al_map_rgb (0,255,0));

    //atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
        //utilize o site rgb map

        ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);
   

        //al_rest(10);
        //deixa a tela 10s parada

        	//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
    }


   
            return 0;




//fila de eventos
//qualquer evento entra nela e começa do final 
//pode mandar quantos eventos quiser mas todos ficam no final da fila 
//o programa é um loop que verifica a fila de eventos e faz ela 

}