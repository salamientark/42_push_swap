/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:30:50 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/25 16:05:02 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/stack.h"

static void	free_list(char ***p_list)
{
	char	**list;
	int		index;

	list = *p_list;
	index = 0;
	while (list[index])
	{
		free(list[index]);
		list[index] = NULL;
		index++;
	}
	free(*p_list);
	*p_list = NULL;
}

static int	arg_is_valid(t_stack *stack, int val, char *s_val)
{
	t_stack	*stack_cp;
	char	*val_to_str;
	int		is_valid;

	if (!ft_isnumber(s_val))
		return (0);
	val_to_str = ft_itoa(val);
	if (!val_to_str)
		return (0);
	is_valid = ft_strcmp(s_val, val_to_str);
	free(val_to_str);
	if (is_valid != 0)
		return (0);
	if (!stack)
		return (1);
	if (stack->next == stack && stack->value != val)
		return (1);
	stack_cp = stack->next;
	while (stack_cp != stack)
	{
		if (stack_cp->value == val)
			return (0);
		stack_cp = stack_cp->next;
	}
	return (stack_cp->value != val);
}

static t_stack	*make_stack(char **arg, int size)
{
	t_stack	*stack;
	int		tmp_value;

	if (size == 0)
		return (NULL);
	stack = NULL;
	while (size-- > 0)
	{
		tmp_value = ft_atoi(arg[size]);
		if (!arg_is_valid(stack, tmp_value, arg[size]))
		{
			ft_putendl_fd("Error", 2);
			if (stack)
				free_stack(&stack);
			return (NULL);
		}
		stack = add_stack(tmp_value, stack);
	}
	return (stack);
}

static t_stack	*make_one_arg_stack(char *arg)
{
	char	**arg_list;
	int		size;
	t_stack	*stack;

	arg_list = ft_split(arg, ' ');
	if (!arg)
		return (NULL);
	size = 0;
	while (arg_list[size])
		size++;
	stack = make_stack(arg_list, size);
	free_list(&arg_list);
	return (stack);
}

t_stack	*parse_arg(int ac, char **av)
{
	if (ac <= 1)
		return (NULL);
	if (ac == 2)
		return (make_one_arg_stack(av[1]));
	return (make_stack(&(av[1]), ac - 1));
}
