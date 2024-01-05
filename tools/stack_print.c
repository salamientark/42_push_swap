/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:22:59 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/05 08:08:57 by dbaladro         ###   ########.fr       */
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
t_stack_data_param   max_param;

void    free_printf_param(){
    if (printf_param && printf_param[2] != '2')
    {
        free(printf_param);
        max_param.printf_param = NULL;
        printf_param = NULL;
    }
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

// Get t_stack_data * information -> t_stack_data_param
//  nbr_len_max && stack_size && printf_param
static t_stack_data_param    get_stack_data_param(t_stack_data *begining, int (*get)(t_stack_data *))
{
    t_stack_data_param   param;
    t_stack_data         *record;

    param.line_nbr = 0;
    param.max_nbr_len = 0;
    if (!begining)
        return (param);
    param.max_nbr_len = nbr_len(get(begining));
    record = begining->next;
    param.line_nbr++;
    while (record != begining)
    {
        param.max_nbr_len = MAX(param.max_nbr_len, nbr_len(get(record)));
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
        param = "%12s";
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

// Init t_stack_data_param
static t_stack_data_param    init_printing_var(t_stack_data *a, t_stack_data *b, int (*get)(t_stack_data *))
{
    t_stack_data_param   a_param;
    t_stack_data_param   b_param;

    a_param = get_stack_data_param(a, get);
    b_param = get_stack_data_param(b, get);

    a_param.line_nbr = MAX(a_param.line_nbr, b_param.line_nbr);
    a_param.max_nbr_len = MAX(a_param.max_nbr_len, b_param.max_nbr_len);
    if (!printf_param)
        printf_param = make_printf_param(a_param.max_nbr_len);
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

// Print s_stack_data_param informations
void    print_param(t_stack_data_param param)
{
    ft_printf("stack :\n");
    ft_printf("max_nbr_len : %d\n", param.max_nbr_len);
    ft_printf("line_nbr : %d\n", param.line_nbr);
    ft_printf("printf_param : %s\n", param.printf_param);
}

// Print t_stack_data * information
//  Debug printing information
void    print_elem(t_stack_data *elem, int (*get)(t_stack_data *))
{
    if (!elem)
    {
        ft_printf("print_stack_data: (NULL)\n");
        return ;
    }
    ft_printf("%p <---| %p : %d |---> %p\n",
        elem->prev, elem, get(elem), elem->next);
}

void	print_operation(t_operation op)
{
	ft_printf("=== PRINT_OPERATION ===\n");
	// ft_printf("| ");
	if (op.arg_a)
	{
        if (op.arg_a->head)
        {
            ft_printf(" - stack_a -\n");
            print_elem(op.arg_a->head, &get_elem_value);
        }
        else
		    ft_printf("| *(op.arg_a) = NULL");
	}
    else
    {
		ft_printf("| op.arg_a = NULL");
    }
    if (op.arg_b->head)
    {
        if (op.arg_b->head)
        {
            ft_printf(" - stack_b -\n");
            print_elem(op.arg_b->head, &get_elem_value);
        }
        else
            ft_printf("| *(op.arg_b) = NULL |");
    }
    else
    {
        ft_printf("| op.arg_b = NULL |");
    }
	ft_printf("\n");
	ft_printf("op.operation = %p\n", op.operation);
}

int    get_elem_key(t_stack_data *stack)
{
    if (!stack)
        return (0);
    return ((int) stack->key);
}

int    get_elem_value(t_stack_data *stack)
{
    if (!stack)
        return (0);
    return (stack->value);
}

static void print_stack_param(t_stack a, t_stack b)
{
    ft_printf("===  STACK A  ===\n");
    ft_printf("= size :%7d =\n", a.size);
    ft_printf("= min  :%7d =\n", a.min);
    ft_printf("= max  :%7d =\n", a.max);
    ft_printf("=================\n");
    ft_printf("===  STACKb B ===\n");
    ft_printf("= size :%7d =\n", b.size);
    ft_printf("= min  :%7d =\n", b.min);
    ft_printf("= max  :%7d =\n", b.max);
    ft_printf("=================\n");
}

// Print t_stack_data * information
//  For every element of the stack
void    print_stack_data_debug(t_stack_data *a, t_stack_data *b, int (*get)(t_stack_data *))
{
    t_stack_data         *a_record;
    t_stack_data         *b_record;
    int             tmp;

    if (!printf_param)
        max_param = init_printing_var(a, b, get);
    ft_printf("%s\n",SEP);
    // PRINT_COMMAND
    a_record = a;
    b_record = b;
    // STACK A PART
    if (a)
    {
        print_elem(a_record, get);
        a_record = a_record->next;
        while (a_record && a_record != a)
        {
            ft_printf("before_print_elem\n");
            print_elem(a_record, get);
            ft_printf("after_print_elem\n");
            a_record = a_record->next;
        }
        tmp = -1;
            while (tmp++ < 62)
                write(1, "_", 1);
        write(1, "\n", 1);
        ft_printf("%31c\n", 'a');
        ft_printf("\n");
    }
    if (b)
    {
        print_elem(b_record, get);
        b_record = b_record->next;
        while (b_record && b_record != b)
        {
            print_elem(b_record, get);
            b_record = b_record->next;
        }
        tmp = -1;
            while (tmp++ < 62)
                write(1, "_", 1);
        write(1, "\n", 1);
        ft_printf("%31c\n", 'b');
    }
}

// Pretty stack print
void    print_stack_data(t_stack_data *a, t_stack_data *b, int (*get)(t_stack_data *))
{
    t_stack_data         *a_record;
    t_stack_data         *b_record;
    int             index;
    int             nbr_len_str;
    char            *value_s;

    // if (!printf_param)
    max_param = init_printing_var(a, b, get);
    ft_printf("%s\n",SEP);
    // PRINT_COMMAND
    a_record = a;
    b_record = b;
    // print_param(max_param);
    index = max_param.line_nbr;
    if (a_record)
    {
        value_s = ft_itoa(get(a_record));
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
        value_s = ft_itoa(get(b_record));
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
    index--;
    ft_printf("\n");
    while (index > 0)
    {
        if (a_record && a_record != a)
        {
            value_s = ft_itoa(get(a_record));
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
            value_s = ft_itoa(get(b_record));
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
        index--;
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

void    print_stack(t_stack a, t_stack b, int (*get)(t_stack_data *), 
        void (*print)(t_stack_data *, t_stack_data *, int (*get)(t_stack_data *)))
{
    print(a.head, b.head, get);
    print_stack_param(a, b);
}

void    print_ps_env(t_push_swap_env *ps_env)
{
    ft_printf("===== PRINT_PS_ENV =====\n");
    ft_printf("= max_size = % 11d=\n", ps_env->max_size);
    ft_printf("========================\n");
}

// =================
// === OP BUFFER ===
// =================

void    print_op_buffer(t_list *op_buffer)
{
    t_list  *head;

    if (!op_buffer)
        return ;
    head = op_buffer;
    ft_putendl_fd(head->content, 1);
    head = head->next;
    while (head != op_buffer)
    {
        ft_putendl_fd(head->content, 1);
        head = head->next;
    }
}