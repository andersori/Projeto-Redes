#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>
#include <semaphore.h>

#include <windows.h>
#include <time.h>

#define MAX_VERIFICADOS 10000
int QTD_VERIFICADOS;

int             *BUFFER;            //Buffer compartilhado entreas threads
sem_t           SEMAFORO_s;         //Semafaro para controlar o acesso a região critica
sem_t           SEMAFORO_produzir;  //Semaforo que da a permição para uma thread produtora produzir
sem_t           SEMAFORO_consumir;  //Semaforo que da a permição para uma thread consumidora consumir
int indice;                         //Serve para ordenar a inserção e remoção de itens do buffer

int c = 0;  //Numeros primos encontrados

void is_primo(int num)
{
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
        n = (rand() % 107) + 1;         //Gerando numero aleatorio
        sem_wait(&SEMAFORO_produzir);   /*  Se o valor desse semaforo for 0 a thread fica esperando,
                                         *  se nao ela decrementa esse semaforo em uma unidade, isso significa que alguma thread
                                         *  vai produziu e vai colocar no buffer
                                         */

        sem_wait(&SEMAFORO_s);          //Se tiver alguma thread na região critica fique esperando,  se nao o valor de SEMAFORO_s vai para 0

        //[-] INICIO da região critica

        BUFFER[indice++] = n;           //Colocando o numero no buffer e incrementando o indice para a proxima thread colocar um novo numero na posição da frente

        //[-] FIM da região critica

        sem_post(&SEMAFORO_s);          //Liberando a região critica para outra thread, almentando o valor de SEMAFORO_s pra 1
        sem_post(&SEMAFORO_consumir);   //Aumentando o valor de semaforo_consumir para que as threads consumidoras possam consumir mais um item do buffer
    }

    pthread_exit(NULL);
}

void *consumir()
{
    int n;
    while(1){
        sem_wait(&SEMAFORO_consumir);   /*  Verificando se possui alguma coisa para consumir, se tiver em 0 essa thread deve esperar.
                                         *  Se o valor desse semaforo for maior que 0 ele deve ser decrementado, isso signica que
                                         *  um numero vai ser consumido
                                         */

        sem_wait(&SEMAFORO_s);          /*  Se tiver alguem na região critica fique esperando, se nao o valor desse semaforo
                                         *  sera decrementado, passando seu valor para 0.
                                         */

        //[-] INICIO da região critica

        n = BUFFER[--indice];           /*  Decrementando antes de retirar pois o valor do indice esta apontando(não no sentido de ponteiro da linguagem)
                                         *  para uma posição onde um produtor vai colocar algo, ou seja, uma posição vazia
                                         */

        QTD_VERIFICADOS++;
        is_primo(n);

        if(QTD_VERIFICADOS == MAX_VERIFICADOS){
            printf("Quantidade de primos produzidos = %d.", c);
            exit(0);
        }

        //[-] FIM da região critica

        sem_post(&SEMAFORO_s);          //Saindo da região critica, aumentando o valor desse semaforo pra 1
        sem_post(&SEMAFORO_produzir);   //Incrementando o valor desse semaforo pois os produtores podem produzir um item a mais do eles podiam
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

    sem_init(&SEMAFORO_s, 0, 1);                    //Semaforo iniciando com 1 para alguem conceguir entrar na regiao critica
    sem_init(&SEMAFORO_produzir, 0, qtd_memoria);   //Dando a permição para as threads produtoras produzir no maximo "qtd_memoria"
    sem_init(&SEMAFORO_consumir, 0, 0);             //As threads consumidoras nao podem cosumir ninguem de inicio
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
