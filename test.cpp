#include "DxLib.h"
#include "map.h"
#include "player.h"
#include "music.h"
int Key[256]; // �L�[��������Ă���t���[�������i�[����
// �L�[�̓��͏�Ԃ��X�V����
int gpUpdateKey(){
        char tmpKey[256]; // ���݂̃L�[�̓��͏�Ԃ��i�[����
        GetHitKeyStateAll( tmpKey ); // �S�ẴL�[�̓��͏�Ԃ𓾂�
        for( int i=0; i<256; i++ ){ 
                if( tmpKey[i] != 0 ){ // i�Ԃ̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
                        Key[i]++;     // ���Z
                } else {              // ������Ă��Ȃ����
                        Key[i] = 0;   // 0�ɂ���
                }
        }
        return 0;
}
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
		SetMainWindowText("�}�C���X�C�[�p�[");
		map_init();
		player_init();
		music_init();
		SetFontSize( 64 ) ;                             //�T�C�Y��64�ɕύX
        SetFontThickness(8) ;                         //������8�ɕύX
        ChangeFontType( DX_FONTTYPE_ANTIALIASING );     //�A���`�G�C���A�X�t�H���g�ɕύX
        // while(����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �L�[�̏�ԍX�V)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0){
			switch(player_fin()){
				case 1:
					DrawString(0,300,"�}�C���X�C�[�p�[",GetColor(255,255,255));
					map_draw();
					player_updata();
					break;
				case 2:
					map_over();
					map_draw();
					//DrawString(165,150,"GAME OVER",GetColor(255,255,255));
					//DrawString(165,220,"J�Ń��g���C",GetColor(255,255,255));
					DrawString(10,300,"GAME OVER",GetColor(255,255,255));
					DrawString(10,370,"J�Ń��g���C",GetColor(255,255,255));
					if(Key[KEY_INPUT_J] == 1){
						map_init();
						player_init();
					}
					break;
				case 3:
					map_draw();
					//DrawString(165,150,"GAME CLEAR",GetColor(255,255,0));
					//DrawString(165,220,"J�Ń��g���C",GetColor(255,255,0));
					DrawString(10,300,"GAME CLEAR",GetColor(255,255,0));
					DrawString(10,370,"J�Ń��g���C",GetColor(255,255,0));
					if(Key[KEY_INPUT_J] == 1){
						map_init();
						player_init();
					}
					break;
				default:
					break;
			}
        }

        DxLib_End(); // DX���C�u�����I������
        return 0;
} 