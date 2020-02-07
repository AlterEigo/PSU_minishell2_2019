/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#ifndef IS_CORE_H_INCLUDED
#define IS_CORE_H_INCLUDED

#include "common_types.h"
#include "env_map.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

typedef enum { GETENV, SETENV, FREE } env_option_t;
typedef uint_t (*builtin_ft)(list_t *args);

char *strerror(int code);

env_map_t env_to_map(char **envp);
env_map_t *env_manager(env_option_t opt, char **environment);
string_t *get_envvar(cchar_t var);
uint_t set_envvar(cchar_t var, cchar_t value);
uint_t unset_envvar(cchar_t var);
void env_add_key(cchar_t key);
void env_rem_key(cchar_t key);
string_t *get_cwd();
string_t *prompt_line();
void print_cchar(cchar_t str);
void print_cerr(cchar_t cmd, cchar_t msg);
void concat_path(string_t **rpath, string_t *part);
int change_dir(cchar_t ndir);
int change_sdir(string_t const *ndir);
uint_t builtin_cd(list_t *args);
uint_t builtin_exit(list_t *args);
uint_t builtin_env(list_t *args);
uint_t builtin_setenv(list_t *args);
uint_t builtin_unsetenv(list_t *args);

uint_t eval_prompt(string_t const *prompt);
void print_env();

#endif
