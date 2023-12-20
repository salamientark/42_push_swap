/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbaladro <dbaladro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:50:23 by dbaladro          #+#    #+#             */
/*   Updated: 2023/11/07 09:50:30 by dbaladro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*s_end;

	s_end = s + ft_strlen(s);
	while (*s_end != (char)c)
	{
		if (s_end-- == s)
			return (NULL);
	}
	return ((char *)s_end);
}
