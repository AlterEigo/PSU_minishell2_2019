/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include <stdlib.h>
#include <unistd.h>
#include <curses.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

static void finish(int sig);

void assign_color_pairs(void)
{
    if (has_colors()) {
        start_color();
        init_pair(1, COLOR_WHITE, COLOR_WHITE);
        init_pair(2, COLOR_GREEN, COLOR_GREEN);
        init_pair(3, COLOR_YELLOW, COLOR_YELLOW);
    }
}

void init_ncurse_stdscr(void)
{
    initscr();
    noecho();
    cbreak();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
}

int main(int argc, char *argv[])
{
    init_ncurse_stdscr();
    assign_color_pairs();
    finish(0);
    return (0);
}

static void finish(int sig)
{
    endwin();
    exit(sig);
}
