#include <system.h>

int _write(int fd, char *ptr, int len) {
  int i = 0;
  while ((i < len) && *ptr ) {
    stdio_putchar(*ptr);
    i++;
    ptr++;
  }
  return i;
}

int _read(int fd, char *ptr, int len) {
  int i;
  for (i = 0; i < len; i++) {
    ptr[i] = stdio_getchar();
    if (ptr[i] == -1) {
      break;
    }
    stdio_putchar(ptr[i]);
    if ((ptr[i] == '\r')) {
      stdio_putchar('\n');
      ptr[++i] = '\0';
      break;
    }
  }
  return i;
}

