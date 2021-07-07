#include <iostream>
#include "pthread.h"
#include <string>
#include <unistd.h>
#include <sstream>

using namespace std;

string int_to_str(int x) {
   stringstream ss;
   ss << x;
   return ss.str();
}
 
#define NUM_THREADS 5
 
#define BLACK   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"
 
static pthread_mutex_t mutex;
 
void* PrintAsciiText(void *id)
{
    string colour;
 
    pthread_mutex_lock(&mutex);
    switch((long)id)
    {
    case 0:
        colour = RED;
        break;
    case 1:
        colour = GREEN;
        break;
    case 2:
        colour = YELLOW;
        break;
    case 3:
        colour = BLUE;
        break;
    case 4:
        colour = CYAN;
        break;
    default:
        colour = BLACK;
        break;
    }
 
   cout << colour << "I'm a new thread, I'm number " << (long)id << BLACK << endl;
   pthread_mutex_unlock(&mutex);

      char str[] = "pthread_yield() of thread() ";
      int sleeping = rand() % 20 + 1;

      string concat_str;
      concat_str = str + int_to_str((long)id);
      const char* myCharArr = concat_str.c_str();

      int err = pthread_yield();
      perror(myCharArr);

      cout << colour << "2nd message, sleeping for " << colour << sleeping << colour << " seconds. I'm thread number " << (long)id << BLACK << endl;
 
      sleep(sleeping);

      cout << colour << "3rd message, I'm thread number " << (long)id << BLACK << endl;

   pthread_exit(NULL);
}
 
int main()
{
    pthread_t threads[NUM_THREADS];
 
    for (long int i = 0 ; i < NUM_THREADS ; ++i)
    {
        int t = pthread_create(&threads[i], NULL, PrintAsciiText, (void*)i);
 
        if (t != 0)
        {
            cout << "Error in thread creation: " << t << endl;
        }
    }
 
    for(int i = 0 ; i < NUM_THREADS; ++i)
    {
        void* status;
        int t = pthread_join(threads[i], &status);
        if (t != 0)
        {
            cout << "Error in thread join: " << t << endl;
            }
    }
 
    return 0;
}
