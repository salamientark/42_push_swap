/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 20:18:42 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/29 13:50:26 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*
    Point of this is to make stack sort easier by having only
    easy to use value.
    [ 458, 98526, 2, 1156, 42, 666]
     ===> Become
    [ 3, 6, 1, 5, 2, 4]
*/

static char *best_rotate(int rot, int size)
{
    if (rot > size / 2)
        return ("rra");
    else
        return ("ra");
}

void    sort_stack_data_3(t_stack_data **stack)
{
    int sorted;

    if ((*stack)->key == (*stack)->next->key - 1)
        operation(stack, NULL, "sa\n");
    if ((*stack)->key)
    sorted = a_sorted(*stack);
    while (sorted > 0)
    {
        operation(stack, NULL, best_rotate(sorted, stack_size(*stack)));
        sorted = a_sorted(*stack);
    }
}