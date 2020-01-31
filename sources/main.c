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

void prompt_loop()
{
    bool_t looped = TRUE;
    uint_t count = 0;
    string_t *prompt = 0;

    while (looped && count < 2) {
        write(1, "$> ", 4);
        prompt = prompt_line(prompt);
        print_cchar("You entered : ");
        str_print(prompt);
        str_free(&prompt);
        count += 1;
    }
}

int main(int argc, char **argv)
{
    prompt_loop();
    return (0);
}
