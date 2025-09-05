/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yihssan  <yihssan @student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:42:35 by yihssan           #+#    #+#             */
/*   Updated: 2019/12/07 04:43:27 by yihssan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libftprintf.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t		i;
	char		*content;

	i = 0;
	while (src[i] != '\0' && i < n)
		i++;
	if ((content = (char*)malloc(sizeof(char) * (i + 1))) == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && i < n)
	{
		content[i] = src[i];
		i++;
	}
	content[i] = '\0';
	return (content);
}
