/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 08:15:31 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/16 10:30:45 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H

# include "../libft/libft.h"

/*
	Double chained rotary structur allow push swap manipulation easily
*/
typedef struct s_stack_data
{
	unsigned int		key;
	int					value;
	struct s_stack_data	*prev;
	struct s_stack_data	*next;
}				t_stack_data;

/*
	Stack_param;
	id : 'a' || 'b'
	size
	min value
	mac value
	pointer to data;
*/
typedef struct s_stack
{
	char			id;
	unsigned int	size;
	unsigned int	min;
	unsigned int	max;
	t_stack_data	*head;
}				t_stack;

/*
	Push_swap_environment
*/
typedef struct s_checker
{
	t_stack				stack_a;
	t_stack				stack_b;
	unsigned int		max_size;
}				t_checker;

// Type containg push_swap opeartion and variable
typedef struct s_operation
{
	t_stack			*arg_a;
	t_stack			*arg_b;
	void			(*operation)(t_stack *, t_stack *);
}				t_operation;

//operation.c
void	swap(t_stack *dest, t_stack *src);
void	rotate(t_stack *dest, t_stack *src);
void	r_rotate(t_stack *dest, t_stack *src);
void	push(t_stack *dest, t_stack *src);

unsigned int	biggest_key(t_stack *stack);
unsigned int	smallest_key(t_stack *stack);
int		operation(t_stack *a, t_stack *b, char *op);

// Checker_utils.c
t_stack	        init_stack(char id);
void	free_stack_data(t_stack_data **stack);
t_stack_data	*add_stack_data(const int val, t_stack_data *stack);
void            end_checker(t_checker *ps_env, char **op, char *msg);

//Checker_init.c
t_checker	init_checker(int ac, char **av);

void    checker(int ac, char **av);
#endif