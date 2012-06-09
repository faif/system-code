/* 
   shell emulation (currently incomplete) 
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

#define TRUE 1
#define FALSE !TRUE
#define MAXLEN 100

int
main (void)
{
  char s[MAXLEN];

  while (TRUE)
    {
      printf ("%s ", "$");
      fgets (s, MAXLEN, stdin);
      /* printf ("%s", s); */

      pid_t proc;		/* process id */
      int *status;		/* waitpid status */

      if ((proc = fork ()) != 0)
	{
	  /* printf ("%s %u\n", "created process",  proc); */
	  waitpid (-1, status, 0);
	}
      else
	{
	  /* save the command and the arguments  */
	  /* TODO: use getopts for the arguments */
	  char cmd[MAXLEN];
	  if (sscanf (s, "%s", cmd) > 0)
	    {
	      /* printf ("%s\n", cmd);     */
	      char *const parm[] = { cmd, NULL };
	      execve (cmd, parm, 0);
	    }
	}
    }
  return 0;
}
