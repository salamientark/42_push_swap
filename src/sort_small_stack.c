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
#include "../includes/stack_print.h"

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

t_list  *optimize_rotate(t_list *op_buffer, unsigned int *index,
    unsigned int buffer_size)
{
    unsigned int    r_count;
    t_list          *record;

    r_count = 0;
    record = op_buffer;
    ft_printf("In optimize_rotate\n");
    while (*index + r_count < buffer_size && ((char *)(record->content))[0] == 'r'
        && ((char *)(record->content))[1] != 'r')
    {
        record = record->next;
        r_count++;
    }
    ft_printf("== Optimize_rotate: r_count == %d\n");
    if (r_count > buffer_size / 2)
    {
        record = lst_replace(op_buffer, make_op_buffer(r_count, "ra"),
            r_count);
        *index = *index + r_count;
    }
    return (record);
}

t_list  *optimize_r_rotate(t_list *op_buffer, unsigned int *index,
    unsigned int buffer_size)
{
    unsigned int    r_count;
    t_list          *record;

    r_count = 0;
    record = op_buffer;

    ft_printf("In optimize_r_rotate\n");
    while (*index + r_count < buffer_size && ((char *)(record->content))[0] == 'r'
        && ((char *)(record->content))[1] == 'r')
    {
        record = record->next;
        r_count++;
    }
    if (r_count > buffer_size / 2)
    {
        record = lst_replace(op_buffer, make_op_buffer(r_count, "rra"),
            r_count);
        *index = *index + r_count;
    }
    return (record);
}

t_list  *optimize_operation(t_list *op_buffer, unsigned int stack_size)
{
    unsigned int    index;
    t_list          *record;

    if (!op_buffer)
        return (op_buffer);
    index = 0;
    record = op_buffer->next;
    while (index < stack_size)
    {
        if (((char *)(record->content))[0] == 'r')
        {
            if (((char *)(record->content))[1] == 'r')
                record = optimize_r_rotate(record, &index, stack_size);
            else
                record = optimize_rotate(record, &index, stack_size);
        }
        record = record->next;
        ft_printf("index = %d\n");
        index++;
    }
    return (op_buffer);
}

t_list  *sort_small_stack(t_stack *stack_a, unsigned int size)
{
    int     sorted;
    t_list  *op_buffer;

    sorted = is_sorted(stack_a);
    op_buffer = NULL;
    while (!(sorted == 1 && stack_a->size == size && stack_a->head->key == 1))
    {
            if (a_sorted(stack_a->head, stack_a->size) > 0)
                op_buffer = add_op_buffer(op_buffer,
                    best_rotate(a_sorted(stack_a->head, size), size));
            else if (follow(stack_a->head, stack_a->head->next, size) == -1)
                op_buffer = add_op_buffer(op_buffer, "sa");
            else if (follow(stack_a->head, stack_a->head->next, size) == 1
                || follow(stack_a->head->prev, stack_a->head, size) == 1)
                op_buffer = add_op_buffer(op_buffer, "ra");
            else if (follow(stack_a->head->prev, stack_a->head, size) == -1)
                op_buffer = add_op_buffer(op_buffer, "raa");
            else
                op_buffer = add_op_buffer(op_buffer, "sa");
            operation(stack_a, NULL, op_buffer->content);
        sorted = is_sorted(stack_a);
    }
    ft_printf("sort_small_stack: before optimize \n");
    print_op_buffer(op_buffer);
    op_buffer = optimize_operation(op_buffer, size);
    ft_printf("sort_small_stack: after optimize \n");
    print_op_buffer(op_buffer);
    ft_printf("sort_small_stack: <-- \n");
    return (op_buffer);
}
