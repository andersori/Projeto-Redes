#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>

#define TRUE 1
#define FALSE 0

#define MAX_NUM_RETIRADOS 10000

int* MEMORIA_COMP;
int NUM_RETIRADOS = 0;
typedef short bool;

bool is_primo(int num){
    int i;
    for(i=0 ; i < (num / 2 )+ 1; i++){
        if(num % 2 == 0)
            return FALSE;
    }

    return TRUE;
}

int pos_livre(int tam_memoria){
    int i;
    for(i = 0; i < tam_memoria; i++){
        if(MEMORIA_COMP[i] == 0){
            return i;
        }
    }

    return -1;
}

int pos_ocupada(int tam_memoria){
    int i;
    for(i = 0; i < tam_memoria; i++){
        if(MEMORIA_COMP[i] != 0){
            return i;
        }
    }

    return -1;
}

void* produzir(void* num_memoria_void){
    int pos_de_memoria = (int) num_memoria_void;

    while(NUM_RETIRADOS <= MAX_NUM_RETIRADOS){
        int pos_memoria_livre = pos_livre(pos_de_memoria);

        if(pos_memoria_livre != -1){
            MEMORIA_COMP[pos_memoria_livre] = (rand() % 107) + 1;
        }

    }

    pthread_exit(NULL);
}

void* consumir(void* num_memoria_void){
    int pos_de_memoria = (int)num_memoria_void;

    while(NUM_RETIRADOS <= MAX_NUM_RETIRADOS){
        int pos_memoria_ocupada = pos_ocupada(pos_de_memoria);

        if(pos_memoria_ocupada != -1){
            int num_retirado = MEMORIA_COMP[pos_memoria_ocupada];
            MEMORIA_COMP[pos_memoria_ocupada] = 0;

            if((num_retirado % 2) == 1){
                printf("%d\n", num_retirado);
            }

            NUM_RETIRADOS++;
        }
    }

    pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
    srand(time(NULL));

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
    MEMORIA_COMP = (int) calloc(tam_memoria, sizeof(int));

    //Alocando memoria para os vetores de threads
    pthread_t* produtor     = (pthread_t) malloc(qtd_produtores * sizeof(pthread_t));
    pthread_t* consumidor   = (pthread_t) malloc(qtd_consumidores * sizeof(pthread_t));

    //Variavel para os "for"
    int i;

    //Criando as threads -> associando um função a uma thread
    for(i=0; i<qtd_produtores;i++){
        pthread_create(&produtor[i], NULL, produzir, (void*)tam_memoria);
    }
    for(i=0; i<qtd_consumidores;i++){
        pthread_create(&consumidor[i], NULL, consumir, (void*)tam_memoria);
    }


    //Executando as threads
    for(i=0; i<qtd_produtores;i++){
        pthread_join(produtor[i], NULL);
    }
    for(i=0; i<qtd_consumidores;i++){
        pthread_join(consumidor[i], NULL);
    }

    //teste

    system("pause");
    return 1;
}
