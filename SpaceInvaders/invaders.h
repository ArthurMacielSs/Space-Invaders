#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>

// constantes
#define PHASES_NUMBER 6

extern const int SCREEN_W;
extern const int SCREEN_H;
extern const int GRASS_H;
extern const float FPS;

extern const int NAVE_W;
extern const int NAVE_H;
const int SHIP_SPEED;

extern const int ALIEN_W;
extern const int ALIEN_H;

extern const int ROW_ALIEN[];
extern const int COLUMN_ALIEN[];
extern const int ALIEN_X_SPEED[];
extern const int ALIEN_SPACEMENT;

extern const int SHOT_SPEED;

// estruturas
typedef struct Nave
{
	float x, y;
	ALLEGRO_COLOR cor;
	float vel;
	int dir, esq;

} Nave;

typedef struct Alien
{
	float x, y;
	float x_vel, y_vel;
	ALLEGRO_COLOR cor;
	int is_active;
} Alien;

struct Shot
{
	float x, y;
	float speed;
	int active;
};

// allegroFunctions
int initialize_Allegro(ALLEGRO_DISPLAY **display,
                       ALLEGRO_EVENT_QUEUE **event_queue,
                       ALLEGRO_TIMER **timer, ALLEGRO_FONT **font, ALLEGRO_FONT **bigFont,
                       ALLEGRO_BITMAP **alien_sprite,ALLEGRO_SAMPLE **background_music,ALLEGRO_SAMPLE **collision_sound);
void show_start_screen(ALLEGRO_FONT **font, ALLEGRO_FONT **big_font);
void show_end_screen(ALLEGRO_FONT **font, ALLEGRO_FONT **big_font, int pontuacao, int recorde);

// criatingInvadersElements
void initNave(Nave *nave);
void initAlien(Alien *alien, int x, int y, int phase);
void draw_alien(Alien alien, ALLEGRO_BITMAP *alien_sprite);
void draw_scenario();
void draw_nave(Nave nave);
void initAllAliens(int linha, int coluna, Alien **bloco, int phase);
int drawAllAliens(int linha, int coluna, Alien **bloco, int *phase, ALLEGRO_BITMAP *alien_sprite);
void init_shots(struct Shot *shots);
void fire_shot(struct Shot *shots, float ship_x, float ship_y);
void draw_shots(struct Shot *shots);

// updatingInvadersElements
void update_nave(Nave *nave);
int colisao_alien_solo(Alien alien);
void update_all_aliens(int linha, int coluna, Alien **bloco);
int colisao_all_alien_solo(int playng, int linha, int coluna, Alien **bloco, int *pontuacao);
void update_shots(struct Shot *shots);
void shot_hit(struct Shot *shot, int row, int col, Alien **alien_matrix, int *score,ALLEGRO_SAMPLE *collision_sound);
int colisao_alien_nave(Alien alien, Nave nave, int *pontuacao);
int colisao_all_alien_nave(int linha, int coluna, Alien **bloco, Nave nave, int *pontuacao);

// fileFunctions
int pega_recorde(FILE **arq, int *recorde);
int adiciona_recorde(FILE **arq, int *recorde, int *pontuacao);

// allocationFunctions
int alloca_alien(int rows, int cols, Alien ***alien);
int free_alien(int rows, Alien ***alien);