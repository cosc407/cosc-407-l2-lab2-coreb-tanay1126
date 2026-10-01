/* Lab 2, core B -- YOUR MINIMAL CORRECTION.
 *
 * wait_() must work every time it is called, at 1, 2, 4 and 8 threads, and at
 * more threads than this machine has cores. It is already correct at two, and
 * that tells you nothing.
 *
 * Your fix here is very small. That is not a reason to write less in S2.3:
 * "minimal" has to be argued, and the argument is the invariant -- state it,
 * then show your version keeps it for every thread and not just for one.
 *
 * Copy anything you like out of given.c. Do not edit it.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "barrier.h"

/* TODO: the barrier's state. What has to be shared between the threads, and
 *       what does each thread have to remember for itself? */

static void *create(int nthreads)
{
    /* TODO: allocate it, initialise everything, and return it. Anything a
     *       thread might lock or wait on has to be ready BEFORE the first
     *       thread can reach it. */
     bar_t *b = malloc(sizeof(*b));
    b->nthreads = nthreads;
    b->count = 0;

    pthread_mutex_init(&b->m, NULL);
    pthread_cond_init(&b->c, NULL);

    return b;
    (void)nthreads;
    
}

static void wait_(void *p)
{
    /* TODO: the barrier. Write the invariant you are keeping in a comment
     *       above it, in one line, before you write the code -- your report
     *       and your oral both ask you to state it. */
     bar_t *b = p;

    pthread_mutex_lock(&b->m);

    b->count++;

    if (b->count == b->nthreads) {
        /* Last thread:*/
        b->count = 0;
        pthread_cond_broadcast(&b->c);
    } else {
        /* Not last: */
        while (b->count != 0)
            pthread_cond_wait(&b->c, &b->m);
    }

    pthread_mutex_unlock(&b->m);
}
    (void)p;


static void destroy(void *p)
{
    /* TODO: release what create() took. Every thread has been joined by the
     *       time this is called. */
     bar_t*b=p
     
    (void)p;
}

const bar_ops_t bar_fixed = { "fixed", create, wait_, destroy };
