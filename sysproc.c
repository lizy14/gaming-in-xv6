#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_write_at(void)
{
  int x, y;
  int c;

  if (argint(0, &x) < 0 || argint(1, &y) < 0 || argint(2, &c) < 0) {
    return -1;
  }

  write_at(x, y, (char)c);
  return 0;
}

int
sys_clear_screen(void)
{
  clear_screen();
  return 0;
}

int
sys_set_console_parameters(void)
{
	int p;
	argint(0,&p);
	set_console_parameters(p);
	return 0;
}

int 
sys_clone(void)
{
  int function, arg, stack;
  if(argint(0, &function) < 0)
    return -1;
  if(argint(1, &arg) < 0)
    return -1;
  if(argint(2, &stack) < 0)
    return -1;
  return clone((void*)function, (void*)arg, (void*)stack);
}

int
sys_join(void)
{
  int stack;
  if(argint(0,&stack)<0)
    return -1;
  return join((void**)stack);
}

int
sys_set_cursor(void)
{
  int x, y;
  if (argint(0, &x) < 0 || argint(1, &y) < 0)
    return -1;
  set_cursor(x, y);
  return 0;
}
