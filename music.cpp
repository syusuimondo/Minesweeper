#include "DxLib.h"
#include "music.h"
#include"player.h"
static int music_zyuu;
static int music_bomb;
void music_init(){//���y�̏����ݒ�
	music_zyuu = LoadSoundMem("�T�E���h/zyuu.mp3");
	music_bomb = LoadSoundMem("�T�E���h/bomb.mp3");
}
void music_draw(int i){//���y�̑I��
	switch(i){
	case 0://�e��
		PlaySoundMem( music_zyuu, DX_PLAYTYPE_BACK );
		break;
	case 1://�n����
		PlaySoundMem( music_bomb, DX_PLAYTYPE_BACK );
		break;
	}
}