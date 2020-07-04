#ifndef FANTASMA_H
#define FANTASMA_H
#include"jogador.h"

class Fantasma:public jogador{
	public:
		Fantasma();
		Fantasma(const float, const float, const int, const int, const int[4], const int[4], const int[4], const int, const int, const int, const int[4]);
                Fantasma(const Fantasma&);
        ~Fantasma();
        void setValores_F(float, float, int, int);
        bool colisao(float, float, int, int);

	private:



};
#endif
