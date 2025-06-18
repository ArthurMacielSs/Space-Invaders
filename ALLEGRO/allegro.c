#include <stdio.h>
#include <allegro5/allegro.h>

//tamanho da tela
const int SCREEN_W = 960;
const int SCREEN_H = 540;

const float FPS =10;


int main(int argc, char **argv){
	
	ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer =NULL;

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

		//instala o teclado
	if(!al_install_keyboard()) {
		fprintf(stderr, "failed to install keyboard!\n");
		return -1;
	}
	
	//instala o mouse
	if(!al_install_mouse()) {
		fprintf(stderr, "failed to initialize mouse!\n");
		return -1;
	}

		//cria um temporizador que incrementa uma unidade a cada 1.0/FPS segundos
    timer = al_create_timer(1.0 / FPS);
    if(!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

    	//registra na fila os eventos de tela (ex: clicar no X na janela)
	al_register_event_source(event_queue, al_get_display_event_source(display));
		//registra na fila os eventos de teclado (ex: pressionar uma tecla)
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	//registra na fila os eventos de mouse (ex: clicar em um botao do mouse)
	al_register_event_source(event_queue, al_get_mouse_event_source());  
		//registra na fila os eventos de tempo: quando o tempo altera de t para t+1
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
      
	al_clear_to_color(al_map_rgb (0,255,0));

    //atualiza a tela (quando houver algo para mostrar)
			al_flip_display();
        //utilize o site rgb map

		//inicia o temporizador
	al_start_timer(timer);

    int playing=1;
    while(playing){ 
  

        ALLEGRO_EVENT ev;
		//espera por um evento e o armazena na variavel de evento ev
		al_wait_for_event(event_queue, &ev);
   

        //al_rest(10);
        //deixa a tela 10s parada
		if(ev.type == ALLEGRO_EVENT_TIMER){


			//atualiza a tela (quando houver algo para mostrar)
			al_flip_display();

			//faz isso para definir um fps basico e não depender do computador

			if(al_get_timer_count(timer)%(int)FPS==0){
				printf("\n%d segundos se passaram...", (int)(al_get_timer_count(timer)/FPS));
			}
		}

        	//se o tipo de evento for o fechamento da tela (clique no x da janela)
		else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			playing = 0;
		}
			//se o tipo de evento for um clique de mouse
		else if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
			printf("\nmouse clicado em: %d, %d", ev.mouse.x, ev.mouse.y);
		}
		//se o tipo de evento for um pressionar de uma tecla
		else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			//imprime qual tecla foi
			printf("\ncodigo tecla: %d", ev.keyboard.keycode);
			al_clear_to_color(al_map_rgb(rand()%256, rand()%256, rand()%256));
			//al_flip_display();
		}	
    }


   
            return 0;




//fila de eventos
//qualquer evento entra nela e começa do final 
//pode mandar quantos eventos quiser mas todos ficam no final da fila 
//o programa é um loop que verifica a fila de eventos e faz ela 

}