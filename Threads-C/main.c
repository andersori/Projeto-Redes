#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

//Definindo o tipo boleano
typedef short bool;
#define TRUE 1
#define FALSE 0

//Maximo de numeros consumidos
#define MAX_NUM_CONSUMIDO 10000

//Parametros passado para as threads
typedef struct{
    short* sem;
    int tam_memoria;
}parametros;

//Memoria compartilhada
int* MEMORIA_COMP;

//Numero de elementos consumidos
int NUM_CONSUMIDO = 0;

//Função que verifica se um numero é primo
bool is_primo(int num){
    int i;
    for(i=0 ; i < (num / 2 )+ 1; i++){
        if(num % 2 == 0)
            return FALSE;
    }

    return TRUE;
}

//Função que busca por uma posição livre no array compartilhado entre as threads (RETORNA O INDICE VAZIO)
int pos_livre(int tam_memoria){
    int i;
    for(i = 0; i < tam_memoria; i++){
        if(MEMORIA_COMP[i] == 0){
            return i;
        }
    }

    return -1;
}

//Função que busca por uma posição ocupada no array compartilhado entre as threads (RETORNA UM INDICE OCUPADO PARA A CONSUMIDOR)
int pos_ocupada(int tam_memoria){
    int i;
    for(i = 0; i < tam_memoria; i++){
        if(MEMORIA_COMP[i] != 0){
            return i;
        }
    }

    return -1;
}

//Thread que produzirá os numeros para colocar no array
void* produzir(void* param_void){

    //Convertendo o parametro passado para o tipo correto
    parametros* p = (parametros*) param_void;

    //Enquanto o numero maximo de itens consumidos não for alcansado
    //Fique produzindo numeros aleatorios
    while(NUM_CONSUMIDO <= MAX_NUM_CONSUMIDO){

        //Buscando um indice da memoria conpartilhada que esteja livre
        int pos_memoria_livre = pos_livre(p->tam_memoria);//RECEBE UM INDICE VAZIO

        //Se uma posição foi encontrada e nenhuma outra thread estiver na região critica ele concegue entrar na regiao
        if(pos_memoria_livre != -1 && p->sem[pos_memoria_livre] == TRUE){
            //Região critica
            p->sem[pos_memoria_livre] = FALSE;//pos_memoria_livre RECEBE O INDICE VAZIO
            MEMORIA_COMP[pos_memoria_livre] = (rand() % 107) + 1;
            p->sem[pos_memoria_livre] = TRUE;
            //Fim da região critica
        }

    }

    pthread_exit(NULL);
}

void* consumir(void* param_void){
    parametros* p = (parametros*)param_void;

    while(NUM_CONSUMIDO <= MAX_NUM_CONSUMIDO){
        int pos_memoria_ocupada = pos_ocupada(p->tam_memoria);//RECEBE UM INDICE DO ARRAY PARA CONSUMIR

        if(pos_memoria_ocupada != -1 && p->sem[pos_memoria_ocupada] == TRUE){//VERIFICA SE TEM INDICE OCUPADO E SE NAO TEM NINGUEM NA REGIÃO CRITICA
            //Inicio região critica
            p->sem[pos_memoria_ocupada] = FALSE;//SETA FALSE PARA NENHUMA OUTRA THREAD ENTRAR NESTA REGIÃO

            int num_retirado = MEMORIA_COMP[pos_memoria_ocupada];//ARAMAZENA SOMENTE PARA VERIFICAR SE É PRIMO
            MEMORIA_COMP[pos_memoria_ocupada] = 0;//SETA COMO CONSUMIDO

            if(is_primo(num_retirado) == TRUE){
                printf("%d\n", num_retirado);
            }

            NUM_CONSUMIDO++;//INCRMENTA PARA PARAR A EXECUÇAO QUANDO CHEGAR A 10000
            p->sem[pos_memoria_ocupada] = TRUE;//SETA COMO TRUE PARA LIBERAR A REGIAO CRITICA PARA OUTRA THREAD
            //Fim da região critica
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));//INICIALIZANDO O METODO DE GERAR NUMEROS ALEATORIOS

    int tam_memoria;
    int qtd_produtores;
    int qtd_consumidores;

    printf("Tamanho do vetor: ");
    scanf("%d", &tam_memoria);

    printf("Quantidade de Threads Produtoras: ");
    scanf("%d", &qtd_produtores);

    printf("Quantidade de Threads Consumidoras: ");
    scanf("%d", &qtd_consumidores);

    //"calloc" aloca memoria para uma variavel e inicializa todas com zero
    MEMORIA_COMP = (int*) calloc(tam_memoria, sizeof(int));//ALOCANDO O ARRAY COMPARTILHADO (REGIAO CRITICA)

    //Alocando memoria para os vetores de threads
    pthread_t* produtor     = (pthread_t*) malloc(qtd_produtores * sizeof(pthread_t));
    pthread_t* consumidor   = (pthread_t*) malloc(qtd_consumidores * sizeof(pthread_t));

    //Variavel para os "for"
    int i;

    parametros p;

    p.tam_memoria = tam_memoria;//RECEBENDO O TAMANHO DO ARRAY DIGITADO PELO USUARIO
    p.sem = (short*) calloc(tam_memoria, sizeof(short));//ALOCANDO O ARRAY DE PERMISSAO DO ACESSO A REGIAO CRITICA (SHORT=boolean)

    for(i = 0; i < p.tam_memoria; i++){
        p.sem[i] = TRUE;//SETA TODO ARRAY COMO TRUE PARA DEIXA TODO MUNDO COM ACESSO PERMISIVEL
    }

    //Criando as threads -> associando um função a uma thread
    for(i=0; i<qtd_produtores;i++){//CRIANDO A QUANTIDADE DE THREAD QUE O USUARIO DIGITOU, A FUNCAO 'PRODUZIR'
        pthread_create(&produtor[i], NULL, produzir, (void*)&p);
    }
    for(i=0; i<qtd_consumidores;i++){//THREADS CONSUMIDORES
        pthread_create(&consumidor[i], NULL, consumir, (void*)&p);
    }

    //Executando as threads
    for(i=0; i<qtd_produtores;i++){
        pthread_join(produtor[i], NULL);
    }
    for(i=0; i<qtd_consumidores;i++){
        pthread_join(consumidor[i], NULL);
    }

    printf("\n\n\n\n\n\n\n\n\n\n");

    for(i = 0; i < tam_memoria; i++){
        printf("%d\n", MEMORIA_COMP[i]);
    }

    system("pause");
    return 1;
}
