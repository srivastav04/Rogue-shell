#include <stdio.h>
#include <string.h>

#include "parser.h"
#include "executor.h"
#include "builtin.h"
#include "history.h"

int main()
{
    char line[256];

    ParsedCommand parsed;

    while (1)
    {
        reap_background_processes();
        printf("$ ");

        if (fgets(line, sizeof(line), stdin) == NULL)
            break;

        line[strcspn(line, "\n")] = '\0';

        if (strcmp(line, "exit") != 0 &&strcmp(line, "history") != 0){
            history_add(line);
        }        
        parse_command(line, &parsed);

        if (parsed.commands[0].args[0] == NULL)
            continue;

        if (is_builtin(parsed.commands[0].args[0]))
        {
            execute_builtin(parsed.commands[0].args);
            continue;
        }

        if (parsed.command_count > 1)
        {
            execute_pipeline(&parsed);
        }
        else
        {
            execute_command(&parsed.commands[0], parsed.background);
        }
    }

    return 0;
}