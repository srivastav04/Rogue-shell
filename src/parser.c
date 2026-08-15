#include <string.h>
#include "parser.h"

void parse_command(char *line, ParsedCommand *parsed)
{
    parsed->command_count = 1;
    parsed->background = 0;

    int cmdIndex = 0;
    int argIndex = 0;

    Command *current = &parsed->commands[0];

    current->redirect_output = 0;
    current->output_file = NULL;

    char *token = strtok(line, " ");

    while (token != NULL)
    {
        // Pipe
        if (strcmp(token, "|") == 0)
        {
            current->args[argIndex] = NULL;

            cmdIndex++;
            argIndex = 0;

            parsed->command_count++;

            current = &parsed->commands[cmdIndex];
            current->redirect_output = 0;
            current->output_file = NULL;
        }

        // Output Redirection
        else if (strcmp(token, ">") == 0)
        {
            current->redirect_output = 1;

            token = strtok(NULL, " ");

            if (token != NULL)
                current->output_file = token;
        }

        // Background
        else if (strcmp(token, "&") == 0)
        {
            parsed->background = 1;
        }

        else
        {
            current->args[argIndex++] = token;
        }

        token = strtok(NULL, " ");
    }

    current->args[argIndex] = NULL;
}