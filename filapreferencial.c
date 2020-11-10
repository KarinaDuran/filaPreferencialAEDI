/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   Turma 94 - Prof. Luciano Antonio Digiampietri                 **/
/**                                                                 **/
/**   EP2 - Fila Preferencial                                       **/
/**                                                                 **/
/**   Karina Duran Munhos                   11295911                **/
/**                                                                 **/
/*********************************************************************/

#include "filapreferencial.h"
#include <malloc.h>

PFILA criarFila()
{
    PFILA res = (PFILA) malloc(sizeof(FILAPREFERENCIAL));
    res->inicioPref = NULL;
    res->fimPref = NULL;
    res->inicioGeral = NULL;
    res->fimGeral = NULL;
    return res;
}

int tamanho(PFILA f)
{
    PONT atual = f->inicioGeral;
    int tam = 0;
    while (atual)
    {
        atual = atual->prox;
        tam++;
    }
    return tam;
}

int tamanhoFilaPreferencial(PFILA f)
{
    PONT atual = f->inicioPref;
    int tam = 0;
    while (atual)
    {
        atual = atual->prox;
        tam++;
    }
    return tam;
}

PONT buscarID(PFILA f, int id)
{
    PONT atual = f->inicioGeral;
    while (atual)
    {
        if (atual->id == id) return atual;
        atual = atual->prox;
    }
    return NULL;
}

void exibirLog(PFILA f)
{
    int numElementos = tamanho(f);
    printf("\nLog fila geral [elementos: %i] - Inicio:", numElementos);
    PONT atual = f->inicioGeral;
    while (atual)
    {
        printf(" [%i;%i]", atual->id, atual->ehPreferencial);
        atual = atual->prox;
    }
    printf("\n");
    numElementos = tamanhoFilaPreferencial(f);
    printf("\nLog fila preferencial [elementos: %i] - Inicio:", numElementos);
    atual = f->inicioPref;
    while (atual)
    {
        printf(" [%i;%i]", atual->id, atual->ehPreferencial);
        atual = atual->prox;
    }
    printf("\n\n");
}
/*Procura o anterior de um elemento em uma fila recebida por parâmetro.
Retorna false se: não existir elemento com o respectivo ID recebido por parâmetro ou
se não existir elemento anterior(primeiro da fila).
Para definir se procura-se na fila preferencial ou na geral, eh recebido um int por paramentro
(0 se for a geral, 1 se for a preferencial). Recebe por parametro o endereco de um ponteiro
para armazenar o elemento anterior ao elemento com o ID recebido por parametro.
*/
bool buscarAnt(PFILA f, int id, int fila, PONT *ant)
{
    bool resposta=false;
    PONT anterior, atual;
    if(f->inicioGeral ==NULL||buscarID(f,id)==NULL)
    {
        return resposta;
    }
    else
    {
        if(fila == 0)atual=f->inicioGeral;
        else atual=f->inicioPref;

        anterior=NULL;
        while(atual->id != id)
        {
            anterior=atual;
            atual=atual->prox;
        }
        *ant=anterior;
        if(anterior!=NULL)resposta = true;
        return resposta;
    }
}


