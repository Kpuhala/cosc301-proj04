#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

#define NTHREAD (256) // upper bound on the number of threads
#define PGSIZE (4096)
/*
 * This is where you'll need to implement the user-level functions
 */

void *thread_stacks[NTHREAD]; // array used to keep references to all stacks

void lock_init(lock_t *lock) {
	lock->locked = 0;
}

void lock_acquire(lock_t *lock) {
	while(xchg(&lock->locked, 1) != 0);
}

void lock_release(lock_t *lock) {
	xchg(&lock->locked, 0);
}

int thread_join(int pid) {
	int thread_id = join(pid);
    
	if (thread_id != -1) {
		free(thread_stacks[thread_id]);
	}
	return thread_id;
}

int thread_create(void (*thread_stacks_routine)(void *), void *arg) {
	void *stack = malloc(PGSIZE*2);

	if((uint)stack % PGSIZE) {
		stack = stack + (PGSIZE - (uint)stack % PGSIZE);
	}
	int pid = clone(thread_stacks_routine, arg, stack);
    // index array by pid so that it is possible to reference
    if (pid > 256) {
        printf(1, "Not enough space to start thread %d.", pid);
    }
    
	thread_stacks[pid] = stack; 
	
	return pid;
}
