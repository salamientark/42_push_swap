/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 13:28:42 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/02 13:42:58 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

unsigned int    biggest_key(t_stack *stack)
{
    unsigned int    biggest_key;
    t_stack_data    *record;

    if (!(stack->head))
        return (0);
    biggest_key = stack->head->key;
    record = stack->head->next;
    while (record != stack->head)
    {
        if (record->key > biggest_key)
            biggest_key = record->key;
        record = record->next;
    }
    return (biggest_key);
}

unsigned int    smallest_key(t_stack *stack)
{
    unsigned int    smallest_key;
    t_stack_data    *record;

    if (!(stack->head))
        return (0);
    smallest_key = stack->head->key;
    record = stack->head->next;
    while (record != stack->head)
    {
        if (record->key < smallest_key)
            smallest_key = record->key;
        record = record->next;
    }
    return (smallest_key);
}