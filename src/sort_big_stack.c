/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:04:34 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/03 12:19:30 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

t_list *find_best_insert(unsigned int key, t_stack *stack)
{
    
}

void    unstack_a(t_stack *stack_a, t_stack *stack_b)
{
    unsigned int    high_limit;
    unsigned int    low_limit;
    unsigned int    final_size;

    low_limit = stack_a->size / 3;
    high_limit = stack_a->size - low_limit;
    final_size = high_limit - low_limit;
    if (final_size < 5)
        final_size = 5;
    while (stack_a->size > final_size)
    {
        if (stack_a->head->key >= high_limit)
        {
            best_pb_move
        }
        else if (stack_a->head->key <= low_limit)
        {

        }
        else
        {
            while (stack_a->head->prev->key )
            if (follow(stack_a->head, stack_a->head->next, size) == -1)
                operation(stack_a, NULL, "sa\n");
           operation(stack_a, NULL, "ra"); 
        }
    }
}
