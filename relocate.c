/*
  relocate.c Simulate memory relocation using fixed addresses
  sample execution: ./relocate asm.o 5
*/

#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
  const unsigned int MAX_CHARS = 10;
  const unsigned int MAX_REL = 8;
  const unsigned int MAX_LINE = 30;
  const char DELIM[] = " ";
  const int ERROR = -1;

  if (argc != 3)
    {
      fprintf (stderr, "Usage: %s [file] [address]\n", argv[0]);
      return ERROR;
    }

  /* input file */
  const size_t LEN = strnlen (argv[1], MAX_CHARS);
  char i_file[LEN + 2];
  i_file[LEN] = 0;
  strncpy (i_file, argv[1], LEN);

  FILE *fp = NULL;
  if (NULL == (fp = fopen(i_file, "r+")))
    {
      fprintf (stderr, "Invalid file: %s\n", i_file);
      return ERROR;
    }

  /* relocation value */
  const size_t RLEN = strnlen (argv[2], MAX_REL);
  char r_addr[RLEN + 2];
  r_addr[LEN] = 0;
  strncpy (r_addr, argv[2], RLEN);
  unsigned int i = 0;
  if (0 == (i = atoi (r_addr)))
    {
      fprintf (stderr, "Invalid argument: %s\n", r_addr);
      return ERROR;
    }

  /* read the contents */
  char line[MAX_LINE + 2];
  while (NULL != fgets (line, MAX_LINE, fp))
    {
      char *word = NULL;

      /* split a single line into strings  */
      word = strtok (line, DELIM);
      unsigned int j = 0;
      unsigned int first = 0;
      while (word != NULL)
	{
	  /* no need to do something */
	  if (0 == (j = atoi (word)))
	    {
	      printf ("%s", word);
	    }
	  /* should relocate */
	  else
	    {
	      printf ("%d ", (j+i));
	    }

	  /* pretty print */
	  if (0 == first)
	    {
	      putchar ('\t');
	      ++first;
	    }

	  /* always last call */
	  word = strtok (NULL, DELIM);
	}
    }

  fclose (fp);
  return 0;
}
