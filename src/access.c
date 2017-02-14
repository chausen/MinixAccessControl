/* This file handles the system calls relating to access control. Currently,
 * this includes getting and setting an integer called tag that is part
 * of an process' PM process table entry.
 */

// TODO: figure out which of these imports are really needed
#include "pm.h"
#include <minix/callnr.h>
#include <minix/endpoint.h>
#include <limits.h>
#include <minix/com.h>
#include <signal.h>
#include "mproc.h"
#include "param.h"

#define FAILURE -1

/*===========================================================================*
 *                              do_tag                                       *
 *===========================================================================*/
int do_tag() {
/* Handle GETTAG, SETTAG */
  int target_pid, newvalue, tag;
  int calling_proc_e, calling_proc_n; // endpoint, number 
  struct mproc *calling_proc, *target_proc;

  calling_proc_e = m_in.m_source;
  if (pm_isokendpt(calling_proc_e, &calling_proc_n) != OK) {
    panic("do_tag: got bad endpoint: %d", calling_proc_e);
  }
  calling_proc = &mproc[calling_proc_n];
  target_pid = m_in.m1_i1;
  target_proc = find_proc(target_pid);
    
  switch(call_nr) {
    case GETTAG:
      /* Return the value of the tag if calling process has the same pid
       * as passed through the message, or has root access.
       * Return -1 on failure.
       */
      if (target_proc == NULL) {
        // call fails if pid out of bounds or not in use
        tag = FAILURE;      
      } else if (calling_proc != target_proc && calling_proc->mp_effuid != 0) {
        // calling process isn't attempting to get it's own tag and it doesn't have root access
        tag = FAILURE;
      } else {
        tag = target_proc->tag;
      }   
      break;
    case SETTAG:
      /* Write a new value to tag if calling process has root access.
       * Return the value of the tag on success. 
       * Return -1 on failure.
       */
  
      newvalue = m_in.m1_i2;

      if (target_proc == NULL) {
        // call fails if pid out of bounds or not in use
        tag = FAILURE;      
      } else if (calling_proc->mp_effuid != 0) {
        // calling process doesn't have root access
        tag = FAILURE;
      } else if (newvalue < 0) {
        // tag cannot have a negative value
        tag = FAILURE;        
      } else {
        target_proc->tag = newvalue;
        tag = target_proc->tag;
      }   
      break;
    default:
      tag = FAILURE;
      break;
  }
  return tag;
}
