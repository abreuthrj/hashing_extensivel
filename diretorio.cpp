#include "diretorio.h"
#include <string>
#include <math.h>

/**
 * Inicia diretório, setando tamanho dos baldes
 * colocando tamanho máximo de diretório como potencia de 2^(Bits+1)
 * e criando o primeiro balde
 **/
Diretorio::Diretorio(int M, int Bits)
{
    this->tamBaldes = M;
    this->profundidade = 1;

    Balde* primeiro_balde = new Balde(M);

    // Associa os dois primeiros indices 0 e 1 ao balde 1
    baldes.push_back(primeiro_balde);
    baldes.push_back(primeiro_balde);

    this->numBaldes = 1;
    this->numChaves = 0;
}

/**
 * Desaloca baldes da memoria
 **/
Diretorio::~Diretorio()
{
    //for( int i=0; i < baldes.size(); i++ )
        //delete baldes[i];
}

void Diretorio::DivideBalde(string ibinDiretorio)
{
    // obtem indice decimal do balde no diretorio
    int iDiretorio = bintodec(ibinDiretorio);

    Balde* balde = baldes[iDiretorio];
    Balde* novoBalde = new Balde(tamBaldes);

    // ajusta a profundidade local
    int profundidadeLocal = balde->GetProfundidade();
    balde->SetProfundidade( profundidadeLocal+1 );
    novoBalde->SetProfundidade( profundidadeLocal+1 );

    // aponta para novo balde
    baldes[iDiretorio] = novoBalde;
    numBaldes++;

    // redistribui as pseudochaves
    for( int i=0; i < tamBaldes; i++ )
    {
        string valBalde = balde->Get(i);
        if( ibinDiretorio.compare( valBalde.substr(0, profundidade) ) == 0 )
        {
            novoBalde->Insere(valBalde);
            balde->Set(i,"");
        }
    }
}

void Diretorio::Insere(string pseudoChave)
{
    // pega o valor em decimal representado pelos ( N = profundidade ) bits a esquerda da pseudochave
    string ibinDiretorio = pseudoChave.substr( 0,this->profundidade );
    int iDiretorio = bintodec( ibinDiretorio );

    // Declara variavel auxiliar balde diretório
    Balde* balde = this->baldes[ iDiretorio ];

    // Caso o balde esteja vazio, insere a pseudo chave
    if( !balde->Cheio() ) 
    {
        balde->Insere( pseudoChave );
        numChaves++;
    }
    else
    {
        int profundidadeLocal = balde->GetProfundidade();

        if( profundidadeLocal == profundidade )
            this->Duplica();

        ibinDiretorio = pseudoChave.substr(0, profundidade);
        iDiretorio = bintodec( ibinDiretorio );

        balde = baldes[ iDiretorio ];
        profundidadeLocal = balde->GetProfundidade();

        DivideBalde(ibinDiretorio);

        // insere a pseudochave no novo balde ( iDiretorio agora apontando para novoBalde )
        // caso o novo balde esteja cheio, pois as pseudo chaves iniciavam
        // todas com os mesmos bits, realiza a função Insere novamente
        if( baldes[iDiretorio]->Cheio() )
        {
            Insere(pseudoChave);
        }
        else
        {
            baldes[iDiretorio]->Insere(pseudoChave);
            numChaves++;
        }
    }
}



/**
 * Aumenta a profundidade do diretorio em 1
 * redireciona todos seus indices para os baldes de 2 em 2
 * ex:
 * antes
 *  0 -> balde 0
 *  1 -> balde 1
 * depois:
 *  00 -> balde 0
 *  01 -> balde 0
 *  10 -> balde 1
 *  11 -> balde 1
 **/
void Diretorio::Duplica()
{
    // Duplica o diretorio apontando
    for( int i=0; i < pow(2,profundidade); i++ )
        baldes.push_back(nullptr);

    profundidade++;
    
    // reajusta ponteiros
    for( int i=pow(2,profundidade)-1; i >= 0; i-- )
        baldes[i] = baldes[i/2];
}

/**
 * Busca a pseudo-chave no balde indicado pelos
 * indice dos seus N primeiros bits no diretorio ( N = profundidade )
 **/
bool Diretorio::Busca(string subChave)
{
    int iDiretorio = bintodec( subChave.substr(0,this->profundidade) );

    Balde* balde = baldes[iDiretorio];
    for( int i=0; i < tamBaldes; i++ )
        if( balde->Get(i).compare( subChave ) == 0 )
            return true;

    return false;
}

/**
 * Função auxiliar que converte de binario para decimal
 **/
int Diretorio::bintodec(string bin)
{
    int val = 0;
    for( int i=0; i < bin.length(); i++ )
        val += pow( 2,bin.length()-1-i )*(bin[i]-'0');

    return val;
}

/**
 * Função auxiliar que converte de decimal para binario
 **/
string Diretorio::dectobin(int dec)
{
    int q = dec;
    string bin;

    q=dec;
    for( int i=0; q/2 > 0; i++,q/=2)
        bin.append( 1,('0'+(q%2)) );
    bin.append( 1,(char)('0'+(q%2)) );

    // PREENCHE COM ZERO A ESQUERDA DE ACORDO COM A PROFUNDIDADE
    while( bin.length() < profundidade ) bin.append(1,(char)'0');

    for( int i=0,k=bin.length()-1; i<=k; i++,k-- )
    {
        int aux = bin[i];
        bin[i] = bin[k];
        bin[k] = aux;
    }

    return bin;
}

/**
 * Funções auxiliar para printar o diretorio
 **/
void Diretorio::print()
{
    int iCount = pow(2,profundidade);
    for( int i=0; i < iCount; i++ )
    {
        cout << dectobin(i) << " - [" << i << "]" << endl;
        this->baldes[i]->print();
    }
}

void Diretorio::print_resultado()
{
    float fc = (float) numChaves/(numBaldes*tamBaldes);
    cout << "Profundidade do diretório: " << profundidade << endl;
    cout << "Tamanho do diretório: " << (int)pow(2,profundidade) << endl;
    cout << "Número de baldes: " << numBaldes << endl;
    cout << "Número de chaves: " << numChaves << endl;
    cout << "Fator de carga: " << fc << endl;
}