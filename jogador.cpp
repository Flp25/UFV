#include "jogador.h"							//px, py = posisão na matriz
#include <iostream>								//jx, jy = posisão em pixel na tela

using namespace std;


jogador::jogador(){	 //construtor padrão
	jx = jy = 0;
	px = py = 0;
	altura = 0;
	largura = 0;
	frames = 0;
	sprite_vitoria[0]=0;
	sprite_vitoria[1]=0;
}

jogador::jogador(const float jx2, const float jy2, const int px2, const int py2, const int*a, const int *b, const int*c, const int f, const int altura1, const int largura1, const int *vitoria1){    //construtor normal
	this->jx = jx2;
	this->jy = jy2;
	this->px = px2;
	this->py = py2;
	this->frames=f;
	this->altura=altura1;
	this->largura=largura1;
	this->sprite_vitoria[0]=vitoria1[0];
	this->sprite_vitoria[1]=vitoria1[1];

	for(int i=0;i<4;i++){
		this->sprite[i]=a[i];
		this->direcao[i]=b[i];
		this->limite[i]=c[i];
	}
}

jogador::jogador(const jogador& obj){
	jx=obj.jx;
	jy=obj.jy;
	px=obj.px;
	py=obj.py;
	frames=obj.frames;
	altura=obj.altura;
	largura=obj.largura;
	sprite_vitoria[0]=obj.sprite_vitoria[0];
	sprite_vitoria[1]=obj.sprite_vitoria[1];

	for(int i=0;i<4;i++){
		this->sprite[i]=obj.sprite[i];
		this->direcao[i]=obj.direcao[i];
		this->limite[i]=obj.limite[i];
	}
}




float jogador::getJogadorX(){ //retorna o valor horizontal do jogador em pixel
	return this->jx;
}

float jogador::getJogadorY(){ //retorna o valor vertical do jogador em pixel
	return this->jy;
}

int jogador::getJogadorpx(){ //retorna o valor horizontal do jogador na matriz
	return this->px;
}

int jogador::getJogadorpy(){  //retorna o valor vertical do jogador na matriz
	return this->py;
}
int jogador::getJogadorAltura(){
	return this->altura;
}
int jogador::getJogadorLargura(){
	return this->largura;
}



void jogador::setJogadorX(float a){ // posisão horizontal em pixel
	this->jx = a;
}

void jogador::setJogadorY(float a){ //posisão vertical em pixel
	this->jy = a;
}

void jogador::setJogadorpx(int a){ //posisão horizontal na matriz
	this->px = a;
}

void jogador::setJogadorpy(int a){ //posisão vertical na matriz
	this->py = a;
}

void jogador::setValores(){
        setJogadorpx(9);//posicao inicial do jogador na matriz de caracteres
        setJogadorpy(9);

        setJogadorX(360);//posicao inicial do jogador no display
        setJogadorY(360);

        this->altura=40;//altura e largura de cada quadro desenhado da sequencia de imagens
        this->largura=33;
        this->sprite_vitoria[0]=0;
        this->sprite_vitoria[1]=6;

        this->frames=1;//contador que irá "passar" ou "voltar" as imagend para dar a sensação de movimento

        int s=0;//contadores auxiliares
        int l=5;

        for(int i=0; i<4; i++){
                this->sprite[i]=s;//estabelece o numero de imagens
                this->direcao[i]=s;//que cada direcao ira representar
                this->limite[i]=l;//EX: as imagens "para cima" irão ser representadas pelos valores de 0 até 5.
                s=l+1;
                l+=6;

        }


}


bool jogador::predict_direita(char mapa[][18]){ //passa a posição a direita do jogador para verificar qual elemente existe ao seu lado
		if(mapa[this->px+1][this->py]=='.'|| mapa[this->px+1][this->py]=='V') return true;
        return false;
}

bool jogador::predict_esquerda(char mapa[][18]){ //passa a posição a esquerda do jogador para verificar qual elemente existe ao seu lado
	    if(mapa[this->px-1][this->py]=='.'|| mapa[this->px-1][this->py]=='V') return true;
        return false;
}

bool jogador::predict_baixo(char mapa[][18]){  //passa a posição abaixo do jogador para verificar qual elemente existe ao seu lado
	    if(mapa[this->px][this->py+1]=='.'|| mapa[this->px][this->py+1]=='V') return true;
        else return false;
}

bool jogador::predict_acima(char mapa[][18]){ //passa a posição acima do jogador para verificar qual elemente existe ao seu lado
	 	if(mapa[this->px][this->py-1]=='.'|| mapa[this->px][this->py-1]=='V') return true;
       return false;
}

bool jogador::predict_acima_pix(){ //retorna true se a posição do jogador é a mesma na matriz em pixel
		float rx;
        rx=this->px*40;
        if(rx==this->jx) return true;
        return false;
}

bool jogador::predict_baixo_pix(){
		float rx;
        rx=this->px*40;
        if(rx==this->jx) return true;
        return false;
}

bool jogador::predict_esquerda_pix(){
		float ry;
        ry=this->py*40;
        if(ry==this->jy) return true;
        return false;
}

bool jogador::predict_direita_pix(){
		float ry;
        ry=this->py*40;
        if(ry==this->jy) return true;
        return false;
}




/*void jogador::corrigir(int *sprite,int* direcao, int* limite){
        for(int i=0; i<4; i++){
                if(sprite[i]<direcao[i])
                        sprite[i]=direcao[i];
                else if(sprite[i]>limite[i])
                        sprite[i]=limite[i];

        }
}
   // USAR ESSA FUNÇAO CASO DÊ ALGUM ERRO NA ANIMAÇÃO DO JOGADOR
*/


int jogador::anima_jogador(int animacao){

        if(this->sprite[animacao] == this->direcao[animacao])
                this->frames = 1;

        else if(this->sprite[animacao] == this->limite[animacao])
                this->frames = -1;

        this->sprite[animacao] += this->frames;

        return this->sprite[animacao];


}
int jogador::anima_jogador_vitoria(int animacao){



        if(this->sprite_vitoria[animacao] == this->direcao[animacao])
                this->frames=1;
        else if(this->sprite_vitoria[animacao] == this->limite[animacao])
                this->frames=-1;

        this->sprite_vitoria[animacao]+=this->frames;

        return this->sprite_vitoria[animacao];
}


jogador::~jogador(){

}


