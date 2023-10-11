#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

void syscall_init (void);
static int get_user(const uint8_t *);
static bool put_user(uint8_t *, uint8_t);
#endif /* userprog/syscall.h */
