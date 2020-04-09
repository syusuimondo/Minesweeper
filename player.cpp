#include"DxLib.h"
#include"player.h"
#include"map.h"
#include"music.h"
#define MAP_SIZE 9
extern int Key[256];
extern int gpUpdateKey();
extern int gameselect;
//�v���C���[�̏����ݒ�
void player_init(){
	player.x = 0;
	player.y = 0;
	player.flag = 1;
	player.count = 0;
	player.load = LoadGraph("�摜/player.png");
	sousa = LoadGraph("�摜/sousa.png");
	tama_count = 10;
	tama = LoadGraph("�摜/tama.png");
}
void player_updata(){
	//���ړ�
	if(Key[KEY_INPUT_D] == 1 && player.x <MAP_SIZE-1){
		player.x++;
	}
	//�E�ړ�
	if(Key[KEY_INPUT_A] == 1 && player.x > 0){
		player.x--;
	}
	//���ړ�
	if(Key[KEY_INPUT_S] == 1 && player.y <MAP_SIZE-1){
		player.y++;
	}
	//��ړ�
	if(Key[KEY_INPUT_W] == 1&& player.y> 0){
		player.y--;
	}
	//�n������
	if(Key[KEY_INPUT_J] == 1){
		if(map_kensa(player.x,player.y) == 1){
			music_draw(1);
			player.flag = 2;
		}
	}
	//�n���j��
	if(Key[KEY_INPUT_K] == 1){
		switch(map_kensa(player.x,player.y)){
		case 0:
			music_draw(1);
			player.flag = 2;
			break;
		case 1:
			music_draw(0);
			tama_count--;
			player.count++;
			break;
		}
		if(player.count >= 10) player.flag = 3;
	}
	player_draw();
}
void player_draw(){
	DrawGraph(player.x*32,player.y*32,player.load,TRUE);
	DrawGraph(320,0,sousa,TRUE);
	for(int i = 0;i<tama_count;i++){
		DrawGraph(i*64+10,360,tama,TRUE);
	}
}
void player_flag(){
	player.flag = 0;
}
int player_fin(){
	if(player.flag == 1) return 1;
	if(player.flag == 2) return 2;
	if(player.flag == 3) return 3;
}