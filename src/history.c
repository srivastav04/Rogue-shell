#include <stdio.h>
#include <string.h>

#include "history.h"

static char history[HISTORY_SIZE][256];

static int history_count = 0;

void history_add(const char *command)
{
    if (command == NULL || command[0] == '\0')
        return;

    // History is not full yet
    if (history_count < HISTORY_SIZE)
    {
        strcpy(history[history_count], command);

        history_count++;
    }
    else
    {
        // Move everything one position toward the beginning
        for (int i = 1; i < HISTORY_SIZE; i++)
        {
            strcpy(history[i - 1], history[i]);
        }

        // Add new command at the end
        strcpy(history[HISTORY_SIZE - 1], command);
    }
}

void history_print(void)
{
    for (int i = 0; i < history_count; i++)
    {
        printf("%d %s\n", i + 1, history[i]);
    }
}