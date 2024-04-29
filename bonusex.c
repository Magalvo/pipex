#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "./includes/pipex.h"


#define DEFAULT_BUFFER_SIZE 4096

void	execute_command(int in_fd, int out_fd, char **command)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{ 
		if (in_fd != STDIN_FILENO)
		{
			dup2(in_fd, STDIN_FILENO);
			close(in_fd);
		}
		if (out_fd != STDOUT_FILENO)
		{
			dup2(out_fd, STDOUT_FILENO);
			close(out_fd);
		}
		perror("execvp");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	char	*infile;
	char	*outfile;
	int		in_fd;
	int		out_fd;
	int		command_index;
	char	**command;
	int		arg_index;

	if (argc < 4)
	{
		fprintf(stderr, "Usage: %s infile cmd1 cmd2 ... cmdn outfile\n",
				argv[0]);
		return (EXIT_FAILURE);
	}
	infile = argv[1];
	outfile = argv[argc - 1];
	in_fd = open(infile, O_RDONLY);
	if (in_fd == -1)
	{
		perror("open");
		return (EXIT_FAILURE);
	}
	out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (out_fd == -1)
	{
		perror("open");
		close(in_fd);
		return (EXIT_FAILURE);
	}
	// Execute commands sequentially
	command_index = 2;
	while (command_index < argc - 1)
	{
		command = malloc((argc - command_index) * sizeof(char *));
		if (command == NULL)
		{
			perror("malloc");
			return (EXIT_FAILURE);
		}
		arg_index = 0;
		while (command_index < argc - 1 && argv[command_index] != NULL)
		{
			command[arg_index++] = argv[command_index++];
		}
		command[arg_index] = NULL; // terminate with NULL
		// Execute command with appropriate input/output redirection
		execute_command(in_fd, out_fd, command);
		// Close input file descriptor for next command
		close(in_fd);
		in_fd = STDIN_FILENO; // use STDIN for subsequent commands
		free(command);
	}
	// Wait for the last command to finish
	wait(NULL);
	close(in_fd);
	close(out_fd);
	return (EXIT_SUCCESS);
}
