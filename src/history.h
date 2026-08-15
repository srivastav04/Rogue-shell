#ifndef HISTORY_H
#define HISTORY_H

#define HISTORY_SIZE 10

void history_add(const char *command);

void history_print(void);

#endif