#include"Fantasma.h"
#include<iostream>

using namespace std;

Fantasma::Fantasma(){ }

Fantasma::Fantasma(const float jx2, const float jy2, const int px2, const int py2, const int*a, const int *b, const int*c, const int f, const int altura1, const int largura1, const int *vitoria1):jogador(jx2, jy2, px2, py2, a, b, c, f, altura1, largura1, vitoria1){
        //construtor normal
}

Fantasma::Fantasma(const Fantasma& obj):jogador(obj){

}

Fantasma::~Fantasma(){ }

void Fantasma::setValores_F(float X, float Y, int x, int y){
        jogador::setValores();

        this->setJogadorX(X);
        this->setJogadorY(Y);

        this->setJogadorpx(x);
        this->setJogadorpy(y);


}

bool Fantasma::colisao(float X, float Y, int mx, int my ){
        if(this->getJogadorpy()-1 == my && this->getJogadorpx() == mx){
                if(this->getJogadorY() - Y <= 22 && this->getJogadorY() - Y >= -22){
                        return true;
                }
        }else if(this->getJogadorpy()+1 == my && this->getJogadorpx() == mx){
                if(this->getJogadorY() - Y <= 22 && this->getJogadorY() - Y >= -22 ){
                        return true;
                }
        }if(this->getJogadorpy() == my && this->getJogadorpx()-1 == mx){
                if(this->getJogadorX() - X <=22 && this->getJogadorX() - X >=-22){
                        return true;
                }
        }if(this->getJogadorpy() == my && this->getJogadorpx()+1 == mx){
                if(this->getJogadorX() - X <=22 && this->getJogadorX() - X >=-22){
                        return true;
                }
        }else return false;
}
