#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"


int main(){

    Jogo jogo;
    int gameOver = 0;

    InitWindow(LARGURA, ALTURA, "Snake Game");
    SetTargetFPS(30);
    IniciaJogo(&jogo);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(BLACK);

        if(!gameOver){
            
            gameOver = AtualizaRodada(&jogo);
            DesenhaJogo(&jogo);
        }else{

            DrawText("Você Perdeu!", 150, 200, 40, WHITE);
            DrawText("Tentar Novamente?", 265, 400, 30, WHITE); 

            if(IsKeyPressed(KEY_ENTER)){
                IniciaJogo(&jogo);
                gameOver = 0;
            }
        }

        EndDrawing();
    }

    LiberaEspaco(&jogo);
    CloseWindow();
    return 0;
}