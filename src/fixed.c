/* MODEL ANSWER -- Lab 2 core B, instructor copy. Do not release until the
 * Lab 2 oral window has closed.
 *
 * The minimal correction is one word: signal -> broadcast.
 *
 * pthread_cond_signal wakes AT LEAST ONE waiter. The barrier needs all n-1 of
 * them woken, and it cannot rely on the next signal to pick up the stragglers,
 * because the generation they are waiting for is already in the past: their
 * predicate is true and nothing will ever wake them again to notice. That is a
 * lost wake-up, and it is a deadlock, not a slowdown.
 *
 * A full-marks S2.3 says what "minimal" could not be: a signal-based barrier
 * is not impossible, it just cannot be THIS barrier. It has to hand the
 * release on -- a relay, where each thread that wakes signals the next, or a
 * counting semaphore that is posted n-1 times. src/alt.c builds the second of
 * those, and the two are worth comparing on the clock.
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "barrier.h"

typedef struct {
    pthread_mutex_t lock;
    pthread_cond_t  cv;
    int             n;
    int             count;
    unsigned long   gen;
} bar_t;

static void *create(int nthreads)
{
    bar_t *b = malloc(sizeof *b);
    if (b == NULL) {
        return NULL;
    }
    if (pthread_mutex_init(&b->lock, NULL) != 0 ||
        pthread_cond_init(&b->cv, NULL) != 0) {
        fprintf(stderr, "barrier init failed\n");
        free(b);
        return NULL;
    }
    b->n     = nthreads;
    b->count = 0;
    b->gen   = 0;
    return b;
}

static void wait_(void *p)
{
    bar_t *b = (bar_t *)p;

    pthread_mutex_lock(&b->lock);

    unsigned long mine = b->gen;

    b->count++;
    if (b->count == b->n) {
        b->count = 0;
        b->gen++;
        pthread_cond_broadcast(&b->cv);        /* THE FIX */
    } else {
        while (b->gen == mine) {
            pthread_cond_wait(&b->cv, &b->lock);
        }
    }

    pthread_mutex_unlock(&b->lock);
}

static void destroy(void *p)
{
    bar_t *b = (bar_t *)p;
    pthread_mutex_destroy(&b->lock);
    pthread_cond_destroy(&b->cv);
    free(b);
}

const bar_ops_t bar_fixed = { "fixed", create, wait_, destroy };
