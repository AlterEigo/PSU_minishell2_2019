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
#include <sys/wait.h>

#include "core.h"
#include "common_types.h"
#include "env_map.h"
#include "list.h"
#include "string.h"
#include "iterator.h"
#include "hash_table.h"
#include "nfa_node.h"
#include "match.h"
#include "builtin_pattern.h"

void prompt_loop()
{
    string_t *prompt = 0;
    string_t *path = get_envvar("PATH");
    string_t *cwd = 0;

    while (1) {
        cwd = get_cwd();
        str_print(cwd);
        str_free(&cwd);
        print_cchar(" > ");
        prompt = prompt_line(prompt);
        if (prompt == 0) {
            print_cchar("exit\n");
            break;
        }
        if (eval_prompt(prompt) == 200)
            break;
        str_free(&prompt);
    }
    str_free(&prompt);
    str_free(&path);
}

int main_2(int argc, char **argv, char **envp)
{
    pid_t pid, wpid;
    int ret;
    char *lscmd[] = { "/usr/bin/ls", "-l", (char*)0 };
    string_t *env_path = 0;
    list_t *dirs = 0;

    env_manager(SETENV, envp);
    env_path = get_envvar("PATH");
    dirs = str_split(env_path, ':');
    str_free(&env_path);
    pid = fork();
    if (pid == -1) {
	print_cerr("fork","Unable to correctly fork the process");
	exit(EXIT_FAILURE);
    } else if (pid == 0) {
	print_cchar("I am the child process!\n");
	print_cchar("Executing ls command:\n");
	execve("/usr/bin/ls", lscmd, envp);
    } else {
	print_cchar("I am the parent!\n");
	do {
	    wpid = waitpid(pid, &ret, WUNTRACED | WCONTINUED);
	    if (wpid == -1) {
		print_cerr("waitpid", 0);
		exit(EXIT_FAILURE);
	    }
	    if (WIFEXITED(ret)) {
		
	    } else if (WIFSIGNALED(ret)) {
		print_cchar("Child process signaled.");
	    } else if (WIFSTOPPED(ret)) {
		print_cchar("Child process stopped.");
	    } else if (WIFCONTINUED(ret)) {
		print_cchar("Child process continued.");
	    } else {
		print_cerr("waitpid","Unexpected status received");
	    }
	} while (!WIFEXITED(ret) && !WIFSIGNALED(ret));
    }
    list_free(&dirs);
    env_manager(FREE, 0);
    return (0);
}

int main(int argc, char **argv, char **env)
{
    env_manager(SETENV, env);
    prompt_loop();
    env_manager(FREE, 0);
    return (0);
}
