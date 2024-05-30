#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

struct data {
  char name[64];
};

struct fp {
  int (*fp)();
};

void flag()
{
  system("/bin/cat flag.txt");
}

void noflag()
{
  printf("sorry, no flag for you\n");
}

int main(int argc, char **argv)
{
  struct data *d;
  struct fp *f;
  
  d = malloc(sizeof(struct data));
  f = malloc(sizeof(struct fp));
  f->fp = noflag;
  
  printf("data is at %p. Enter your access code:\n", d);
  
  gets(d->name);
  f->fp();
}

