/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restack_optimize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:15:06 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 11:10:07 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

void    extract_op_buffer(t_list **op_buffer, t_list **a_op_buffer,
    t_list **b_op_buffer)
{
    t_list  *record;
    size_t  op_len;

    // *a_op_buffer = NULL;
    // *b_op_buffer = NULL;
    if (!(*op_buffer))
        return ;
    op_len = ft_strlen((char *)(*op_buffer)->content);
    if (((char *)(*op_buffer)->content)[op_len - 1] == 'a')
        *a_op_buffer = add_op_buffer(*a_op_buffer, (*op_buffer)->content);
    else
        *b_op_buffer = add_op_buffer(*b_op_buffer, (*op_buffer)->content);
    record = (*op_buffer)->next;
    while (record != (*op_buffer))
    {
        op_len = ft_strlen(record->content);
        if (((char *)record->content)[op_len - 1] == 'a')
            *a_op_buffer = add_op_buffer(*a_op_buffer, record->content);
        else
            *b_op_buffer = add_op_buffer(*b_op_buffer, record->content);
        record = record->next;
    }
    // *a_op_buffer = (*a_op_buffer)->next;
    // *b_op_buffer = (*b_op_buffer)->next;
}

t_list  *optimize_rotate(t_list *op_buffer_a, t_list *op_buffer_b, char *rot)
{
    t_list          *op_buffer;
    unsigned int    a_size;
    unsigned int    b_size;

    a_size = op_buffer_size(op_buffer_a);
    b_size = op_buffer_size(op_buffer_b);
    op_buffer = make_op_buffer(ft_min(a_size, b_size), rot);
    if (a_size > b_size)
        op_buffer = lst_join(op_buffer, make_op_buffer(a_size - b_size,
            op_buffer_a->content));
    else
        op_buffer = lst_join(op_buffer, make_op_buffer(b_size - a_size,
            op_buffer_b->content));
    // free_op_buffer(op_buffer_a);
    // free_op_buffer(op_buffer_b);
    return (op_buffer);
}

// t_list  *optimize_r_rotate(t_list *op_buffer_a, t_list *op_buffer_b)
// {
//     t_list          *op_buffer;
//     unsigned int    a_size;
//     unsigned int    b_size;

//     a_size = op_buffer_size(op_buffer_a);
//     b_size = op_buffer_size(op_buffer_b);
//     op_buffer = make_op_buffer(min(a_size, b_size), "rrr");
//     if (a_size > b_size)
//         op_buffer = lst_join(op_buffer, make_op_buffer(a_size - b_size, "rra"));
//     else
//         op_buffer = lst_join(op_buffer, make_op_buffer(b_size - a_size, "rrb"));
//     // free_op_buffer(op_buffer_a);
//     // free_op_buffer(op_buffer_b);
//     return (op_buffer);
// }

t_list  *make_optimize_restack(t_list **op_buffer_a, t_list **op_buffer_b)
{
    t_list          *op_buffer;

    if ((((char *)(*op_buffer_a)->content)[1] == 'a'
        && ((char *)(*op_buffer_b)->content)[1] == 'r')
        || (((char *)(*op_buffer_a)->content)[1] == 'r'
        && ((char *)(*op_buffer_b)->content)[1] == 'b'))
        return (lst_join((*op_buffer_a), (*op_buffer_b)));
    if (((char *)(*op_buffer_a)->content)[1] == 'a')
        op_buffer = optimize_rotate(*op_buffer_a, *op_buffer_b, "rr");
    else
        op_buffer = optimize_rotate(*op_buffer_a, *op_buffer_b, "rrr");
    free_op_buffer(op_buffer_a, NULL);
    free_op_buffer(op_buffer_b, NULL);
    return (op_buffer);
}

void    restack_optimize(t_list **op_buffer)
{
    t_list  *a_op_buffer;
    t_list  *b_op_buffer;

    if (!(*op_buffer))
        return ;
    a_op_buffer = NULL;
    b_op_buffer = NULL;
    extract_op_buffer(op_buffer, &a_op_buffer, &b_op_buffer);
    free_op_buffer(op_buffer, NULL);
    if (!a_op_buffer)
        *op_buffer = b_op_buffer;
    else if (!b_op_buffer)
        *op_buffer = a_op_buffer;
    else
        *op_buffer = make_optimize_restack(&a_op_buffer, &b_op_buffer);
}