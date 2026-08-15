#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "builtin.h"
#include "history.h"

int is_builtin(char *command)
{
    if(command == NULL)
        return 0;

    return
        strcmp(command, "cd") == 0 ||
        strcmp(command, "help") == 0 ||
        strcmp(command, "exit") == 0 ||
        strcmp(command, "history") == 0;
}

void execute_builtin(char *args[]){

    if(strcmp(args[0], "cd") == 0){
        if(args[1] == NULL){
            printf("cd: missing operand\n");
            return;
        }else if (chdir(args[1]) == -1)
        {
            perror("No such directory");
            return;
        }
        
        return;
     
    }

    else if(strcmp(args[0], "help") == 0){
        printf("Built-in Commands\n");

        printf("cd\n");
        printf("help\n");
        printf("exit\n");

        return;
    }   
    else if(strcmp(args[0], "exit") == 0){
        exit(0);
    }
    else if (strcmp(args[0], "history") == 0){
        history_print();
        return;
    }
}
