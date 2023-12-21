/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:29:21 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/20 22:26:29 by dbaladro         ###   ########.fr       */
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

void    print_param(t_stack_param param);
void    print_elem(t_stack *elem);
void    print_stack_debug(t_stack *a, t_stack *b);
void    print_stack(t_stack *a, t_stack *b);

#endif