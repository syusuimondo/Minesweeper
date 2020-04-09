#include "DxLib.h"
#include "music.h"
#include"player.h"
static int music_zyuu;
static int music_bomb;
void music_init(){//音楽の初期設定
	music_zyuu = LoadSoundMem("サウンド/zyuu.mp3");
	music_bomb = LoadSoundMem("サウンド/bomb.mp3");
}
void music_draw(int i){//音楽の選択
	switch(i){
	case 0://銃声
		PlaySoundMem( music_zyuu, DX_PLAYTYPE_BACK );
		break;
	case 1://地雷音
		PlaySoundMem( music_bomb, DX_PLAYTYPE_BACK );
		break;
	}
}