#include <iostream>
#include "balde.h"
#include <vector>

using namespace std;

class Diretorio
{
    private:
        vector<Balde*> baldes;
        int numBaldes;
        int tamBaldes;
        int profundidade;
        int numChaves;

        void DivideBalde(string ibinDiretorio);
        int bintodec(string bin);

    public:
        Diretorio(int M, int Bits);
        ~Diretorio();

        void Insere(string Chave);
        void Duplica();
        bool Busca(string Chave);
        string dectobin(int dec);

        void print();
        void print_resultado();
};