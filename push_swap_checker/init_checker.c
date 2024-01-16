/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 23:28:35 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 08:34:25 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/checker.h

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

static int	arg_is_valid(t_stack_data *stack, int val, char *s_val)
{
	t_stack_data	*stack_cp;
	char			*val_to_str;
	int				is_valid;

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

static t_stack	parse_arg(int ac, char **av)
{
	char	**av_one_arg;
	int		size;
	t_stack	stack_a;

	if (ac <= 1)
		return (init_stack('a'));
	if (ac == 2)
	{
		av_one_arg = ft_split(av[1], ' ');
		size = 0;
		while (av_one_arg[size])
			size++;
		if (size == 0)
			return (stack_a);
		stack_a = make_stack(av_one_arg, size);
		free_list(&av_one_arg);
		return (stack_a);
	}
	return (make_stack(&(av[1]), ac - 1));
}

t_checker	init_checker(int ac, char **av)
{
	t_checker	ps_env;

	ps_env.stack_b = init_stack('b');
	ps_env.stack_a = parse_arg(ac, av);
	ps_env.max_size = ps_env.stack_a.size;
	return (ps_env);
}
