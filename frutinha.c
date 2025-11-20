#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "frutinha.h"
#include "jogo.h"

void IniciaFrutinha(Fruta* fruta, float resize){
    fruta->existe = false;

    fruta->foto = LoadImage("moranguinho.png");

    if(resize == 1){
        fruta->posicao.height = 20;
        fruta->posicao.width = 20;        
        ImageResize(&fruta->foto, 20, 20);

    }else if(resize != 1){
        fruta->posicao.height = 20;
        fruta->posicao.width = 20;        
        ImageResize(&fruta->foto, 20*1.2424, 20*1.2424);
    }
    fruta->pontuacao = 0;

    //carregar o som
    fruta->come_fruta = LoadSound("menu_sound_effect_fx.wav");
    SetSoundVolume(fruta->come_fruta, 10.0f);

    fruta->textura = LoadTextureFromImage(fruta->foto);
}

void DesenhaFrutinha(Fruta* fruta, ListaCobra* Cobra){
    if(fruta->existe == false){
        AtualizaPosFrutinha(fruta, Cobra);
        DrawTexture(fruta->textura, fruta->posicao.x, fruta->posicao.y, WHITE);

    }else if(fruta->existe == true){
        DrawTexture(fruta->textura, fruta->posicao.x, fruta->posicao.y, WHITE);
    }
}

void AtualizaPosFrutinha(Fruta* frutinha, ListaCobra* Cobra){

    TipoApontador testadouro = Cobra->Cabeca;
    if(Cobra->resize == 1){

        frutinha->posicao.x = (12.424+20*((int)rand()%((660/20)-1)));
        frutinha->posicao.y = (12.424+20*((int)rand()%((660/20)-1)));
        if(frutinha->existe == false){
            PlaySound(frutinha->come_fruta);
            frutinha->existe = true;
        }
        while(testadouro != NULL){
    
            if(CheckCollisionRecs(testadouro->posicao, frutinha->posicao)){
                
                frutinha->posicao.x = 12.424+20*(rand()%30);
                frutinha->posicao.y = 12.424+20*(rand()%30);
                testadouro = Cobra->Cabeca;
                continue;
            }
    
            testadouro = testadouro->Prox;
        } 
    }else if(Cobra->resize != 1){
        
        frutinha->posicao.x = (12.424+20*((int)rand()%((820/20)-1)));
        frutinha->posicao.y = (12.424+20*((int)rand()%((820/20)-1)));
        if(frutinha->existe == false){
            PlaySound(frutinha->come_fruta);
            frutinha->existe = true;
        }
        while(testadouro != NULL){
    
            if(CheckCollisionRecs(testadouro->posicao, frutinha->posicao)){
                
                frutinha->posicao.x = (12.424+20*((int)rand()%((820/20)-1)));
                frutinha->posicao.y = (12.424+20*((int)rand()%((820/20)-1)));
                testadouro = Cobra->Cabeca;
                continue;
            }
    
            testadouro = testadouro->Prox;
        } 
    }

}