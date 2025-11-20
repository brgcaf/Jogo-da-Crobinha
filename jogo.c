#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "jogo.h"
#include "snake.h"
#include "frutinha.h"
#include <time.h>


void IniciaBordas(Jogo *jogo){
    if(jogo->screen.altura == 660){
        //Borda de cima
        jogo->borda[0] = (Rectangle) {0, 0, jogo->screen.largura, 10};
        //Borda da direita
        jogo->borda[1] = (Rectangle) {jogo->screen.largura - 10, 0, 10, jogo->screen.altura};
        //Borda de baixo
        jogo->borda[2] = (Rectangle) {0, jogo->screen.altura - 10, jogo->screen.largura, 10};
        //Borda da esquerda
        jogo->borda[3] = (Rectangle) {0, 0, 10, jogo->screen.altura};
    }else{
        //Borda de cima
        jogo->borda[0] = (Rectangle) {0, 0, jogo->screen.largura, 12.424};
        //Borda da direita
        jogo->borda[1] = (Rectangle) {jogo->screen.largura - 12.424, 0, 12.424, jogo->screen.altura};
        //Borda de baixo
        jogo->borda[2] = (Rectangle) {0, jogo->screen.altura - 12.424, jogo->screen.largura, 12.424};
        //Borda da esquerda
        jogo->borda[3] = (Rectangle) {0, 0, 12.424, jogo->screen.altura};
    }
}

void IniciaFundo(Jogo *jogo){
    jogo->fundo = LoadImage("fundo.png");
    if(jogo->screen.altura == 660){
        ImageResize(&jogo->fundo, 660,660);
    }else if(jogo->screen.largura == 820){
        ImageResize(&jogo->fundo, 820, 820);
    }
    jogo->textura = LoadTextureFromImage(jogo->fundo);
}



void DesenhaBordas(Jogo* jogo){
    
    for(int i = 0; i < 4; i++){
        DrawRectangleRec(jogo->borda[i], GRAY);
    }
}

void DesenhaFundo(Jogo* jogo){
    
    DrawTexture(jogo->textura, 12.424, 12.424, WHITE);
}
void DesenhaJogo(Jogo* jogo){
    DesenhaFundo(jogo);
    MostraTempo(jogo);
    DesenhaBordas(jogo);
    DesenhaCobra(&jogo->cobra);
    MostraTempo(jogo);
    DesenhaFrutinha(&jogo->frutinha, &jogo->cobra);
}


int AtualizaRodada(Jogo* jogo){
    
    AtualizaDirecao(&jogo->cobra);
    
    if(GetTime() - jogo->tempo >= 0.2){
        
        jogo->tempo = GetTime();
        AtualizaPosCobra(&jogo->cobra);
        jogo->cobra.cooldown = 0.2;
        jogo->sessao += 0.2;
        CobraGulosa(jogo);
    }
    
    return MataCobra(&jogo->cobra, jogo->borda);
}

void DescarregaText(Jogo* jogo){
    UnloadTexture(jogo->textura);
    UnloadTexture(jogo->frutinha.textura);
}

void LiberaEspaco(Jogo* jogo){
    
    LiberaEspacoCobra(&jogo->cobra);
    DescarregaText(jogo);
}

void MostraTempo(Jogo* jogo){
    int minutos, segundos;
    minutos = jogo->sessao/60;
    segundos = (int)(jogo->sessao)%60;
    DrawRectangle(485, 45, 75, 35, (Color){0,0,0,150});
    DrawText(TextFormat("%d:%02d", minutos, segundos), 500, 50, 30, RAYWHITE);
}

void CobraGulosa(Jogo* jogo){
    
    if(CheckCollisionRecs(jogo->cobra.Cabeca->posicao, jogo->frutinha.posicao)){
        
        AumentaCobra(&jogo->cobra);
        jogo->frutinha.pontuacao++;
        jogo->frutinha.existe = false;
    }
}

void FimdeJogotxt(Jogo* jogo){
    DrawText("Você Perdeu!", 225, 200, 40, WHITE);
    DrawText(TextFormat("Tempo da partida anterior: %d:%02d", (int)jogo->sessao/60, (int)jogo->sessao%60), 225, 300, 20, WHITE);
    DrawText(TextFormat("Pontuação: %d", jogo->frutinha.pontuacao), 225, 350, 20, WHITE);
    DrawText("Pressione ENTER para tentar novamente.", 150, 400, 20, WHITE); 
}

//A PARTIR DAQUI, É TUDO PT2

void InicializaMenu(Jogo* jogo){
    if(jogo->screen.altura == 660){
        jogo->menu.imagem = LoadImage("cobrinha_menu.jpg");
        ImageResize(&jogo->menu.imagem, jogo->screen.largura/2.5, jogo->screen.altura/2.5);
        jogo->menu.textura = LoadTextureFromImage(jogo->menu.imagem);
        jogo->menu.start = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*2, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
        jogo->menu.leaderboards = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*4, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
        jogo->menu.config = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*6, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
        jogo->menu.exit = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*8, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
    }else if(jogo->screen.altura == 820){
        jogo->menu.imagem = LoadImage("cobrinha_menu.jpg");
        ImageResize(&jogo->menu.imagem, jogo->screen.largura/2.5, jogo->screen.altura/2.5);
        jogo->menu.textura = LoadTextureFromImage(jogo->menu.imagem);
        jogo->menu.start = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*2, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
        jogo->menu.leaderboards = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*4, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
        jogo->menu.config = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*6, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
        jogo->menu.exit = (Rectangle){jogo->screen.largura*0.6, (jogo->screen.altura/10)*8, jogo->screen.largura*0.3, jogo->screen.altura*0.125};
    }
}

