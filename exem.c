/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:56:35 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/11 17:48:55 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
/* 
int	main(void)
{
	printf("PID before the execve is: %d\n", getpid());
	char *const args[] = { "ls", NULL};
	char *const envp[] = { NULL };

	execve("/usr/bin/ls", args, envp);

	perror("execve");

	printf("PID AFTER the execve %d\n", getpid());
	return 1;
} */

/* int main() {
    pid_t pid;    
    pid = fork();
 
   printf("Hello, I am the parent process! My PID is %d, and my child's PID is %d.\n", getpid(), pid);
   return 0;
} */


/* #include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void    callexecve()
{
 char *const args[] = { "ls", NULL };
 char *const envp[] = { NULL };
 
 execve("/usr/bin/ls", args, envp);
 perror("execve");
    exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

int main(void)
{
 pid_t pid;
 
 printf("Hi I am the main process. My PID is :%d\n", getpid());
 pid = fork();
 if (pid == -1)
  printf("Error while forking\n");
 else if (pid == 0)
 {
  printf("I am the child. But now a new parent. My PID is :%d --- My child's PID is %d\n", getpid(), pid);
  callexecve();
 }
 else if (pid > 1)
 {
  printf("I am the parent. My PID is :%d --- My child's PID is %d\n", getpid(), pid);
  waitpid(pid, NULL, 0); 
  printf("Got back the control?\n");
 }
} */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char **argv, char **envp)
{
 pid_t	pid;
 int	pfd[2];

 pipe(pfd);
 pid = fork();
 if (pid < 0) 
 {
  fprintf(stderr, "Fork2 failed.\n");
  return 1;
 }
else if (pid == 0)
 {
  close(pfd[0]); //close unused end (the reading end) of the pipe
  dup2(pfd[1], 1);
  close(pfd[1]); //close it immediately as it will no longer be used
  write(1, "this is a new message", 22);  
  exit(EXIT_SUCCESS);     
 }
 else 
 {
  close(pfd[1]); //close unused end (the writing end) of the pipe
  dup2(pfd[0], 0);
  close(pfd[0]); //close it immediately as it will no longer be used
  char  str[22];
  read(0, str, 22);
  printf("Parent received:%s\n", str);
  wait(NULL);
 }
 return EXIT_SUCCESS;
}