#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>


void flag()
{
  system("/bin/cat flag.txt");
}

void validate_passwd(char* passwd) {
 size_t inputLen;
 char passwd_buf[11];

 inputLen = strlen(passwd);
 unsigned char inputLenByte = (unsigned char) inputLen;
 if((unsigned char)inputLen < 4||  8 < (unsigned char)inputLen) { 
  printf("Invalid Password\n"); 
  fflush(stdout);
  
 } else {
  printf("Valid Password\n"); 
  strcpy(passwd_buf,passwd);
  fflush(stdout);
 }
 return;
}

int main(int argc, char* argv[]) {
 printf("Please enter a valid Passcode:");
 char bigbuff[300];
 fgets(bigbuff, sizeof(bigbuff)-1, stdin);
 char* input = &bigbuff[0];
 validate_passwd(input);
 return 0;
}
