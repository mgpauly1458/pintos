#include <stdbool.h>
#include <stdint.h>
#include "userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "threads/interrupt.h"
#include "threads/thread.h"

static void syscall_handler (struct intr_frame *);


void
syscall_init (void) 
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

void *extract_arg(struct intr_frame *f, int offset) {
	return f->esp + offset;
}

static void
syscall_handler (struct intr_frame *f) 
{
  int syscall_number = *(int*)f->esp;

  switch(syscall_number) {
	case 9: sys_write(f); break;
	case 1: sys_exit(); break;
	default: ;
  }
  printf ("system call!\n");
 // thread_exit ();
}

void sys_write(struct intr_frame *f) {
	int fd = *(int*)extract_arg(f, 4);
	void *buf = *(void **)extract_arg(f, 8);
	unsigned length = *(unsigned *)extract_arg(f, 12);
	printf("sys_write\n");
	printf("fd=%d buf=%p length=%d\n", fd, buf, length);
	
	// print word in user memory
	for (int i = 0; i < length; i++) {
		printf("%c", (char)get_user(buf+i));
	}
	
	// add a new line, for some reason program skips over new line
	printf("\n");
}

void sys_exit() {
	printf("sys_exit called\n");
	thread_exit();
	NOT_REACHED();
}

/* Reads a byte at user virtual address UADDR.
UADDR must be below PHYS_BASE.
Returns the byte value if successful, -1 if a segfault
occurred. */
static int
get_user (const uint8_t *uaddr)
{
int result;
asm ("movl $1f, %0; movzbl %1, %0; 1:"
: "=&a" (result) : "m" (*uaddr));
return result;
}

/* Writes BYTE to user address UDST.
UDST must be below PHYS_BASE.
Returns true if successful, false if a segfault occurred. */
static bool
put_user (uint8_t *udst, uint8_t byte)
{
int error_code;
asm ("movl $1f, %0; movb %b2, %1; 1:"
: "=&a" (error_code), "=m" (*udst) : "q" (byte));
return error_code != -1;
}

