/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:18:17 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/12 23:28:30 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/* 
    Distance in rotate count OR -1 if not found
*/
int get_distance_from_head(unsigned int value, t_stack *stack)
{
    int             distance;
    t_stack_data    *record;

    if (stack->head->key == value)
        return (0);
    distance = 1;
    record = stack->head->next;
    while (record != stack->head)
    {
        if (record->key == value)
            return (distance);
        distance++;
        record = record->next;
    }
    return (-1);
}



// int get_next_size(t_stack stack_a, t_stack *stack_b)
// {
    
// }