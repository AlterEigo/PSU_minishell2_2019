/*
** EPITECH PROJECT, 2019
** Title
** File description:
** Description
*/
#include "utility.h"

uint_t expect_uint(uint_t val, uint_t lhs, uint_t rhs)
{
    val = val < lhs ? lhs : val;
    val = val > rhs ? rhs : val;
    return (val);
}
