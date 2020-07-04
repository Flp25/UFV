#ifndef BLOCO_H
#define BLOCO_H

class BLOCO{
    public:
        BLOCO();
        BLOCO(const int, const int);
        BLOCO(const BLOCO &);
        void set_BLOCO();
        int get_BLOCO();
        ~BLOCO();
        void carrega_mapa(char[18][18]);
        int anima_fundo(int);
    private:
        int bloco;
        int i;
};
#endif
