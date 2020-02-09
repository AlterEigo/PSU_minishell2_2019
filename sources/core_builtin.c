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
#include <signal.h>
#include <sys/wait.h>

#include "core.h"
#include "common_types.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

uint_t builtin_cd(list_t *args)
{
    int res = 0;
    string_t *arg = 0;
    string_t *var = 0;

    if (args == 0 || list_len(args) == 0) {
	var = get_envvar("HOME");
	res = change_sdir(var);
	str_free(&var);
    } else if (list_len(args) == 1) {
	arg = (string_t*)list_data(list_begin(args));
	res = change_sdir(arg);
    } else {
	print_cerr("cd", "Too many arguments");
	res = 84;
    }
    return (res);
}

uint_t builtin_exit(list_t *args)
{
    uint_t res = 0;

    if (args == 0 || list_len(args) == 0)
	res = 200;
    else {
	res = 84;
	print_cerr("exit", "Too many arguments");
    }
    return (res);
}

uint_t builtin_env(list_t *args)
{
    uint_t res = 0;

    if (args == 0 || list_len(args) == 0) {
	print_env();
    } else {
	res = 84;
	print_cerr("env", "Too many arguments");
    }
    return (res);
}

uint_t builtin_setenv(list_t *args)
{
    uint_t res = 0;
    string_t *key = 0;
    string_t *value = 0;

    if (args == 0 || list_len(args) == 0) {
	print_env();
    } else if (list_len(args) > 2) {
	res = 84;
	print_cerr("setenv", "Too many arguments");
    } else {
	key = (string_t*)list_data(list_begin(args));
	value = (string_t*)list_data(it_next(list_begin(args)));
	if (value == 0)
	    set_envvar(str_cstr(key), "");
	else
	    set_envvar(str_cstr(key), str_cstr(value));
    }
    return (res);
}

uint_t builtin_unsetenv(list_t *args)
{
    uint_t res = 0;
    string_t *key = 0;

    if (args == 0 || list_len(args) == 0) {
	print_env();
    } else if (list_len(args) > 1) {
	res = 84;
	print_cerr("unsetenv", "Too many arguments");
    } else {
	key = (string_t*)list_data(list_begin(args));
	unset_envvar(str_cstr(key));
    }
    return (res);
}

static bool_t is_abs_path(string_t const *cmd)
{
    if (cmd == 0 || str_len(cmd) < 2)
	return (FALSE);
    if (str_cstr(cmd)[0] == '/')
	return (TRUE);
    else
	return (FALSE);
}

static bool_t is_a_path(string_t const *cmd)
{
    if (cmd == 0 || str_len(cmd) < 1)
	return (FALSE);
    if (str_count(cmd, '/') > 0)
	return (TRUE);
    else
	return (FALSE);
}

static int exec_try(string_t const *cmd, list_t *args)
{
    char **cargs = 0;
    iterator_t it;

    if (cmd == 0)
	return (-1);
    cargs = malloc(sizeof(char*) * (list_len(args) + 2));
    it = (args != 0) ? list_begin(args) : it;
    cargs[0] = str_to_cstr(cmd);
    for (uint_t i = 0; i < list_len(args); i++, it = it_next(it)) {
	cargs[i + 1] = str_to_cstr(list_data(it));
    }
    cargs[list_len(args) + 2] = 0;
    if (is_a_path(cmd)) {
	execve(str_cstr(cmd), cargs, 0);
    }
    return (-1);
}

uint_t eval_extern(string_t const *cmd, list_t *args)
{
    pid_t ret_pid = fork();
    int status;

    if (ret_pid == -1) {
	print_cerr("fork", 0);
	return (84);
    } else if (ret_pid == 0) {
	if (exec_try(cmd, args) == -1)
	    exit(EXIT_FAILURE);
    } else {
	do {
	    waitpid(ret_pid, &status, WCONTINUED | WUNTRACED);
	    if (WIFSIGNALED(status)) {
		print_cerr("child process", "Segfault");
	    }
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (0);
}
