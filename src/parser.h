#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64
#define MAX_COMMANDS 10

typedef struct
{
    char *args[MAX_ARGS];

    int redirect_output;
    char *output_file;

} Command;

typedef struct
{
    Command commands[MAX_COMMANDS];

    int command_count;

    int background;

} ParsedCommand;

void parse_command(char *line, ParsedCommand *parsed);

#endif