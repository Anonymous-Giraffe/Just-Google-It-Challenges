#include <stdio.h>

char flag[] = "redacted";

int main(int argc, char **argv) {
    printf("The flag is located at %p. Enter your access code now:", &flag);
    char buffer[64];
    fgets(buffer, sizeof(buffer)-1, stdin);
    
    printf("Sorry, access codes have not been implemented yet. You entered the following code:\n");
    printf(buffer);
    printf("\n");
}

