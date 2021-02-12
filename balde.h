#include <iostream>

using namespace std;

class Balde
{
    private:
        int tam;
        string* vet;
        int pos;
        int profundidade;

    public:
        Balde(int M);
        ~Balde();

        bool Cheio();
        void Insere(string PseudoChave);
        int GetProfundidade(){ return this->profundidade; }
        void SetProfundidade(int Profundidade){ this->profundidade = Profundidade; }

        string Get(int i){ return this->vet[i]; }
        void Set(int i, string val){ this->vet[i] = val; }

        void print();
};