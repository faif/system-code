/*
    syscalls.c Test the MINIX 3 (POSIX-compatible) system calls.
*/

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/ptrace.h>
#include <sys/ioctl.h>
#include <sys/file.h>

#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <errno.h>

int mknod (const char *, mode_t, dev_t);
int brk (void *);

static void
handler (int signum)
{
  printf ("\nsignal %d caught, %s\n", signum,
	  signum == SIGINT ? "exiting..." : "ignoring...");

  if (signum == SIGINT)
    {
      exit (0);
    }
}


/** 
 * Most system calls should be executed
 * individually (comment the rest). Comments
 * are folded using Emacs. Don't spend all
 * your time trying to cleanup manually...
 * 
 * @return 0 on success. Another value otherwise
 */
int
main (void)
{
  pid_t proc;
  int fd;
  const char dname[] = "tty007";
  const char fname[] = "file_1";
  const char fname2[] = "file_2";
  const char msg[] = "bravo!\n";
  const mode_t mode = S_IRUSR | S_IWUSR;
  int i;
  char *ptr;
  /* struct sigaction action; */
  struct stat file_stat;
  int status;

  /* -- process management -- */

  /* child process creation */
  /* if ((proc = fork ()) != 0) */
  /*   { */
  /*     int status; */

  /*     printf ("created child process %u in group %u\n", getpid (), getpgrp ()); */

  /*     /\* send a kill signal to the child process *\/ */
  /*     int s; */
  /*     if (s = kill (getpid (), SIGKILL) != 0) */
  /*            { */
  /*      perror ("getpid"); */
  /*            } */

  /*     /\* waiting for the child process to finish *\/ */
  /*     waitpid (proc, &status, 0); */
  /*     printf ("process %u ended\n", getpid ()); */
  /*   } */

  /* replace the image of a process */
  /* int out = 0; */
  /* char *const args[] = {"uname", "-a", NULL}; */
  /* char *const env[] = {NULL}; */
  /* execve ("/bin/uname", args, env); */
  /* perror ("execve"); /\* execve normally never returns *\/ */

  /* terminate execution */
  /* exit (3); */

  /* change the size of the data segment */
  /* ptr = (char *) malloc (1); */
  /* if (brk (ptr + 30) == -1) */
  /*   { */
  /*     perror ("brk"); */
  /*   } */

  /* -- signal handling -- */

  /* Set up the structure to specify the action. */
  /* action.sa_handler = handler; */
  /* sigemptyset (&action.sa_mask); */
  /* action.sa_flags = 0; */

  /* /\* disable the default signal actions *\/ */
  /* sigaction (SIGINT, &action, NULL); */
  /* sigaction (SIGHUP, &action, NULL); */
  /* sigaction (SIGTERM, &action, NULL); */
  /* sigaction (SIGQUIT, &action, NULL); */

  /* alarm a signal */
  /* alarm (3); */

  /* wait for signals */
  /* while (1) */
  /*   { */
  /*     /\* pause the process *\/ */
  /*     pause (); */
  /*   } */

  /* -- file management -- */

  /* create a file (thank you ken) */
  /* if (fd = creat (fname, 0664) != -1) */
  /*   { */
  /*     printf ("created file %s\n", fname); */
  /*   } */

  /* /\* create an i-node (typically superuser only) *\/ */
  /* if (fd = mknod (dname, 020744, 0x0407) != -1) */
  /*   { */
  /*     printf ("created device file %s\n", dname); */
  /*   } */
  /* else */
  /*   { */
  /*     perror ("mknod"); */
  /*   } */

  /* /\* open a file for read/write *\/ */
  /* if ((fd = open (fname, O_RDWR | O_CREAT, mode)) != -1) */
  /*   { */
  /*     printf ("opened file %s\n", fname); */

  /*     /\* seek to the end of file (to append) *\/ */
  /*     lseek(fd, 0L, SEEK_END); */

  /*     /\* write to the file *\/ */
  /*     if ((i = write (fd, msg, strlen (msg))) == -1) */
  /*    { */
  /*      perror ("write"); */
  /*      return 1; */
  /*    } */

  /*     /\* close the file *\/ */
  /*     close (fd); */

  /*     /\* get file status *\/ */
  /*     if (stat (fname, &file_stat) == -1) */
  /* 	{ */
  /* 	  perror ("stat"); */
  /* 	} */
  /*     printf ("Last file access: %s", ctime (&file_stat.st_atime)); */
  /*     printf("Mode: %lo (octal)\n", (unsigned long) file_stat.st_mode); */
  /*   } */

  /* ioctl example (TODO: find a better one) */
/*  if (fd = open ("/dev/ttyS0", O_RDONLY) == -1)
    {
      perror ("open");
    }
  if (ioctl(fd, TIOCMGET, &status) == -1)
    {
      printf("TIOCMGET failed: %s\n",
	     strerror(errno));
    }
  else {
    if (status & TIOCM_DTR)
      puts("TIOCM_DTR is not set");
    else
      puts("TIOCM_DTR is set");
  }
  close(fd);*/

  /* check accessibility of a file */
  if (access (fname, F_OK) == -1)    /* check that file exists */
    {
      perror("access");
    }
  if (access (fname, R_OK) == -1)    /* check that file can be read */
    {
      perror ("access");
    }
  else
    {
      printf ("File %s can be read\n", fname);
    }

  /* rename a file */
  if (rename (fname, fname2) == -1)
    {
      perror ("rename");
    }

  /* fcntl example */
  

  return 0;
}
