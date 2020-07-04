#include "BLOCO.h"
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_primitives.h"
#include<fstream>
#include<iostream>




using namespace std;
BLOCO::BLOCO(){
        bloco=0;
        i=1;
}

BLOCO::BLOCO(const int b, const int c){
        bloco=b;
        i=c;
}
BLOCO::BLOCO(const BLOCO &obj){
        bloco=obj.bloco;
}
void BLOCO::set_BLOCO(){
        bloco=40;
}

int BLOCO::get_BLOCO(){
        return bloco;
}
BLOCO::~BLOCO(){}

void BLOCO::carrega_mapa(char mapa[][18]){//desenho o mapa atraves do arquivo txt
        ifstream mapaz;
        int i=0,j=0;
        char c;

        mapaz.open("map.txt");

        while(mapaz.get(c)){//copia cada caractere do arq e copia para a matriz nas posições corretas
                cout<<c;

                if(j<18){
                        if(i<18) mapa[i][j]=c;
                        j++;
                }else {
                        j=0;
                        i++;
                }
        }

        for(i=0;i<18;i++){//imprime a matriz no terminal para ver se copia foi concluida sem erros
        cout<<" "<<endl;
            for(j=0;j<18;j++){
                cout<<mapa[i][j];

            }

        }

    }

    int BLOCO::anima_fundo(int sprite){
            int inicio=0;
            int limite=5;

            if(sprite==inicio)
                    this->i=1;

            if(sprite==limite)
                    this->i=-1;

            sprite+=i;
            return sprite;

    }


