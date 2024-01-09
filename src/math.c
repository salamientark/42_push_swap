/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:55:18 by dbaladro          #+#    #+#             */
/*   Updated: 2024/01/09 14:43:08 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/stack.h"

int ft_min(int  a, int b)
{
    if (a <= b)
        return (a);
    return (b);
}

int ft_max(int a, int b)
{
    if (a >= b)
        return (a);
    return (b);
}

unsigned int    ft_abs(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}