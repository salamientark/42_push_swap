/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer_cmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:48:34 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/15 13:26:07 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack_print.h"
#include "../includes/stack.h"

int op_buffer_equal(t_list *op_buffer_a, t_list *op_buffer_b)
{
    int size;
    t_list  *a_record;
    t_list  *b_record;

    size = 0;
    a_record = op_buffer_a;
    b_record = op_buffer_b;
    while ((a_record != op_buffer_a && b_record != op_buffer_b) || size == 0)
    {
        if (ft_strcmp(a_record->content, b_record->content) != 0)
            return (0);
        size++;
        a_record = record->next;
        b_record = record->next;
        if (a_record == op_buffer_a && b_record != op_buffer_b
            || b_record == op_buffer_b && a_record != op_buffer_a)
        {
            return (0);
        }
    }
    return (1);
}

int stack_equal(t_stack stack_a, t_stack stack_b)
{
    unsigned int    index;
    unsigned int    size;
    t_stack_data    *a_record;
    t_stack_data    *b_record;

    if (stack_a.size != stack_b.size)
        return (0);
    index = 0;
    size = stack_a.size;
    a_record = stack_a.head;
    b_record = stack_b.head;
    while (index < size)
    {
        if (a_record->key != b_record->key)
            return (0);
        a_record = a_record->next;
        b_record = b_record->next;
        index++;
    }
    return (1);
}

static t_stack	make_stack(char **arg, int size)
{
	t_stack			stack;
	int				tmp_value;

	stack = init_stack('a');
	if (size == 0)
		return (stack);
	stack.size = size;
	stack.min = 1;
	stack.max = size;
	while (size-- > 0)
	{
		tmp_value = ft_atoi(arg[size]);
		if (!arg_is_valid(stack.head, tmp_value, arg[size]))
		{
			ft_putendl_fd("Error", 2);
			if (stack.head)
				free_stack_data(&stack.head);
			stack.size = 0;
			return (stack);
		}
		stack.head = add_stack_data(tmp_value, stack.head);
	}
	return (stack);
}