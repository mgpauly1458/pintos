#include <syscall.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	printf("test_print\n");
	printf("argc=%d argv=%p", argc, argv);
	printf("*argv=%p\n",*argv);
	printf("char argv[0]=%s\n", argv[0]);
	return 0;
}
