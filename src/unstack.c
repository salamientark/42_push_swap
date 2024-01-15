/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:04:34 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 19:28:02 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

static char *best_b_rotate(int rot, int size)
{
    if (rot > size / 2)
        return ("rrb");
    else
        return ("rb");
}

int is_block_aligned(t_limit limit, t_stack_data *stack)
{
	if (!stack || stack->next == stack)
        return (1);
	if (!both_bound_in_block(limit, stack))
		return (1);
    if (is_in_bound(limit, stack->prev->key) && is_in_bound(limit, stack->key)
        && !(are_in_same_block(stack->prev->key, stack->key, limit)))
        return (1);
    return (0);
}

char    *align_block(t_limit limit, t_stack *stack)
{
    t_stack_data    *record;
    unsigned int    rotate;
    unsigned int    r_rotate; 
   
    record = stack->head;
    rotate = 0;
    while (!(is_block_aligned(limit, record)))
    {
        rotate++;
        record = record->next;
    }
    r_rotate = 0;
    record = stack->head;
    while (!(is_block_aligned(limit, record)))
    {
        r_rotate++;
        record = record->prev;
    }
    if (r_rotate < rotate)
        return (best_b_rotate(stack->size - r_rotate, stack->size));
    return (best_b_rotate(rotate, stack->size));
}

t_limit make_limit(t_stack  *stack)
{
    t_limit limit;

    limit.a_high_lim = stack->size / 3 + stack->min - 1;
    limit.a_low_lim = stack->min - 1;
    limit.b_low_lim = stack->max - stack->size / 3;
    limit.b_high_lim = stack->max;
    return (limit);
}

t_list  *unstack_a(t_stack *stack_a, t_stack *stack_b)
{
    t_limit         limit;
    unsigned int    final_size;
    t_list          *op_buffer;

    int index = 0;
    op_buffer = NULL;
    limit = make_limit(stack_a);
    final_size = limit.b_low_lim - limit.a_high_lim;
    while (stack_a->size > final_size)
    {
        if (stack_a->head->key > limit.b_low_lim)
        {
            if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, limit))
                op_buffer = add_op_buffer(op_buffer, "pb");
            else if (!is_block_aligned(limit, stack_b->head))
                op_buffer = add_op_buffer(op_buffer,align_block(limit, stack_b));
            else if (stack_a->head->key > stack_a->head->next->key &&
                stack_a->head->key < stack_a->head->next->next->key)
                op_buffer = add_op_buffer(op_buffer,"sa");
            else
                op_buffer = add_op_buffer(op_buffer, "pb");
        }
        else if (stack_a->head->key <= limit.a_high_lim)
        {
            if ((are_in_same_block(stack_a->head->key, stack_a->head->next->key, limit)
                    && stack_a->head->key > stack_a->head->next->key))
                op_buffer = add_op_buffer(op_buffer,"sa");
            else if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, limit))
                op_buffer = add_op_buffer(op_buffer, "pb");
            else if (!is_block_aligned(limit, stack_b->head))
                op_buffer = add_op_buffer(op_buffer,align_block(limit, stack_b));
            else
                op_buffer = add_op_buffer(op_buffer, "pb");
        }
        else
        {
            if (are_in_same_block(stack_a->head->key, stack_a->head->next->key, limit)
                && stack_a->head->key > stack_a->head->next->key)
                op_buffer = add_op_buffer(op_buffer,"sa");
            else
                op_buffer = add_op_buffer(op_buffer,"ra"); 
        }
        operation(stack_a, stack_b, op_buffer->content);
        index++;
    }
    while (!is_block_aligned(limit, stack_b->head))
    {
        op_buffer = add_op_buffer(op_buffer, align_block(limit, stack_b));
        operation(stack_a, stack_b, op_buffer->content);
    }
    op_buffer = op_buffer->next;
    return (op_buffer);
}
