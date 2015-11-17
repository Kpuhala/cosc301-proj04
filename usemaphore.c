#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

#define NTHREAD (64) // upper bound on the number of threads
#define PGSIZE (4096)

void semaphore_init(semaphore_t* s, int val) {
    s->locked = 0;
    s->val = val;
    //barrier();
}

void semaphore_down(semaphore_t* s) {
    while (1) {
        while (xchg(1, &s->lock) == 1); // spinlock
        if (s->val > 0) {
            s->val --;
            break;
        }
        xchng(0, &s->lock);
    }
}

void semaphore_up(semaphore_t* s) {
    while (xchg(1, &s->lock) == 1);
    s->val++;
    xchg(0, &s->lock);
}
