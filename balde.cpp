#include "balde.h"

using namespace std;

Balde::Balde(int M)
{
    this->tam = M;
    this->pos = 0;
    this->profundidade = 0;
    this->vet = new string[this->tam];
}

Balde::~Balde()
{
    delete [] vet;
}

bool Balde::Cheio()
{
    return ( this->pos == this->tam );
}

void Balde::Insere(string PseudoChave)
{
    this->vet[this->pos] = PseudoChave;
    this->pos++;
}

void Balde::print()
{
    for( int i=0; i < tam; i++ )
        cout << "|-" << (vet[i].empty() ? "VAZIO":vet[i]) << endl;
}