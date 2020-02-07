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

#include "core.h"
#include "common_types.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

string_t *prompt_line()
{
    size_t b_size = 256;
    char *buffer = 0;
    string_t *prompt = 0;

    buffer = malloc(sizeof(char) * b_size);
    if (buffer == 0)
        return (0);
    if (getline(&buffer, &b_size, stdin) == -1) {
        free(buffer);
        return (0);
    }
    prompt = str_wcreate(buffer);
    str_pick(&prompt, '\n');
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

void print_cerr(cchar_t cmd, cchar_t msg)
{
    string_t *scmd = 0;
    string_t *smsg = 0;

    if (cmd == 0)
        return;
    if (msg == 0)
        msg = strerror(errno);
    scmd = str_create(cmd);
    smsg = str_create(msg);
    write(2, str_cstr(scmd), str_len(scmd));
    write(2, " : ", 4);
    write(2, str_cstr(smsg), str_len(smsg));
    write(2, ".\n", 3);
    str_free(&scmd);
    str_free(&smsg);
}
