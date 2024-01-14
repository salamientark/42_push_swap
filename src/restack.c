/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:18:17 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/14 12:20:12 by dbaladro         ###   ########.fr       */
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

t_list  *distance_from_head_to_op_buffer();

/*
    Distance from stack_b->head to ideal spot in stack_b in rotate counting
    NOT_PRROTECTED
*/
int distance_from_good_spot(t_stack *dest, t_stack *stack_head)
{
    t_stack_data    *record;
    unsigned int    distance;
    unsigned int    val;
    unsigned int    ref;

    record = dest->head;
    val = stack_head->head->key;
    if (val < dest->min || dest->max < val)
    {
        ref = dest->min;
        while (record->key != ref)
        {
            distance++;
            record = record->next;
        }
    }
    else
    {
        while (!(dest->head->prev->key < val && val < dest->head->key))
        {
            distance++;
            record = record->next;
        }
    }
    return (distance);
}

t_list  *distance_from_good_spot_to_op_buffer();



t_list  *best_insert(t_stack *dest, t_stack *src)
{
    
}

// t_list  *restack(t_stack *stack_a, t_stack *stack_b)
// {
    // 
// }

// int get_next_size(t_stack stack_a, t_stack *stack_b)
// {
    
// }