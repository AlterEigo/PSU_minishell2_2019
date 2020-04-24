/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/

#ifndef COMMAND_MODEL_H_INCLUDED
#define COMMAND_MODEL_H_INCLUDED

#include "istl/string.h"

typedef struct PipeModel {
    bool_t opened;
    union {
        struct {
            int in;
            int out;
        };
        int vals[2];
    };
} (pipe_t);

typedef struct CommandModel {
    string_t *name;
    list_t *args;
    string_t *op;
    pipe_t std_out;
    pipe_t err_out;
} (cmd_t);

bool_t pipe_open(pipe_t *);
bool_t pipe_opened(pipe_t const *pipe);
void pipe_close(pipe_t *pipe);

bool_t cmd_is_piped(cmd_t const *);
bool_t cmd_drain(cmd_t *);

#endif
