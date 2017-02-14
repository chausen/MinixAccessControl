#include <lib.h>
#include <unistd.h>

int set_tag(int pid, int newvalue) {
  message msg; // Pass parameters through message

  msg.m1_i1 = pid; // set first integer of message to pid
  msg.m1_i2 = newvalue; // set second integer of message to newvalue

  return _syscall(PM_PROC_NR, SETTAG, &msg);
  
}
