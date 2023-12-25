/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:22:59 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/25 02:06:46 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  -------------------------------------------------
    --          >>> Contain functiond for <<<      --
    --  >>> pretty printing && debug printing <<<  --
    -------------------------------------------------
*/


/*
    ==  ___ _  _ ___ _____     __   ___ ___  _  _ ___ ___ ___   ==
    == |_ _| \| |_ _|_   _|   / /  / __/ _ \| \| | __|_ _/ __|  ==
    ==  | || .` || |  | |    / /  | (_| (_) | .` | _| | | (_ |  ==
    == |___|_|\_|___| |_|   /_/    \___\___/|_|\_|_| |___\___|  ==
    ==                                                          ==
*/

#include "stack_print.h"

// int             line_nbr;
char            *printf_param = NULL;
t_stack_param   max_param;

void    free_print_param(void)
{
    if (max_param.printf_param[2] == '2')
    {
        // free(max_param.printf_param);
        free(printf_param);
        max_param.printf_param = NULL;
        printf_param = NULL;
    }
    ft_printf("free_print_param end\n");
}

// Get len of number in char nbr
//  Mostly for pretty printing
static int              nbr_len(int n)
{
    long    n_cp;
    int     nbr_len;

    nbr_len = 0;
    n_cp = (long) n;
    if (n_cp < 0)
    {
        nbr_len++;
        n_cp = -n_cp;
    }
    while (n_cp != 0)
    {
        n_cp /= 10;
        nbr_len++;
    }
    if (n == 0)
        nbr_len = 1;
    return (nbr_len);
}

// Get t_stack * information -> t_stack_param
//  nbr_len_max && stack_size && printf_param
static t_stack_param    get_stack_param(t_stack *begining)
{
    t_stack_param   param;
    t_stack         *record;

    param.line_nbr = 0;
    param.max_nbr_len = 0;
    if (!begining)
        return (param);
    param.max_nbr_len = nbr_len(begining->value);
    record = begining->next;
    param.line_nbr++;
    while (record != begining)
    {
        param.max_nbr_len = MAX(param.max_nbr_len, nbr_len(record->value));
        record = record->next;
        param.line_nbr++;
    }
    return (param);
}

static char             *make_printf_param_failed_itoa(char *nbr_len)
{
    char    *param;
    int     index;

    param = (char *)malloc(ft_strlen(nbr_len) + 3);
    if (!param)
        return (NULL);
    index = 0;
    param[0] = '%';
    while(nbr_len[index])
    {
        param[index + 1] = nbr_len[index];
        index++;
    }
    param[index + 1] = 's';
    param[ft_strlen(nbr_len) + 2] = '\0';
    max_param.max_nbr_len = 12;
    return (param);
}

static char             *make_printf_param(int nbr_len)
{
    char    *param;
    char    *str_n_len;
    int     index;

    str_n_len = ft_itoa(nbr_len);
    if (!str_n_len)
        return (make_printf_param_failed_itoa("12"));
    param = (char *)malloc(ft_strlen(str_n_len) + 3);
    if (!param)
        return (NULL);
    index = 0;
    param[0] = '%';
    while(str_n_len[index])
    {
        param[index + 1] = str_n_len[index];
        index++;
    }
    param[index + 1] = 's';
    param[ft_strlen(str_n_len) + 2] = '\0';
    free(str_n_len);
    return (param);
}

// Init t_stack_param
static t_stack_param    init_printing_var(t_stack *a, t_stack *b)
{
    t_stack_param   a_param;
    t_stack_param   b_param;

    a_param = get_stack_param(a);
    b_param = get_stack_param(b);

    a_param.line_nbr = MAX(a_param.line_nbr, b_param.line_nbr);
    a_param.max_nbr_len = MAX(a_param.max_nbr_len, b_param.max_nbr_len);
    if (!printf_param)
        printf_param = make_printf_param(a_param.max_nbr_len);
    if (printf_param[2] == '2')
        a_param.max_nbr_len = 12;
    a_param.printf_param = printf_param;
    return (a_param);
}

/*
    ==                                          ==
    ==   ___ ___ ___ _  _ _____ ___ _  _  ___   ==
    ==  | _ \ _ \_ _| \| |_   _|_ _| \| |/ __|  ==
    ==  |  _/   /| || .` | | |  | || .` | (_ |  ==
    ==  |_| |_|_\___|_|\_| |_| |___|_|\_|\___|  ==
    ==                                          ==
*/

// Print s_stack_param informations
void    print_param(t_stack_param param)
{
    ft_printf("stack :\n");
    ft_printf("max_nbr_len : %d\n", param.max_nbr_len);
    ft_printf("line_nbr : %d\n", param.line_nbr);
    ft_printf("printf_param : %s\n", param.printf_param);
}

