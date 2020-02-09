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

uint_t exec_extern(string_t *cmd, list_t *args)
{
    pid_t ret_pid = fork();
    int status;

    if (ret_pid == -1) {
	print_cerr("fork", 0);
	return (84);
    } else if (ret_pid == 0) {
	
	exit(EXIT_SUCCESS);
    } else {
	do {
	    waitpid(ret_pid, &status, WCONTINUED | WUNTRACED);
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (0);
}
