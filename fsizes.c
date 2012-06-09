#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#define LEN(arr) (sizeof(arr)) / (sizeof(arr[0]))

enum {BINS = 5};
enum {TRUE, FALSE};

void print_hor_hist (const int, const int []);

int main (void)
{
  struct dirent *de;
  struct stat finfo;
  DIR *dp = opendir ("./");
  const unsigned long bin_size = 1024;
  int bins[BINS];
  int i;
  int bin_pos;

  for (i = 0; i != BINS; ++i)
    {
      bins[i] = 0;
    }

  if (NULL == dp)
    {
      perror ("opendir");
      return -1;
    }

  while ((de = readdir (dp)))
    {
      if (strcmp (".", de->d_name) != 0 && strcmp ("..", de->d_name) != 0)
	{
	  stat (de->d_name, &finfo);
	  bin_pos = ((long)finfo.st_size / bin_size);
	  /* printf ("%s: %ld bytes goes in bin %d\n", de->d_name, (long)finfo.st_size, (bin_pos > BINS - 1 ? BINS - 1 : bin_pos)); */
	  i = (bin_pos > BINS - 1 ? BINS - 1 : bin_pos);
	  ++bins[i];
	}
    }

  print_hor_hist (LEN (bins), bins);

  closedir (dp);

  return 0;
}

void print_hor_hist (const int size, const int arr[])
{
  int i, j;
  for (i = 0; i != size; ++i)
    {
      printf ("%4d: ", i);

      for (j = 0; j != arr[i]; ++j)
	{
	  putchar ('*');
	}

      putchar ('\n');
    }
}
