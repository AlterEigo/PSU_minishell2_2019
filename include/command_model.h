/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/

#ifndef COMMAND_MODEL_H_INCLUDED
#define COMMAND_MODEL_H_INCLUDED

#include "istl/string.h"

struct PipeModel {
    int in;
    int out;
} (pipe_t);

typedef struct CommandModel {
    string_t *name;
    list_t *args;
    string_t *op;
} (cmd_t);

bool_t cmd_is_piped(cmd_t const *);

#endif
