/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unstack.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:04:34 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/08 15:23:53 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

static char *best_rotate(int rot, int size)
{
    if (rot > size / 2)
        return ("rrb");
    else
        return ("rb");
}

int     is_in_block(unsigned int low_lim, unsigned int high_lim,
                        unsigned int val)
{
    return ((int)low_lim < (int)val && (int)val <= (int)high_lim);
}

int     are_in_same_block(unsigned int val_a, unsigned int val_b,
            unsigned int low_lim, unsigned int high_lim)
{
    int result;
    unsigned int diff;

    // diff = (high_lim - low_lim + 3) % 3;
    diff = high_lim - low_lim;
    
    result = 0;
    result = is_in_block(low_lim - diff, low_lim, val_a);
    if (result)
        return (result && is_in_block(low_lim - diff, low_lim, val_b));
    result = is_in_block(low_lim, high_lim, val_a);
    if (result)
        return (result && is_in_block(low_lim, high_lim, val_b));
    result = is_in_block(high_lim, high_lim + diff, val_a);
    return (result && is_in_block(high_lim, high_lim + diff, val_b));

}

int is_block_aligned(unsigned int low_limit, unsigned int high_limit, t_stack_data *stack)
{
    t_stack_data    *record;

    if (!stack || stack->next == stack)
        return (1);
    if (!(are_in_same_block(stack->prev->key, stack->key, low_limit, high_limit)))
        return (1);
    record = stack->next;
    while (record != stack)
    {
        if (!(are_in_same_block(record->prev->key, record->key, low_limit, high_limit)))
            return (0);
        record = record->next;
    }
    return (1);
}

char    *align_block(unsigned int low_limit, unsigned int high_limit, t_stack_data *stack, unsigned int stack_size)
{
    t_stack_data    *record;
    unsigned int    rotate;
    unsigned int    r_rotate; 
   
    record = stack;
    rotate = 0;
    while (!(is_block_aligned(low_limit, high_limit, record)))
    {
        rotate++;
        record = record->next;
    }
    r_rotate = 0;
    record = stack;
    while (!(is_block_aligned(low_limit, high_limit, record)))
    {
        r_rotate++;
        record = record->prev;
    }
    if (r_rotate < rotate)
        return (best_rotate(stack_size - r_rotate, stack_size));
    return (best_rotate(rotate, stack_size));
}

int swap_b(t_stack *stack_b, unsigned int low_limit, unsigned int high_limit)
{
    int in_same_block;

    if (!(stack_b->head) || stack_b->head == stack_b->head->next)
        return (0);
    in_same_block = are_in_same_block(stack_b->head->key, stack_b->head->next->key, low_limit, high_limit);
    if (in_same_block)
    {
        if (stack_b->head->key < stack_b->head->next->key)
            // && (stack_b->head == stack_b->head->next->next
            //     || stack_b->head->key > stack_b->head->next->next->key
            //         || (stack_b->head->next->key < stack_b->head->next->next->key)))
            return (1);
        return (0);
    }
    in_same_block = are_in_same_block(stack_b->head->key, stack_b->head->next->next->key, low_limit, high_limit);
    if (in_same_block && stack_b->head->key > stack_b->head->next->next->key)
        return (1);
    return (0);
}

// int     valid_push_swap(t_stack_data *stack_a, t_stack_data *stack_b, unsigned int low_limit, unsigned int high_limit)
// {
//     int same_block;

//     same_block = are_in_same_block(stack_a->key, stack_b->key, low_limit, high_limit);
//     if (same_block == 1)
//     {
//         if (are_in_same_block(stack_a->key, stack_b->next->key, low_limit, high_limit))
//         if (stack_a->key < stack_b->key)
//         {
//             if ()
//         }
//         if (are_in_same_block(stack_a))
//     }
// }

t_list  *unstack_a(t_stack *stack_a, t_stack *stack_b)
{
    unsigned int    high_limit;
    unsigned int    low_limit;
    unsigned int    final_size;
    t_list          *op_buffer;

    int index = 0;
    op_buffer = NULL;
    low_limit = stack_a->size / 3;
    high_limit = stack_a->size - low_limit;
    final_size = high_limit - low_limit;
    while (stack_a->size > final_size)
    {
        print_stack_data(stack_a->head, stack_b->head, &get_elem_key);
        if (swap_b(stack_b, low_limit, high_limit))
        {
                op_buffer = add_op_buffer(op_buffer,"sb");
                ft_putendl_fd(op_buffer->content, 1);
        }
        else if (stack_a->head->key > high_limit)
        {
            if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, low_limit, high_limit)
                && stack_a->head->key > stack_b->head->key)
                op_buffer = add_op_buffer(op_buffer, "pb");
            else if (!is_block_aligned(low_limit, high_limit, stack_b->head))
                op_buffer = add_op_buffer(op_buffer,align_block(low_limit, high_limit, stack_b->head, stack_b->size));
            else if (stack_a->head->key > stack_a->head->next->key &&
                stack_a->head->key < stack_a->head->next->next->key)
                op_buffer = add_op_buffer(op_buffer,"sa");
            else
                op_buffer = add_op_buffer(op_buffer, "pb");
        }
        else if (stack_a->head->key <= low_limit)
        {
            if ((are_in_same_block(stack_a->head->key, stack_a->head->next->key, low_limit, high_limit)
                    && stack_a->head->key > stack_a->head->next->key))
                op_buffer = add_op_buffer(op_buffer,"sa");
            else if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, low_limit, high_limit))
                op_buffer = add_op_buffer(op_buffer, "pb");
            else if (!is_block_aligned(low_limit, high_limit, stack_b->head))
                op_buffer = add_op_buffer(op_buffer,align_block(low_limit, high_limit, stack_a->head, stack_a->size));
            else
                op_buffer = add_op_buffer(op_buffer, "pb");
        }
        else
        {
            if (are_in_same_block(stack_a->head->key, stack_a->head->next->key, low_limit, high_limit)
                && stack_a->head->key > stack_a->head->next->key)
                op_buffer = add_op_buffer(op_buffer,"sa");
            else
                op_buffer = add_op_buffer(op_buffer,"ra"); 
        }
                ft_putendl_fd(op_buffer->content, 1);
        operation(stack_a, stack_b, op_buffer->content);
        index++;
    }
    ft_printf("NB_COUP : %d\n", index);
    op_buffer = optimize_unstack(op_buffer->next, op_buffer_size(op_buffer));
    return (op_buffer);
}
