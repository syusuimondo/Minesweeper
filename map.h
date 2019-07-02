#ifndef DEF_MAP_H //“ñdinclude–h~
#define DEF_MAP_H
//‰Šú‰»
void map_init();
int map_kensa(int x,int y);
void map_henka(int bx,int by);
void map_atari(int mx,int my);
//
void map_updata();
//
void map_draw();
void map_over();
//
void map_fin();
int map_raandom(int min,int max);
#endif