#include "allegro5/allegro.h"							//m_l - jg.getJogadorX();
#include "allegro5/allegro_image.h"						//m_a - jg.getJogadorY();
#include "allegro5/allegro_primitives.h"
#include<allegro5/allegro_acodec.h>
#include<allegro5/allegro_audio.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>


#include<iostream>
#include<fstream>
#include<math.h>
#include<time.h>
#include<stdlib.h>


#include "BLOCO.h"
#include "PILULA.h"
#include "jogador.h"
#include "Fantasma.h"

//PROJETO PACMAN

//ALEXANDRE  - (ADD MATRICULA AQ)
//CARLOS     - (ADD MATRICULA AQ)
//FELIPE DIAS MACEDO - (4799)



using namespace std;


int main(int argc, char **argv){
    //**************************** OBJETOS ****************************************
    BLOCO b;//objeto bloco
    PILULA p;//objeto pilula
    Fantasma ft[5];

	jogador jg; //objeto jogador



	//************************************ SET DE VALORES DOS OBJETOS ******************************

	p.set_valores();//Atribui os valores necessários para a animação da pilula
    b.set_BLOCO();//Atribui os valores inteiros necessários para o bloco
    jg.setValores();
    ft[0].setValores_F(b.get_BLOCO()*4,b.get_BLOCO()*1,4,1);
    ft[1].setValores_F(b.get_BLOCO()*13,b.get_BLOCO()*1,13,1);
    ft[2].setValores_F(b.get_BLOCO()*1,b.get_BLOCO()*13,1,13);
    ft[3].setValores_F(b.get_BLOCO()*16,b.get_BLOCO()*13,16,13);
    ft[4].setValores_F(b.get_BLOCO()*9,b.get_BLOCO()*16,9,16);
    //ft[5].setValores_F(b.get_BLOCO()*10,b.get_BLOCO()*13,10,13);



    //********************************** VARIÁVEIS GENÉRICAS ***************************************

    int animacao, frame, animacao_f[5];
    int i,j,k,l,prioridade, ativo;//contadores
    int d,movendo, espera, contador,ciclos, sprite_fundo;
    int movendoF[5], lF[5], kF[5],frame_f[5];

    bool up,down,left,right;
    bool upF[5], downF[5], leftF[5], rightF[5];

    bool re_desenha = true;
    bool termina = false;
    bool teclas[255] = {false};



    up=down=left=right=false;
    k=l=prioridade=ativo=movendo=espera=contador=ciclos=sprite_fundo=0;



    int sorteia;

    animacao=1;



    //0 down
    //6 right
    //12 left
    //18 right



    for(i=0;i<5; i++){
            lF[i]=0;
            kF[i]=0;
            downF[i]=leftF[i]=rightF[i]=false;
            frame_f[i]=3;
            movendoF[i]=2;


    }

    downF[0]=leftF[1]=rightF[2]=leftF[3]=rightF[4]=true;
	movendoF[4]=4;






    char marcas_mapa[18][18];//matriz auxiliar para ajudar na construçao do mapa


    //****************************** ALLEGRO BASICO ********************************

    ALLEGRO_DISPLAY *display=NULL;//variável tela

    ALLEGRO_BITMAP*parede=NULL;//variáveis paredes
    ALLEGRO_BITMAP*pvertical=NULL;
    ALLEGRO_BITMAP*pvertical2=NULL;
    ALLEGRO_BITMAP*phorizontal=NULL;

    ALLEGRO_BITMAP*wood=NULL;//base das estátuas
    ALLEGRO_BITMAP*magus=NULL;//variavel do jogador
    ALLEGRO_BITMAP*statue=NULL;//variavel das estátuas
    ALLEGRO_BITMAP*magus_vitoria=NULL;//animação de vitoria

    ALLEGRO_BITMAP*enemy1=NULL;
    ALLEGRO_BITMAP*enemy2=NULL;
    ALLEGRO_BITMAP*enemy3=NULL;
    ALLEGRO_BITMAP*enemy4=NULL;

    ALLEGRO_BITMAP*Pilula=NULL;//pilula que preenche as celulas vazias
    ALLEGRO_BITMAP *fundo=NULL;//fundo vermelho
    ALLEGRO_BITMAP*fundo2=NULL;//zona externa ao mapa

    ALLEGRO_EVENT_QUEUE *event_queue = NULL; //Fila de Eventos
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_SAMPLE *fanfare=NULL;//musica de vitoria
    ALLEGRO_SAMPLE *bgm=NULL;//musica de fundo
    ALLEGRO_SAMPLE *lose=NULL;
    ALLEGRO_SAMPLE *slap=NULL;

    ALLEGRO_SAMPLE_INSTANCE *musica_de_fundo=NULL;
    ALLEGRO_SAMPLE_INSTANCE *fim=NULL;
    ALLEGRO_SAMPLE_INSTANCE *fim2=NULL;
    ALLEGRO_SAMPLE_INSTANCE *hit=NULL;

    ALLEGRO_FONT *pontos=NULL;//variavel dos pontos
    ALLEGRO_FONT *nomes=NULL;

    //************************ INICIALIZAÇÃO OBRIGATÓRIA DE BIBLIOTECAS ***********************************

    al_init();//inicialização obrigatoria do ALLEGRO

    al_init_image_addon();//inicialização das funções de imagem
    al_init_primitives_addon();//incialização das funções de desenho

    al_install_audio();//inicialização do audio
    al_init_acodec_addon();
    al_reserve_samples(3);//Quantidade de Audios que podem ser tocados ao mesmo tempo


    al_init_font_addon();//incialização de fonte
    al_init_ttf_addon();// True Type Font


    //******************************** DESENHOS ***************************************************


    display=al_create_display(1200,700);//cria a tela com as resoluções especificadas
    al_clear_to_color(al_map_rgb(0,0,0));//cria um fundo ta tela preto

    //carrega as imagens da pasta nas variáveis correspondentes

    enemy1=al_load_bitmap("enemy1.png");
    enemy2=al_load_bitmap("enemy2.png");
    enemy3=al_load_bitmap("enemy3.png");
    enemy4=al_load_bitmap("enemy4.png");

    fundo2=al_load_bitmap("bg5_A.png");//paisagem externa do mapa

    fundo=al_load_bitmap("bg2.png");//fundo vermelho do mapa #RPG


    /*fundo=al_load_bitmap("bg2_p.png");//fundo verde #pokemon
    parede=al_load_bitmap("roca8.png");//parede interna #pokemon
    pvertical=al_load_bitmap("vwallr_p.png");//parede vertical #pokemon
    pvertical2=al_load_bitmap("vwall_p.png");//parede vertical inversa #pokemon
    phorizontal=al_load_bitmap("hwall_p.png");//parede horizontal #pokemon
    Pilula=al_load_bitmap("poke_pill_A.png");//pilulas #pokemon
    magus=al_load_bitmap("player5.png");//jogador #pokemon*/



    wood=al_load_bitmap("roca7.png");//tiles abaixo das estátuas
    statue=al_load_bitmap("bg3.png");//estátuas


    parede=al_load_bitmap("roca5.png");//parede interna do mapa #RPG 
    pvertical=al_load_bitmap("vwallr.png");//parede vertical #RPG
    pvertical2=al_load_bitmap("vwall.png");//parede vertical inversa #RPG
    phorizontal=al_load_bitmap("hwall.png");//parede horizontal #RPG
    Pilula=al_load_bitmap("Pill_A.png");//pilulas #RPG
    magus=al_load_bitmap("player2.png");//jogador #RPG 


    magus_vitoria=al_load_bitmap("player_pose.png");


    //************************************** AUDIO ***********************************


    bgm=al_load_sample("BB.wav");//carrega a musica de fundo
    fanfare=al_load_sample("fanfare.wav");//10 40 VICTORY
    lose=al_load_sample("game_over.wav");
    slap=al_load_sample("slap.wav"); //Faliceu 

    pontos=al_load_ttf_font("X.ttf",40,0);//carrega a fonte que está na pasta do projeto
    nomes=al_load_ttf_font("X.ttf",24,0);

    musica_de_fundo=al_create_sample_instance(bgm);
    fim=al_create_sample_instance(fanfare);
    fim2=al_create_sample_instance(lose);
    hit=al_create_sample_instance(slap);


    al_set_sample_instance_playmode(musica_de_fundo, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(musica_de_fundo, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(fim, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(fim2, al_get_default_mixer());
    al_attach_sample_instance_to_mixer(hit, al_get_default_mixer());


    al_play_sample_instance(musica_de_fundo);


    //******************************* DESENHO INICIAL *****************************************

    al_draw_bitmap(fundo,0,0,0);//desenha o fundo vermelho, ficará na camada mais baixa dos desenhos
    al_draw_bitmap(fundo2,701,0,0);//Desenha muro externo e lago, e fundo azul para o menu de pontos.
    al_draw_bitmap(statue,0*p.get_PILULA(),0*p.get_PILULA(),0);//na camada do topo desenho as estatuas e outros objetos que posso adc futuramente
    al_draw_bitmap_region(magus,0,0,33,40,jg.getJogadorX(),jg.getJogadorY(),0);



    //***************************************** MAPA TXT ******************************************************

    b.carrega_mapa(marcas_mapa);//carrega o arq de texto contendo o mapa de caracteres e os copia para a matriz auxiliar
    p.preenche_mapa(marcas_mapa);//copia a posição das pílulas do arv de texto para a matriz auxiliar



    //***************************************** TECLADO & TIMER & FILA DE EVENTOS **************************************

    al_install_keyboard();//Funcoes Teclado
    timer = al_create_timer(1.0 / 60);
    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_display_event_source(display));//Evento da Tela
    al_register_event_source(event_queue, al_get_timer_event_source(timer));//Evento de tempo
    al_register_event_source(event_queue, al_get_keyboard_event_source());//Evento de Teclado

    al_start_timer(timer);
    al_clear_to_color(al_map_rgb(0,0,0));



    //******************************************* INICIO DO JOGO *****************************************************

    while(!termina){      //laço do jogo

		    ALLEGRO_EVENT ev;
		    al_wait_for_event(event_queue, &ev);


		    if(ev.type == ALLEGRO_EVENT_TIMER) {

		            if(ciclos==6) {//Quando tempo == FPS equivale a 1 segundo, assim a cada x milisegundos ele muda a sprite
		                al_set_timer_count(timer, 0);//Volta ao tempo 0
		                 //0 1 2 3 2 1 0

		                frame = jg.anima_jogador(animacao);
		                sprite_fundo=b.anima_fundo(sprite_fundo);


		                for(i=0;i<5;i++){
		                        animacao_f[i]=ft[i].anima_jogador(frame_f[i]);
		                }

		                //cout<<"jg: "<<frame<<" an: "<<animacao<<"|||ft: "<<frame_f[0]<<" | "<<animacao_f[0]<<"\n";
		                p.anima_pilula();

		                ciclos=0;


		            }

		            ciclos++;
		    }

		    cout<<jg.getJogadorpx()<<" - "<<jg.getJogadorpy()<<"\n";


		    //**************************** PRÉ-MOVIMENTO (FILA DE MOVIMENTO) *********************************************


		    //Aqui será feita a organização da fila de movimento.

		    //Se a fila estiver vazia qualquer direçao será ativada como movimento sem ter que esperar.

		    //Se a movimento aqui registrado for oposto ao que está ativo no momento então
		    //o movimento ativo será setado para 0 e a nova direçao registrada será a ativa
		    //para que personagem dê meia volta imediatamente.

		    //Caso a direção registrada não se aplica a nenhum dos casos acima então
		    //essa direção irá para a fila de espera por meio da variável "espera" que
		    //poderá ser ativada nas funçoes das linhas 221 ~ 247.

		    if(teclas[ALLEGRO_KEY_W] &&  jg.getJogadorY() >= 42 && up==false) {

		            if(marcas_mapa[jg.getJogadorpx()][jg.getJogadorpy()-1]=='.' || marcas_mapa[jg.getJogadorpx()][jg.getJogadorpy()-1]=='V'){
		                    if(movendo==2){
		                            espera=0;
		                            movendo=1;
		                            down=false;
		                    }else if(movendo==0){
		                            movendo=1;
		                    }else espera=1;
		                    up=true;

		            }

		    }else  if(teclas[ALLEGRO_KEY_S] && jg.getJogadorY() <= 638 && down==false) {
		            if(marcas_mapa[jg.getJogadorpx()][jg.getJogadorpy()+1]=='.' || marcas_mapa[jg.getJogadorpx()][jg.getJogadorpy()+1]=='V'){
		                    if(movendo==1){
		                            espera=0;
		                            movendo=2;
		                            up=false;
		                    }else if(movendo==0){
		                            movendo=2;
		                    }else espera=2;
		                    down=true;

		            }
		    }else if(teclas[ALLEGRO_KEY_A] && jg.getJogadorX() >= 42 && left==false) {

		            if(marcas_mapa[jg.getJogadorpx()-1][jg.getJogadorpy()]=='.' || marcas_mapa[jg.getJogadorpx()-1][jg.getJogadorpy()]=='V'){
		                    if(movendo==4){
		                            espera=0;
		                            movendo=3;
		                            right=false;
		                    }else if(movendo==0) movendo=3;
		                    else espera=3;
		                    left=true;

		            }
		    }else  if(teclas[ALLEGRO_KEY_D] && jg.getJogadorX() <= 638 && right==false) {

		            if(marcas_mapa[jg.getJogadorpx()+1][jg.getJogadorpy()]=='.' || marcas_mapa[jg.getJogadorpx()+1][jg.getJogadorpy()]=='V'){
		                    if(movendo==3){
		                            espera=0;
		                            movendo=4;
		                            left=false;
		                    }else if(movendo==0) movendo=4;
		                    else espera=4;
		                    right=true;
		            }
		    }


		    //******************************************* EXECUÇÃO DO MOVIMENTO & COLISÃO ****************************************

		    //O movimento "espera" ficará na fila até que apareça uma casa valida na direcao que deseja seguir
		    //caso apareça ele será ativado por meio da atribuição mov=espera
		    //caso uma nova tecla seja apertada o valor registrado na variável "espera" será reescrito.

		    if(movendo!=0){
		            if(espera==0){
		            }else if(espera==1){
		                    if(jg.predict_acima(marcas_mapa)){
		                                movendo=espera;
		                                espera=0;
		                                down=left=right=false;

		                    }
		            }else if(espera==2){
		                    if(jg.predict_baixo(marcas_mapa)){
		                           movendo=espera;
		                           espera=0;
		                           up=left=right=false;
		                    }
		            }else if(espera==3){
		                    if(jg.predict_esquerda(marcas_mapa)){
		                            movendo=espera;
		                            espera=0;
		                            up=down=right=false;
		                    }
		            }else if(espera==4){
		                    if(jg.predict_direita(marcas_mapa)){
		                            movendo=espera;
		                            espera=0;
		                            up=down=left=false;
		                    }
		            }

		            //O valor de "movimento" determina a direçao em pixels que a imagem irá percorrer na tela
		            //as funções "predict" normal e pix servem para alinhar a imagem com a matriz ( i e j )
		            // e a tela ( pixels ), assim evitando que o jogador entre em paredes pela quina
		            // as funções "setJogador" X & Y servem para registrar a posição do jogador (pixels) na tela.
		            //Após colidir com uma parede a variavel "movendo" é setada para 0.

		            if(movendo==1){
		                    if(jg.predict_acima(marcas_mapa) && jg.predict_acima_pix()){
		                            animacao=0;
		                            jg.setJogadorY(jg.getJogadorY()-2);
		                            k--;
		                    }else{
		                            movendo=0;
		                            up=false;
		                    }
		            }else if(movendo==2){
		                    if(jg.predict_baixo(marcas_mapa) && jg.predict_baixo_pix()){
		                            animacao=1;
		                            jg.setJogadorY(jg.getJogadorY()+2);
		                            k++;
		                    }else{
		                            movendo=0;
		                            down=false;
		                    }
		            }else if(movendo==3){
		                    if(jg.predict_esquerda(marcas_mapa) && jg.predict_esquerda_pix()){
		                            animacao=3;
		                            jg.setJogadorX(jg.getJogadorX()-2);
		                            l--;
		                    }else{
		                            movendo=0;
		                            left=false;
		                    }
		            }else if(movendo==4){
		                    if(jg.predict_direita(marcas_mapa) && jg.predict_direita_pix()){
		                            animacao=2;
		                            jg.setJogadorX(jg.getJogadorX()+2);
		                            l++;
		                    }else{
		                            movendo=0;
		                            right=false;
		                    }
		            }
		    }


		    //*************************************** MOVIMENTO (COORDENADAS DA MATRIZ) **************************************************

		                 /* O jogador anda 2 pixels por ciclo para andar uma casa, que possui valor de
		                  40 pixels, logo ele precisa de +-20 ciclos, +20 para baixo e direita, e -20 para esquerda e cima
		                  para que ele mova uma posicao na matriz de caracteres, onde será representado
		                  pela letra 'J' assim iniciando um novo ciclo.
		                   Se a posicao atual do jogador (contador k) estiver alinhada com
		                  a posicao da matriz (k = +-20) por meio do contador K
		                  entao atribui o char 'J' na matriz para dizer que o jogador está
		                  naquela posicao [i][j] da matriz.*/


		    if(k==20){
		            jg.setJogadorpy(jg.getJogadorpy()+1); 					//jg.setJogadorpy(jg.getJogadorpy()+1);
		            k=0;

		    }else if(k==-20){
		            jg.setJogadorpy(jg.getJogadorpy()-1);
		            k=0;

		    }if(l==20){
		            l=0;
		            jg.setJogadorpx(jg.getJogadorpx()+1);

		    }else if(l==-20){
		            l=0;
		            jg.setJogadorpx(jg.getJogadorpx()-1);
		    }



		    //********************************* COME PÍLULA ******************************************************

		    if(marcas_mapa[jg.getJogadorpx()][jg.getJogadorpy()]=='.'){
				marcas_mapa[jg.getJogadorpx()][jg.getJogadorpy()]='V';//Troca o ponto na matriz por v (Vazio).
				contador++; //Pontos
			}



		    //******************************** INIMIGOS ********************************************************
			// [0] = 2
			// [1] = 3
			// [2] = 4
			// [3] = 3
			int difx, dify;
			
			int hor,vert;
			//*********************************** Fantas que persegue *******************************************//

			if(jg.getJogadorpx() > ft[4].getJogadorpx()){
				difx=jg.getJogadorpx() - ft[4].getJogadorpx();
				hor=1; //direita

			}else if(jg.getJogadorpx() < ft[4].getJogadorpx()){
				difx=ft[4].getJogadorpx() - jg.getJogadorpx();
				hor=2; //esquerda
			}else	
				difx=0;



			if(jg.getJogadorpy() > ft[4].getJogadorpy()){
				dify=jg.getJogadorpy() - ft[4].getJogadorpy();
				vert=2; //esq

			}else if(jg.getJogadorpy() < ft[4].getJogadorpy()){
				dify=ft[4].getJogadorpy() - jg.getJogadorpy();
				vert=1; //dir
			}else	
				dify=0;



			if(difx>dify){
				if(hor==2){ 	
					if(ft[4].predict_esquerda(marcas_mapa) && ft[4].predict_esquerda_pix())	
						movendoF[4]=3;
					else if(ft[4].predict_acima(marcas_mapa) && ft[4].predict_acima_pix())
						movendoF[4]=1;
					else if(ft[4].predict_baixo(marcas_mapa) && ft[4].predict_baixo_pix())
						movendoF[4]=2;
					
				}else if(hor==1){
					if(ft[4].predict_direita(marcas_mapa) && ft[4].predict_direita_pix())
						movendoF[4]=4;
					else if(ft[4].predict_acima(marcas_mapa) && ft[4].predict_acima_pix())
						movendoF[4]=1;
					else if(ft[4].predict_baixo(marcas_mapa) && ft[4].predict_baixo_pix())
						movendoF[4]=2;
					
				}
			
			}else{
				if(vert==2){ 	
					if(ft[4].predict_baixo(marcas_mapa) && ft[4].predict_baixo_pix())	
						movendoF[4]=2;
					else if(ft[4].predict_esquerda(marcas_mapa) && ft[4].predict_esquerda_pix())
						movendoF[4]=3;
					else if(ft[4].predict_direita(marcas_mapa) && ft[4].predict_direita_pix())
						movendoF[4]=4;
					
				}else if(vert==1){
					if(ft[4].predict_acima(marcas_mapa) && ft[4].predict_acima_pix())
						movendoF[4]=1;
					else if(ft[4].predict_esquerda(marcas_mapa) && ft[4].predict_esquerda_pix())
						movendoF[4]=3;
					else if(ft[4].predict_direita(marcas_mapa) && ft[4].predict_direita_pix())
						movendoF[4]=4;
					
				}
			}
				

			for(i=0;i<4;i++){
					srand(movendoF[i]+ciclos+contador);
					if(upF[i]){ // VERIFICA LEFT E RIGHT
							if(ft[i].predict_direita_pix() && ft[i].predict_direita(marcas_mapa)&& ft[i].predict_esquerda_pix() && ft[i].predict_esquerda(marcas_mapa)){

		                    		sorteia=rand()%4;
		                    		sorteia++;
		                    		//VERIFICA UMA ENCRUZILHADA COM 3 NOVOS CAMINHOS, SORTEIA 4 DIRECOES

		                    		movendoF[i]=sorteia;

							}else if(ft[i].predict_direita_pix() && ft[i].predict_direita(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;
									//2 NOVOS CAMINHOS, SORTEIA 3 DIRECOES

									if(sorteia==3) sorteia=4;
									movendoF[i]=sorteia;

							}else if(ft[i].predict_esquerda_pix() && ft[i].predict_esquerda(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;

									movendoF[i]=sorteia;
							}

							if(movendoF[i]!=1){

									if(movendoF[i]==2){

											downF[i]=true;

									}else if(movendoF[i]==3){

											leftF[i]=true;

									}else if(movendoF[i]==4){

											rightF[i]=true;

									}
									upF[i]=false;
		                    }
					}else if(downF[i]){// VERIFICA LEFT E RIGHT
							if(ft[i].predict_direita_pix() && ft[i].predict_direita(marcas_mapa)&& ft[i].predict_esquerda_pix() && ft[i].predict_esquerda(marcas_mapa)){

		                    		sorteia=rand()%4;
		                    		sorteia++;

		                    		movendoF[i]=sorteia;

							}else if(ft[i].predict_direita_pix() && ft[i].predict_direita(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;

									if(sorteia==3) sorteia=4;
									movendoF[i]=sorteia;

							}else if(ft[i].predict_esquerda_pix() && ft[i].predict_esquerda(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;

									movendoF[i]=sorteia;
							}

							if(movendoF[i]!=2){

									if(movendoF[i]==1){

											upF[i]=true;

									}else if(movendoF[i]==3){

											leftF[i]=true;

									}else if(movendoF[i]==4){

											rightF[i]=true;

									}
									downF[i]=false;
		                    }
					}else if(leftF[i]){ //VERIFICA UP DOWN
							if(ft[i].predict_baixo_pix() && ft[i].predict_baixo(marcas_mapa)&& ft[i].predict_acima_pix() && ft[i].predict_acima(marcas_mapa)){

		                    		sorteia=rand()%4;
		                    		sorteia++;

		                    		movendoF[i]=sorteia;

							}else if(ft[i].predict_acima_pix() && ft[i].predict_acima(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;

									if(sorteia==2) sorteia=4;
									movendoF[i]=sorteia;

							}else if(ft[i].predict_baixo_pix() && ft[i].predict_baixo(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;

									if(sorteia==1) sorteia=4;

									movendoF[i]=sorteia;
							}

							if(movendoF[i]!=3){

									if(movendoF[i]==1){

											upF[i]=true;

									}else if(movendoF[i]==2){

											downF[i]=true;

									}else if(movendoF[i]==4){

											rightF[i]=true;

									}
									leftF[i]=false;
		                    }
					}else if(rightF[i]){ //VERIFICA UP DOWN
							if(ft[i].predict_baixo_pix() && ft[i].predict_baixo(marcas_mapa)&& ft[i].predict_acima_pix() && ft[i].predict_acima(marcas_mapa)){

		                    		sorteia=rand()%4;
		                    		sorteia++;

		                    		movendoF[i]=sorteia;

							}else if(ft[i].predict_acima_pix() && ft[i].predict_acima(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;

									if(sorteia==2) sorteia=4;
									movendoF[i]=sorteia;

							}else if(ft[i].predict_baixo_pix() && ft[i].predict_baixo(marcas_mapa)){

									sorteia=rand()%3;
									sorteia++;

									if(sorteia==1) sorteia=4;

									movendoF[i]=sorteia;
							}

							if(movendoF[i]!=4){

									if(movendoF[i]==1){

											upF[i]=true;

									}else if(movendoF[i]==2){

											downF[i]=true;

									}else if(movendoF[i]==3){

											leftF[i]=true;

									}
									rightF[i]=false;
		                    }
					}
			}




			for(i=0;i<5;i++){ //define as posições na matriz 
					if(movendoF[i]==1){


							//0 down, 1 right, 2 left, 3 up
							if(ft[i].predict_acima(marcas_mapa) && ft[i].predict_acima_pix()){
									ft[i].setJogadorY(ft[i].getJogadorY()-2);
									kF[i]--;
									frame_f[i]=2;


							}
					}else if(movendoF[i]==2){

		                    //0 down, 1 right, 2 left, 3 up
							if(ft[i].predict_baixo(marcas_mapa) && ft[i].predict_baixo_pix()){
									ft[i].setJogadorY(ft[i].getJogadorY()+2);
									kF[i]++;
									frame_f[i]=3;


							}
					}else if(movendoF[i]==3){

		                    //0 down, 1 right, 2 left, 3 up
							if(ft[i].predict_esquerda(marcas_mapa) && ft[i].predict_esquerda_pix()){
									ft[i].setJogadorX(ft[i].getJogadorX()-2);
									lF[i]--;
									frame_f[i]=1;


							}
					}else if(movendoF[i]==4){

		                    //0 down, 1 right, 2 left, 3 up
							if(ft[i].predict_direita(marcas_mapa) && ft[i].predict_direita_pix()){
									ft[i].setJogadorX(ft[i].getJogadorX()+2);
									lF[i]++;
									frame_f[i]=0;

							}
					}



			}




		    for(i=0;i<5;i++){
		            if(kF[i]==20){

		                    kF[i]=0;
		                    ft[i].setJogadorpy(ft[i].getJogadorpy()+1);

		            }else if(kF[i]==-20){

		                    kF[i]=0;
		                    ft[i].setJogadorpy(ft[i].getJogadorpy()-1);
		            }
		            if(lF[i]==20){

		                    lF[i]=0;
		                    ft[i].setJogadorpx(ft[i].getJogadorpx()+1);

		            }else if(lF[i]==-20){

		                    lF[i]=0;
		                    ft[i].setJogadorpx(ft[i].getJogadorpx()-1);

		            }
		    }




			//************************************ COUT PARA TESTES **********************************************

			//cout << jg.getJogadorpx()<<" - "<<jg.getJogadorpy()<<" - "<< sprite_fundo << endl;
		    //Coloque variáveis que queira testar em caso de erro para ver se estão funcionando corretamente

		    re_desenha = true;


		    //************************************ REGISTRA AS TECLAS PRESSIONADAS NO LAÇO ****************************

		    if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
		            break;

		    }else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { //Tecla X Apertada
		            teclas[ev.keyboard.keycode] = true;

		    }else if(ev.type == ALLEGRO_EVENT_KEY_UP) { //Tecla X Liberada
		            teclas[ev.keyboard.keycode] = false;
		            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) termina = true;

		    }



		    //******************************* REDESENHA ************************************************************


		    if(re_desenha && al_is_event_queue_empty(event_queue)) { //Redesenha se a fila de eventos esta vazia
		            re_desenha = false;
		         //Limpa a tela e Redesenha
		            al_clear_to_color(al_map_rgb(0,0,0));
		            al_draw_bitmap(fundo,0,0,0);
		            al_draw_bitmap(statue,0*p.get_PILULA(),0*p.get_PILULA(),0);//na camada do topo desenho as estatuas e outros objetos que posso adc futuramente

		            for(i=0;i<18;i++){//desenha todos os elementos do mapa, i=Horizontal (eixo x), j=Vertical (eixo Y)
		                    for(j=0;j<18;j++){
		                            if(marcas_mapa[i][j]=='1')   al_draw_bitmap(parede,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se a matriz na posição i,j é =1 desenha bloco

		                            else if(marcas_mapa[i][j]=='3') al_draw_bitmap(phorizontal,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se =2 desenha paredes horizontais

		                            else if(marcas_mapa[i][j]=='4') al_draw_bitmap(pvertical,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se =3 desenha paredes verticais da direita

		                            else if(marcas_mapa[i][j]=='5') al_draw_bitmap(pvertical2,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se=4 desenha paredes verticais da esquerda

		                            else if(marcas_mapa[i][j]=='6') al_draw_bitmap(wood,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se =6 desenha os blocos que ficarão abaixo das estátuas

		                            else if(marcas_mapa[i][j]=='.') al_draw_bitmap_region(Pilula, 0, p.get_sprite()*p.get_PILULA(), p.get_PILULA(), p.get_PILULA(), i*p.get_PILULA(),j*p.get_PILULA(),0);//se = P desenha as pílulas
		                    }
		            }
		            al_draw_bitmap(statue,0*p.get_PILULA(),0*p.get_PILULA(),0);
		            al_draw_bitmap_region(fundo2,sprite_fundo*274,0,274,701,720,0,0);//Desenha muro externo e lago, e fundo azul para o menu de pontos.

		            al_draw_textf(pontos, al_map_rgb_f(255, 255, 255), 1000, 100, 0, "Score: %d", contador);
		            al_draw_text(nomes, al_map_rgb(255,255,255),1000,480,0,"Felipe Dias");
		            al_draw_text(nomes, al_map_rgb(255,255,255),1000,520,0,"Carlos Henrique");
		            al_draw_text(nomes, al_map_rgb(255,255,255),1000,560,0,"Alexandre Melo");


		            al_draw_bitmap_region(enemy1, 0, animacao_f[0]*ft[0].getJogadorAltura(), ft[0].getJogadorLargura(), ft[0].getJogadorAltura(), ft[0].getJogadorX(), ft[0].getJogadorY(), 0);
		            al_draw_bitmap_region(enemy1, 0, animacao_f[1]*ft[1].getJogadorAltura(), ft[1].getJogadorLargura(), ft[1].getJogadorAltura(), ft[1].getJogadorX(), ft[1].getJogadorY(), 0);
		            al_draw_bitmap_region(enemy3, 0, animacao_f[2]*ft[2].getJogadorAltura(), ft[2].getJogadorLargura(), ft[2].getJogadorAltura(), ft[2].getJogadorX(), ft[2].getJogadorY(), 0);
		            al_draw_bitmap_region(enemy2, 0, animacao_f[3]*ft[3].getJogadorAltura(), ft[3].getJogadorLargura(), ft[3].getJogadorAltura(), ft[3].getJogadorX(), ft[3].getJogadorY(), 0);
		            al_draw_bitmap_region(enemy4, 0, animacao_f[4]*ft[4].getJogadorAltura(), ft[4].getJogadorLargura(), ft[4].getJogadorAltura(), ft[4].getJogadorX(), ft[4].getJogadorY(), 0);
		            //al_draw_bitmap_region(enemy3, 0, animacao_f[5]*ft[5].getJogadorAltura(), ft[5].getJogadorLargura(), ft[5].getJogadorAltura(), ft[5].getJogadorX(), ft[5].getJogadorY(), 0);


		            al_draw_bitmap_region(magus, frame*jg.getJogadorLargura(), 0, jg.getJogadorLargura(), jg.getJogadorAltura(), jg.getJogadorX(), jg.getJogadorY(), 0);
		            al_flip_display();


		            //******************************************* FIM DE JOGO **********************************************
					if(contador == 148){//Sem pílulas no mapa

						al_stop_sample_instance(musica_de_fundo);
						break;


		            }
		    }
		}

    al_flip_display();
    int aux=contador;
    termina=false;
    k=l=360;
    al_clear_to_color(al_map_rgb(0,0,0));

    //************************************ ANIMAÇAO POS-JOGO ***************************************

    while(!termina){

        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);

        re_desenha=true;


        if(contador==148){
            al_stop_sample_instance(musica_de_fundo);//Para a musica de fundo
            al_play_sample_instance(fim);//Toca musica de vitória

            contador=0;
            animacao=0;
            ativo=2;


        }else if(contador>0){

            contador=0;
            animacao=1;
            ativo=3;

            al_stop_sample_instance(musica_de_fundo);//Para a musica de fundo
            al_play_sample_instance(fim2);//Toca musica de derrota


        }

        if(ev.type == ALLEGRO_EVENT_TIMER) {

            if(ciclos==6) {//Quando tempo == FPS equivale a 1 segundo, assim a cada x milisegundos ele muda a sprite
                al_set_timer_count(timer, 0);//Volta ao tempo 0
                     //0 1 2 3 2 1 0

                frame = jg.anima_jogador_vitoria(animacao);
                sprite_fundo=b.anima_fundo(sprite_fundo);
                p.anima_pilula();

                for(i=0;i<5;i++){
                    animacao_f[i]=ft[i].anima_jogador(ativo);
                }

                ciclos=0;

            }

            ciclos++;
        }


        if(ev.type == ALLEGRO_EVENT_KEY_DOWN) { //Tecla X Apertada
            teclas[ev.keyboard.keycode] = true;

        }else if(ev.type == ALLEGRO_EVENT_KEY_UP) { //Tecla X Liberada
            teclas[ev.keyboard.keycode] = false;
            if(ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) termina = true;

        }

        if(re_desenha && al_is_event_queue_empty(event_queue)) { //Redesenha se a fila de eventos esta vazia
                re_desenha = false;
             //Limpa a tela e Redesenha
                al_clear_to_color(al_map_rgb(0,0,0));

                al_draw_bitmap(fundo,0,0,0);
                al_draw_bitmap(statue,0*p.get_PILULA(),0*p.get_PILULA(),0);//na camada do topo desenho as estatuas e outros objetos que posso adc futuramente

                for(i=0;i<18;i++){//desenha todos os elementos do mapa, i=Horizontal (eixo x), j=Vertical (eixo Y)
                        for(j=0;j<18;j++){
                                if(marcas_mapa[i][j]=='1')   al_draw_bitmap(parede,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se a matriz na posição i,j é =1 desenha bloco

                                else if(marcas_mapa[i][j]=='3') al_draw_bitmap(phorizontal,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se =2 desenha paredes horizontais

                                else if(marcas_mapa[i][j]=='4') al_draw_bitmap(pvertical,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se =3 desenha paredes verticais da direita

                                else if(marcas_mapa[i][j]=='5') al_draw_bitmap(pvertical2,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se=4 desenha paredes verticais da esquerda

                                else if(marcas_mapa[i][j]=='6') al_draw_bitmap(wood,i*b.get_BLOCO(),j*b.get_BLOCO(),0);//se =6 desenha os blocos que ficarão abaixo das estátuas

                                else if(marcas_mapa[i][j]=='.') al_draw_bitmap_region(Pilula, 0, p.get_sprite()*p.get_PILULA(), p.get_PILULA(), p.get_PILULA(), i*p.get_PILULA(),j*p.get_PILULA(),0);//se = P desenha as pílulas
                        }
                }
                al_draw_bitmap(statue,0*p.get_PILULA(),0*p.get_PILULA(),0);
                al_draw_bitmap_region(fundo2,sprite_fundo*274,0,274,701,720,0,0);//Desenha muro externo e lago, e fundo azul para o menu de pontos.
                al_draw_textf(pontos, al_map_rgb_f(255,255,255), 1000, 100, 0, "Score: %d", aux);

                al_draw_text(pontos, al_map_rgb(255,255,255),1000,280,0,"GAME OVER!");


                al_draw_text(nomes, al_map_rgb(255,255,255),1000,480,0,"Felipe Dias");
                al_draw_text(nomes, al_map_rgb(255,255,255),1000,520,0,"Carlos Henrique");
                al_draw_text(nomes, al_map_rgb(255,255,255),1000,560,0,"Alexandre Melo");

                al_draw_bitmap_region(enemy1, 0, animacao_f[0]*ft[0].getJogadorAltura(), ft[0].getJogadorLargura(), ft[0].getJogadorAltura(), ft[0].getJogadorX(), ft[0].getJogadorY(), 0);
                al_draw_bitmap_region(enemy1, 0, animacao_f[1]*ft[1].getJogadorAltura(), ft[1].getJogadorLargura(), ft[1].getJogadorAltura(), ft[1].getJogadorX(), ft[1].getJogadorY(), 0);
                al_draw_bitmap_region(enemy3, 0, animacao_f[2]*ft[2].getJogadorAltura(), ft[2].getJogadorLargura(), ft[2].getJogadorAltura(), ft[2].getJogadorX(), ft[2].getJogadorY(), 0);
                al_draw_bitmap_region(enemy2, 0, animacao_f[3]*ft[3].getJogadorAltura(), ft[3].getJogadorLargura(), ft[3].getJogadorAltura(), ft[3].getJogadorX(), ft[3].getJogadorY(), 0);
                al_draw_bitmap_region(enemy4, 0, animacao_f[4]*ft[4].getJogadorAltura(), ft[4].getJogadorLargura(), ft[4].getJogadorAltura(), ft[4].getJogadorX(), ft[4].getJogadorY(), 0);
                //al_draw_bitmap_region(enemy3, 0, animacao_f[5]*ft[5].getJogadorAltura(), ft[5].getJogadorLargura(), ft[5].getJogadorAltura(), ft[5].getJogadorX(), ft[5].getJogadorY(), 0);


                al_draw_bitmap_region(magus_vitoria, 0, frame*jg.getJogadorAltura(), jg.getJogadorLargura(), jg.getJogadorAltura(), jg.getJogadorX(), jg.getJogadorY(), 0);

                al_flip_display();
        }




    }



    //FREE as variáveis abaixo
    //***ELEMENTOS DE TELA
    al_destroy_display(display);
    al_destroy_bitmap(fundo);
    al_destroy_bitmap(fundo2);
    al_destroy_bitmap(parede);
    al_destroy_bitmap(pvertical);
    al_destroy_bitmap(pvertical2);
    al_destroy_bitmap(phorizontal);
    al_destroy_bitmap(Pilula);
    al_destroy_bitmap(statue);

    //***JOGADOR & INIMIGOS
    al_destroy_bitmap(magus);
    al_destroy_bitmap(magus_vitoria);
    al_destroy_bitmap(enemy1);
    al_destroy_bitmap(enemy2);
    al_destroy_bitmap(enemy3);
    al_destroy_bitmap(enemy4);

    //***TIMER
    al_destroy_timer(timer);

    //***AUDIO
    al_destroy_sample(bgm);
    al_destroy_sample(fanfare);
    al_destroy_sample(lose);
    al_destroy_sample(slap);


    al_destroy_sample_instance(musica_de_fundo);
    al_destroy_sample_instance(fim);
    al_destroy_sample_instance(fim2);
    al_destroy_sample_instance(hit);

    //***FILA DE EVENTOS
    al_destroy_event_queue(event_queue);

    //***TEXTO
    al_destroy_font(pontos);
    al_destroy_font(nomes);

    return 0;


}
