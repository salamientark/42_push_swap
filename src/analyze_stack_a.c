// // /* ************************************************************************** */
// // /*                                                                            */
// // /*                                                        :::      ::::::::   */
// // /*   analyze_stack_a.c                                  :+:      :+:    :+:   */
// // /*                                                    +:+ +:+         +:+     */
// // /*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
// // /*                                                +#+#+#+#+#+   +#+           */
// // /*   Created: 2023/12/27 17:06:51 by dbaladro          #+#    #+#             */
// // /*   Updated: 2023/12/27 21:32:51 by dbaladro         ###   ########.fr       */
// // /*                                                                            */
// // /* ************************************************************************** */

#include "../includes/stack.h"

// // typedef struct s_stack_data_data
// // {
// //     /* data */
// // };


/*  USE ON STACK_A ONLY:
    Check if value are in ASCENDING order.
    Return:
    0        : Is_sorted
    [1,n]    : Sorted but n rotate to start with 1
    -1       : Not sorted
*/
int a_sorted(t_stack_data *stack, unsigned int stack_size)
{
    int     rot;
    unsigned int     index;
    t_stack_data *record;

    if (!stack || stack == stack->next)
        return (0);
    index = 0;
    record = stack;
    rot = 0;
    while (index < stack_size)
    {
        if ((record->key != (record->next)->key - 1)
            && !(record->key == stack_size && record->next->key == 1))
            return (-1);
        if (record->key == 1)
            rot = index;
        index++;
        record = record->next;
    }
    return (rot);
}

int r_sorted(t_stack_data *stack, unsigned int stack_size)
{

    unsigned int    index;
    t_stack_data    *record;

    if (!stack || stack == stack->prev)
        return (0);
    index = 0;
    record = stack;
    while (index < stack_size)
    {
        if ((record->key != record->prev->key - 1)
            && !(record->key == stack_size && record->prev->key == 1))
            return (0);
        index++;
        record = record->prev;
    }
    return (1);
}

/*  Check if the two value perfectly follow
    1 : TRUE
    0 : FALSE
*/
int follow(t_stack_data *elem_a, t_stack_data *elem_b, unsigned int total_stack_size)
{
    if (elem_a->key == elem_b->key - 1
        || (elem_a->key == total_stack_size && elem_b->key == 1))
        return (1);
    if ((elem_a->key == elem_b->key + 1
        || (elem_a->key == 1 && elem_b->key == total_stack_size)))
        return (-1);
    return (0);
}



// // /*  USE ON STACK_ ONLY:
// //     Check if value are in DECREASING order.
// //     So the 'pa' operation would push to stack_a in the sorted order
// //     Return:
// //     0        : Is_sorted
// //     [1,n]    : Sorted but n rotate to start with 1
// //     -1       : Not sorted
// // */
// // // int sorted_stack_a(t_stack_data *stack)
// // // {
// // //     int     rot;
// // //     int     index;
// // //     int     stack_size;
// // //     t_stack_data *record;

// // //     if (!stack || stack == stack->next)
// // //         return (0);
// // //     index = 0;
// // //     size_stack = stack_size(stack);
// // //     record = stack;
// // //     while (index < size_stack)
// // //     {
// // //         if ((record->value != (record->prev)->value - 1)
// // //             && !(record->prev->value == 1 && record->value == size_stack))
// // //             return (-1);
// // //         if (record->value == 1)
// // //             rot = size_stack - index;
// // //         index++;
// // //         record = record->next;
// // //     }
// // //     return (rot);
// // // }

// // char    *action(t_stack_data *a, t_stack_data *b, int stack_len)
// // {
// //     char    *stack_a_move;
// //     char    *stack_b_move;
// //     char    *nice_move;

// //     stack_a_move =  ("pb");
// //     if (sorted_stack_a(a) > 0)
// //         stack_a_move =  ("rra");
// //     if (a->next->value == next_value('a', a->value, stack_len)
// //         || follow('a', a, stack_len) > (stack_len % 20))
// //         stack_a_move =  ("rra\n");
// //     if (a->next->value == a->value - 1)
// //         stack_a_move =  ("sa");
// //     if (sorted_stack_a(a) == 0 && !b)
// //     stack_b_move =  ("pb");
// //     if (!b)
// //         return (stack_a_move);
// //     if (sorted_stack_b(b) > 0)
// //         stack_b_move =  ("rb");
// //     if (b->next->value == next_value('b', b->value, stack_len)
// //         || follow('b', a, stack_len) > (stack_len % 20))
// //         stack_b_move =  ("rb\n");
// //     if (b->next->value == b->value + 1)
// //         stack_b_move =  ("sb");
// // }
