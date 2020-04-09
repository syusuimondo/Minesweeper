#ifndef DEF_PLAYER_H //“ñdinclude–h~
#define DEF_PLAYER_H
//‰Šú‰»
typedef struct{
	int x;
	int y;
	int flag;
	int count;
	int load;
}PLAYER;
static int sousa;
static int tama;
static int tama_count;
static PLAYER player;
void player_init();
//;
void player_updata();
//
void player_flag();
//
void player_draw();
//
int player_fin();
#endif