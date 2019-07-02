#include "DxLib.h"
#include "map.h"
#include "player.h"
#include "music.h"
int Key[256]; // キーが押されているフレーム数を格納する
// キーの入力状態を更新する
int gpUpdateKey(){
        char tmpKey[256]; // 現在のキーの入力状態を格納する
        GetHitKeyStateAll( tmpKey ); // 全てのキーの入力状態を得る
        for( int i=0; i<256; i++ ){ 
                if( tmpKey[i] != 0 ){ // i番のキーコードに対応するキーが押されていたら
                        Key[i]++;     // 加算
                } else {              // 押されていなければ
                        Key[i] = 0;   // 0にする
                }
        }
        return 0;
}
int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int){
        ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); //ウィンドウモード変更と初期化と裏画面設定
		SetMainWindowText("マインスイーパー");
		map_init();
		player_init();
		music_init();
		SetFontSize( 64 ) ;                             //サイズを64に変更
        SetFontThickness(8) ;                         //太さを8に変更
        ChangeFontType( DX_FONTTYPE_ANTIALIASING );     //アンチエイリアスフォントに変更
        // while(裏画面を表画面に反映, メッセージ処理, 画面クリア, キーの状態更新)
        while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && gpUpdateKey()==0){
			switch(player_fin()){
				case 1:
					DrawString(0,300,"マインスイーパー",GetColor(255,255,255));
					map_draw();
					player_updata();
					break;
				case 2:
					map_over();
					map_draw();
					//DrawString(165,150,"GAME OVER",GetColor(255,255,255));
					//DrawString(165,220,"Jでリトライ",GetColor(255,255,255));
					DrawString(10,300,"GAME OVER",GetColor(255,255,255));
					DrawString(10,370,"Jでリトライ",GetColor(255,255,255));
					if(Key[KEY_INPUT_J] == 1){
						map_init();
						player_init();
					}
					break;
				case 3:
					map_draw();
					//DrawString(165,150,"GAME CLEAR",GetColor(255,255,0));
					//DrawString(165,220,"Jでリトライ",GetColor(255,255,0));
					DrawString(10,300,"GAME CLEAR",GetColor(255,255,0));
					DrawString(10,370,"Jでリトライ",GetColor(255,255,0));
					if(Key[KEY_INPUT_J] == 1){
						map_init();
						player_init();
					}
					break;
				default:
					break;
			}
        }

        DxLib_End(); // DXライブラリ終了処理
        return 0;
} 