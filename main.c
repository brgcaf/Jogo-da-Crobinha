#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"


int main(){
    //carrega dispositivos de áudio
    InitAudioDevice();
    
    Jogo jogo;

    int gameOver = 0;
    srand(time(NULL));

    InitWindow(660, 660, "Snake Game");
    SetTargetFPS(30);
    IniciaJogo660(&jogo);
    jogo.game_state = menu_prin;
    InicializaMenu(&jogo);
    InicializaConfig(&jogo);    

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);

        if(jogo.game_state == menu_prin){
            DrawMenu(&jogo);
            AtualizaMenu(&jogo);
        }else if(jogo.game_state == leaderboards){
            
        }else if(jogo.game_state == config){
            DrawConfig(&jogo);
            AtualizaConfig(&jogo);
        }else if(jogo.game_state == sair){
            EndDrawing();
            LiberaEspaco(&jogo);
            CloseAudioDevice();
            CloseWindow();
            return 0;
        }
        else if(!gameOver && jogo.game_state == start){   
            gameOver = AtualizaRodada(&jogo);
            DesenhaJogo(&jogo);
        }else{

            FimdeJogotxt(&jogo);
            
            if(IsKeyPressed(KEY_ENTER)){
                if(jogo.screen.altura == 660){
                    IniciaJogo660(&jogo);
                }else if(jogo.screen.altura == 820){
                    IniciaJogo820(&jogo);
                }
                gameOver = 0;
                jogo.sessao = 0;
            }
        }

        EndDrawing();
    }

    LiberaEspaco(&jogo);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}