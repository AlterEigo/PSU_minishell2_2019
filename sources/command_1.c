/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <unistd.h>
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

bool_t cmd_drain(cmd_t *cmd)
{
    bool_t res = FALSE;

    if (cmd == NULL)
        return (FALSE);
    res = pipe_open(&cmd->output);
    return (res);
}

bool_t pipe_open(pipe_t *p)
{
    if (p == NULL)
        return (FALSE);
    if (pipe(p->vals) == 0) {
        p->opened = TRUE;
        return (TRUE);
    }
    return (FALSE);
}

bool_t pipe_opened(pipe_t const *pipe)
{
    if (pipe == NULL)
        return (FALSE);
    return (pipe->opened);
}

void pipe_close(pipe_t *pipe)
{
    if (pipe == NULL || !pipe_opened(pipe))
        return;
    close(pipe->in);
    close(pipe->out);
}
