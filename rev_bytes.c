/* Reverse the bytes of a file. */

#include <stdio.h>
#include <stdlib.h>
#define NELEMS(arr) (sizeof(arr)) / (sizeof(arr[0]))

size_t get_fsize (FILE *f)
{
  size_t n = 0, c;
  rewind (f);
  while (!feof (f))
    {
      c = getc (f);
      if (-1 != c)
	{
	  ++n;
	}
    }
  rewind (f);
  return n;
}

int main (void)
{
  FILE *startp;
  int c;
  int i;
  char *bytes;
  size_t fsize;

  startp = fopen ("filea", "r+");

  if (NULL == startp)
    {
      perror ("fopen");
      return -1;
    }
  
  fsize = get_fsize (startp);
  bytes = (char *) malloc (fsize);

  if (NULL == bytes)
    {
      perror ("malloc");
      return -1;
    }

  /* save the bytes in an array */
  i = 0;
  while (!feof (startp))
    {
      c = bytes[i] = getc (startp);
      if (-1 != c)
	{
	  ++i;
	  /* printf ("%o ", c); */
	}
    }

  /* write the reversed bytes in place */
  rewind (startp);
  for (i = NELEMS (bytes) - 1; i >= 0; --i)
    {
      fputc (bytes[i], startp);
    }

  free (bytes);
  fclose (startp);

  return 0;
}
