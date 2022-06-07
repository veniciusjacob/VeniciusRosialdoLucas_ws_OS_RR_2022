#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

pthread_mutex_t mutex;
sem_t semaphore;


int *calcFibo(void *arg){
    int n = *(int *)arg;
    int a = 0, b = 1, c, i;
 
    pthread_mutex_lock(&mutex);
    printf("hello from thread %d\n", *(int *)arg);

    for (i = 0; i < 30; i++){        
        c = a + b;
        a = b; 
        b = c;     
        printf("%d-",b);
    }
    pthread_mutex_unlock(&mutex);
    printf("\n");
    free(arg);
}

// fib(30) = 832.040;
// fib(31) = 1.346.269;
int main(){
    pthread_t tid[2];
        
    for(int j = 0; j < 2 ; j++){
        int *a = malloc(sizeof(int));
        *a = j;
        if(pthread_create(&tid[j], NULL, &calcFibo, a) != 0){
            perror("Failed to create thread");
        }
    }

    for(int j = 0; j < 2; j++){
        if(pthread_join(tid[j], NULL) != 0){
            perror("Failed to create thread");
        }
        
    }    
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
