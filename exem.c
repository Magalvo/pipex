/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exem.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:56:35 by dde-maga          #+#    #+#             */
/*   Updated: 2024/04/22 17:07:40 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
/* 
int	main(void)
{
	printf("PID before the execve is: %d\n", getpid());
	char *const args[] = { "ls", NULL};
	char *const envp[] = { NULL };
	execve("/usr/bin/ls", args, envp);
	perror("execve");
	printf("PID AFTER the execve %d\n", getpid());
	return (1);
} */
/* int main() {
    pid_t pid;    
    pid = fork();
 
   printf("Hello, I am the parent process! My PID is %d, and my child's PID is
		%d.\n", getpid(), pid);
   return (0);
} */
/* #include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
void	callexecve(void)
{
 char *const args[] = { "ls", NULL };
 char *const envp[] = { NULL };
 
 execve("/usr/bin/ls", args, envp);
 perror("execve");
    exit(EXIT_FAILURE); // Make sure to exit the child process if execve fails 
}

int	main(void)
{
 pid_t pid;
 
 printf("Hi I am the main process. My PID is :%d\n", getpid());
 pid = fork();
 if (pid == -1)
  printf("Error while forking\n");
 else if (pid == 0)
 {
  printf("I am the child. But now a new parent. My PID is :%d --- My child's PID is
		%d\n", getpid(), pid);
  callexecve();
 }
 else if (pid > 1)
 {
  printf("I am the parent. My PID is :%d --- My child's PID is %d\n", getpid(),
		pid);
  waitpid(pid, NULL, 0); 
  printf("Got back the control?\n");
 }
} */

#include "./includes/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t pid1;
	pid_t pid2;
	int pfd[2];
  int infile;
  int outfile;
  char **paths;

	if (argc < 5)
		exit_error("num of args");
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		exit_error("err opening in file");
	outfile = open(argv[argc - 1], O_TRUNC | O_CREAT | O_RDWR | 0000644);
	if (outfile < 0)
		exit_error("err opening out file");
    
	pipe(pfd);
	pid1 = fork();
	if (pid1 < 0)
	{
		fprintf(stderr, "Fork2 failed.\n");
		return (1);
	}
  else if (pid1 == 0)
	{
		close(pfd[0]); //close unused end (the reading end) of the pipe
		dup2(pfd[1], 1);
		close(pfd[1]); //close it immediately as it will no longer be used
		write(1, "this is a new message", 22);
		exit(EXIT_SUCCESS);
	}
  pid2 = fork();
	if (pid2 < 0)
	{
		fprintf(stderr, "Fork2 failed.\n");
		return (1);
	}
	else if (pid2 == 0)
	{
		close(pfd[1]); //close unused end (the writing end) of the pipe
		dup2(pfd[0], 0);
		close(pfd[0]); //close it immediately as it will no longer be used
		char str[22];
		read(0, str, 22);
		printf("Parent received:%s\n", str);
	}
  
}