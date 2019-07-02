#include "DxLib.h"
#include "map.h"
#include"player.h"
//#include"player.h"
//#include"music.h"
static int map[9][9];
static int map_flag[9][9];
static int image[10];
/*
-3�@: �����ɂ͔��e�����������ꂽ�B
-2�@: �����ɂ͔��e�������Ă���B
-1�@: �����ɂ͔��e�͓����Ă��Ȃ��B�v���[���[�ɂ���ĊJ�����Ă����Ȃ��ꏊ�B
0�@: �v���[���[�ɂ���ĊJ����ꂽ�B���̎���ɂ͔��e�������B
1�@: �v���[���[�ɂ���ĊJ����ꂽ�B���̎���ɂ͔��e�� 1 ����B
2�@: �v���[���[�ɂ���ĊJ����ꂽ�B���̎���ɂ͔��e�� 2 ����B
3�@: �v���[���[�ɂ���ĊJ����ꂽ�B���̎���ɂ͔��e�� 3 ����B*/
void map_init(){//�}�b�v�̏����ݒ�
	LoadDivGraph( "�摜/map.png",10,10,1,32,32,image);
	for(int i = 0;i<9;i++){ //������
		for(int j = 0;j<9;j++){
			map[i][j] = -1;
			map_flag[i][j] = 0;
		}
	}
	for(int i = 0;i<10;i++){ //�n���̔z�u
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
int map_kensa(int x,int y){//�}�b�v�̌���
		if(map[x][y] == -1){//�}�b�v���n�ʂ������ꍇ
			map[x][y] = 0;
			map_flag[x][y] = 1;
			map_henka(x,y);
			return 0;
		}
		if(map[x][y] == -2 && map_flag[x][y] == 1){//�}�b�v���n���������ꍇ
			map_flag[x][y] = 0;
			//map[x][y] = -3;
			return 1;
		}
}
void map_henka(int x,int y){//���v����ɒn�������邩���ׂ�
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
void map_atari(int x,int y){//�}�b�v�𕽒n�ɂ���
	if(map[x][y] == -1){//�}�b�v���n�ʂ������ꍇ
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
void map_draw(){//�}�b�v��`�悷��
	for(int y = 0;y<9;y++){
		for(int x = 0;x<9;x++){
			switch(map[x][y]){
				case -3://���������ꂽ�ꍇ
					DrawGraph( x*32, y*32, image[2], TRUE );
					break;
				case -2://�}�b�v���n���̏ꍇ
					//�n���̐��̂��΂�Ă��Ȃ��ꍇ
					if(map_flag[x][y] == 1) DrawGraph( x*32, y*32, image[0], TRUE );
					//����ȊO
					else if(map_flag[x][y] == 0 && player_fin() == 2){
						DrawGraph( x*32, y*32, image[1], TRUE );
					}
					else DrawGraph( x*32, y*32, image[2], TRUE );
					break;
				case -1://�}�b�v�����n�̏ꍇ
					DrawGraph( x*32, y*32, image[0], TRUE );
					break;
				case 0://�n���������̏ꍇ
					DrawGraph( x*32, y*32, image[3], TRUE );
					break;
				case 1://�n���������̏ꍇ
					DrawGraph( x*32, y*32, image[4], TRUE );
					break;
				case 2://�n���������̏ꍇ
					DrawGraph( x*32, y*32, image[5], TRUE );
					break;
				case 3://�n���������̏ꍇ
					DrawGraph( x*32, y*32, image[6], TRUE );
					break;
				case 4://�n���������̏ꍇ
					DrawGraph( x*32, y*32, image[7], TRUE );
					break;
				case 5://�n���������̏ꍇ
					DrawGraph( x*32, y*32, image[8], TRUE );
					break;
				case 6://�n���������̏ꍇ
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
int map_raandom(int min,int max){//�����֐�
	return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}