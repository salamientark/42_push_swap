/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big_stack.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 10:04:34 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/05 18:57:28 by dbaladro         ###   ########.fr       */
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
    
    record = stack;
    rotate = 0;
    while (!(is_block_aligned(low_limit, high_limit, record)))
    {
        rotate++;
        record = record->next;
    }
    ft_printf("after_while\n");
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
        if (stack_b->head->key < stack_b->head->next->key
            && (stack_b->head == stack_b->head->next->next
                || stack_b->head->key > stack_b->head->next->next->key
                    || (stack_b->head->next->key < stack_b->head->next->next->key)))
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

void    unstack_a(t_stack *stack_a, t_stack *stack_b)
{
    unsigned int    high_limit;
    unsigned int    low_limit;
    unsigned int    final_size;

    int index = 0;

    low_limit = stack_a->size / 3;
    high_limit = stack_a->size - low_limit;
    final_size = high_limit - low_limit;
    // if (final_size < 5)
    //     final_size = 5;
    ft_printf("LIMITS : = %d - %d\n", low_limit, high_limit);
    while (stack_a->size > final_size)
    {
        ft_printf("\n");
        print_stack_data(stack_a->head, stack_b->head, &get_elem_key);
        if (swap_b(stack_b, low_limit, high_limit))
                operation(NULL, stack_b, "sb");
        if (stack_a->head->key > high_limit)
        {
            ft_printf("stack > high_limit\n");
            if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, low_limit, high_limit)
                && stack_a->head->key > stack_b->head->key)
                operation(stack_a, stack_b, "pb");
            else if (!is_block_aligned(low_limit, high_limit, stack_b->head))
                operation(NULL, stack_b, align_block(low_limit, high_limit, stack_a->head, stack_a->size));
            else if (stack_a->head->key > stack_a->head->next->key &&
                stack_a->head->key < stack_a->head->next->next->key)
                operation(stack_a, NULL, "sa");
            else
                operation(stack_a, stack_b, "pb");
        }
        else if (stack_a->head->key <= low_limit)
        {
            ft_printf("stack < low_limit\n");
            if ((are_in_same_block(stack_a->head->key, stack_a->head->next->key, low_limit, high_limit)
                    && stack_a->head->key > stack_a->head->next->key))
                // || (stack_b->head && are_in_same_block(stack_a->head->next->key, stack_b->head->key, low_limit, high_limit)
                //         && stack_a->head->next->key > stack_b->head->key))
                operation(stack_a, NULL, "sa");
            else if (stack_b->head && are_in_same_block(stack_a->head->key, stack_b->head->key, low_limit, high_limit))
                // && stack_a->head->key > stack_b->head->key)
                operation(stack_a, stack_b, "pb");
            else if (!is_block_aligned(low_limit, high_limit, stack_b->head))
                operation(NULL, stack_b, align_block(low_limit, high_limit, stack_a->head, stack_a->size));
            // if (are_in_same_block(low_limit, high_limit, stack_a->head->key, stack_a->head->next->key)
            //     && )
            else
                operation(stack_a, stack_b, "pb");
        }
        else
        {
            ft_printf("stack in_between\n");
            if (are_in_same_block(stack_a->head->key, stack_a->head->next->key, low_limit, high_limit)
                && stack_a->head->key > stack_a->head->next->key)
                operation(stack_a, NULL, "sa");
            // while (stack_a->head->prev->key )
            // if (follow(stack_a->head, stack_a->head->next, size) == -1)
            //     operation(stack_a, NULL, "sa\n");
            else
                operation(stack_a, NULL, "ra"); 
        }
        index++;
    }
    ft_printf("=\n=== NB Coup : %d\n=\n", index);
}
