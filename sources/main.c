/*
** EPITECH PROJECT, 2019
** minishell1 main
** File description:
** Description
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>

#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"
#include "core.h"
#include "env_map.h"

extern char **environ;

void print_invite(void)
{
    string_t *cwd = get_cwd();

    if (!isatty(0))
        return;
    str_print(cwd);
    str_free(&cwd);
    print_cchar("> ");
}

int prompt_loop(void)
{
    string_t *prompt = 0;
    int res = 0;

    do {
        res = 0;
        print_invite();
        prompt = prompt_line(prompt);
        if (prompt == 0) {
            if (isatty(0))
                print_cchar("exit\n");
            break;
        }
        res = eval_prompt(prompt);
        str_free(&prompt);
    } while (res != 200 && isatty(0));
    res = (res == 200) ? 0 : res;
    return (res);
}

void handle_sigint(int sig)
{
    write(1, "\n", 1);
    print_invite();
}

int main(int argc, char **argv)
{
    string_t *arg = 0;
    int res = 0;

    signal(SIGINT, handle_sigint);
    env_manager(SETENV, environ);
    if (argv[1] != 0) {
        arg = str_create(argv[1]);
        res = eval_prompt(arg);
        str_free(&arg);
    } else
        res = prompt_loop();
    env_manager(FREE, 0);
    return (res);
}

int crasher(int argc, char **argv)
{
    string_t *arg = NULL;
    string_t *floating = str_create("zero");
    string_t *seg = str_create("crash");
    int zero = 0;

    if (argc < 2)
        return (1);
    arg = str_create(argv[1]);
    if (str_cmp(arg, floating) == TRUE) {
        return (10 / zero);
    }
    if (str_cmp(arg, seg) == TRUE) {
        free(argv[3]);
    }
    return (0);
}
