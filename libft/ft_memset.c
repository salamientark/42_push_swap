/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 14:33:40 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/09 20:47:21 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	value;

	s_ptr = (unsigned char *)s;
	value = (unsigned char)c;
	while (n--)
		*s_ptr++ = value;
	return (s);
}
