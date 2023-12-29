/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 22:39:37 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/29 13:51:42 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_H
# define STACK_H

# ifndef NULL
#  define NULL 0
# endif

typedef enum e_bool
{
    FALSE = 0,
    TRUE = !FALSE
}           t_bool;

// Double chained rotary structur allow push swap manipulation easily
typedef struct s_stack_data
{
    int             value;
    struct s_stack_data  *prev;
    struct s_stack_data  *next;
}               t_stack_data;

t_stack_data *init_stack_data();
t_stack_data push();
t_stack_data init_stack_data();
t_stack_data init_stack_data();


#endif