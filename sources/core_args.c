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

static builtin_ft h_to_b(hash_value_t hs, hash_value_t ha[], builtin_ft fa[])
{
    if (ha == 0 || fa == 0)
	return (0);
    for (int i = 0; ha[i] != 0; i++) {
	if (ha[i] == hs)
	    return (fa[i]);
    }
    return (0);
}

static hash_value_t *get_hash_array()
{
    static hash_value_t harray[6] = {0};
    static bool init = FALSE;

    if (!init) {
	harray[0] = hash_str("cd");
	harray[1] = hash_str("exit");
	harray[2] = hash_str("env");
	harray[3] = hash_str("setenv");
	harray[4] = hash_str("unsetenv");
	init = TRUE;
    }
    return (harray);
}

static builtin_ft *get_builtin_array()
{
    static builtin_ft farray[6] = {0};
    static bool init = FALSE;

    if (!init) {
	farray[0] = builtin_cd;
	farray[1] = builtin_exit;
	farray[2] = builtin_env;
	farray[3] = builtin_setenv;
	farray[4] = builtin_unsetenv;
	init = TRUE;
    }
    return (farray);
}

builtin_ft get_builtin(string_t const *command)
{
    hash_value_t chash;
    hash_value_t *harray = get_hash_array();
    builtin_ft *farray = get_builtin_array();

    if (command == 0)
	return (0);
    chash = hash_str(str_cstr(command));
    return (h_to_b(chash, harray, farray));
}

static string_t *interpret_cmd(string_t const *prompt, list_t **args)
{
    fnode_t const *pattern = REGEX_CMD;
    map_t *processed = map_create(5, MB_STR);
    string_t *cmd = 0;
    string_t *tmp = NULL;

    if (regex_extract(str_cstr(prompt), pattern, processed) != TRUE)
        return (NULL);
    cmd = (string_t*)map_get(processed, 1);
    cmd = str_create(str_cstr(cmd));
    if (args != 0) {
        tmp = str_copy(map_get(processed, 2));
        str_strip(&tmp);
        str_pick(&tmp, '\t');
	(*args) = str_split(tmp, ' ');
    }
    map_free(&processed);
    return (cmd);
}

uint_t eval_prompt(string_t const *prompt)
{
    string_t *command = 0;
    builtin_ft function = 0;
    list_t *args = 0;
    uint_t res = 0;

    if (prompt == 0)
	return (84);
    command = interpret_cmd(prompt, &args);
    function = get_builtin(command);
    if (function != 0)
	res = function(args);
    else
	if (eval_extern(command, args) == 84) {
	    res = 84;
	    print_cerr(str_cstr(command), 0);
	}
    list_free(&args);
    str_free(&command);
    return (res);
}