void DrawMenu(Jogo* jogo){
    DrawTexture(jogo->menu.textura, 0, 0, WHITE);
    DrawText("Jogo da Crobinha", jogo->screen.largura*0.4, jogo->screen.altura*0.1, 40, RAYWHITE);
    DrawRectangleRec(jogo->menu.start, RAYWHITE);
    DrawText("Jogar", jogo->menu.start.x+jogo->screen.largura*0.08, jogo->menu.start.y+jogo->screen.altura*0.05, 25, BLACK);
    DrawRectangleRec(jogo->menu.leaderboards, RAYWHITE);
    DrawText("Rankings", jogo->menu.leaderboards.x+jogo->screen.largura*0.06, jogo->menu.leaderboards.y+jogo->screen.altura*0.05, 25, BLACK);
    DrawRectangleRec(jogo->menu.config, RAYWHITE);
    DrawText("Configurações", jogo->menu.config.x+jogo->screen.largura*0.03, jogo->menu.config.y+jogo->screen.altura*0.05, 25, BLACK);
    DrawRectangleRec(jogo->menu.exit, RAYWHITE);
    DrawText("Sair", jogo->menu.exit.x+jogo->screen.largura*0.1, jogo->menu.exit.y+jogo->screen.altura*0.05, 25, BLACK);
}

void AtualizaMenu(Jogo* jogo){
    Vector2 mouse = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse, jogo->menu.start)){
            jogo->game_state = start;
        }else if(CheckCollisionPointRec(mouse, jogo->menu.leaderboards)){
            jogo->game_state = leaderboards;
        }else if(CheckCollisionPointRec(mouse, jogo->menu.config)){
            jogo->game_state = config;
        }else if(CheckCollisionPointRec(mouse, jogo->menu.exit)){
            jogo->game_state = sair;
        }
    }
}

void InicializaConfig(Jogo *jogo){
    jogo->config.res660 = (Rectangle){jogo->screen.largura*0.10, jogo->screen.altura*0.2, jogo->screen.largura*0.35, jogo->screen.altura*0.2};
    jogo->config.res820 = (Rectangle){jogo->screen.largura*0.60, jogo->screen.altura*0.2, jogo->screen.largura*0.35, jogo->screen.altura*0.2};
    jogo->config.voltar = (Rectangle){jogo->screen.largura*0.40, jogo->screen.altura*0.6, jogo->screen.largura*0.35, jogo->screen.altura*0.2};
}

void DrawConfig(Jogo *jogo){
    DrawRectangleRec(jogo->config.res660, WHITE);
    DrawText("660x660", jogo->config.res660.x+jogo->screen.largura*0.05, jogo->config.res660.y+jogo->screen.altura*0.05, 25, BLACK);
    DrawRectangleRec(jogo->config.res820, WHITE);
    DrawText("820x820", jogo->config.res820.x+jogo->screen.largura*0.05, jogo->config.res820.y+jogo->screen.altura*0.05, 25, BLACK);
    DrawRectangleRec(jogo->config.voltar, WHITE);
    DrawText("Voltar", jogo->config.voltar.x+jogo->screen.largura*0.05, jogo->config.voltar.y+jogo->screen.altura*0.05, 25, BLACK);
}

void AtualizaConfig(Jogo *jogo){
    Vector2 mouse = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(CheckCollisionPointRec(mouse, jogo->config.res660)){
            if(jogo->screen.largura != 660 && jogo->screen.altura != 660){
                IniciaJogo660(jogo);
                SetWindowSize(jogo->screen.largura, jogo->screen.altura);
                
            }
            
        }else if(CheckCollisionPointRec(mouse, jogo->config.res820)){
            if(jogo->screen.largura != 820 && jogo->screen.altura != 820){
                
                IniciaJogo820(jogo);
                SetWindowSize(jogo->screen.largura, jogo->screen.altura);
                
            }
            
        }else if(CheckCollisionPointRec(mouse, jogo->config.voltar)){
            jogo->game_state = menu_prin;
        }
    }
}

void IniciaJogo660(Jogo *jogo){

    jogo->screen.largura = 660;
    jogo->screen.altura = 660;
    

    jogo->tempo = GetTime();
    jogo->cobra.cooldown = 0.2;
    
    jogo->game_state = menu_prin;


    IniciaFundo(jogo);
    IniciaBordas(jogo);
    IniciaCobra(&jogo->cobra, 1);
    IniciaFrutinha(&jogo->frutinha, 1);
    InicializaMenu(jogo);
    InicializaConfig(jogo);
    
}

void IniciaJogo820(Jogo *jogo){

    jogo->screen.largura = 820;
    jogo->screen.altura = 820;
    
    jogo->game_state = menu_prin;

    jogo->tempo = GetTime();
    jogo->cobra.cooldown = 0.2;
    
    IniciaFundo(jogo);
    IniciaBordas(jogo);
    IniciaCobra(&jogo->cobra, 1.2424);
    IniciaFrutinha(&jogo->frutinha, 1.2424);
    
}