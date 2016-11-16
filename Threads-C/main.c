#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//Vetor global, isso facilitará a manipulação desse vetor
unsigned int* memoria_comp;

unsigned int* pos_livre(void* argumento){
    int* tam_memoria = (int*) argumento;

    int i;
    for(i=0; i<*tam_memoria; i++){
        if(memoria_comp[*tam_memoria] == 0){
            return memoria_comp[*tam_memoria];
        }
    }

    return NULL;
}

void* produzir(unsigned int* num_memoria){

    pthread_exit(NULL);
}

void* consumir(){

}

int main(int argc, char* argv[])
{
    unsigned int tam_memoria;
    unsigned int qtd_produtores;
    unsigned int qtd_consumidores;

    printf("Tamanho do vetor: ");
    scanf("%d", &tam_memoria);

    printf("Quantidade de Threads Produtoras: ");
    scanf("%d", &qtd_produtores);

    printf("Quantidade de Threads Consumidoras: ");
    scanf("%d", &qtd_consumidores);

    //"calloc" aloca memoria para uma variavel e inicializa todas com zero
    memoria_comp = (unsigned int) calloc(tam_memoria, sizeof(unsigned int));


    pthread_t* produtor     = (pthread_t) malloc(qtd_produtores * sizeof(pthread_t));
    pthread_t* consumidor   = (pthread_t) malloc(qtd_produtores * sizeof(pthread_t));

    int i;
    for(i=0; i<qtd_produtores;i++){
        pthread_create(&produtor[i], NULL, produzir, (void*)&tam_memoria);
    }


    system("pause");
    return 1;
}
