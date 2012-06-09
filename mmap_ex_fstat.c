#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

/** 
 * Write to a memory mapped file
 * 
 * @param fd The file descriptor
 * @param buf The file contents
 * 
 * @return The number of bytes written. 
 * -1 on error
 */
int m_write (int fd, const char *buf)
{
  const int error = -1;
  const char *m_ptr = buf;
  const int f_size = 
    (strlen (buf) * sizeof (char)) + 1; /* buffer size */

  char *map_ptr;
  char *i;
  int written = 0;		/* bytes written */

  /* Stretch the file size to the size of the input file */
  /* When not applied `file' reports no magic and the size  */
  /* report of `du', `ls', etc. is wrong */
  if (lseek (fd, f_size - 1, SEEK_SET) == -1)
    {
      perror ("lseek");
      return error;
    }

  /* Something needs to be written at the end of the file to */
  /* have the file actually have the new size. If not done,
   a SIGBUS signal error is generated */
  if (write (fd, "", 1) != 1)
    {
      perror ("write");
      return error;
    }

  /* Now the file is ready to be mmapped. */
  if ((map_ptr = mmap (0, f_size, PROT_WRITE, MAP_SHARED,
  		      fd, 0)) == MAP_FAILED)
    {
      perror ("mmap");
      return error;
    }

  /* write the contents of the input file 
     to the mmapped file */
  i = map_ptr;
  while (++written && (*i++ = *m_ptr++)) ; 
  
  /* free the mmapped memory */
  if (munmap (map_ptr, f_size) == -1)
    {
      perror ("munmap");
      return error;
    }

  return written;
}




/** 
 * Get the size of a file using
 * fstat
 * 
 * @param fd The file descriptor
 * 
 * @return The size in bytes. -1
 * on error
 */
int get_fsize (int fd)
{
  const int error = -1;
  struct stat f_stat;

  if (fstat (fd, &f_stat) == -1)    
    {
      perror ("fstat");
      return error;
    }

  return f_stat.st_size;
}

int main (void)
{
  /* const char i_path[] = "/etc/motd"; */
  const char message[] = "the file contents\n";
  const char *m_ptr = message;
  const char o_path[] = "file1";
  const int mode = 0664;

  /* int i_fd; */
  int o_fd;
  int f_size;
  int i;

  /* if ((i_fd = open (i_path, O_RDONLY)) == -1) */
  /*   { */
  /*     perror ("open"); */
  /*     goto error; */
  /*   } */

  if ((o_fd = open (o_path, O_RDWR | O_CREAT, 
		  (mode_t)mode)) == -1)
    {
      perror ("open");
      goto error;
    }

  /* f_size = (strlen (message) * sizeof (char)) + 1; */

  /* if ((f_size = get_fsize (i_fd)) == -1) */
  /*   { */
  /*     perror ("fstat"); */
  /*     goto error; */
  /*   }  */

  /* printf ("size: \t%d bytes\n", f_size); */

  if ((i = m_write (o_fd, message)) == -1)
    {
      perror ("m_write");
      goto error;
    }

  printf ("mapped: \t%d bytes\n", i);

  /* close (i_fd); */
  close (o_fd);



  return 0;

 error:
  /* close (i_fd); */
  close (o_fd);
  return 1;
}
