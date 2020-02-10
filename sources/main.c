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

#include "core.h"
#include "common_types.h"
#include "env_map.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

void print_invite()
{
    string_t *cwd = get_envvar("PWD");

    str_print(cwd);
    str_free(&cwd);
    print_cchar(" > ");
}

void prompt_loop()
{
    string_t *prompt = 0;

    while (1) {
	print_invite();
        prompt = prompt_line(prompt);
        if (prompt == 0) {
            print_cchar("exit\n");
            break;
        }
        if (eval_prompt(prompt) == 200)
            break;
        str_free(&prompt);
    }
    str_free(&prompt);
}

void handle_sigint(int sig)
{
    write(1, "\n", 1);
    print_invite();
}

int main(int argc, char **argv, char **env)
{
    signal(SIGINT, handle_sigint);
    env_manager(SETENV, env);
    prompt_loop();
    env_manager(FREE, 0);
    return (0);
}
