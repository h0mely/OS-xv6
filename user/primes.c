#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
prime(int pipe_read, int pipe_write) 
{
    char flag[36];
    read(pipe_read, flag, 36);
    int val = 0;
    for (int i = 0; i < 36; i++) {
        if (flag[i] == '1') {
            val = i;
        }
    }
    printf("prime %d\n", val);
    for (int num = val * val; num < 36; num += val) {
        flag[num] = '0';
    }
    int pid = fork();
    if (pid > 0) {
        write(pipe_write, flag, 36);
        wait(0);
    } else if (pid == 0) {
        prime(pipe_read, pipe_write);
        exit(0);
    }
}

int
main(int argc, char *argv[])
{
  
  if(argc > 1){
    fprintf(2, "Usage: primes...\n");
    exit(1);
  }

  char flag[36];
  for (int i = 0; i < 36; i++) {
    flag[36] = '1';
  }

  int p[2];
  p[0] = 0;
  p[1] = 1;

  int pid = fork();
  if (pid > 0) {
    flag[0] = '0';
    flag[1] = '0';
    write(p[1], flag, 36);
    wait(0);
  } else if (pid == 0) {
    prime(p[0], p[1]);
    exit(0);
  } else {
    printf("fork error\n");
  }

  exit(0);
}