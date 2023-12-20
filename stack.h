/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:37 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/20 01:04:54 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# include "libft/libft.h"

# ifndef NULL
#  define NULL 0
# endif

// typedef enum e_bool
// {
//     FALSE = 0,
//     TRUE = !FALSE
// }           t_bool;

// Double chained rotary structur allow push swap manipulation easily
typedef struct s_stack
{
    int             value;
    struct s_stack  *prev;
    struct s_stack  *next;
}               t_stack;

void    rot(t_stack *stack);

t_stack *init_stack();
t_stack *add_stack(const int val, t_stack *stack);
t_stack *delete(t_stack *top);

// push_swap operation
t_stack *push();
t_stack *swap(t_stack *stack);
t_stack *rotate(t_stack *stack);

#endif
