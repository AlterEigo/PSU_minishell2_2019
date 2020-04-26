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

#include "istl/utility.h"
#include "istl/common_types.h"
#include "istl/list.h"
#include "istl/string.h"
#include "istl/iterator.h"
#include "istl/hash_table.h"
#include "command_model.h"
#include "core.h"

static void print_fault_msg(int res)
{
    string_t *segfault = str_create("Segmentation fault");
    string_t *floating = str_create("Floating exception");
    string_t *dump = str_create(" (core dumped)");

    if (res == 139 || res == 134)
        str_errprint(segfault);
    if (res == 136 || res == 126)
        str_errprint(floating);
    if (res == 134 || res == 126)
        str_errprint(dump);
    str_free(&segfault);
    str_free(&floating);
    str_free(&dump);
    write(2, "\n", 1);
}
