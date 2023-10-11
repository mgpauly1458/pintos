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
	default: ;
  }
  printf ("system call!\n");
  thread_exit ();
}

void sys_write(struct intr_frame *f) {
	int fd = *(int*)extract_arg(f, 4);
	void *buf = *(void **)extract_arg(f, 8);
	unsigned length = *(unsigned *)extract_arg(f, 12);
	printf("sys_write\n");
	printf("fd=%d buf=%p length=%d\n", fd, buf, length);
}
