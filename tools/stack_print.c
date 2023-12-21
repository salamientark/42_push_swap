/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:22:59 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/21 16:33:21 by dbaladro         ###   ########.fr       */
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

int             line_nbr;
char            *printf_param = NULL;
t_stack_param   max_param;

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

//  Make printf_param based on max_nbr_len
static char             *make_printf_param(char *nbr_len)
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
    a_param.printf_param = make_printf_param(ft_itoa(a_param.max_nbr_len));
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
        return ;
    ft_printf("%p <---| %p : %d |---> %p\n",
        elem->prev, elem, elem->value, elem->next);
}

// Print t_stack * information
//  For every element of the stack
void    print_stack_debug(t_stack *a, t_stack *b)
{
    t_stack         *a_record;
    t_stack         *b_record;
    int             tmp;
    // int             nbr_len_str;

    max_param = init_printing_var(a, b);
    // printf_param = ft_strjoin(ft_strjoin("%",
    //     ft_itoa(max_param->max_nbr_len)), "s");
    ft_printf("%s\n",SEP);
    // PRINT_COMMAND
    a_record = a;
    b_record = b;
    print_param(max_param);
    // STACK A PART
    if (a_record)
    {
        print_elem(a_record);
        a_record = a_record->next;
        while (a_record && a_record != a)
        {
            print_elem(a_record);
            a_record = a_record->next;
        }
        tmp = -1;
            while (tmp++ < 62)
                write(1, "_", 1);
        write(1, "\n", 1);
        ft_printf("%31c\n", 'a');
    }
    ft_printf("\n");
    if (b_record)
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
    // // DOTTED LINE
    // nbr_len_str = nbr_len(max_param.max_nbr_len);
    // if (a_record)
    // {
    //     tmp = -1;
    //     while (tmp++ < 62)
    //         write(1, "_", 1);
    //     if (b_record)
    //         ft_printf(" ");
    // }
    // if (b_record)
    // {
    //     tmp = -1;
    //     while (tmp++ < nbr_len_str)
    //         write(1, "_", 1);
    // }
    // ft_printf("\n");
    // // a or b LINE
    // if (a_record)
    // {
    //     ft_printf(printf_param, "a");
    //     if (b_record)
    //         ft_printf(" ");
    // }
    // if (b_record)
    //     ft_printf(printf_param, "b");
    // ft_printf("\n");
}

// Pretty stack print
void    print_stack(t_stack *a, t_stack *b)
{
    t_stack         *a_record;
    t_stack         *b_record;
    int             tmp;
    int             nbr_len_str;

    max_param = init_printing_var(a, b);
    ft_printf("%s\n",SEP);
    // PRINT_COMMAND
    a_record = a;
    b_record = b;
    // print_param(max_param);
    if (a_record)
    {
        ft_printf(max_param.printf_param, ft_itoa(a_record->value));
        if (b_record)
            ft_printf(" ");
        a_record = a_record->next;
    }
    if (b_record)
    {
        ft_printf(max_param.printf_param, ft_itoa(b_record->value));
        b_record = b_record->next;
    }
    max_param.line_nbr--;
    ft_printf("\n");
    while (max_param.line_nbr > 0)
    {
        if (a_record && a_record != a)
        {
            ft_printf(max_param.printf_param, ft_itoa(a_record->value));
            if (b_record)
                ft_printf(" ");
            a_record = a_record->next;
        }
        if (b_record && b_record != b)
        {
            ft_printf(max_param.printf_param, ft_itoa(b_record->value));
            b_record = b_record->next;
        }
        max_param.line_nbr--;
        ft_printf("\n");
    }
    // DOTTED LINE
    nbr_len_str = max_param.max_nbr_len;
    tmp = 0;
    while (tmp++ < nbr_len_str)
        write(1, "_", 1);
    ft_printf(" ");
    tmp = 0;
    while (tmp++ < nbr_len_str)
        write(1, "_", 1);
    ft_printf("\n");
    // a or b LINE
    ft_printf(max_param.printf_param, "a");
    ft_printf(" ");
    ft_printf(max_param.printf_param, "b");
    ft_printf("\n");
}
