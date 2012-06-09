/*
  aging.c Simulation of the aging algorithm found in paging systems
  sample execution: ./aging 4 rbits
*/

#include <stdio.h>
#include <string.h>
#define UINT_BIT	8

/* just for testing */
void uint_to_binary(unsigned int n, char s[UINT_BIT + 1])
{
	unsigned int mask;
	int i;

	mask = 0x01 << UINT_BIT - 1;
	i = 0;
	while (mask != 0 && i < UINT_BIT) {
		if (n & mask)
			s[i] = '1';
		else
			s[i] = '0';
		mask >>= 1;
		i++;
	}
	s[i] = '\0';

	return;
}


int main (int argc, char *argv[])
{
  const unsigned int MAX_CHARS = 10;
  const int ERROR = -1;
  const unsigned int MAX_FR = 8;
  const unsigned int MAX_LINE = 30;
  char binary[UINT_BIT + 1];

  if (argc != 3)
    {
      fprintf (stderr, "Usage: %s [frames] [file]\n", argv[0]);
      return ERROR;
    }

  /* number of page frames */
  const size_t FLEN = strnlen (argv[1], MAX_FR);
  char f_num[FLEN + 2];
  f_num[FLEN] = 0;
  strncpy (f_num, argv[1], FLEN);
  unsigned int frame_num = 0;
  if (0 == (frame_num = atoi (f_num)))
    {
      fprintf (stderr, "Invalid argument: %s\n", f_num);
      return ERROR;
    }

  /* 1 counter per frame */
  unsigned int counter[frame_num];
  int x;
  for (x = 0; x != frame_num; ++x)
    {
      counter[x] = 0;
    }
  
  /* input file */
  const size_t LEN = strnlen (argv[2], MAX_CHARS);
  char i_file[LEN + 2];
  i_file[LEN] = 0;
  strncpy (i_file, argv[2], LEN);

  FILE *fp = NULL;
  if (NULL == (fp = fopen(i_file, "r")))
    {
      fprintf (stderr, "Invalid file: %s\n", i_file);
      return ERROR;
    }

  /* read the contents */
  char line[MAX_LINE + 2];
  int cnt = 0;
  while (NULL != fgets (line, MAX_LINE, fp))
    {
      /* validate input */
      if ((strnlen (line, MAX_LINE) - 1) != frame_num)
	{
	  fprintf (stderr, "Invalid input: %s", line);	  
	  return ERROR;
	}
      /* parse the values of a clock tick */
      int j;
      for (j = 0; j != frame_num; ++j)
	{
	  /* shift the counter 1 bit right */
	  counter[j] >>= 0x1;	  

	  /* and put 1 if the R bit is 1 */
	  if ('1' == line[j])
	    {
	      counter[j] |= 0x1 << 7;	      
	    }
	}
    }

  /* print the final contents of the counters */
  int k;
  for (k = 0; k != frame_num; ++k)
    {
      uint_to_binary(counter[k], binary);
      printf("%s\n", binary);
    }

  fclose (fp);
  return 0;
}
