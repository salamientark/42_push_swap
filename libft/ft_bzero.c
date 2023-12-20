/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:40:20 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/09 20:46:04 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*s_cp;
	size_t			index;

	index = 0;
	s_cp = (unsigned char *)s;
	while (index < n)
		s_cp[index++] = '\0';
}
