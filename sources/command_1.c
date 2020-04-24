/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include "core.h"
#include "command_model.h"

bool_t cmd_is_piped(cmd_t const *cmd)
{
    if (cmd == NULL || str_cstr(cmd->op) == NULL)
        return (FALSE);
    if (str_cstr(cmd->op)[0] == '|')
        return (TRUE);
    return (FALSE);
}
