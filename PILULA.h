#ifndef PILULA_H
#define PILULA_H
class PILULA{
    public:
        PILULA();
        PILULA(const int, const int, const int, const int, const int);
        PILULA(const PILULA &);

        void set_valores();
        int get_PILULA();
        int get_sprite();

        ~PILULA();

        void preenche_mapa(char[18][18]);
        void anima_pilula();
    private:
        int pilula;
        int limite;
        int sprite;
        int inicio;
        int frames;
};
#endif
