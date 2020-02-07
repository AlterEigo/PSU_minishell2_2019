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

void concat_path(string_t **rpath, string_t const *part)
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
    int res = 0;
    string_t *str = str_create(ndir);

    res = change_sdir(str);
    str_free(&str);
    return (res);
}

static string_t *fix_path_prefix(string_t const *dir, bool_t append)
{
    string_t *tmp = 0;

    if (dir == 0)
	return (0);
    if (append && str_cstr(dir)[0] != '/')
	tmp = str_cconcat("/", str_cstr(dir));
    if (!append && str_cstr(dir)[0] == '/')
	tmp = str_substr(dir, 1, str_len(dir));
    tmp = (tmp == 0) ? str_create(str_cstr(dir)) : tmp;
    return (tmp);
}

static int set_current_path(string_t const *path)
{
    int res = 0;
    string_t *current = 0;
    string_t *tmp = 0;

    if (path == 0)
	return (-1);
    current = get_envvar("PWD");
    res = chdir(str_cstr(path));
    if (res != -1) {
	tmp = fix_path_prefix(path, TRUE);
	set_envvar("PWD", str_cstr(tmp));
	set_envvar("OLDPWD", str_cstr(current));
	str_free(&tmp);
    }
    str_free(&current);
    return (res);
}

int change_sdir(string_t const *sdir)
{
    string_t *path = 0;
    int res = 0;
    string_t *dir = 0;

    if (sdir == 0)
        return (84);
    path = get_cwd();
    dir = fix_path_prefix(sdir, FALSE);
    concat_path(&path, dir);
    str_free(&dir);
    if (set_current_path(path) != 0)
        if (set_current_path(sdir) != 0) {
            print_cerr("cd", 0);
            res = 84;
        }
    str_free(&dir);
    str_free(&path);
    return (res);
}
