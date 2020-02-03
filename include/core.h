/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_CORE_H_INCLUDED
#define IS_CORE_H_INCLUDED

#include "common_types.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

typedef enum { GETENV, SETENV, GETCENV } env_option_t;

char *strerror(int code);

map_t *env_to_map(char **envp);
map_t *env_manager(env_option_t opt, char **environment, char ***penv);
string_t *get_envvar(cchar_t var);
uint_t set_envvar(cchar_t var, cchar_t value);
string_t *get_cwd();
string_t *prompt_line();
void print_cchar(cchar_t str);
void print_cerr(cchar_t cmd, cchar_t msg);
void concat_path(string_t **rpath, string_t *part);
int change_dir(cchar_t ndir);
int change_sdir(string_t const *ndir);
uint_t exec_builtin_cd(string_t const *command);
uint_t exec_builtin_exit(string_t const *command);
uint_t exec_builtin_env(string_t const *command);
uint_t exec_builtin_setenv(string_t const *command);
list_t *get_args_if_matched(string_t const *cmd, nfa_node_t *pat, bool_t *flag);
uint_t exec_command(string_t const *command, string_t const *path);
void print_env();

#endif
