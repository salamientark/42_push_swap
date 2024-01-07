/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_buffer_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:06:15 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/07 16:12:41 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack_print.h"

#ifndef MAX
# define MAX(a,b) (a >= b ? a : b)
#endif

int line_before_next_push(t_list *op_buffer, unsigned int pos,
    unsigned int size)
{
    int     line_nbr;
    t_list  *record;

    record = op_buffer;
    line_nbr = 0;
    while (((char *)(record->content))[0] != 'p' && pos + line_nbr <= size)
    {
        line_nbr++;
        record = record->next;
    }
    return (line_nbr);
}

void    print_op_buffer_a_and_b(t_list  *a, t_list  *b)
{
    int             line_nbr;
    int             line_space;
    int             counter;
    t_list          *a_record;
    t_list          *b_record;
    unsigned int    buffer_a_pos;
    unsigned int    buffer_b_pos;
    unsigned int    a_size;
    unsigned int    b_size;
    // unsigned int    max_size;

    a_record = a;
    b_record = b;
    a_size = op_buffer_size(a);
    b_size = op_buffer_size(b);
    buffer_a_pos = 0;
    buffer_b_pos = 0;
    ft_printf("OP_SIZE A: %d | B: %d \n", a_size, b_size);
    // max_size = MAX(a_size, b_size);
    line_nbr = 0;
    while ((a_record != a && b_record != b) || line_nbr == 0)
    {
        line_space = MAX(line_before_next_push(a_record, buffer_a_pos, a_size),
            line_before_next_push(b_record, buffer_b_pos, b_size));
        counter = 0;
        while (counter < line_space)
        {
            if ((a_record != a || line_nbr == 0)
                && ((char *)(a_record->content))[0] != 'p')
            {
                ft_printf("%3s", a_record->content);
                a_record = a_record->next;
                buffer_a_pos++;
            }
            else
                write(1, "   ", 3);
            if ((b_record != b || line_nbr == 0)
                && ((char *)(b_record->content))[0] != 'p')
            {
                ft_printf(" %3s", b_record->content);
                b_record = b_record->next;
                buffer_b_pos++;
            }
            write(1, "\n", 1);
            counter++;
        }
        line_nbr += counter;
        if ((a_record != a || line_nbr == 0)
            && ((char *)(a_record->content))[0] == 'p')
        {
            ft_printf("%3s", a_record->content);
            a_record = a_record->next;
            buffer_a_pos++;
        }
        else
            write(1, "   ", 3);
        if ((b_record != b || line_nbr == 0)
            && ((char *)(b_record->content))[0] == 'p')
        {
            ft_printf(" %3s", b_record->content);
            b_record = b_record->next;
            buffer_b_pos++;
        }
        write(1, "\n", 1);
        line_nbr++;
    }
    ft_printf("___ ___\n");
    ft_printf("%3c %3c\n", 'a', 'b');
}