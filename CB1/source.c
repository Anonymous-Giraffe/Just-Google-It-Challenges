#include <stdio.h>
#include <stdlib.h>

void flag() {
    printf("print the flag\n");
	system("/bin/cat flag.txt");
	exit(0);
}

void vuln() {
	char buf[48];
	puts("Enter the access code: ");
	gets(buf);
    puts("Access granted!");
}

int main() {
	setbuf(stdout, 0);
	setbuf(stdin, 0);
	setbuf(stderr, 0);
	vuln();
	return 0;
}
