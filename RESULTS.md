# Lab 2 results — sealed core

Name:  Tanay Desai
Student number:  76319540
Lab section:  L2 Thursday 2-4
Core:  — B
Machine:  Hp Victus
Cores: 12

## Tools and sources

Tools and sources: Used class notes on lecture 6 pacheco 4.7 and some other parts of textbook, previewed portions of prelab and learned more thru semaphores on google. Used Gemini AI and copilot to learn BEFORE lab not during.

> Mandatory, even if it says "none". **No AI in the lab, at all** — see the
> README. Missing declaration: zero until you supply one. False one: misconduct.

## S2 — the defect · 40 marks

Three or more runs of `./bar given`, including one thread:

```
```

**S2.1** Name the mechanism: which claim in `given.c`'s header is false, and
what is actually happening? State the barrier's invariant and say which half of
it this code does not keep.

In line 17 in given.c , not every threads is released due to POSIX rules. pthread_cond_signal() doesnt wake all waiting threads, only one at a time. Most of the statement seems correct but this part is vague

**S2.2** Prove it, in the form your `BRIEF.md` requires.

(1)It's correct at 2 threads because they both use the barrier but it resets the counter after last thread
(2) My prediction was 1 thread
(3) cpu usage is very low almost near 0, this means threads are stopped and requires waiters 

**S2.3** Minimality: what breaks if you do less, what it costs if you do more.

REPLACE THIS LINE

## S3 — the measurement · 30 marks

`./bar all <t> <rounds>` at 1, 2, 4 and 8 threads. Pasted, not retyped. If a
mode stops, `all` stops with it — run the modes one at a time and paste those.

```
```

| threads | given: correct? | given: time | given: cpu | fixed: time | fixed: cpu | alt: time | alt: cpu |
|---|---|---|---|---|---|---|---|
| 1 | yes| 0.0033 | 0.0035 | | | | |
| 2 |yes | 0.3501 | 0.2768 | | | | |
| 4 | no | 0.0137 | 0.0146 | | | | |
| 8 | no | 5.1204 | 0.0140 | | | | |

**S3.1** Reconcile with `PREDICTION.md`: quote what you predicted, say what
happened, account for the difference. If you were right, say what would have
made you wrong.

P1 -"Yes, as it shares the same virtual address."

i predicted it would be correct but not necessarily sure whether it was because of virtual address

P2- "It stops halfway"

i was relatively close but not accurate to the answer here as a deadlock happens

mode=given threads=8 rounds=2000 bad=-1 firstbad=-1 checksum=unknown correct=no deadlock=yes time=5.1204 cpu=0.0140
given: no progress after 5.1 s -- giving up.



**S3.2** Which would you ship on this machine, **and what measurement would
change your mind?**

Ship 1 thread as its fastest and most efficient, ship 8 if there was no deadlock occurence

## S4 — explain-back · 15 marks

> Two or three sentences, your own words: someone who has not seen this code
> asks *what was wrong with it, and what did fixing it cost?*

What was wrong with this code is that it was trying to run a process and expected the barrier to catch up with all the threads but instead the barrier wasnt initialized well so only 1 thread was caught.

## Anything you got stuck on

Prelab was confusing and so was understanding setup for this lab.
