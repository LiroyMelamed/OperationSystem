#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler5(int signum)
{
 printf("Invalid memory - signal5\n");
 fflush(stdout);
 printf("5 different signals were raised\n");
 exit(1);
}

void handler4(int signum)
{
 printf("Abort - signal4\n");
 signal(SIGSEGV, handler5); // Accesing an unvalid memory to raise signal
 int *unvalid;
 *unvalid = 0;
 fflush(stdout);
}

void handler3(int signum)
{
 printf("Floating-point exception - signal3\n");
 signal(SIGABRT, handler4); // abort() command to raise signal
 abort();
 fflush(stdout);
}

void handler2(int signum)
{
 printf("USER1 raised - signal2\n");
 signal(SIGFPE, handler3); // dividing by zero to raise signal
 int zero = 0;
 int num = 1;
 int err = num / zero;
 fflush(stdout);
}

void handler1(int signum)
{
 printf("Child stopped or terminated - signal1\n");
 signal(SIGUSR1, handler2); // raised by raise() command
 raise(SIGUSR1);
 fflush(stdout);
}

int main()
{
 int status;
 signal(SIGCHLD, handler1); // raised by terminating child
 if (!(fork()))
 {
  exit(1);
 }
 wait(&status);
 return 0;
}