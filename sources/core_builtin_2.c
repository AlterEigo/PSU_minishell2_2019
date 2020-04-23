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

bool_t is_abs_path(string_t const *cmd)
{
    if (cmd == 0 || str_len(cmd) < 2)
        return (FALSE);
    if (str_cstr(cmd)[0] == '/')
        return (TRUE);
    else
        return (FALSE);
}

bool_t is_a_path(string_t const *cmd)
{
    if (cmd == 0 || str_len(cmd) < 1)
        return (FALSE);
    if (str_count(cmd, '/') > 0)
        return (TRUE);
    else
        return (FALSE);
}

string_t *find_in_path(string_t const *file)
{
    string_t *path = (file == 0) ? 0 : get_envvar("PATH");
    list_t *dirs = (file == 0) ? 0 : str_split(path, ':');
    iterator_t it;
    string_t *cur = 0;

    if (file == 0)
        return (0);
    it = (dirs == 0) ? it : list_begin(dirs);
    for (; !list_final(dirs, it); it = it_next(it)) {
        cur = str_copy(list_data(it));
        concat_path(&cur, file);
        if (access(str_cstr(cur), F_OK) == 0)
            return (cur);
        str_free(&cur);
    }
    return (0);
}

int exec_system(string_t const *cmd, char **cargs, char **envp)
{
    string_t *path = 0;

    if (cmd == 0 || cargs == 0)
        return (-1);
    path = find_in_path(cmd);
    if (path != 0) {
        return (execve(str_cstr(path), cargs, envp));
    }
    print_cerr(str_cstr(cmd), 0);
    return (1);
}

char **to_cargs(string_t const *cmd, list_t *args)
{
    char **cargs = 0;
    iterator_t it;
    char **envp = (cmd == 0) ? 0 : env_to_char();

    if (cmd == 0)
        return (0);
    cargs = malloc(sizeof(char *) * (list_len(args) + 2));
    it = (args != 0) ? list_begin(args) : it;
    cargs[0] = str_to_cstr(cmd);
    for (uint_t i = 0; i < list_len(args); i++, it = it_next(it))
        cargs[i + 1] = str_to_cstr(list_data(it));
    cargs[list_len(args) + 1] = 0;
    return (cargs);
}
