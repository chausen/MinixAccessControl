#include <lib.h>
#include <unistd.h>

int get_tag(int pid) {
  message msg; // Pass parameters through message

  msg.m1_i1 = pid; // set first integer of message to pid

  return _syscall(PM_PROC_NR, GETTAG, &msg);
  
}
