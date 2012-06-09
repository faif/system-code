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
 * @return The number of bytes written. -1 on 
 * error.
 */
int m_write (const int fd, const char *buf)
{
  const int error = -1;
  const char *m_ptr = buf;
  const int f_size = 
    (strlen (buf) * sizeof (char)); /* buffer size */

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
 * Read from a memory mapped file 
 * 
 * @param fd The file descriptor
 * @param buf The output buffer
 * 
 * @return The number of bytes read. -1 on
 * error
 */
int m_read (const int fd, char *buf)
{
  const int error = -1;
  const int f_size = 
    (strlen (buf) * sizeof (char) + 1); /* buffer size */

  char *m_ptr = buf;
  char *map_ptr;
  int read = 0;			/* bytes read */
  char *i;

  /* mmap the file */
  if ((map_ptr = mmap (0, f_size, PROT_READ, MAP_SHARED,
  		      fd, 0)) == MAP_FAILED)
    {
      perror ("mmap");
      return error;
    }
  
  /* read the file contents */
  i = map_ptr;
  while (++read && (*m_ptr++ = *i++)) ;

  /* free the mmapped memory */
  if (munmap (map_ptr, f_size) == -1)
    {
      perror ("munmap");
      return error;
    }

  return read;
}


int main (void)
{
  const char message[] = "file contents\n"; /* contents written */
  const char o_path[] = "file1";	    /* file name */
  const mode_t mode = S_IRUSR | S_IWUSR;    /* open mode */
  const char *m_ptr = message;

  char i_msg[strlen (message) + 1]; /* contents read */
  int fd;			    /* file descriptor */
  int i;

  /* open for writing an mmapped file */
  if ((fd = open (o_path, O_RDWR | O_CREAT, 
		  mode)) == -1)
    {
      perror ("open");
      goto error;
    }

  /* write the file using map */
  if ((i = m_write (fd, message)) == -1)
    {
      perror ("m_write");
      goto error;
    }

  printf ("mapped: %d bytes\n", i);

  close (fd);

  /* open for reading mmapped files */
  if ((fd = open (o_path, O_RDONLY)) == -1)
    {
      perror ("open");
      goto error;
    }

  /* read the file using mmap */
  if ((i = m_read (fd, i_msg)) == -1)
    {
      perror ("m_read");
      goto error;
    }

  printf ("read: %d bytes\n", i);
  printf ("%s", i_msg);

  close (fd);
  return 0;

 error:
  close (fd);
  return 1;
}
