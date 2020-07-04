#ifndef JOGADOR_H
#define JOGADOR_H

class jogador{
	public:
		jogador();
		jogador(const float, const float, const int, const int, const int[4], const int[4], const int[4], const int, const int, const int, const int[2]);
                jogador(const jogador&);

		float getJogadorX();
		float getJogadorY();
		int getJogadorpx();
		int getJogadorpy();
		int getJogadorAltura();
		int getJogadorLargura();

		void setJogadorX(float); // atibui valores
		void setJogadorY(float);
		void setJogadorpx(int);
		void setJogadorpy(int);
		void setValores();

		bool predict_direita(char[18][18]);
		bool predict_esquerda(char[18][18]);
		bool predict_baixo(char[18][18]);
		bool predict_acima(char[18][18]);
		bool predict_acima_pix();
		bool predict_baixo_pix();
		bool predict_esquerda_pix();
		bool predict_direita_pix();
		//void corrigir(int[4], int[4], int[4]); //Usar em caso de erro nas animações

		int anima_jogador(int);
		int anima_jogador_vitoria(int);

		~jogador();


	private:
        int sprite_vitoria[2];
		float jx, jy;
		int px, py;
		int altura, largura;
		int sprite[4], direcao[4], limite[4], frames;

};


#endif

