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
#include "command_model.h"
#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"

void check_stat(string_t const *cmd, int stret, struct stat fs)
{
    if (stret == -1) {
        print_cerr(str_cstr(cmd), "Command not found");
        return;
    }
    if (S_ISREG(fs.st_mode)) {
        print_cerr(str_cstr(cmd), "Wrong architecture");
        return;
    }
    print_cerr(str_cstr(cmd), "Permission denied");
}

int exec_try(cmd_t const *cmd, list_t *args, cmd_t *texas_oil)
{
    int res = 0;
    string_t const *path = cmd->name;
    struct stat fs;

    if (cmd == 0)
        return (1);
    if (texas_oil != NULL) {
        dup2(texas_oil->output.out, 0);
        close(texas_oil->output.out);
    }
    if (cmd_is_piped(cmd)) {
        close(cmd->output.out);
        dup2(cmd->output.in, 1);
    }
    if (!is_a_path(cmd->name))
        path = find_in_path(cmd->name);
    res = stat(str_cstr(path), &fs);
    execve(str_cstr(path), to_cargs(cmd->name, args), env_to_char());
    check_stat(cmd->name, res, fs);
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

int eval_extern(cmd_t const *cmd, list_t *args, cmd_t *texas_oil)
{
    pid_t ret_pid = fork();
    int ret;

    if (ret_pid == -1)
        return (84);
    if (ret_pid == 0) {
        if (cmd_is_piped(cmd)) {
            dup2(cmd->output.in, 1);
            close(cmd->output.in);
        }
        ret = exec_try(cmd, args, texas_oil);
        if (ret != 0)
            _exit(ret);
    } else {
        if (cmd_is_piped(cmd))
            close(cmd->output.in);
        waitpid(ret_pid, &ret, WCONTINUED | WUNTRACED);
        return (WIFEXITED(ret) ? WEXITSTATUS(ret) : process_returned(ret));
    }
    return (84);
}