/*Função para inserir pessoa na fila. Recebe uma fila, o ID da pessoa e o int que define se
eh preferencial ou nao (1 se sim, 0 se não). Cria-se 2 registros diferentes se ehpreferencial
for true: um para a fila preferencial, outro para a fila geral. Senão, só
para a fila geral. Acertam-se os ponteiros de fim da fila das respectivas filas e se for o
primeiro da fila, o ponteiro de inicio também, além do prox do elemento anterior.
*/
bool inserirPessoaNaFila(PFILA f, int id, bool ehPreferencial)
{
    bool resposta = false;
    if(id<0 || buscarID(f, id)!= NULL)
    {
        return resposta;
    }
    else
    {
        //Para a fila geral
        PONT novoGeral =(PONT)malloc(sizeof(ELEMENTO));
        novoGeral->id = id;
        novoGeral->ehPreferencial=ehPreferencial;
        novoGeral->prox=NULL;
        //verifica-se se e o primeiro elemento da filaGeral
        if(tamanho(f) == 0)f->inicioGeral=novoGeral;
        else f->fimGeral->prox = novoGeral;
        f->fimGeral = novoGeral;
        // se for tambem preferencial
        if(ehPreferencial == true)
        {
            PONT novoPreferencial = (PONT) malloc (sizeof(ELEMENTO));
            novoPreferencial->id = id;
            novoPreferencial->ehPreferencial=ehPreferencial;
            novoPreferencial->prox = NULL;

            if(tamanhoFilaPreferencial(f)==0)f->inicioPref=novoPreferencial;
            else f->fimPref->prox = novoPreferencial;

            f->fimPref = novoPreferencial;
        }
        resposta = true;
    }
    return resposta;
}

/*Funcao para desistir da fila. Recebe como parametro o id e a fila.
retorna false se nao exisitir nenhum elemento com o id recebido por parametro
verifica se e preferencial e se for chama a funcao auxiliar buscarAnt para
redirecionar os ponteiros dos elementos envolvidos com a exclusao.
*/
bool desistirDaFila(PFILA f, int id)
{
    bool resposta= false;
    PONT aux= buscarID(f, id);
    if(aux==NULL)
    {
        return resposta;
    }
    else
    {
//booleans auxiliares para a funcao
        bool x, m;
//Ponteiros para os elementos anteriores
        PONT antP, antG;
//Ponteiros auxiliares para a busca na funcao.
        PONT y, n;
        if(aux->ehPreferencial == true)
        {
            x=buscarAnt(f, id, 1, &antP);
            //se nao houver ant, eh o primeiro
            if(x==false)
            {
                y = f->inicioPref;
                f->inicioPref = y->prox;
            }
            else
            {
                y = antP->prox;
                antP->prox = y->prox;
            }
            if(y==f->fimPref)
            {
                f->fimPref = antP;
            }
            free(y);
        }
        m=buscarAnt(f, id, 0, &antG);
        if(m==false)
        {
            n=f->inicioGeral;
            f->inicioGeral = n->prox;
        }
        else
        {
            n=antG->prox;
            antG->prox = n->prox;
        }
        if(n==f->fimGeral)
        {
            f->fimGeral=antG;
        }
        free (n);
        return true;
    }
}
/*Funcao para atender a pessoa na primeira posicao da fila geral, contida
em f->inicioGeral. Se a pessoa for preferencial, exclui ela da fila preferencial
pois ja foi atendida. Salva o id no endereco para inteiro recebido por parametro e
chama a funcao desistirDaFila para acertar ponteiros e eliminar o elemento.

Retorna false somente se a fila geral estiver vazia.
*/

bool atenderPrimeiraDaFilaGeral(PFILA f, int* id)
{
    if(tamanho(f)==0)
    {
        return false;
    }
    else
    {
        *id = f->inicioGeral->id;
        bool x = desistirDaFila(f, f->inicioGeral->id);
    }
    return true;
}
/*Funcao para atender a pessoa na primeira posicao da fila preferencial, contido
em f->inicioPref. Caso a fila preferencial esteja vazia, atende-se o primeiro da
fila geral, por isso chama-se o metodo atenderFilaGeral. Salva o id do atendido
no endereco para inteiro recebido por parametro e chama a funcao desistirDaFila
para acertar os ponteiros e eliminar o elemento.

Retorna false somente se a fila geral estiver vazia.
*/
bool atenderPrimeiraDaFilaPreferencial(PFILA f, int* id)
{
    if(tamanho(f)==0)
    {
        return false;
    }
    else
    {
        int x;
        if(tamanhoFilaPreferencial(f)!=0)
        {
            x = f->inicioPref->id;
            bool y =desistirDaFila(f, x);
        }
        else
        {
            atenderPrimeiraDaFilaGeral(f, &x);
        }
        *id = x;
        return true;
    }
}



