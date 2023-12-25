/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 01:30:50 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/25 11:49:00 by dbaladro         ###   ########.fr       */
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

static t_stack	*make_stack(char **arg, int size)
{
	t_stack	*stack;

	if (size == 0)
		return (NULL);
	stack = NULL;
	while (size-- > 0)
	{
		if (!ft_isnumber(arg[size]))
		{
			ft_putendl_fd("Error", 2);
			if (stack)
				free_stack(&stack);
			return (NULL);
		}
		stack = add_stack(ft_atoi(arg[size]), stack);
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
