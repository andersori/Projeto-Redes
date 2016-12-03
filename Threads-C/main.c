#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>

#include <windows.h>
#include <time.h>

#define MAX_VERIFICADOS 10000
int QTD_VERIFICADOS;

int             *BUFFER;
sem_t           SEMAFORO_s;
sem_t           SEMAFORO_vazio;
sem_t           SEMAFORO_cheio;
int indice;

int c = 0;

void is_primo(int num){
    int i;
    for(i=0 ; i < (num / 2 )+ 1; i++){
        if(num % 2 == 0)
            return;
    }

    printf("%d\n", num);
    c++;
}

void *produzir()
{
    int n;
    while(1){
        n = (rand() % 107) + 1;
        sem_wait(&SEMAFORO_vazio);
        sem_wait(&SEMAFORO_s);

        //[-] INICIO da região critica

        BUFFER[indice++] = n;

        //[-] FIM da região critica

        sem_post(&SEMAFORO_s);
        sem_post(&SEMAFORO_cheio);

        //printf("QTD_VERIFICADOS = %d\n", QTD_VERIFICADOS);
        //printf("[-]Produio %d\n", n);
        //Sleep(2000);
    }

    pthread_exit(NULL);
}

void *consumir()
{
    int n;
    while(1){
        sem_wait(&SEMAFORO_cheio);
        sem_wait(&SEMAFORO_s);

        //[-] INICIO da região critica

        n = BUFFER[--indice];

        QTD_VERIFICADOS++;
        is_primo(n);
        if(QTD_VERIFICADOS == MAX_VERIFICADOS){
            printf("Quantidade de primos produzidos = %d.", c);
            exit(0);
        }

        //[-] FIM da região critica

        sem_post(&SEMAFORO_s);
        sem_post(&SEMAFORO_vazio);

        //printf("QTD_VERIFICADOS = %d\n", QTD_VERIFICADOS);
        //printf("[-]C< %d\n", n);
        //Sleep(2000);
    }

    pthread_exit(NULL);
}

int main()
{
    indice = 0;
    QTD_VERIFICADOS = 0;
    srand(time(NULL));

    pthread_t *produtor, *consumidor;

    int qtd_memoria;
    int qtd_produtores;
    int qtd_consumidores;

    printf("Tamanho da memoria: ");
    scanf("%d", &qtd_memoria);
    printf("Quantidade de produtores: ");
    scanf("%d", &qtd_produtores);
    printf("Quantidade de consumidores: ");
    scanf("%d", &qtd_consumidores);

    BUFFER = (int*) calloc(qtd_memoria, sizeof(int));
    produtor = (pthread_t*) malloc(qtd_produtores * sizeof(pthread_t));
    consumidor = (pthread_t*) malloc(qtd_consumidores * sizeof(pthread_t));

    sem_init(&SEMAFORO_s, 0, 1);
    sem_init(&SEMAFORO_vazio, 0, qtd_memoria);
    sem_init(&SEMAFORO_cheio, 0, 0);

    int i;
    for(i = 0; i < qtd_produtores; i++){
        pthread_create(&produtor[i], NULL, produzir, NULL);
    }
    for(i = 0; i <qtd_consumidores; i++){
        pthread_create(&consumidor[i], NULL, consumir, NULL);
    }

    for(i = 0; i < qtd_produtores; i++){
        pthread_join(produtor[i], NULL);
    }
    for(i = 0; i <qtd_consumidores; i++){
        pthread_join(consumidor[i], NULL);
    }
    return 0;
}
