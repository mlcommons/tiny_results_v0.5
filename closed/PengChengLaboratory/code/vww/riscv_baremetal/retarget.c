#include <sys/stat.h>
#include <string.h>
#include <errno.h>


#if 0
/*-- GCC - Newlib runtime support --------------------------------------------*/

int open (const char * path, int flags, ...) 
{
  return (-1);
}

int close (int fd) 
{
  return (-1);
}

int lseek (int fd, int ptr, int dir) 
{
  return (0);
}

int __attribute__((weak)) fstat (int fd, struct stat * st) 
{
  memset (st, 0, sizeof (* st));
  st->st_mode = S_IFCHR;
  return (0);
}

int isatty (int fd) 
{
  return (1);
}

int read (int fd, char * ptr, int len) 
{
#if 0
  char c;
  int  i;

  for (i = 0; i < len; i++) 
  {
    c = SER_GetChar();
    if (c == 0x0D) break;
    *ptr++ = c;
    SER_PutChar(c);
  }
  return (len - i);
#else
	return 0;
#endif
}

int write (int fd, char * ptr, int len) 
{
#if 0
  int i;

  for (i = 0; i < len; i++) SER_PutChar (*ptr++);
  return (i);
#else
	return 0;
#endif
}

caddr_t sbrk (int incr) 
{

	errno = ENOMEM;
	return (caddr_t) -1;

}

void _exit(int num)
{

}

#endif
