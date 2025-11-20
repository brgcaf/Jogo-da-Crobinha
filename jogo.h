#ifndef JOGO_H
#define JOGO_H

extern float resize_var;

#include "snake.h"
#include "frutinha.h"

typedef struct{
    Rectangle start;
    Rectangle config;
    Rectangle leaderboards;
    Rectangle exit;
    Texture2D textura;
    Image imagem;
}Menu;

typedef struct{
    int largura;
    int altura;
    float resize_var;
}Screen;

typedef struct{
    Rectangle res660;
    Rectangle res820;
    Rectangle voltar;
}Config;

typedef enum{
    menu_prin, config, leaderboards, start, sair
}Game_state;

typedef struct{

    Rectangle borda[4];
    ListaCobra cobra;
    Fruta frutinha;
    double tempo;
    float sessao;
    Image fundo;
    Texture2D textura;
    Menu menu;
    Config config;
    Screen screen;
    Game_state game_state;
}Jogo;



void IniciaBordas(Jogo* jogo);
void IniciaJogo660(Jogo* jogo);
void IniciaJogo820(Jogo* jogo);
void DesenhaJogo(Jogo* jogo);
void DesenhaBordas(Jogo* jogo);
extern int AtualizaRodada(Jogo* jogo);
void CobraGulosa(Jogo* jogo);
void MostraTempo(Jogo* jogo);
void FimdeJogotxt(Jogo* jogo);
void LiberaEspaco(Jogo* jogo);
void InicializaMenu(Jogo* jogo);
void DrawMenu(Jogo* jogo);
void AtualizaMenu(Jogo* jogo);
void InicializaConfig(Jogo* jogo);
void DrawConfig(Jogo* jogo);
void AtualizaConfig(Jogo* jogo);


#endif