/*
  demonstrate the TLB misses by parsing a large array
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (void)
{
  const unsigned long long size = 100000999LLU;
  long long *data;
  data = (long long *) calloc (size, sizeof (long long));

  if (NULL == data)
    {
      fprintf (stderr, "cannot allocate memory\n");
      return 1;
    }

  time_t start, stop;
  double diff = 0;

  time (&start);
  int i;
  for (i = 0; i != size; ++i)
    {
      data[i] = i * 4;
    }
  time (&stop);

  diff = difftime (stop, start);
  printf ("it took %.2lf seconds to parse the array\n", diff);

  free (data);

  return 0;
}
