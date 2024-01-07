/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   optimize_unstack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 11:41:07 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/07 16:09:54 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"
#include "../includes/stack_print.h"

t_list  *exract_a_op(t_list *op_buffer, unsigned int op_buffer_size)
{
    t_list          *a_op_buffer;
    t_list          *record;
    unsigned int    index;
    size_t          op_len;

    a_op_buffer = NULL;
    record = op_buffer;
    index = 0;
    while ((index < op_buffer_size) || index == 0)
    {
        op_len = ft_strlen((char *)record->content);
        if (((char *)record->content)[0] == 'p'
            || (((char *)record->content)[op_len - 1] == 'a'))
            a_op_buffer = add_op_buffer(a_op_buffer, record->content);
        record = record->next;
        index++;
    }
    return (a_op_buffer->next);
}

t_list  *exract_b_op(t_list *op_buffer, unsigned int op_buffer_size)
{
    t_list          *b_op_buffer;
    t_list          *record;
    unsigned int    index;
    size_t          op_len;

    b_op_buffer = NULL;
    record = op_buffer;
    index = 0;
    while ((index < op_buffer_size) || index == 0)
    {
        op_len = ft_strlen((char *)record->content);
        if (((char *)record->content)[0] == 'p'
            || (((char *)record->content)[op_len - 1] == 'b'))
            b_op_buffer = add_op_buffer(b_op_buffer, record->content);
        record = record->next;
        index++;
    }
    return (b_op_buffer->next);
}

// t_list  *make_optimize_op_buffer(t_list *a_op_buffer, t_list *b_op_buffer,
//     unsigned int a_buffer_size, unsigned int b_buffer_size)
// {
        
// }

t_list  *optimize_unstack(t_list *op_buffer, unsigned int op_buffer_size)
{
    t_list  *op_buffer_a;
    t_list  *op_buffer_b;
    // t_list  *op_optimized;
    t_list  *record;

    if (!op_buffer)
        return (NULL);
    record = op_buffer;
    // op_optimized = NULL;
    op_buffer_a = exract_a_op(op_buffer, op_buffer_size);
    op_buffer_b = exract_b_op(op_buffer, op_buffer_size);

    print_op_buffer(op_buffer_a);
    ft_printf("===\n");
    print_op_buffer(op_buffer_b);
    ft_printf("===\n");

	print_op_buffer_a_and_b(op_buffer_a, op_buffer_b);

    ft_printf("===\n");
    print_op_buffer(op_buffer);
    return (record);
}