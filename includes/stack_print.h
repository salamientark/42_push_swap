/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:29:21 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/06 15:50:30 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_PRINT_H
# define STACK_PRINT_H

# include "stack.h"
# define SEP "---------------------------------------------------------------"
# define MAX(a,b) a >= b ? a : b

typedef struct s_stack_data_param
{
    int     max_nbr_len;
    int     line_nbr;
    char    *printf_param;
}           t_stack_data_param;

void    free_printf_param(void);

int    get_elem_key(t_stack_data *stack);
int    get_elem_value(t_stack_data *stack);

void    print_param(t_stack_data_param param);
void    print_elem(t_stack_data *elem, int (*get)(t_stack_data *));
void    print_stack_data_debug(t_stack_data *a, t_stack_data *b, int (*get)(t_stack_data *));
void    print_stack_data(t_stack_data *a, t_stack_data *b, int (*get)(t_stack_data *));
void	print_operation(t_operation op);
void    print_stack(t_stack a, t_stack b, int (*get)(t_stack_data *), 
        void (*print)(t_stack_data *, t_stack_data *, int (*get)(t_stack_data *)));

void    print_ps_env(t_push_swap_env *ps_env);
void    print_op_buffer(t_list *op_buffer);
// void    print_dict(t_stack_data_dict dict);
void    print_op_buffer_a_and_b(t_list  *a, t_list  *b);

#endif