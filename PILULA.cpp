#include "PILULA.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include<iostream>


using namespace std;

PILULA::PILULA(){
            pilula=0;
}
PILULA::PILULA(const int p, const int q, const int r, const int s, const int t){
            this->pilula=p;
            this->inicio=q;
            this->sprite=r;
            this->limite=s;
            this->frames=t;
}
PILULA::PILULA(const PILULA &obj){
        pilula=obj.pilula;
}
void PILULA::set_valores(){
        pilula=40;
        sprite=0;
        inicio=0;
        limite=5;
}

int PILULA::get_PILULA(){
        return pilula;
}

int PILULA::get_sprite(){
        return sprite;
}
PILULA::~PILULA(){}

void PILULA::preenche_mapa(char mapa[][18]){


        for(int i=0;i<18;i++){
            for(int j=0;j<18;j++){

                if(mapa[i][j]=='.'){
                    mapa[i][j]='.';

                }
            }
        }
}

void PILULA::anima_pilula(){

     if(this->sprite==this->limite)
             this->frames = -1;


    else if(this->sprite == this->inicio)
            this->frames = 1;

    this->sprite+=this->frames;

}
