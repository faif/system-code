/*  
    The producer-consumer problem using pthreads
    compile with: cc -lpthread
*/

#include <stdio.h>
#include <pthread.h>
#define MAX 10

pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;

void *producer (void *ptr)
{
  int i;

  for (i = 1; i <= MAX; ++i)
    {
      pthread_mutex_lock (&the_mutex); /* critical region access */
      while (buffer != 0)	       /* no need to produce, sleep */
	{
	  pthread_cond_wait (&condp, &the_mutex);
	}
      buffer = i;
      printf ("producing %d\n", buffer);
      pthread_cond_signal (&condc); /* wake up the consumer */
      pthread_mutex_unlock (&the_mutex);
    }
  puts ("end of producer");  
  pthread_exit (0);
}

void *consumer (void *ptr)
{
  int i;

  for (i = 1; i <= MAX; ++i)
    {
      pthread_mutex_lock (&the_mutex); /* critical region access */
      while (buffer == 0)	       /* nothing to consume, sleep... */
	{
	  pthread_cond_wait (&condc, &the_mutex);
	}
      buffer = 0;
      printf ("consuming %d\n", i);
      pthread_cond_signal (&condp); /* wake up the producer */
      pthread_mutex_unlock (&the_mutex);
    }
  puts ("end of consumer");
  pthread_exit (0);
}

int main (void)
{
  pthread_t pro, con;

  pthread_mutex_init (&the_mutex, 0);
  pthread_cond_init (&condc, 0);
  pthread_cond_init (&condp, 0);

  pthread_create (&con, 0, consumer, 0);
  pthread_create (&pro, 0, producer, 0);

  pthread_join (pro, 0);
  pthread_join (con, 0);

  pthread_cond_destroy (&condc);
  pthread_cond_destroy (&condp);
  pthread_mutex_destroy (&the_mutex); 

  return 0;
}
