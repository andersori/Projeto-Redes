#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


void* foo(void){
    char* mensagem = malloc(20 * sizeof(char));

    strcpy(mensagem ,"hello world");;

    pthread_exit((void*)mensagem);
}

int main(int argc, char** argv)
{
    pthread_t t1;

    char* b;

    pthread_create(&t1, NULL, foo, NULL );

    pthread_join(t1, (void**)&b);

    printf(b);

    return 1;
}
