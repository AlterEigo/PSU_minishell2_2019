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
#include <sys/stat.h>

#include "core.h"
#include "p_core_builtin.h"
#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"

void check_path(string_t const *cmd, string_t const *path, struct stat fs)
{
    if (path == NULL) {
        print_cerr(str_cstr(cmd), "Command not found");
        return;
    }
    if (S_ISREG(fs.st_mode)) {
        print_cerr(str_cstr(cmd), "Wrong architecture");
        return;
    }
    print_cerr(str_cstr(cmd), "Permission denied");
}

int exec_try(string_t const *cmd, list_t *args)
{
    char **cargs = (cmd == 0) ? 0 : to_cargs(cmd, args);
    char **envp = (cmd == 0) ? 0 : env_to_char();
    int res = 0;
    string_t *path = NULL;
    struct stat fs;

    if (cmd == 0)
        return (1);
    if (is_a_path(cmd))
        res = execve(str_cstr(cmd), cargs, envp);
    else {
        path = find_in_path(cmd, &fs);
        execve(str_cstr(path), cargs, envp);
        check_path(cmd, path, fs);
    }
    return (1);
}

int process_returned(int status)
{
    int res = status;

    switch (status) {
        case 11:
        case 139:
            res = 139;
            res = (WCOREDUMP(status)) ? 134 : res;
            break;
        case 8:
        case 136:
            res = 136;
            res = (WCOREDUMP(status)) ? 126 : res;
            break;
        default:
            break;
    }
    return (res);
}

int eval_extern(string_t const *cmd, list_t *args)
{
    pid_t ret_pid = fork();
    int status;

    if (ret_pid == -1) {
        return (84);
    } else if (ret_pid == 0) {
        status = exec_try(cmd, args);
        if (status != 0)
            _exit(status);
    } else {
        waitpid(ret_pid, &status, WCONTINUED | WUNTRACED);
        if (WIFEXITED(status))
            return (WEXITSTATUS(status));
        return (process_returned(status));
    }
    return (84);
}
