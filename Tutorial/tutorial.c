#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>

void flag()
{
  system("/bin/cat flag.txt");
}


void menu(char* pass) {
  printf("Welcome to the tutorial problem, please enter the passphrase\n");
  char *temp = "Tutorial ";
  char *input = NULL;
  ssize_t chars;
  unsigned long len = 0;
  chars = getline(&input, &len, stdin);
  if((input)[chars-1]=='\n')
    (input)[chars-1]='\0';
  char* almost = malloc(strlen(pass) +strlen(temp)+1);
  strcpy(almost,pass);
  strcat(almost,temp);

  if (strcmp(input, "Just Google It!") == 0) {
    printf("You don't have permission for this function.\n");
    return;
  }
  char* key = malloc(strlen(almost) +4);
  char* final = "It!";
  strcpy(key,almost);
  strcat(key,final);

  if (strcmp(input, key)==0) {
    flag();
  } else {
    printf("Sorry, incorrect passphrase.\n");
  }
}

int main(int argc, char **argv)
{
  char *det = "Just ";
  menu(det);
}


