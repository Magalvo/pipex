/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testingPipex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dde-maga <dde-maga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 18:57:03 by dde-maga          #+#    #+#             */
/*   Updated: 2024/05/02 18:53:05 by dde-maga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "./includes/pipex.h"

void execute_command(char **cmd_args, int in_fd, int out_fd, char **envp) {
    dup2(in_fd, 0);  // Redirect input
    if (out_fd != 1)  // Redirect output if not stdout
        dup2(out_fd, 1);
    
    execve(cmd_args[0], cmd_args, envp);
    perror("execve");
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv, char **envp) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <infile> <cmd1> <cmd2> ... <outfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    int num_cmds = argc - 3;
    int in_fd = open(argv[1], O_RDONLY);
    int out_fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
    
    if (in_fd == -1 || out_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    
    int prev_pipe[2];
    int curr_pipe[2];
    
    for (int i = 0; i < num_cmds; i++) {
        if (i < num_cmds - 1)
            pipe(curr_pipe);  // Create pipe for all commands except the last one
        
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            if (i > 0) 
            {
                close(prev_pipe[1]);  // Close previous pipe write end
                dup2(prev_pipe[0], 0);  // Read from previous pipe
                close(prev_pipe[0]);  // Close previous pipe read end
            }
            else
                dup2(in_fd, 0);  // First command reads from input file

                
            if (i < num_cmds - 1) 
            {
                close(curr_pipe[0]);  // Close current pipe read end
                dup2(curr_pipe[1], 1);  // Write to current pipe
                close(curr_pipe[1]);  // Close current pipe write end
            } 
            else
                dup2(out_fd, 1);  // Last command writes to output file
            

            
            // Execute the command
            execute_command(&argv[2 + i], in_fd, out_fd, envp);
        } else {
            if (i > 0) {
                close(prev_pipe[0]);  // Close previous pipe read end
                close(prev_pipe[1]);  // Close previous pipe write end
            }
            
            prev_pipe[0] = curr_pipe[0];
            prev_pipe[1] = curr_pipe[1];
        }
    }
    
    // Close file descriptors and wait for all children to finish
    close(in_fd);
    close(out_fd);
    
    for (int i = 0; i < num_cmds; i++) {
        wait(NULL);
    }
    
    return 0;
}
