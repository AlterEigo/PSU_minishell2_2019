/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>

#include "core.h"
#include "p_core_builtin.h"
#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"

int exec_try(string_t const *cmd, list_t *args)
{
    char **cargs = (cmd == 0) ? 0 : to_cargs(cmd, args);
    char **envp = (cmd == 0) ? 0 : env_to_char();

    if (cmd == 0)
        return (-1);
    if (is_a_path(cmd))
        execve(str_cstr(cmd), cargs, envp);
    else
        exec_system(cmd, cargs, envp);
    return (-1);
}

uint_t eval_extern(string_t const *cmd, list_t *args)
{
    pid_t ret_pid = fork();
    int status;

    if (ret_pid == -1) {
        return (84);
    } else if (ret_pid == 0) {
        if (exec_try(cmd, args) == -1)
            exit(EXIT_FAILURE);
    } else {
        waitpid(ret_pid, &status, WCONTINUED | WUNTRACED);
        if (WIFSIGNALED(status) || WIFEXITED(status) == 0)
            return (84);
    }
    return (0);
}
