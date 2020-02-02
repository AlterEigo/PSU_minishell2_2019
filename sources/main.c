/*
** EPITECH PROJECT, 2019
** minishell1 main
** File description:
** Description
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include "common_types.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

char *strerror(int code);

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
    str_pick(&prompt, '\n');
    return (prompt);
}

string_t *get_cwd()
{
    char *buffer = 0;
    size_t b_size = 512;
    string_t *cwd = 0;

    buffer = malloc(sizeof(char) * b_size);
    if (getcwd(buffer, b_size) == 0) {
        if (buffer != 0)
            free(buffer);
        return (0);
    }
    cwd = str_wcreate(buffer);
    return (cwd);
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
}

void concat_path(string_t **rpath, string_t *part)
{
    string_t *tmp = 0;
    string_t *path = *rpath;

    if (rpath == 0 || path == 0 || part == 0)
        return;
    tmp = str_addch(path, '/');
    str_free(&path);
    path = tmp;
    tmp = str_concat(path, part);
    str_free(&path);
    *rpath = tmp;
}

int change_dir(cchar_t ndir)
{
    string_t *dir = 0;
    string_t *path = 0;

    if (ndir == 0)
        return (84);
    path = get_cwd();
    dir = str_create(ndir);
    concat_path(&path, dir);
    if (chdir(str_cstr(path)) != 0)
        if (chdir(str_cstr(dir)) != 0) {
            print_cerr("cd", 0);
            str_free(&dir);
            str_free(&path);
            return (84);
        }
    str_free(&dir);
    str_free(&path);
    return (0);
}

uint_t exec_builtin_cd(string_t const *command)
{
    nfa_node_t *cd_pat = bi_cd_pattern();
    map_t *matched = 0;
    string_t *arg = 0;
    cchar_t ex = 0;
    list_t *arg_list = 0;
    int res = 0;

    if (command == 0)
        return (84);
    matched = match(str_cstr(command), cd_pat);
    arg_list = str_split(map_get(matched, 1), ' ');
    if (arg_list == 0)
        res = change_dir(getenv("HOME"));
    if (arg_list != 0 && list_len(arg_list) > 1) {
        print_cerr("cd", "Too many arguments");
        res = 84;
    }
    if (arg_list != 0 && list_len(arg_list) == 1) {
        arg = (string_t*)list_data(list_begin(arg_list));
        res = change_dir(str_cstr(arg));
    }
    map_free(&matched);
    list_free(&arg_list);
    nfa_free(&cd_pat);
    return (res);
}

uint_t exec_builtin_exit(string_t const *command)
{
    nfa_node_t *exit_pat = bi_exit_pattern();
    map_t *matched = 0;
    string_t *args = 0;

    if (command == 0)
        return (84);
    matched = match(str_cstr(command), exit_pat);
    if (matched == 0)
        return (84);
    args = map_get(matched, 1);
    if (args != 0) {
        print_cerr("exit", "Invalid Syntax");
        return (84);
    }
    return (0);
}

uint_t exec_command(string_t const *command, string_t const *path)
{
    exec_builtin_cd(command);
    //exec_builtin_exit(command);
    return (0);
}

void prompt_loop()
{
    string_t *prompt = 0;
    string_t *path = get_envvar("PATH");
    string_t *cwd = 0;
    uint_t count = 0;

    while (count < 2) {
        cwd = get_cwd();
        str_print(cwd);
        str_free(&cwd);
        print_cchar(" > ");
        prompt = prompt_line(prompt);
        exec_command(prompt, path);
        str_free(&prompt);
        count += 1;
    }
    str_free(&path);
}

int main(int argc, char **argv)
{
    prompt_loop();
    return (0);
}
