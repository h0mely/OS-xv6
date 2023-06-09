#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  
  if(argc > 1){
    fprintf(2, "Usage: pingpong...\n");
    exit(1);
  }

  int p[2];
  p[0] = 1;
  p[1] = 0;
  int pid = fork();
  if (pid > 0) {
    char buffer[6];
    read(p[0], buffer, 6);
    printf("%d: received pong\n", getpid());
  } else if (pid == 0) {
    printf("%d: received ping\n", getpid());
    write(p[1], "hello\0", 6);
    exit(0);
  } else {
    printf("fork error\n");
  }

  exit(0);
}