#include <iostream>
#include <time.h>
#include <math.h>

using namespace std;

#include "diretorio.h"

void etapa01(Diretorio& diretorio, int N, int Bits);
void etapa02(Diretorio& diretorio, int N, int Bits);

int main(int argc, char** argv)
{
    int Bits,M;

    cout << "Digite o tamanho M para os baldes: ";
    cin >> M;
    cout << "Digite agora, o número de Bits para as pseudo-chaves: ";
    cin >> Bits;

    Diretorio diretorio01(M,Bits);
    Diretorio diretorio02(M,Bits);

    cout << "Gerando N aleatorio..." << endl;

    srand(time(NULL));
    int N = 30;

    cout << "N = " << N << endl;

    etapa01(diretorio01,N,Bits);
    etapa02(diretorio02,N,Bits);

    return 0;
}

void etapa01(Diretorio& diretorio, int N, int Bits) {
    // Realizando teste 01
    // N Pseudo-Chaves aleatórias

    cout << "Iniciando etapa 01..." << endl;
    cout << "Gerando " << N << " Pseudo-Chaves aleatórias..." << endl;

    int antiloop = 1;
    int antiloop_limit = 15;

    for( int i=0; i < N; i++ ) {
        string pseudo_chave = "";

        if( antiloop >= antiloop_limit )
        {
            cout << "Não foi possível gerar uma subchave diferente..." << endl;
            cout << "Saindo do loop..." << endl;
            break;
        }
            
        for( int j=0; j < Bits; j++ ) {
            pseudo_chave.append( 1,(char)('0'+rand()%2) );
        }
        
        if( diretorio.Busca(pseudo_chave) )
        {
            antiloop++;
            i--;
        }
        else
        {
            diretorio.Insere( pseudo_chave );
        }
    }

    cout << "========== RESULTADO ETAPA 01 ==========" << endl;

    diretorio.print_resultado();
    //diretorio.print();

    cout << "========================================" << endl;
}

void etapa02(Diretorio& diretorio, int N, int Bits) {
    // Realizando teste 02
    // N Pseudo-Chaves com nEqualBits iguais no inicio
    //system("cls");
    cout << "Iniciando etapa 02..." << endl;
    cout << "Gerando " << N << " Pseudo-Chaves com mesmo padrão inicial de bits..." << endl;

    // Numero de bits iguais = 1/3 do tamanho da sub-chave
    int nEqualBits = (int)floor( Bits/3 );
    string inicio_pseudo_chave;

    for( int i=0; i < nEqualBits; i++ )
        inicio_pseudo_chave.append( 1,(char)('0'+rand()%2) );

    int antiloop = 1;
    int antiloop_limit = 15;

    for( int i=0; i < N; i++ ) {
        string pseudo_chave = "";

        if( antiloop >= antiloop_limit )
        {
            cout << "Não foi possível gerar uma subchave diferente..." << endl;
            cout << "Saindo do loop..." << endl;
            break;
        }
            
        for( int j=0; j < Bits-nEqualBits; j++ ) {
            pseudo_chave.append( 1,(char)('0'+rand()%2) );
        }
        
        pseudo_chave = inicio_pseudo_chave+pseudo_chave;

        if( diretorio.Busca(pseudo_chave) )
        {
            antiloop++;
            i--;
        }
        else
        {
            diretorio.Insere( pseudo_chave );
        }
    }

    cout << "========== RESULTADO ETAPA 02 ==========" << endl;

    diretorio.print_resultado();
    //diretorio.print();

    cout << "========================================" << endl;
}