// Print t_stack * information
//  Debug printing information
void    print_elem(t_stack *elem)
{
    if (!elem)
    {
        ft_printf("print_elem: (NULL)\n");
        return ;
    }
    ft_printf("%p <---| %p : %d |---> %p\n",
        elem->prev, elem, elem->value, elem->next);
}

void	print_operation(t_operation op)
{
	ft_printf("=== PRINT_OPERATION ===\n");
	ft_printf("| ");
	if (!op.arg_a || !(*op.arg_a))
	{
		ft_printf("op.arg_a = NULL | ");
		return ;
	}
	if (!(*op.arg_a))
		ft_printf("*op.arg_a = NULL | ");
	if (!op.arg_b)
		ft_printf("op.arg_b = NULL | ");
	if (!(*op.arg_b))
		ft_printf("*op.arg_b = NULL |");
	ft_printf("\n");
	ft_printf("op.operation = %p\n", op.operation);
}

// Print t_stack * information
//  For every element of the stack
void    print_stack_debug(t_stack *a, t_stack *b)
{
    t_stack         *a_record;
    t_stack         *b_record;
    int             tmp;

    if (!printf_param)
        max_param = init_printing_var(a, b);
    ft_printf("%s\n",SEP);
    // PRINT_COMMAND
    a_record = a;
    b_record = b;
    print_param(max_param);
    // STACK A PART
    if (a)
    {
        print_elem(a_record);
        a_record = a_record->next;
        while (a_record && a_record != a)
        {
            ft_printf("before_print_elem\n");
            print_elem(a_record);
            ft_printf("after_print_elem\n");
            a_record = a_record->next;
        }
        tmp = -1;
            while (tmp++ < 62)
                write(1, "_", 1);
        write(1, "\n", 1);
        ft_printf("%31c\n", 'a');
        ft_printf("\n");
        ft_printf("en_of_while\n");
    }
    if (b)
    {
        print_elem(b_record);
        b_record = b_record->next;
        while (b_record && b_record != b)
        {
            print_elem(b_record);
            b_record = b_record->next;
        }
        tmp = -1;
            while (tmp++ < 62)
                write(1, "_", 1);
        write(1, "\n", 1);
        ft_printf("%31c\n", 'b');
    }
    free(max_param.printf_param);
}

// Pretty stack print
void    print_stack(t_stack *a, t_stack *b)
{
    t_stack         *a_record;
    t_stack         *b_record;
    int             index;
    int             nbr_len_str;
    char            *value_s;

    if (!printf_param)
        max_param = init_printing_var(a, b);
    print_param(max_param);
    ft_printf("%s\n",SEP);
    // PRINT_COMMAND
    a_record = a;
    b_record = b;
    // print_param(max_param);
    if (a_record)
    {
        value_s = ft_itoa(a_record->value);
        if (!value_s)
            ft_printf(max_param.printf_param, "itoa:Error");
        else
        {
            ft_printf(max_param.printf_param, value_s);
            free(value_s);
            value_s = NULL;
        }
        a_record = a_record->next;
    }
    else
        ft_printf(max_param.printf_param, " ");
    if (b_record)
    {
        ft_printf(" ");  
        value_s = ft_itoa(b_record->value);
        if (!value_s)
            ft_printf(max_param.printf_param, "itoa:Error");
        else
        {
            ft_printf(max_param.printf_param, value_s);
            free(value_s);
            value_s = NULL;
        }
        b_record = b_record->next;
    }
    index = 1;
    ft_printf("\n");
    while (index < max_param.line_nbr)
    {
        if (a_record && a_record != a)
        {
            value_s = ft_itoa(a_record->value);
            if (!value_s)
                ft_printf(max_param.printf_param, "itoa:Error");
            else
            {
                ft_printf(max_param.printf_param, value_s);
                free(value_s);
                value_s = NULL;
            }
            a_record = a_record->next;
        }
        else
        {
            ft_printf(max_param.printf_param, " "); 
        }
        if (b_record && b_record != b)
        {
            ft_printf(" ");
            value_s = ft_itoa(b_record->value);
            if (!value_s)
                ft_printf(max_param.printf_param, "itoa:Error");
            else
            {
                ft_printf(max_param.printf_param, value_s);
                free(value_s);
                value_s = NULL;
            }
            b_record = b_record->next;
        }
        max_param.line_nbr--;
        ft_printf("\n");
    }
    // DOTTED LINE
    nbr_len_str = max_param.max_nbr_len;
    index = 0;
    while (index++ < nbr_len_str)
        write(1, "_", 1);
    ft_printf(" ");
    index = 0;
    while (index++ < nbr_len_str)
        write(1, "_", 1);
    ft_printf("\n");
    // a or b LINE
    ft_printf(max_param.printf_param, "a");
    ft_printf(" ");
    ft_printf(max_param.printf_param, "b");
    ft_printf("\n");
}
