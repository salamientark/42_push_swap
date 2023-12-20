/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 23:22:59 by dbaladro          #+#    #+#             */
/*   Updated: 2023/12/20 15:28:24 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "stack.h"
# define SEP "---------------------------------------------------------------"
# define MAX(a,b) a >= b ? a : b

typedef struct s_stack_param
{
    int     max_int_len;
    int     line_nbr;
    char    *printf_param;
}           t_stack_param;

int             line_nbr;
char            *printf_param = NULL;
t_stack_param   max_param;

int     int_len(int n)
{
    long    n_cp;
    int     int_len;

    int_len = 0;
    n_cp = (long) n;
    if (n_cp < 0)
    {
        int_len++;
        n_cp = -n_cp;
    }
    while (n_cp != 0)
    {
        n_cp /= 10;
        int_len++;
    }
    if (n == 0)
        int_len = 1;
    return (int_len);
}

void    print_param(t_stack_param param)
{
    ft_printf("stack :\n");
    ft_printf("max_int_len : %d\n", param.max_int_len);
    ft_printf("line_nbr : %d\n", param.line_nbr);
}

void    print_elem(t_stack *elem)
{
    if (!elem)
        return ;
    ft_printf("%p <---| %p : %d |---> %p\n",
        elem->prev, elem, elem->value, elem->next);
}

t_stack_param     get_stack_param(t_stack *begining)
{
    t_stack_param   param;
    t_stack         *record;

    param.line_nbr = 0;
    if (!begining)
        return (param);
    param.max_int_len = int_len(begining->value);
    record = begining->next;
    param.line_nbr++;
    while (record != begining)
    {
        param.max_int_len = MAX(param.max_int_len, int_len(record->value));
        record = record->next;
        // ft_printf("record : %d\n", param.line_nbr);
        // ft_printf("\n");
        // print_elem(begining);
        // print_elem(record);
        param.line_nbr++;
    }
    return (param);
}

char    *make_printf_param(char *nbr_len)
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

t_stack_param    init_printing_var(t_stack *a, t_stack *b)
{
    t_stack_param   a_param;
    t_stack_param   b_param;

    a_param = get_stack_param(a);
    b_param = get_stack_param(b);

    a_param.line_nbr = MAX(a_param.line_nbr, b_param.line_nbr);
    a_param.max_int_len = MAX(a_param.max_int_len, b_param.max_int_len);
    a_param.printf_param = make_printf_param(ft_itoa(a_param.max_int_len));
    return (a_param);
}

void    print_stack_debug(t_stack *a, t_stack *b)
{
    t_stack         *a_record;
    t_stack         *b_record;
    int             tmp;
    // int             int_len_str;

    max_param = init_printing_var(a, b);
    // printf_param = ft_strjoin(ft_strjoin("%",
    //     ft_itoa(max_param->max_int_len)), "s");
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
    // int_len_str = int_len(max_param.max_int_len);
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
    //     while (tmp++ < int_len_str)
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

void    print_stack(t_stack *a, t_stack *b)
{
    t_stack         *a_record;
    t_stack         *b_record;
    int             tmp;
    int             int_len_str;

    max_param = init_printing_var(a, b);
    ft_printf("%s\n",SEP);
    // PRINT_COMMAND
    a_record = a;
    b_record = b;
    print_param(max_param);
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
    int_len_str = int_len(max_param.max_int_len);
    tmp = 0;
    while (tmp++ < int_len_str)
        write(1, "_", 1);
    ft_printf(" ");
    tmp = 0;
    while (tmp++ < int_len_str)
        write(1, "_", 1);
    ft_printf("\n");
    // a or b LINE
    ft_printf(max_param.printf_param, "a");
    ft_printf(" ");
    ft_printf(max_param.printf_param, "b");
    ft_printf("\n");
}

void    insert(t_stack **dest, t_stack *elem)
{
    if (!(*dest))
    {
        (*dest) = elem;
        elem->next = elem;
        elem->prev = elem;
    }
    if ((*dest) == (*dest)->next)
        (*dest)->next = elem;
    else
        ((*dest)->prev)->next = elem;
    elem->prev = (*dest)->prev;
    elem->next = (*dest);
    (*dest)->prev = elem;
    *dest = elem;
}

// void    remove(t_stack **stack, t_stack **elem)
// {
//     if (*elem != *stack)
//         return ;
// }

void    push(t_stack **dest, t_stack **src)
{
    t_stack *elem;

    if (!(*src))
        return ;
    elem = *src;
    if (*src != (*src)->next)
    {
        ((*src)->prev)->next = (*src)->next;
        ((*src)->next)->prev = (*src)->prev;
        *src = (*src)->next;
    }
    else
        *src = NULL;
    if (!(*dest))
    {
        (*dest) = elem;
        elem->next = elem;
        elem->prev = elem;
    }
    if ((*dest) == (*dest)->next)
        (*dest)->next = elem;
    else
        ((*dest)->prev)->next = elem;
    elem->prev = (*dest)->prev;
    elem->next = (*dest);
    (*dest)->prev = elem;
    *dest = elem;
}


int    main()
{
    t_stack *a = add_stack(1, NULL);
    // t_stack *b = add_stack(4, NULL);
    t_stack *b = add_stack(4, NULL);

    a = add_stack(2, a);
    a = add_stack(3, a);
    print_stack(a, b);

    // a = rotate(a);
    rotate(&a);
    print_stack(a, b);

    print_stack_debug(a, b);
    swap(&a);
    print_stack(a, b);

    // remove(&a);
    // remove(&a);
    // remove(&a);

    // insert(&a, b);
    push(&a, &b);
    push(&a, &b);
    print_stack_debug(a, b);
    print_stack(a, b);

    push(&b, &a);
    push(&b, &a);
    print_stack_debug(a, b);
    print_stack(a, b);

    // print_stack_debug(a, NULL);

    // a = add_stack(2, a);
    // print_stack(a, b);

    // b = delete(b);
    // print_stack(a, b);
    
    // a = delete(a);
    // print_stack(a, b);
    
    // a = delete(a);
    // print_stack(a, b);
    
    // a = delete(a);
    // print_stack(a, b);
    
    return (0);
}