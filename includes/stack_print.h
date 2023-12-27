/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:29:21 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/27 22:56:09 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_PRINT_H
# define STACK_PRINT_H

# include "stack.h"
# define SEP "---------------------------------------------------------------"
# define MAX(a,b) a >= b ? a : b

typedef struct s_stack_param
{
    int     max_nbr_len;
    int     line_nbr;
    char    *printf_param;
}           t_stack_param;

void    free_printf_param(void);

int    get_stack_key(t_stack *stack);
int    get_stack_value(t_stack *stack);

void    print_param(t_stack_param param);
void    print_elem(t_stack *elem, int (*get)(t_stack *));
void    print_stack_debug(t_stack *a, t_stack *b, int (*get)(t_stack *));
void    print_stack(t_stack *a, t_stack *b, int (*get)(t_stack *));
void	print_operation(t_operation op);
// void    print_dict(t_stack_dict dict);

#endif