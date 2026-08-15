#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "parser.h"

void execute_command(Command *cmd, int background);
void execute_pipeline(ParsedCommand *parsed);
void reap_background_processes(void);


#endif