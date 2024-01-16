/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:14:03 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 08:26:12 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_stack	init_stack(char id)
{
	t_stack	stack;

	stack.id = id;
	stack.size = 0;
	stack.min = 0;
	stack.max = 0;
	stack.head = NULL;
	return (stack);
}

static void	update_val(t_stack_data *stack)
{
	t_stack_data	*index;

	index = stack->next;
	while (index != stack)
	{
		if (index->value > stack->value)
			index->key++;
		else
			stack->key++;
		index = index->next;
	}
}

t_stack_data	*add_stack_data(const int val, t_stack_data *stack)
{
	t_stack_data	*elem;

	elem = (t_stack *)malloc(sizeof(struct s_stack_data));
	if (!elem)
		return (NULL);
	elem->key = 1;
	elem->value = val;
	if (!stack)
	{
		elem->next = elem;
		elem->prev = elem;
	}
	else
	{
		elem->prev = stack->prev;
		elem->next = stack;
		if (stack->next == stack)
			stack->next = elem;
		(elem->prev)->next = elem;
		stack->prev = elem;
	}
	update_val(elem);
	return (elem);
}

static void	free_stack(t_stack **stack)
{
	t_stack	*tmp;

	if (!(*stack))
		return ;
	if (*stack == (*stack)->next)
	{
		free(*stack);
		*stack = NULL;
		return ;
	}
	tmp = (*stack)->next;
	(*stack)->prev->next = NULL;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}

void    end_checker(t_checker *ps_env, char **op, char *msg)
{
    free_stack(ps_env->stack_a);
    ps_env->stack_a = NULL;
    free_stack(ps_env->stack_b);
    ps_env->stack_b = NULL;
    if (*ps_env)
    {
        free(*ps_env);
        *ps_env = NULL.
    }
    free(*op);
    if (!msg)
        return ;
    if (msg[0] == 'K')
        ft_putendl_fd("KO", 1);
    if (msg[0] == 'O')
        ft_putendl_fd("OK", 1);
    if (msg[0] == 'E')
        ft_putendl_fd("Error", 2);
}
