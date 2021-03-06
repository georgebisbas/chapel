/*
 * test program for the task_group class (identical to
 * the one found in TBB) on top of 
 * MassiveThreads/Qthreads/NANOX/TBB
 */

#include <stdio.h>

#define DAG_RECORDER 2
#include <mtbb/task_group.h>

long bin(int n);

struct bin_ {
  long &x;
  int n;
  bin_(long &x_, int n_) : x(x_), n(n_) { }
  void operator() () {
    x = bin(n);
  }
};

long bin(int n) {
  if (n == 0) {
    return 1;
  } else {
    mtbb::task_group tg;
    long x, y;
    tg.run(bin_(x, n - 1));
    y = bin(n - 1);
    tg.wait();
    return x + y;
  }
}

int main(int argc, char ** argv) {
  int n = (argc > 1 ? atoi(argv[1]) : 5);
  dr_start(0);
  long x = bin(n);
  dr_stop();
  printf("bin(%d) = %ld\n", n, x);
  dr_dump();
  return 0;
}

