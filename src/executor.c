#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>      
#include <string.h>  

#include "executor.h"
#include "parser.h"

void reap_background_processes()
{
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("[Background process %d finished]\n", pid);
    }
}


void setup_output_redirection(Command *cmd){
    int offset = open(cmd->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (offset == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(offset, STDOUT_FILENO) == -1){
        perror("dup2");
        close(offset);
        exit(EXIT_FAILURE);
    }
    close(offset);
}

void execute_pipeline(ParsedCommand *parsed)
{
    int pipes[MAX_COMMANDS-1][2];

    int n = parsed->command_count;

    // Create all pipes
    for(int i=0;i<n-1;i++)
    {
        if(pipe(pipes[i]) < 0)
        {
            perror("pipe");
            return;
        }
    }

    // Create one child per command
    for(int i=0;i<n;i++)
    {
        pid_t pid = fork();

        if(pid < 0)
        {
            perror("fork");
            return;
        }

        if(pid == 0)
        {
            // Not first command
            if(i > 0)
            {
                dup2(pipes[i-1][0],STDIN_FILENO);
            }

            // Not last command
            if(i < n-1)
            {
                dup2(pipes[i][1],STDOUT_FILENO);
            }

            // Close ALL pipe fds
            for(int j=0;j<n-1;j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }

            execvp(parsed->commands[i].args[0],
                   parsed->commands[i].args);

            perror(parsed->commands[i].args[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Parent closes all pipe fds
    for(int i=0;i<n-1;i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for every child
    for(int i=0;i<n;i++)
    {
        wait(NULL);
    }
}void execute_command(Command *cmd, int background)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        if (cmd->redirect_output)
            setup_output_redirection(cmd);

        execvp(cmd->args[0], cmd->args);

        perror(cmd->args[0]);
        exit(EXIT_FAILURE);
    }
    else
    {
        if (background)
        {
            printf("[Background process %d]\n", pid);
        }
        else
        {
            if (waitpid(pid, NULL, 0) == -1)
            {
                perror("waitpid");
            }
        }
    }
}