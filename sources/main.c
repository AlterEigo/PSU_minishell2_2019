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

#include "string.h"
#include "hash_table.h"
#include "list.h"

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
    raw();
    noecho();
    curs_set(TRUE);
    keypad(stdscr, TRUE);
    //nodelay(stdscr, TRUE);
}

int main(int argc, char *argv[])
{
    chtype ch;
    string_t *buff = str_create("");
    string_t *tmp = 0;

    init_ncurse_stdscr();
    assign_color_pairs();

    printw("$> ");
    while (1) {
        ch = getch();
        if (ch == ('d' & 0x1f))
            break;
        switch (ch) {
        case '\n':
            printw("\nObtained command : %s", str_cstr(buff));
            str_free(&buff);
            buff = str_create("");
            printw("\n$> ");
        break;
        default:
            addch(ch | A_BOLD);
            tmp = str_addch(buff, ch);
            str_free(&buff);
            buff = tmp;
        break; 
        }
        refresh();
    }
    str_free(&buff);
    finish(0);
    return (0);
}

static void finish(int sig)
{
    endwin();
    exit(sig);
}
