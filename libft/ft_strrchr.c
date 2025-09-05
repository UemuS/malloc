/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 17:54:05 by yihssan           #+#    #+#             */
/*   Updated: 2019/10/11 02:16:40 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*temp;

	temp = NULL;
	while (*s)
	{
		if (*s == c)
			temp = s;
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	else
		return ((char *)temp);
}
