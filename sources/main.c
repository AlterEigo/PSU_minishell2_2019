/*
** EPITECH PROJECT, 2019
** minishell1 main
** File description:
** Description
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "common_types.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

string_t *get_envvar(cchar_t var)
{
    char *env = 0;
    string_t *str = 0;

    env = getenv(var);
    if (env == 0)
        return (0);
    str = str_create(env);
    return (str);
}

string_t *prompt_line()
{
    size_t b_size = 256;
    char *buffer = 0;
    string_t *prompt = 0;

    buffer = malloc(sizeof(char) * b_size);
    if (buffer == 0)
        return (0);
    getline(&buffer, &b_size, stdin);
    if (buffer == 0)
        return (0);
    prompt = str_wcreate(buffer);
    return (prompt);
}

string_t *get_cwd()
{
    char *buffer = 0;
    size_t b_size = 512;
    string_t *cwd = 0;

    buffer = malloc(sizeof(char) * b_size);
    if (getcwd(buffer, b_size) == 0) {
        if (buffer != 0)
            free(buffer);
        return (0);
    }
    cwd = str_wcreate(buffer);
    return (cwd);
}

void print_cchar(cchar_t str)
{
    uint_t len;

    if (str == 0)
        return;
    for (len = 0; str[len] != 0; len++);
    if (len == 0)
        return;
    write(1, str, len);
}

uint_t exec_builtin_cd(string_t const *command)
{
    nfa_node_t *cd_pat = bi_cd_pattern();
    map_t *matched = 0;
    string_t *args = 0;

    if (command == 0)
        return (84);
    matched = match(str_cstr(command), cd_pat);
    if (matched == 0)
        return (84);
    print_cchar("Cd recognized\n");
    args = map_get(matched, 1);
    if (args != 0)
        str_print(args);
    return (0);
}

uint_t exec_builtin_exit(string_t const *command)
{
    nfa_node_t *exit_pat = bi_exit_pattern();
    map_t *matched = 0;

    if (command == 0)
        return (84);
    matched = match(str_cstr(command), exit_pat);
    if (matched == 0)
        return (84);
    print_cchar("Exit recognized\n");
    return (0);
}

uint_t exec_command(string_t const *command, string_t const *path)
{
    exec_builtin_cd(command);
    exec_builtin_exit(command);
    return (0);
}

void prompt_loop()
{
    string_t *prompt = 0;
    string_t *path = get_envvar("PATH");
    string_t *cwd = get_cwd();

    while (1) {
        str_print(cwd);
        write(1, " $> ", 5);
        prompt = prompt_line(prompt);
        exec_command(prompt, path);
        str_free(&prompt);
    }
}

int main(int argc, char **argv)
{
    prompt_loop();
    return (0);
}
