/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_stack.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 20:18:42 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/27 22:43:42 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

/*
    Point of this is to make stack sort easier by having only
    easy to use value.
    [ 458, 98526, 2, 1156, 42, 666]
     ===> Become
    [ 3, 6, 1, 5, 2, 4]
*/

void    sort_stack_key(t_stack **stack)
{
    t_stack *limit;
    t_stack *index;
    int     tmp;

    limit = (*stack)->prev;
    while (limit != *stack)
    {
        index = *stack;
        while (index != limit)
        {
            if (index->value > limit->value)
            {
                if (index->key > limit->key)
                {
                    tmp = limit->key;
                    limit->key = index->key;
                    index->key = tmp;
                }
            }
            index = index->next;
        }
        limit = limit->prev;
    }
}
    
// t_stack_dict    stack_to_dict(t_stack *stack, int size)
// {
//     t_stack_dict    dict;
//     t_stack         *stack_cp;

//     dict.size = 0;
//     dict.stack_dict = (t_dict *)malloc(sizeof(struct s_stack_dict) * size);
//     if (!dict.stack_dict)
//         return (dict);
//     dict.size = size;
//     stack_cp = stack->next;
//     dict.stack_dict[--size].value = stack->value;
//     dict.stack_dict[size].key = size + 1;
//     while (stack_cp != stack)
//     {
//         dict.stack_dict[--size].value = stack_cp->value;
//         dict.stack_dict[size].key = size + 1;
//         stack_cp = stack_cp->next;
//     }
//     return (dict);
// }

// t_stack_dict  make_dict(int ac, char *av)
// {
//     t_stack_dict  dict.;

//     dict.

//     if ()
// }