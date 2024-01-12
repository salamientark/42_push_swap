/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:04:34 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/13 00:31:35 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

typedef struct s_limit
{
    unsigned int    a_low_lim;
    unsigned int    a_high_lim;
    unsigned int    b_low_lim;
    unsigned int    b_high_lim;
}               t_limit;

static char *best_rotate(int rot, int size)
{
    if (rot > size / 2)
        return ("rrb");
    else
        return ("rb");
}

int     is_in_bound(t_limit limit, unsigned int val)
{
    return ((limit.a_low_lim < val && val <= limit.a_high_lim)
        || (limit.b_low_lim < val && val <= limit.b_high_lim));
}

int     is_in_block(unsigned int low_lim, unsigned int high_lim,
                        unsigned int val)
{
    return (low_lim < val && val <= high_lim);
}

int     are_in_same_block(unsigned int val_a, unsigned int val_b,
            t_limit limit)
{
    int result;
    
    // ft_printf("Are_in same_block?\n");
    result = 0;
    result = is_in_block(limit.a_low_lim, limit.a_high_lim, val_a);
    if (result)
        return (result && is_in_block(limit.a_low_lim, limit.a_high_lim, val_b));
    result = is_in_block(limit.b_low_lim, limit.b_high_lim, val_a);
    if (result)
        return (result && is_in_block(limit.b_low_lim, limit.b_high_lim, val_b));
    result = is_in_block(limit.a_high_lim, limit.b_low_lim, val_a);
    return (result && is_in_block(limit.a_high_lim, limit.b_low_lim, val_b));

}

int both_bound_in_block(t_limit limit, t_stack_data *stack)
{
    t_stack_data    *record;
    t_stack_data    *first_bound;
    int             bound_nbr;

	if (!stack ||  stack->next == stack)
		return (0);
    bound_nbr = 0;
    bound_nbr = is_in_bound(limit, stack->prev->key);
    if (bound_nbr)
        first_bound = stack->prev;
    record = stack;
    while (record->next != stack)
    {
        // ft_printf("both_bound_in_block in while\n");
        if (bound_nbr == 1 && is_in_bound(limit, record->key) && !are_in_same_block(first_bound->key, record->key, limit))
            return (1);
        if (bound_nbr == 0 && is_in_bound(limit, record->key))
        {
            bound_nbr++;
            first_bound = record;
        }
        record = record->next;
    }
    return (0);
}

int is_block_aligned(t_limit limit, t_stack_data *stack)
{
    // ft_printf("is_block_aligned?\n");
	if (!stack || stack->next == stack)
        return (1);
	if (!both_bound_in_block(limit, stack))
    {
        // ft_printf("block_aligned : Not both bound in block\n");
		return (1);
    }
    if (is_in_bound(limit, stack->prev->key) && is_in_bound(limit, stack->key)
        && !(are_in_same_block(stack->prev->key, stack->key, limit)))
        return (1);
    return (0);
    // while (record != stack)
    // {
    //     if (both_bound_in_block(low_limit, high_limit, record) && !(are_in_same_block(record->prev->key, record->key, low_limit, high_limit)))
    //         return (0);
    //     record = record->next;
    // }
    // return (1);
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
        // ft_printf("align_block: in first while\n");
        rotate++;
        record = record->next;
    }
    r_rotate = 0;
    record = stack->head;
    while (!(is_block_aligned(limit, record)))
    {
        // ft_printf("align_block: in second while\n");
        r_rotate++;
        record = record->prev;
    }
    if (r_rotate < rotate)
        return (best_rotate(stack->size - r_rotate, stack->size));
    return (best_rotate(rotate, stack->size));
}

int swap_b(t_stack *stack_b, t_limit limit)
{
    int in_same_block;

    if (!(stack_b->head) || stack_b->head == stack_b->head->next)
        return (0);
    in_same_block = are_in_same_block(stack_b->head->key, stack_b->head->next->key, limit);
    if (in_same_block)
    {
        if (stack_b->head->key < stack_b->head->next->key)
            // && (stack_b->head == stack_b->head->next->next
            //     || stack_b->head->key > stack_b->head->next->next->key
            //         || (stack_b->head->next->key < stack_b->head->next->next->key)))
            return (1);
        return (0);
    }
    in_same_block = are_in_same_block(stack_b->head->key, stack_b->head->next->next->key, limit);
    if (in_same_block && stack_b->head->key > stack_b->head->next->next->key)
        return (1);
    return (0);
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

void    print_limit(t_limit lim)
{
    ft_printf("=== LIMIT ===\n");
    ft_printf("[%d,%d], ... , [%d, %d]\n", lim.a_low_lim, lim.a_high_lim, lim.b_low_lim, lim.b_high_lim);
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
    print_limit(limit);
    while (stack_a->size > final_size)
    {
        // if (swap_b(stack_b, low_limit, high_limit))
        // {
        //         op_buffer = add_op_buffer(op_buffer,"sb");
        // }
        if (stack_a->head->key > limit.b_low_lim)
        {
            if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, limit))
                // && stack_a->head->key > stack_b->head->key)
            {
                op_buffer = add_op_buffer(op_buffer, "pb");
                ft_printf("In same_block\n");
            }
            else if (!is_block_aligned(limit, stack_b->head))
            {
                op_buffer = add_op_buffer(op_buffer,align_block(limit, stack_b));
                ft_printf("Not aligned\n");
            }
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
            if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, limit))
            {
                op_buffer = add_op_buffer(op_buffer, "pb");
                ft_printf("In same block\n");
            }
            else if (!is_block_aligned(limit, stack_b->head))
            {
                op_buffer = add_op_buffer(op_buffer,align_block(limit, stack_b));
                ft_printf("Not aligned\n");
            }
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
        ft_printf("--\n%s\n", op_buffer->content);
        operation(stack_a, stack_b, op_buffer->content);
        print_stack_data(stack_a->head, stack_b->head, &get_elem_key);
        index++;
    }
    while (!is_block_aligned(limit, stack_b->head))
    {
        op_buffer = add_op_buffer(op_buffer,align_block(limit, stack_b));
        operation(stack_a, stack_b, op_buffer->content);
    }
    optimize_unstack(op_buffer->next, op_buffer_size(op_buffer));
    return (op_buffer);
}
