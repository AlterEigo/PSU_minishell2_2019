/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/

#ifndef COMMAND_MODEL_H_INCLUDED
#define COMMAND_MODEL_H_INCLUDED

#include "istl/string.h"

typedef struct Command {
    string_t *name;
    list_t *args;
    string_t *op;
} (cmd_t);

#endif
