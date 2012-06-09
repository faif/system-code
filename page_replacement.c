/*
  <one line to give the program's name and a brief idea of what it does.>
  Copyright (C) <year> Sakis Kasampalis <faif at dtek period gr>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

enum state
  {
    MISS,
    HIT
  };

enum boolean
  {
    TRUE,
    FALSE
  };

const unsigned int fr_num = 5;

enum boolean not_exists (const unsigned int n, unsigned int frames[])
{
  int i;
  enum boolean found = FALSE;
  for (i = 0; i != fr_num; ++i)
    {
      if (n == frames[i])
	{
	  found = TRUE;
	}
    }
  return found;
}

void insert_rnd (const unsigned int n, unsigned int frames[])
{
  const float p = 1 / (float)n;

  int i;
  for (i = 0; i != fr_num; ++i)
    {
      unsigned int ref = -1;
      do
	{
	  ref = rand () % n;     
	} while (TRUE == not_exists (ref, frames));
      assert (-1 != ref);
      frames[i] = ref;
    }  
}

void page_ref (const unsigned int n, unsigned int frames[])
{
  const float p = 1 / (float)n;
  const unsigned int ref = rand () % n;
  enum state s = MISS;
  
  int i;
  for (i = 0; i != fr_num; ++i)
    {
      if (ref == frames[i])
      	{
	  s = HIT;
	  break;
      	}
      else
	{
	  s = MISS;
	  frames[i] = ref;
	}
    }

  printf ("page %d\n", ref);
}

int main (void)
{
  srand (time (NULL));
  const int pages = 5;
  unsigned int frames[fr_num];
  insert_rnd (pages, frames);
  int i;
  for (i = 0; i != fr_num; ++i)
    {
      printf ("%d ", frames[i]);
    }
  putchar ('\n');
  /* page_ref (pages, frames); */
  return 0;
}
