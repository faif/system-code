#include <sys/ioctl.h>
#include <sys/types.h>

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main (void)
{
  int fd, status = 0;

  /* ioctl example (TODO: find a better one) */
  if (fd = open ("/dev/ttyS0", O_RDONLY) == -1)
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
  close(fd);


  return 0;
}
