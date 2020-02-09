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
    nfa_node_t *pattern = bi_command_pattern();
    map_t *processed = 0;
    string_t *cmd = 0;

    processed = match(str_cstr(prompt), pattern);
    cmd = (string_t*)map_get(processed, 1);
    cmd = str_create(str_cstr(cmd));
    if (args != 0)
	(*args) = str_split(map_get(processed, 2), ' ');
    map_free(&processed);
    nfa_free(&pattern);
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
    else {
	if (eval_extern(command, args) == 84) {
	    res = 84;
	    print_cerr(str_cstr(command), "Command not found");
	}
    }
    list_free(&args);
    str_free(&command);
    return (res);
}
