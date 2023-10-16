#include <syscall.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("test_print\n");
	printf("argc=%d argv=%p", argc, argv);
	return 0;
}
