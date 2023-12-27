// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   analyze_stack_a.c                                  :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/12/27 17:06:51 by dbaladro          #+#    #+#             */
// /*   Updated: 2023/12/27 21:32:51 by dbaladro         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../includes/stack.h"

// typedef struct s_stack_data
// {
//     /* data */
// };


// /*  USE ON STACK_A ONLY:
//     Check if value are in ASCENDING order.
//     Return:
//     0        : Is_sorted
//     [1,n]    : Sorted but n rotate to start with 1
//     -1       : Not sorted
// */
// int sorted_stack_a(t_stack *stack)
// {
//     int     rot;
//     int     index;
//     int     size_stack;
//     t_stack *record;

//     if (!stack || stack == stack->next)
//         return (0);
//     index = 0;
//     size_stack = stack_size(stack);
//     record = stack;
//     while (index < size_stack)
//     {
//         if ((record->value != (record->prev)->value + 1)
//             && !(record->prev->value == size_stack && record->value == 1))
//             return (-1);
//         if (record->value == 1)
//             rot = size_stack - index;
//         index++;
//         record = record->next;
//     }
//     return (rot);
// }



// /*  USE ON STACK_ ONLY:
//     Check if value are in DECREASING order.
//     So the 'pa' operation would push to stack_a in the sorted order
//     Return:
//     0        : Is_sorted
//     [1,n]    : Sorted but n rotate to start with 1
//     -1       : Not sorted
// */
// // int sorted_stack_a(t_stack *stack)
// // {
// //     int     rot;
// //     int     index;
// //     int     size_stack;
// //     t_stack *record;

// //     if (!stack || stack == stack->next)
// //         return (0);
// //     index = 0;
// //     size_stack = stack_size(stack);
// //     record = stack;
// //     while (index < size_stack)
// //     {
// //         if ((record->value != (record->prev)->value - 1)
// //             && !(record->prev->value == 1 && record->value == size_stack))
// //             return (-1);
// //         if (record->value == 1)
// //             rot = size_stack - index;
// //         index++;
// //         record = record->next;
// //     }
// //     return (rot);
// // }

// char    *action(t_stack *a, t_stack *b, int stack_len)
// {
//     char    *stack_a_move;
//     char    *stack_b_move;
//     char    *nice_move;

//     stack_a_move =  ("pb");
//     if (sorted_stack_a(a) > 0)
//         stack_a_move =  ("rra");
//     if (a->next->value == next_value('a', a->value, stack_len)
//         || follow('a', a, stack_len) > (stack_len % 20))
//         stack_a_move =  ("rra\n");
//     if (a->next->value == a->value - 1)
//         stack_a_move =  ("sa");
//     if (sorted_stack_a(a) == 0 && !b)
//     stack_b_move =  ("pb");
//     if (!b)
//         return (stack_a_move);
//     if (sorted_stack_b(b) > 0)
//         stack_b_move =  ("rb");
//     if (b->next->value == next_value('b', b->value, stack_len)
//         || follow('b', a, stack_len) > (stack_len % 20))
//         stack_b_move =  ("rb\n");
//     if (b->next->value == b->value + 1)
//         stack_b_move =  ("sb");
// }
