/*  
    Example of using POSIX threads
    compile with: cc -lpthread
*/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define N_THREADS 5 

void *print_hello (void *id)
{
  printf ("hello thread %d\n", id); 
  pthread_exit (NULL);
}

int main (void)
{
  pthread_t threads[N_THREADS];

  int status, i;

  for (i = 0; i < N_THREADS; ++i)
    {
      printf ("creating thread %d\n", i);
      status = pthread_create (&threads[i], NULL, print_hello, (void *) i);

      if (status != 0)
	{
	  printf ("cannot create thread, error code %d\n", status);
	  exit (-1);
	}
    }
  return 0;
}
