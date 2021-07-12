#include <stdio.h>     /* printf(), fprintf */
#include <stdlib.h>    /* [s]rand() */
#include <unistd.h>    /* sleep() */
#include <pthread.h>   /* pthread_... */

#define PRODUCERS 10
#define CONSUMERS 10

int done = 0;
int count = 0;

static pthread_mutex_t mutex;
pthread_cond_t cond;

pthread_t consumer_tid[CONSUMERS], producer_tid[PRODUCERS];

void *
producer(void *param)
{
    long int id = (long int)param;

    pthread_mutex_lock(&mutex);

    count = count + 1; 
    printf("Producer: thread_id: %2d  count: %2d\n", id+1, count);

    if ( count == 10 ){ 
      pthread_cond_broadcast(&cond);
      done = 1;
    }

    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *
consumer(void *param)
{
    long int id = (long int)param;

    pthread_mutex_lock(&mutex);

    while ( done != 1 )
      pthread_cond_wait(&cond, &mutex);
    
    printf("Consumer: thread_id: %2d  count: %2d\n", id+11, count);
    count = count - 1;
    
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

int
main()
{
    long int i;

    /* Create the producer threads */
    for (i = 0; i < PRODUCERS; i++)
	if (pthread_create(&producer_tid[i], NULL, producer, (void *)i) != 0) {
	    perror("producer: pthread_create");
	    abort();
	}
    /* Create the consumer threads */
    for (i = 0; i < CONSUMERS; i++)
	if (pthread_create(&consumer_tid[i], NULL, consumer, (void *)i) != 0) {
	    perror("consumer: pthread_create");
	    abort();
	}
    
    /* Wait for them to complete */
        for (i = 0; i < PRODUCERS; i++)
	if (pthread_join(producer_tid[i], NULL) != 0) {
	    perror("producer: pthread_join");
	    abort();
	}

        for (i = 0; i < CONSUMERS; i++)
	if (pthread_join(consumer_tid[i], NULL) != 0) {
	    perror("consumer: pthread_join");
	    abort();
	}
        
    return 0;
}
