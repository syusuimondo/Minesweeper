#include "DxLib.h"
#include "map.h"
#include"player.h"
//#include"player.h"
//#include"music.h"
static int map[9][9];
static int map_flag[9][9];
static int image[10];
/*
-3　: ここには爆弾が撃ち抜かれた。
-2　: ここには爆弾が入っている。
-1　: ここには爆弾は入っていない。プレーヤーによって開けられてもいない場所。
0　: プレーヤーによって開けられた。この周りには爆弾が無い。
1　: プレーヤーによって開けられた。この周りには爆弾が 1 つある。
2　: プレーヤーによって開けられた。この周りには爆弾が 2 つある。
3　: プレーヤーによって開けられた。この周りには爆弾が 3 つある。*/
void map_init(){//マップの初期設定
	LoadDivGraph( "画像/map.png",10,10,1,32,32,image);
	for(int i = 0;i<9;i++){ //初期化
		for(int j = 0;j<9;j++){
			map[i][j] = -1;
			map_flag[i][j] = 0;
		}
	}
	for(int i = 0;i<10;i++){ //地雷の配置
		int x = GetRand(8);
		int y = GetRand(8);
		while(map_flag[x][y] == 1){
			x = GetRand(8);
			y = GetRand(8);
		}
		map[x][y] = -2;
		map_flag[x][y] = 1;
	}
}
int map_kensa(int x,int y){//マップの検査
		if(map[x][y] == -1){//マップが地面だった場合
			map[x][y] = 0;
			map_flag[x][y] = 1;
			map_henka(x,y);
			return 0;
		}
		if(map[x][y] == -2 && map_flag[x][y] == 1){//マップが地雷だった場合
			map_flag[x][y] = 0;
			//map[x][y] = -3;
			return 1;
		}
}
void map_henka(int x,int y){//時計周りに地雷があるか調べる
	if(map[x][y-1] == -2 && y> 0){
		map[x][y]++;
	} 
	if(map[x+1][y-1] == -2 && y> 0 && x <8){
		map[x][y]++;
	}
	if(map[x+1][y] == -2 && x <8){
		map[x][y]++;
	}
	if(map[x+1][y+1] == -2 && y < 8 && x <8){
		map[x][y]++;
	}
	if(map[x][y+1] == -2 && y < 8){
		map[x][y]++;
	}
	if(map[x-1][y+1] == -2 && x > 0 && y < 8){ 
		map[x][y]++;
	}
	if(map[x-1][y] == -2 && x > 0){
		map[x][y]++;
	}
	if(map[x-1][y-1] == -2 && x >0 && y> 0){
		map[x][y]++;
	}
	if(map[x][y] == 0 && y> 0){
		map_atari(x,y-1);
	} 
	if(map[x][y] == 0 && y> 0 && x <8){
		map_atari(x+1,y-1);
	}
	if(map[x][y] == 0 && x <8){
		map_atari(x+1,y);
	}
	if(map[x][y] == 0 && y < 8 && x <8){
		map_atari(x+1,y+1);
	}
	if(map[x][y] == 0 && y < 8){
		map_atari(x,y+1);
	}
	if(map[x][y] == 0 && x > 0 && y < 8){ 
		map_atari(x-1,y+1);
	}
	if(map[x][y] == 0 && x > 0){
		map_atari(x-1,y);
	}
	if(map[x][y] == 0 && x >0 && y> 0){
		map_atari(x-1,y-1);
	}
	/*if(map[x][y] == 0 && y < 8 && x <8 && x >0 && y> 0){
		map_atari(x,y-1);
		map_atari(x+1,y-1);
		map_atari(x+1,y);
		map_atari(x+1,y+1);
		map_atari(x,y+1);
		map_atari(x-1,y+1);
		map_atari(x-1,y);
		map_atari(x-1,y-1);
	}*/
}
void map_atari(int x,int y){//マップを平地にする
	if(map[x][y] == -1){//マップが地面だった場合
			map[x][y] = 0;
			map_henka(x,y);
			map_flag[x][y] = 1;
		}
	/*if(map[x][y-1] == -2 && y> 0 && map_flag[x][y] == 0){
		map[x][y]++;
	}
	if(map[x+1][y-1] == -2 && y> 0 && x <8 && map_flag[x][y] == 0){
		map[x][y]++;
	}
	if(map[x+1][y] == -2 && x <8 && map_flag[x][y] == 0){
		map[x][y]++;
	}
	if(map[x+1][y+1] == -2 && y < 8 && x <8  && map_flag[x][y] == 0){
		map[x][y]++;
	}
	if(map[x][y+1] == -2 && y < 8 && map_flag[x][y] == 0){
		map[x][y]++;
	}
	if(map[x-1][y+1] == -2 && x > 0 && y < 8 && map_flag[x][y] == 0){ 
		map[x][y]++;
	}
	if(map[x-1][y] == -2 && x > 0 && map_flag[x][y] == 0){
		map[x][y]++;
	}
	if(map[x-1][y-1] == -2 && x >0 && y> 0 && map_flag[x][y] == 0){
		map[x][y]++;
	}*/
}
	//music_draw(0);
void map_draw(){//マップを描画する
	for(int y = 0;y<9;y++){
		for(int x = 0;x<9;x++){
			switch(map[x][y]){
				case -3://撃ち抜かれた場合
					DrawGraph( x*32, y*32, image[2], TRUE );
					break;
				case -2://マップが地雷の場合
					//地雷の正体がばれていない場合
					if(map_flag[x][y] == 1) DrawGraph( x*32, y*32, image[0], TRUE );
					//それ以外
					else if(map_flag[x][y] == 0 && player_fin() == 2){
						DrawGraph( x*32, y*32, image[1], TRUE );
					}
					else DrawGraph( x*32, y*32, image[2], TRUE );
					break;
				case -1://マップが平地の場合
					DrawGraph( x*32, y*32, image[0], TRUE );
					break;
				case 0://地雷が無いの場合
					DrawGraph( x*32, y*32, image[3], TRUE );
					break;
				case 1://地雷が無いの場合
					DrawGraph( x*32, y*32, image[4], TRUE );
					break;
				case 2://地雷が無いの場合
					DrawGraph( x*32, y*32, image[5], TRUE );
					break;
				case 3://地雷が無いの場合
					DrawGraph( x*32, y*32, image[6], TRUE );
					break;
				case 4://地雷が無いの場合
					DrawGraph( x*32, y*32, image[7], TRUE );
					break;
				case 5://地雷が無いの場合
					DrawGraph( x*32, y*32, image[8], TRUE );
					break;
				case 6://地雷が無いの場合
					DrawGraph( x*32, y*32, image[9], TRUE );
					break;
				default:
					break;
			}
		}
	}
}
void map_over(){
	for(int x=0;x<9;x++){
		for(int y=0;y<9;y++){
			map_flag[x][y] = 0;
		}
	}
}
int map_raandom(int min,int max){//乱数関数
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}