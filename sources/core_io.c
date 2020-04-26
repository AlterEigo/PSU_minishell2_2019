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

#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"
#include "core.h"

string_t *prompt_line(void)
{
    size_t b_size = 0;
    char *buffer = NULL;
    string_t *prompt = 0;

    if (getline(&buffer, &b_size, stdin) == -1) {
        free(buffer);
        return (0);
    }
    prompt = str_wcreate(buffer);
    str_pick(&prompt, '\n');
    if (str_len(prompt) == 0)
        str_free(&prompt);
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
    write(2, ": ", 3);
    write(2, str_cstr(smsg), str_len(smsg));
    write(2, ".\n", 3);
    str_free(&scmd);
    str_free(&smsg);
}
