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

#include "core.h"
#include "common_types.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

void prompt_loop()
{
    string_t *prompt = 0;
    string_t *path = get_envvar("PATH");
    string_t *cwd = 0;

    while (1) {
        cwd = get_cwd();
        str_print(cwd);
        str_free(&cwd);
        print_cchar(" > ");
        prompt = prompt_line(prompt);
        if (exec_command(prompt, path) == 200)
            break;
        str_free(&prompt);
    }
    str_free(&prompt);
    str_free(&path);
}

int main(int argc, char **argv, char **env)
{
    map_t *ref = 0;

    env_manager(SETENV, env, 0);
    ref = env_manager(GETENV, 0, 0);
    prompt_loop();
    map_free(&ref);
    return (0);
}
